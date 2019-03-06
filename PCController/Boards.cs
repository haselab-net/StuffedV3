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
        int nMotor;
        int nCurrent;
        int nForce;
        int nTarget;
        public int NMotor { get { return nMotor; } }
        public int NCurrent { get { return nCurrent; } }
        public int NForce { get { return nForce; } }
        public int NTarget { get { return nTarget; } }
        short[] pos;
        short[] vel;
        short[] current;
        short[] force;
        public static void WriteShort(byte[] buf, ref int cur, short v)
        {
            buf[cur++] = (byte)(v & 0xFF);
            buf[cur++] = (byte)(v >> 8);
        }
        public static short ReadShort(byte[] buf, ref int cur)
        {
            short v;
            v = buf[cur++];
            v = (short) (v | (short)(buf[cur++] << 8));
            return v;
        }
        //  return received currents;
        public short[] SendCurrent(short[] currents)
        {
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
        public void SendParam(short[] k, short[] b, short[] a)
        {
            int ki = 0;
            int bi = 0;
            int ai = 0;
            foreach (Board board in this)
            {
                //  compute length
                int wait = board.GetWaitLen(CommandId.CI_PDPARAM);
                int bufLen = wait + board.CommandLen(CommandId.CI_PDPARAM);
                int retLen = board.ReturnLen(CommandId.CI_PDPARAM);
                byte[] sendBuf = Enumerable.Repeat((byte)0, bufLen).ToArray();
                byte[] recvBuf = new byte[retLen];
                sendBuf[0] = Board.MakeHeader(CommandId.CI_PDPARAM, board.boardId);
                int cur = 1;
                for (int i = 0; i < board.nMotor; ++i)
                {
                    WriteShort(sendBuf, ref cur, k[ki++]);
                }
                for (int i = 0; i < board.nMotor; ++i)
                {
                    WriteShort(sendBuf, ref cur, b[bi++]);
                }
                for (int i = 0; i < board.nMotor; ++i)
                {
                    WriteShort(sendBuf, ref cur, a[ai++]);
                }
                Serial.Write(sendBuf, 0, bufLen);
            }
        }
        public void ListBoard() {
            if (serial == null) return;
            byte[] tempInit = { 0, 0, 0, 0, 0, 0 };
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
            nTarget = int.MaxValue; nMotor = 0; nCurrent = 0; nForce = 0;
            foreach (Board board in this) {
                nTarget = board.nTarget < nTarget ? board.nTarget : nTarget;
                nMotor += board.nMotor;
                nCurrent += board.nCurrent;
                nForce += board.nForce;
            }
            pos = Enumerable.Repeat((short)0, NMotor).ToArray();
            vel = Enumerable.Repeat((short)0, NMotor).ToArray();
            current = Enumerable.Repeat((short)0, NCurrent).ToArray();
            force = Enumerable.Repeat((short)0, NForce).ToArray();
        }
    }
}
