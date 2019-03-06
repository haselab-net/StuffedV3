using System;
using System.ComponentModel;
using System.Windows.Forms;

namespace Robokey
{
    public partial class MainForm : Form
    {
        private void btLoad_Click(object sender, EventArgs e)
        {
            openPose.ShowDialog();
        }
        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            LoadMotion(openPose.FileName);
        }

        private void btSave_Click(object sender, EventArgs e)
        {
            savePose.ShowDialog();
        }

        private void saveFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            System.IO.StreamWriter file = new System.IO.StreamWriter(savePose.FileName);
            file.Write(poses.Count); file.Write("\t");
            file.Write(udpComm.RobotInfo.nMotor); file.Write("\t");
            file.Write(udLoopTime.Value); file.Write("\n");
            int lastTime = 0;
            for (int h = 0; h < poses.Count; ++h)
            {
                Pose pose = (Pose)poses[h];
                file.Write(pose.Time - lastTime);
                lastTime = pose.Time;
                for (int i = 0; i < udpComm.RobotInfo.nMotor; ++i)
                {
                    file.Write("\t");
                    file.Write(pose.values[i]);
                }
                file.Write("\n");
            }
            file.Close();
        }
        private void udTime_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == '\r')
                UpdateCurTime((int)udTime.Value);
            udpComm.SendPoseDirect(Interpolate(curTime) + motors.Offset());
            udpComm.SendPackets();
        }

        private void btCopy_Click(object sender, EventArgs e)
        {
            String str = "";
            for (int i = 0; i < udpComm.RobotInfo.nMotor; ++i)
            {
                str += ((Motor)motors[i]).Value;
                if (i < udpComm.RobotInfo.nMotor - 1) str += "\t";
            }
            Clipboard.SetDataObject(str);
        }

        public bool LoadMotion(String Filename)
        {
            System.IO.StreamReader file = new System.IO.StreamReader(Filename);
            String[] cells;
            do
            {
                cells = file.ReadLine().Split('\t');
            } while (cells[0].IndexOf('#') != -1);

            int nPose = int.Parse(cells[0]);
            if (udpComm.IsConnected && udpComm.RobotInfo.nMotor != int.Parse(cells[1]))
            {
                SetErrorMessage("Dofs of file data and connected system do not match.");
                return false;
            }
            else
            {
                RobotInfo info = udpComm.RobotInfo;
                info.nMotor = int.Parse(cells[1]);
                udpComm.SetRobotInfo(info);
            }
            udLoopTime.Value = int.Parse(cells[2]);
            foreach (Pose pose in poses)
            {
                Controls.Remove(pose.button);
            }
            poses.Clear();
            int lastTime = 0;
            while (true)
            {
                string line = file.ReadLine();
                if (line == null) break;
                if (line.IndexOf('#') != -1) continue;
                string[] cells2 = line.Split('\t');
                if (cells2.Length < udpComm.RobotInfo.nMotor + 1) break;
                Pose pose = NewPose();
                lastTime += int.Parse(cells2[0]);
                pose.Time = lastTime;
                for (int i = 0; i < udpComm.RobotInfo.nMotor; ++i)
                {
                    pose.values[i] = int.Parse(cells2[i + 1]);
                }
                poses.Add(pose);
            }
            file.Close();
            //udLoopTime.Value = lastTime;
            PoseData p = Interpolate(track.Value) + motors.Offset();
            if (p != null) LoadToEditor(p);

            return (true);
        }
    }
}
