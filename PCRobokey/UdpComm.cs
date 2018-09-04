using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace Robokey
{
    class RobotInfo : ICloneable, IComparable
    {
        public int systemId;
        public int nTarget;
        public int nMotor;
        public int nForce;
        public byte[] macAddress = new byte[6];
        public void Clear()
        {
            for (int i = 0; i < macAddress.Count(); ++i) {
                macAddress[i] = 0;
            }
        }
        public Object Clone()
        {
            RobotInfo rv = new RobotInfo();
            rv.systemId = systemId;
            rv.nTarget = nTarget;
            rv.nMotor = nMotor;
            rv.nForce = nForce;
            macAddress.CopyTo(rv.macAddress, 0);
            return rv;
        }
        public int CompareTo(object o) {
            RobotInfo s = (RobotInfo)o;
            if (systemId - s.systemId != 0) return systemId - s.systemId;
            if (nTarget - s.nTarget != 0) return nTarget - s.nTarget;
            if (nMotor - s.nMotor != 0) return nMotor - s.nMotor;
            return nForce - s.nForce;
        }
    };

    class UdpComm
    {
        const int localBcPort = 9091;
        const int remotePort = 9090;
        const int localPort = 9090;
        bool bFindRobot = false;
        public StreamWriter log;

        //  board info
        RobotInfo robotInfo = new RobotInfo();
        public RobotInfo RobotInfo
        {
            set { SetRobotInfo(value); }
            get { return (RobotInfo)robotInfo.Clone(); }
        }
        public void SetRobotInfo(RobotInfo info)
        {
            if (info.CompareTo(robotInfo) != 0)
            {
                byte[] prevMacAddress = new byte[6];
                robotInfo.macAddress.CopyTo(prevMacAddress, 0);
                robotInfo = info;
                pose = new Pose(robotInfo.nMotor);
                velocity = new Pose(robotInfo.nMotor);
                force = new short[robotInfo.nForce];
                nInterpolateTotal = robotInfo.nTarget;
                nInterpolateVacancy = nInterpolateTotal;
                if (OnUpdateRobotInfo != null)
                {
                    owner.Invoke(new UpdateRobotInfoHandlerType(OnUpdateRobotInfo), prevMacAddress);
                }
            }
        }


        //  network
        volatile System.Net.Sockets.UdpClient udp = null;
        volatile System.Net.Sockets.UdpClient udpBc = null;
        public System.Net.IPEndPoint sendPoint = null;
        public System.Net.IPEndPoint recvPoint = null;
        bool bConnected = false;
        public bool IsConnected { get { return bConnected; } }

        //  robot state
        public PoseData pose = null;                        //  current angles of motors; ReadPose
        public PoseData velocity = null;                    //  current velocities of motors; ReadVelocity
        public short [] force = null;                       //  force sensor's values
        public int nInterpolateTotal=0;                     //  capacity of interpolation targets.
        public byte interpolateTargetCountOfWrite = 0;      //  count of interpolation at write cursor
        public byte interpolateTargetCountOfRead = 0;       //  count of interpolation at read cursor
        public int interpolateTickMin = 0;                  //  tick of interpolation
        public int interpolateTickMax = 0;                  //  tick of interpolation
        public int nInterpolateRemain = 0;                  //  number of data in target buffer 
        public int nInterpolateVacancy =0;                  //  target buffer vacancy
        public struct Packet {
            byte[] data;
            int length;
            public Packet(byte[] d, int l)
            {
                data = d;
                length = l;
            }
        }
        public class CommandQueue{
            public ushort commandCount;
            const int bufferLen = 50;
            byte[][] buffers = new byte [bufferLen][];
            volatile int write = 0;
            volatile int read = 0;
            volatile int sent = 0;
            public int writeAvail { get { return (read-1 + bufferLen - write) % bufferLen; } }
            public int readAvail { get { return (write + bufferLen - read) % bufferLen; } }
            public int UpdateRead() {
                int rv = (sent - read + bufferLen) % bufferLen;
                read = sent;
                return rv;
            }
            public bool Write(byte[] b)
            {
                if (writeAvail == 0) return false;
                int p = 2;
                commandCount++;
                UdpComm.WriteShort(commandCount, ref p, b);
                buffers[write] = b;
                if (write < bufferLen - 1) write++;
                else write = 0;
                return true;
            }
            public void Clear()
            {
                read = write = sent = 0;
            }
            public void FreeTo(ushort ct) {
                while (sent != write) {
                    int p = 2;
                    ushort cmdCount = (ushort)ReadShort(ref p, buffers[sent]);
                    if (ct >= cmdCount)
                    {   //  erase command
                        if (sent < bufferLen - 1) sent++;
                        else sent = 0;
                    }
                    else {
                        break;
                    }
                }
            }
            public byte[] Peek(int i = 0)
            {
                if (readAvail > i) return buffers[(read + i) % bufferLen];
                else return null;
            }
        } 
        CommandQueue sendQueue = new CommandQueue();
        public UdpComm(Control o)
        {
            owner = o;
        }
        public void SetAddress(String adr)
        {
            if (udp != null)
            {
                udp.Close();
                udp = null;
            }
            System.Net.IPAddress[] adrs = null;
            try
            {
                adrs = System.Net.Dns.GetHostAddresses(adr);
            }
            catch
            {
            }
            if (adrs != null && adrs.Length > 0)
            {
                sendPoint = new System.Net.IPEndPoint(adrs[0], remotePort);
                recvPoint = null;
            }
        }
        static void WriteShort(int s, ref int cur, byte[] buf) {
            buf[cur] = (byte)s;
            buf[cur+1] = (byte)(s >> 8);
            cur += 2;
        }
        static byte ReadByte(ref int cur, byte[] buf)
        {
            byte s = buf[cur];
            cur ++;
            return s;
        }
        static short ReadShort(ref int cur, byte[] buf)
        {
            int s = buf[cur] | (buf[cur + 1] << 8);
            cur += 2;
            return (short)s;
        }
        void ReadShortExt(ref int s, ref int cur, byte[] buf)
        {
            int t = buf[cur] | (buf[cur + 1] << 8);
            short diff = (short)(t - (s & 0xFFFF));
            s += diff;
            cur += 2;
        }
        void WriteHeader(int cmd, ref int cur, byte[] buf)
        {
            WriteShort(0, ref cur, buf);
            WriteShort(0, ref cur, buf);
            WriteShort(cmd, ref cur, buf);
        }
        void ReadHeader(ref ushort len, ref ushort ct, ref ushort cmd, ref int cur, byte[] buf)
        {
            len = (ushort)ReadShort(ref cur, buf);
            ct = (ushort)ReadShort(ref cur, buf);
            cmd = (ushort)ReadShort(ref cur, buf);
        }
        void ReadBoard(ref int cur, byte[] buf){
            RobotInfo info = new RobotInfo();
            info.systemId = ReadShort(ref cur, buf);
            info.nTarget = ReadShort(ref cur, buf);
            info.nMotor = ReadShort(ref cur, buf);
            info.nForce = ReadShort(ref cur, buf);
            for (int i = 0; i < 6; ++i)
            {
                info.macAddress[i] = ReadByte(ref cur, buf);
            }
            SetRobotInfo(info);
            bConnected = true;
        }
        void ReadPose(ref int cur, byte[] buf)
        {
            for (int i = 0; i < pose.values.Length; ++i) {
                ReadShortExt(ref pose.values[i], ref cur, buf);
            }
        }
        void ReadForce(ref int cur, byte[] buf)
        {
            for (int i = 0; i < force.Length; ++i)
            {
                force[i] = ReadShort(ref cur, buf);
            }
        }
        void ReadVelocity(ref int cur, byte[] buf)
        {
            for (int i = 0; i < velocity.values.Length; ++i)
            {
                velocity.values[i] = ReadShort(ref cur, buf);
            }
        }
        void ReadTick(ref int cur, byte[] buf)
        {
            interpolateTargetCountOfRead = (byte)ReadShort(ref cur, buf);
            interpolateTickMin = ReadShort(ref cur, buf);
            interpolateTickMax = ReadShort(ref cur, buf);
            nInterpolateRemain = ReadShort(ref cur, buf);
            nInterpolateVacancy = ReadShort(ref cur, buf);
        }
        void CallUpdateRobotState() {
            if (OnUpdateRobotState != null)
            {
                owner.Invoke(new UpdateRobotStateHandlerType(OnUpdateRobotState));
            }
        }
        void ReadPeerIPAddress(ref int cur, byte[] buf)
        {
            int[] adr = new int[16];
            for (int i = 0; i < 16; ++i) {
                adr[i] = ReadShort(ref cur, buf);
            }
        }

        void SetMessage(int type, string msg)
        {
            if (OnMessageReceive != null)
            {
                try
                {
                    owner.Invoke(new MessageRecieveHandlerType(OnMessageReceive), type, msg);
                }catch (Exception ex){
                    System.Diagnostics.Debug.WriteLine("Exception:" + ex.ToString() + " in SetMessage()");
                }

            }
        }
        void ReadText(ref int cur, byte[] buf)
        {
            int type = ReadShort(ref cur, buf);
            int len = ReadShort(ref cur, buf);
            char[] cs = new char[len];
            for (int i=0; i<len; ++i)
            {
                cs[i] = (char)buf[cur + i];
            }
            string str = new string(cs, 0, len);
            SetMessage(type, str);
        }

        private void OnReceive(IAsyncResult ar)
            {
            UdpComm uc = (UdpComm)(ar.AsyncState);
            byte[] receiveBytes;
            try
            {
                if (uc.udp == null) return;
                receiveBytes = uc.udp.EndReceive(ar, ref uc.recvPoint);
                if (uc.recvPoint.Port != localBcPort)   //  In broad cast case, sent packet can be received. Must skip.
                {
                    int cur = 0;
                    ushort length = 0;
                    ushort count = 0;
                    ushort commandId = 0;
                    while (cur < receiveBytes.Length)
                    {
                        int start = cur;
                        ReadHeader(ref length, ref count, ref commandId, ref cur, receiveBytes);
                        if (log != null)
                        {
                            log.Write("L" + length + " C" + commandId);
                            for (int i = cur; i < receiveBytes.Length; i += 2)
                            {
                                short s = (short)(receiveBytes[i] | (receiveBytes[i + 1] << 8));
                                log.Write(" " + string.Format("{0,0:X4}", s));
                            }
                            log.Write("\r\n");
                        }
                        sendQueue.FreeTo(count);
                        switch ((CommandId)commandId)
                        {
                            case CommandId.CI_BOARD_INFO:
                                ReadBoard(ref cur, receiveBytes);
                                break;
                            case CommandId.CI_DIRECT:
                                ReadPose(ref cur, receiveBytes);
                                cur += pose.values.Length * 2;
                                CallUpdateRobotState();
                                break;
                            case CommandId.CI_INTERPOLATE:
                                ReadPose(ref cur, receiveBytes);
                                ReadTick(ref cur, receiveBytes);
                                CallUpdateRobotState();
                                break;
                            case CommandId.CI_SENSOR:
                                ReadPose(ref cur, receiveBytes);
                                ReadForce(ref cur, receiveBytes);
                                CallUpdateRobotState();
                                break;
                            case CommandId.CIU_GET_IPADDRESS:
                                ReadPeerIPAddress(ref cur, receiveBytes);
                                if (bFindRobot)
                                {
                                    lock (sendQueue)
                                    {
                                        sendQueue.Clear();
                                        sendQueue.commandCount = count;
                                    }
                                    if (OnRobotFound != null)
                                    {
                                        owner.Invoke(new RobotFindHandlerType(OnRobotFound), recvPoint.Address);
                                    }
                                }
                                break;
                            case CommandId.CIU_TEXT:
                                ReadText(ref cur, receiveBytes);
                                break;
                            default:
                                if (commandId >= (int)CommandId.CIU_NCOMMAND)
                                {
                                    string msg = "Invalid command " + commandId + " received";
                                    SetMessage(-1, msg);
                                }
                                break;
                        }
                        if (cur != start + length) {
                            System.Diagnostics.Debug.WriteLine("Recv lengths not match !");
                        }
                        cur = start + length;
                    }
                }
                if (uc.udp != null)
                {
                    uc.udp.BeginReceive(OnReceive, ar.AsyncState);
                }
            }
            catch (Exception)
            {
                return;
            }
        }
        public void Close()
        {
            bConnected = false;
            robotInfo.Clear();
            if (udp != null) udp.Close();
            udp = null;
        }
        public void Open()
        {
            if (udp == null)
            {
                udp = new System.Net.Sockets.UdpClient(localPort);
                udp.BeginReceive(OnReceive, this);
            }
        }
        public void PutCommand(byte[] cmd, int len) {
            if (udp == null || sendPoint == null) return;
            int p = 0;
            WriteShort(len, ref p, cmd);
            for (int i=0; i<100 && !sendQueue.Write(cmd); ++i) {
                int cur = 2;
                ushort ct = (ushort)ReadShort(ref cur, sendQueue.Peek());
                sendQueue.FreeTo(ct);
            }
            SendPackets();
        }
        public void SendPackets()
        {
            if (udp == null || sendPoint == null) return;
            sendQueue.UpdateRead();
            if (sendQueue.readAvail <= 0) return;
            byte[] buf = new byte[1500];
            int pos = 0;
            for (int i = 0; i < sendQueue.readAvail; ++i)
            {
                byte[] cmd = sendQueue.Peek(i);
                int p = 0;
                int len = ReadShort(ref p, cmd);
                if (pos + len > buf.Length)
                {
                    udp.Send(buf, pos, sendPoint);
                    pos = 0;
                }
                i -= sendQueue.UpdateRead();
                if (i < 0)
                {
                    i = 0;
                } else {
                    for (p = 0; p < len; ++p)
                    {
                        buf[pos + p] = cmd[p];
                    }
                    pos += len;
                }
            }
            if (pos > 0)
            {
                udp.Send(buf, pos, sendPoint);
                pos = 0;
            }
        }
        public void SendPoseDirect(PoseData pose)
        {
            if (pose == null) return;
            byte[] packet = new byte[1000];
            int p = 0;
            WriteHeader((int)CommandId.CI_DIRECT, ref p, packet);
            for (int i = 0; i < pose.values.Count(); ++i)
            {
                int v = pose == null ? 0 : pose.values[i];
                WriteShort(v, ref p, packet);
            }
            for (int i = 0; i < pose.values.Count(); ++i)
            {
                WriteShort(0, ref p, packet);   //  Tentative: set velocity to 0 
            }
            PutCommand(packet, p);
            interpolateTargetCountOfWrite = 0;
        }
        public void SendPoseInterpolate(PoseData pose, ushort period)
        {
            if (pose == null) return;
            byte[] packet = new byte[1000];
            int p = 0;
            WriteHeader((int)CommandId.CI_INTERPOLATE, ref p, packet);
            for (int i = 0; i < pose.nMotor; ++i)
            {
                int v = pose == null ? 0 : pose.values[i];
                WriteShort(v, ref p, packet);
            }
            WriteShort(period, ref p, packet);
            WriteShort(interpolateTargetCountOfWrite, ref p, packet);
            PutCommand(packet, p);
            if (period != 0) interpolateTargetCountOfWrite++;
        }
        public void SendPoseForceControl(PoseData pose, ushort period, short [][] jacob)
        {
            if (pose == null) return;
            byte[] packet = new byte[1000];
            int p = 0;
            WriteHeader((int)CommandId.CI_FORCE_CONTROL, ref p, packet);
            for (int i = 0; i < pose.nMotor; ++i)
            {
                int v = pose == null ? 0 : pose.values[i];
                WriteShort(v, ref p, packet);
            }
            WriteShort(period, ref p, packet);
            WriteShort(interpolateTargetCountOfWrite, ref p, packet);
            //  same as interpolate until here. Add jacobian
            for(int f=0; f<robotInfo.nForce; ++f)
            {
                for (int m = 0; m < 3; ++m)
                {
                    WriteShort(jacob[f][m], ref p, packet);
                }
            }
            PutCommand(packet, p);
            if (period != 0) interpolateTargetCountOfWrite++;
        }
        public void SendPdParam(int nMotor, int[] k, int[] b)
        {
            byte[] packet = new byte[1000];
            int p = 0;
            WriteHeader((int)CommandId.CI_PDPARAM, ref p, packet);
            for (int i = 0; i < nMotor; ++i)
            {
                WriteShort(k[i], ref p, packet);
            }
            for (int i = 0; i < nMotor; ++i)
            {
                WriteShort(b[i], ref p, packet);
            }
            PutCommand(packet, p);
        }
        public void SendTorqueLimit(int nMotor, int[] minT, int[] maxT)
        {
            byte[] packet = new byte[1000];
            int p = 0;
            WriteHeader((int)CommandId.CI_TORQUE_LIMIT, ref p, packet);
            for (int i = 0; i < nMotor; ++i)
            {
                WriteShort(minT[i], ref p, packet);
            }
            for (int i = 0; i < nMotor; ++i)
            {
                WriteShort(maxT[i], ref p, packet);
            }
            PutCommand(packet, p);
        }
        public void SendResetSensor(ResetSensorFlag f) {
            byte[] packet = new byte[1000];
            int p = 0;
            WriteHeader((int)CommandId.CI_RESET_SENSOR, ref p, packet);
            WriteShort((short)f, ref p, packet);
            PutCommand(packet, p);
            if ((f & ResetSensorFlag.RSF_MOTOR) != 0 && pose != null)
            {
                for (int i = 0; i < pose.values.Count(); i++)
                {
                    pose.values[i] = pose.values[i] % SDEC.ONE;
                }
            }
        }
        public void SendSetIp()
        {
            byte[] packet = new byte[1000];
            int p = 0;
            WriteHeader((int)CommandId.CIU_SET_IPADDRESS, ref p, packet);
            PutCommand(packet, p);
        }
        public void SendGetIp() {
            byte[] packet = new byte[10];
            int p = 0;
            WriteHeader((int)CommandId.CIU_GET_IPADDRESS, ref p, packet);
            PutCommand(packet, p);
        }
        public void SendGetBoardInfo() {
            byte[] packet = new byte[10];
            int p = 0;
            WriteHeader((int)CommandId.CI_BOARD_INFO, ref p, packet);
            PutCommand(packet, p);
        }
        public void SendSensor() {
            byte[] packet = new byte[10];
            int p = 0;
            WriteHeader((int)CommandId.CI_SENSOR, ref p, packet);
            PutCommand(packet, p);
        }
        public void FindRobot()
        {
            sendPoint = null;
            Open();
            if (udpBc == null)
            {
                udpBc = new UdpClient(localBcPort);
            }
            byte[] packet = new byte[10];
            int p = 0;
            WriteShort(6, ref p, packet);   //  len
            WriteShort(0, ref p, packet);   //  count
            WriteShort((int)CommandId.CIU_GET_IPADDRESS, ref p, packet);    // cmd
            udpBc.EnableBroadcast = true;
            System.Net.IPEndPoint ep = new System.Net.IPEndPoint(System.Net.IPAddress.Broadcast, remotePort);
            udpBc.Send(packet, p, ep);
            bFindRobot = true;
        }
        public void StopFindRobot()
        {
            bFindRobot = false;
        }
        //  For call backs
        public Control owner;
        public delegate void RobotFindHandlerType(System.Net.IPAddress adr);
        public event RobotFindHandlerType OnRobotFound = null;
        public delegate void UpdateRobotInfoHandlerType(byte[] prevMacAddress);
        public event UpdateRobotInfoHandlerType OnUpdateRobotInfo = null;
        public delegate void MessageRecieveHandlerType(int type, string msg);
        public event MessageRecieveHandlerType OnMessageReceive = null;
        public delegate void UpdateRobotStateHandlerType();
        public event UpdateRobotStateHandlerType OnUpdateRobotState = null;
    }
}
