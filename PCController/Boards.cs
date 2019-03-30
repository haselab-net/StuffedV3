using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Diagnostics;

namespace PCController
{
    class Boards: List<Board>{
        System.IO.Ports.SerialPort serial=null;
        public System.IO.Ports.SerialPort Serial
        {
            get { return serial; }
            set { serial = value; }
        }
        public enum ControlMode {
            CM_DIRECT,
            CM_CURRENT,
            CM_INTERPOLATE
        };
        ControlMode controlMode = ControlMode.CM_DIRECT;
        byte interpolateTargetCountWrite;
        public byte InterpolateTargetCountWrite { get { return interpolateTargetCountWrite; } }
        public byte InterpolateTargetCountRead { get {
                if (Count == 0) return 0;
                byte rv = this[0].interpolateTargetCountRead;
                foreach (Board b in this)
                {
                    int diff = b.interpolateTargetCountRead - rv;
                    if (diff < 0) rv = (byte)(rv + diff);
                }
                return rv;
            }
        }
        public ushort TickMin
        {
            get
            {
                if (Count == 0) return 0;
                ushort rv = this[0].tickRead;
                foreach (Board b in this)
                {
                    int diff = b.tickRead - rv;
                    if (diff < 0) rv = (ushort)(rv + diff);
                }
                return rv;
            }
        }
        public ushort TickMax
        {
            get
            {
                if (this.Count == 0) return 0;
                ushort rv = this[0].tickRead;
                foreach (Board b in this)
                {
                    int diff = b.tickRead - rv;
                    if (diff > 0) rv = (ushort)(rv + diff);
                }
                return rv;
            }
        }
        int nMotor;
        int nCurrent;
        int nForce;
        int nTouch;
        int nTarget;
        public int NMotor { get { return nMotor; } }
        public int NCurrent { get { return nCurrent; } }
        public int NForce { get { return nForce; } }
        public int NTarget { get { return nTarget; } }
        public int NTouch { get { return nTouch; } }
        public void SetNMotor(int n) { nMotor = n; }
        short[] pos;
        short[] vel;
        short[] current;
        short[] force;
        public static void WriteShort(byte[] buf, ref int cur, short v)
        {
            buf[cur++] = (byte)(v & 0xFF);
            buf[cur++] = (byte)(v >> 8);
        }
        public static void WriteByte(byte[] buf, ref int cur, byte v)
        {
            buf[cur++] = v;
        }
        public static short ReadShort(byte[] buf, ref int cur)
        {
            short v;
            v = buf[cur++];
            v = (short) (v | (short)(buf[cur++] << 8));
            return v;
        }
        public void SendPosDirect(short[] targets)
        {
            SetControlMode(ControlMode.CM_DIRECT);
            int mi = 0;
            foreach (Board board in this)
            {
                //  compute length
                int wait = board.GetWaitLen(CommandId.CI_DIRECT);
                int bufLen = wait + board.CommandLen(CommandId.CI_DIRECT);
                int retLen = board.ReturnLen(CommandId.CI_DIRECT);
                byte[] sendBuf = Enumerable.Repeat((byte)0, bufLen).ToArray();
                byte[] recvBuf = new byte[retLen];
                sendBuf[0] = Board.MakeHeader(CommandId.CI_DIRECT, board.boardId);
                int cur = 1;
                for (int i = 0; i < board.nMotor; ++i)
                {
                    WriteShort(sendBuf, ref cur, targets[mi++]);
                }
                Serial.Write(sendBuf, 0, bufLen);
                int nRead = 0;
                while (nRead < retLen)
                {
                    nRead += Serial.Read(recvBuf, nRead, retLen - nRead);
                }
                cur = 1;
                for (int i = 0; i < board.nMotor; ++i)
                {
                    pos[board.motorMap[i]] = ReadShort(recvBuf, ref cur);
                }
                for (int i = 0; i < board.nMotor; ++i)
                {
                    vel[board.motorMap[i]] = ReadShort(recvBuf, ref cur);
                }
            }
        }
        public void SetControlMode(ControlMode m) {
            if (m != controlMode) {
                if (m == ControlMode.CM_INTERPOLATE)
                {
                    interpolateTargetCountWrite = 0;
                    foreach (Board b in this)
                    {
                        b.interpolateTargetCountRead = 0x100 - 2;
                    }
                }
                controlMode = m;
            }
        }
        public void SendPosInterpolate(short[] targets, ushort period)
        {
            int mi = 0;
            SetControlMode(ControlMode.CM_INTERPOLATE);
            foreach (Board board in this)
            {
                //  compute length
                int wait = board.GetWaitLen(CommandId.CI_INTERPOLATE);
                int bufLen = wait + board.CommandLen(CommandId.CI_INTERPOLATE);
                int retLen = board.ReturnLen(CommandId.CI_INTERPOLATE);
                byte[] sendBuf = Enumerable.Repeat((byte)0, bufLen).ToArray();
                byte[] recvBuf = new byte[retLen];
                sendBuf[0] = Board.MakeHeader(CommandId.CI_INTERPOLATE, board.boardId);
                int cur = 1;
                for (int i = 0; i < board.nMotor; ++i)
                {
                    WriteShort(sendBuf, ref cur, targets[mi++]);
                }
                WriteShort(sendBuf, ref cur, (short)period);
                WriteByte(sendBuf, ref cur, interpolateTargetCountWrite);
                if (period > 0) //  period == 0 means no target is sent but get the state.
                {
                    interpolateTargetCountWrite++;
                }
                Serial.Write(sendBuf, 0, bufLen);
                int nRead = 0;
                while (nRead < retLen)
                {
                    nRead += Serial.Read(recvBuf, nRead, retLen - nRead);
                }
                cur = 1;
                for (int i = 0; i < board.nMotor; ++i)
                {
                    pos[board.motorMap[i]] = ReadShort(recvBuf, ref cur);
                }
                board.tickRead = (ushort)ReadShort(recvBuf, ref cur);
                board.interpolateTargetCountRead = recvBuf[cur];
            }
        }

        //  return received currents;
        public short[] SendCurrent(short[] currents)
        {
            SetControlMode(ControlMode.CM_CURRENT);
            int mi = 0;
            short[] rv = new short [currents.Length];
            foreach(Board board in this)
            {
                //  compute length
                int wait = board.GetWaitLen(CommandId.CI_CURRENT);
                int bufLen = wait + board.CommandLen(CommandId.CI_CURRENT);
                int retLen = board.ReturnLen(CommandId.CI_CURRENT);
                byte[] sendBuf = Enumerable.Repeat((byte)0, bufLen).ToArray();
                byte[] recvBuf = new byte[retLen];
                sendBuf[0] = Board.MakeHeader(CommandId.CI_CURRENT, board.boardId);
                int cur = 1;
                for (int i=0; i<board.nMotor; ++i)
                {
                    WriteShort(sendBuf, ref cur, currents[mi++]);
                }
                Serial.Write(sendBuf, 0, bufLen);
                int nRead = 0;
                while (nRead < retLen) {
                    nRead += Serial.Read(recvBuf, nRead, retLen-nRead);
                }
                cur = 1;
                for (int i = 0; i < board.nMotor; ++i)
                {
                    pos[board.motorMap[i]] = ReadShort(recvBuf, ref cur);
                }
                for (int i = 0; i < board.nMotor; ++i)
                {
                    vel[board.motorMap[i]] = ReadShort(recvBuf, ref cur);
                }
                for (int i = 0; i < board.nMotor; ++i)
                {
                    rv[board.motorMap[i]] = ReadShort(recvBuf, ref cur);
                }
            }
            return rv;
        }
        public void SendParamPd(short[] k, short[] b)
        {
            int ki = 0;
            int bi = 0;
            foreach (Board board in this)
            {
                //  compute length
                int wait = board.GetWaitLen(CommandId.CI_SETPARAM);
                int bufLen = wait + board.CommandLen(CommandId.CI_SETPARAM);
                int retLen = board.ReturnLen(CommandId.CI_SETPARAM);
                byte[] sendBuf = Enumerable.Repeat((byte)0, bufLen).ToArray();
                byte[] recvBuf = new byte[retLen];
                sendBuf[0] = Board.MakeHeader(CommandId.CI_SETPARAM, board.boardId);
                sendBuf[1] = (byte)SetParamType.PT_PD;
                int cur = 2;
                for (int i = 0; i < board.nMotor; ++i)
                {
                    WriteShort(sendBuf, ref cur, k[ki++]);
                }
                for (int i = 0; i < board.nMotor; ++i)
                {
                    WriteShort(sendBuf, ref cur, b[bi++]);
                }
                Serial.Write(sendBuf, 0, bufLen);
            }
        }
        public void SendParamCurrent(short[] a)
        {
            int ai = 0;
            foreach (Board board in this)
            {
                //  compute length
                int wait = board.GetWaitLen(CommandId.CI_SETPARAM);
                int bufLen = wait + board.CommandLen(CommandId.CI_SETPARAM);
                int retLen = board.ReturnLen(CommandId.CI_SETPARAM);
                byte[] sendBuf = Enumerable.Repeat((byte)0, bufLen).ToArray();
                byte[] recvBuf = new byte[retLen];
                sendBuf[0] = Board.MakeHeader(CommandId.CI_SETPARAM, board.boardId);
                sendBuf[1] = (byte)SetParamType.PT_CURRENT;
                int cur = 2;
                for (int i = 0; i < board.nMotor; ++i)
                {
                    WriteShort(sendBuf, ref cur, a[ai++]);
                }
                Serial.Write(sendBuf, 0, bufLen);
            }
        }
        public void SendParamTorqueLimit(short[] tmin, short[] tmax)
        {
            int i1 = 0;
            int i2 = 0;
            foreach (Board board in this)
            {
                //  compute length
                int wait = board.GetWaitLen(CommandId.CI_SETPARAM);
                int bufLen = wait + board.CommandLen(CommandId.CI_SETPARAM);
                int retLen = board.ReturnLen(CommandId.CI_SETPARAM);
                byte[] sendBuf = Enumerable.Repeat((byte)0, bufLen).ToArray();
                byte[] recvBuf = new byte[retLen];
                sendBuf[0] = Board.MakeHeader(CommandId.CI_SETPARAM, board.boardId);
                sendBuf[1] = (byte)SetParamType.PT_TORQUE_LIMIT;
                int cur = 2;
                for (int i = 0; i < board.nMotor; ++i)
                {
                    WriteShort(sendBuf, ref cur, tmin[i1++]);
                }
                for (int i = 0; i < board.nMotor; ++i)
                {
                    WriteShort(sendBuf, ref cur, tmax[i2++]);
                }
                Serial.Write(sendBuf, 0, bufLen);
            }
        }
        public void SendParamBoardId(byte [] ids)
        {
            int i = 0;
            foreach (Board board in this)
            {
                //  compute length
                int wait = board.GetWaitLen(CommandId.CI_SETPARAM);
                int bufLen = wait + board.CommandLen(CommandId.CI_SETPARAM);
                int retLen = board.ReturnLen(CommandId.CI_SETPARAM);
                byte[] sendBuf = Enumerable.Repeat((byte)0, bufLen).ToArray();
                byte[] recvBuf = new byte[retLen];
                sendBuf[0] = Board.MakeHeader(CommandId.CI_SETPARAM, board.boardId);
                sendBuf[1] = (byte)SetParamType.PT_BOARD_ID;
                int cur = 2;
                board.boardId = ids[i];
                sendBuf[cur++] = ids[i++];
                Serial.Write(sendBuf, 0, bufLen);
            }
        }
        public void ListBoard() {
            if (serial == null) return;
            byte[] tempInit = { 0, 0, 0, 0, 0, 0, 0 };
            Board boardTemp = new Board(tempInit, null);
            //  clear serial receive buffer
            while (Serial.BytesToRead > 0) Serial.DiscardInBuffer();
            //  compute length
            int wait = boardTemp.GetWaitLen(CommandId.CI_BOARD_INFO);
            int bufLen = wait + boardTemp.CommandLen(CommandId.CI_BOARD_INFO);
            int retLen = boardTemp.ReturnLen(CommandId.CI_BOARD_INFO);
            byte[] sendBuf = Enumerable.Repeat((byte)0, bufLen).ToArray();
            byte[] recvBuf = new byte[retLen];
            //  get information of all boards.
            for (int bi = 0; bi < 8; ++bi) {
                sendBuf[0] = Board.MakeHeader(CommandId.CI_BOARD_INFO, bi);
                Serial.Write(sendBuf, 0, bufLen);
                for (int t = 0; t < 10; ++t) {
                    if (Serial.BytesToRead == retLen) {
                        Serial.Read(recvBuf, 0, retLen);
                        Board board = new Board(recvBuf, Count > 0 ? this[Count-1] : null);
                        Add(board);
                    }
                    Thread.Sleep(2);
                }
            }
            //  set command length of all boards.
            foreach(Board board in this)
            {
                sendBuf[0] = Board.MakeHeader(CommandId.CI_SET_CMDLEN, board.boardId);
                for (int i = 0; i < (int)CommandId.CI_NCOMMAND; ++i) {
                    sendBuf[i + 1] = (byte)board.CommandLen((CommandId)i);
                }
                Serial.Write(sendBuf, 0, bufLen);
            }
            //  Calc nXXX.
            nTarget = int.MaxValue; nMotor = 0; nCurrent = 0; nForce = 0; nTouch = 0;
            foreach (Board board in this) {
                nTarget = board.nTarget < nTarget ? board.nTarget : nTarget;
                nMotor += board.nMotor;
                nCurrent += board.nCurrent;
                nForce += board.nForce;
                nTouch += board.nTouch;
            }
            pos = Enumerable.Repeat((short)0, NMotor).ToArray();
            vel = Enumerable.Repeat((short)0, NMotor).ToArray();
            current = Enumerable.Repeat((short)0, NCurrent).ToArray();
            force = Enumerable.Repeat((short)0, NForce).ToArray();
        }
    }
}
