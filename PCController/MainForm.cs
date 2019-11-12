using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;

namespace PCController
{
    public partial class MainForm : Form
    {
        Boards boards;
        Motors motors;
        public MainForm()
        {
            InitializeComponent();
            boards = new Boards();
            boards.Serial = uartBin;
            string[] ports = SerialPort.GetPortNames();
            Array.Sort(ports);
            cmbPortBin.Items.AddRange(ports);
            if (cmbPortBin.Items.Count > 0)
            {
                cmbPortBin.Text = cmbPortBin.Items[0].ToString();
            }
            motors = new Motors();
            udLoopTime_ValueChanged(udLoopTime, null);
        }
        void SetTextMessage(string msg)
        {
            txMsg.Text = msg;
        }
        private void cmbPortBin_TextChanged(object sender, EventArgs e)
        {

        }
        private void ResetPanels() {
            ResetCurrentTab();
            ResetMotor();
        }
        List<CurrentControl> currentControls = new List<CurrentControl>();
        private void ResetCurrentTab()
        {
            flCurrent.Controls.Clear();
            currentControls.Clear();
            for (int i = 0; i < boards.NMotor; ++i) {
                CurrentControl cc = new CurrentControl();
                cc.Init();
                flCurrent.Controls.Add(cc.panel);
                currentControls.Add(cc);
            }
        }
        void ResetMotor() {
            motors.Clear();
            flParam.Controls.Clear();
            flPos.Controls.Clear();
            for (int i = 0; i < boards.NMotor; ++i) {
                Motor m = new Motor();
                motors.Add(m);
                flParam.Controls.Add(m.pd.panel);
                flPos.Controls.Add(m.position.panel);
                m.position.ValueChanged += GetEditedValue;
            }
        }
        private void btListBoards_Click(object sender, EventArgs e)
        {
            if (uartBin.IsOpen) uartBin.Close();
            if (cmbPortBin.Text.Length == 0) return;
            uartBin.PortName = cmbPortBin.Text;
            uartBin.BaudRate = 2000000;
            try
            {
                uartBin.Open();
            }
            catch {
                return;
            }
            if (uartBin.IsOpen) {
                trBoards.Nodes.Clear();
                boards.Clear();
                boards.ListBoard();
                foreach (Board b in boards)
                {
                    TreeNode nb = trBoards.Nodes.Add("#" + b.boardId
                        + "M" + b.nMotor + "C" + b.nCurrent + "F" + b.nForce
                        );
                    nb.Nodes.Add("ID " + b.boardId);
                    nb.Nodes.Add("model " + b.modelNumber);
                    nb.Nodes.Add("nTarget " + b.nTarget);
                    nb.Nodes.Add("nMotor " + b.nMotor);
                    nb.Nodes.Add("nCurrent " + b.nCurrent);
                    nb.Nodes.Add("nForce " + b.nForce);
                }
                ResetPanels();
            }
        }
        private void UpdateCurrent()
        {
            short[] currents = new short[boards.NMotor];
            for (int i = 0; i < currentControls.Count; ++i)
            {
                currents[i] = (short)currentControls[i].udTargetCurrent.Value;
            }
            short[] curCurrents = boards.SendCurrent(currents);
            for (int i = 0; i < currentControls.Count; ++i)
            {
                currentControls[i].lbCurrent.Text = "" + curCurrents[i];
            }
        }
        private void UpdateParam()
        {
            short[] k = new short[boards.NMotor];
            short[] b = new short[boards.NMotor];
            short[] a = new short[boards.NMotor];
            for (int i = 0; i < motors.Count; ++i)
            {
                k[i] = (short)motors[i].pd.K;
                b[i] = (short)motors[i].pd.B;
                a[i] = (short)motors[i].pd.A;
            }
            boards.SendParamPd(k, b);
            boards.SendParamCurrent(a);
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            if (tbControl.SelectedTab == tpPos)
            {
                UpdatePos();
            }
            if (tbControl.SelectedTab == tpCurrent)
            {
                UpdateCurrent();
            }
            if (tbControl.SelectedTab == tpParam)
            {
                UpdateParam();
            }
        }

        private void trBoards_AfterLabelEdit(object sender, NodeLabelEditEventArgs e)
        {
            if (e.Label != null)
            {
                int id;
                if (!int.TryParse(e.Label, out id)) {
                    if (!int.TryParse(e.Label.Substring(2), out id))
                    {
                        e.CancelEdit = true;
                    }
                }
                if (!e.CancelEdit)
                {
                    foreach (Board b in boards)
                    {
                        if (b.boardId == id)
                        {
                            e.CancelEdit = true;
                        }
                    }
                }
                if (!e.CancelEdit) {
                    int oid;
                    int.TryParse(e.Node.Text.Substring(2), out oid);
                    byte[] ids = new byte[boards.Count];
                    for (int i = 0; i < boards.Count; ++i) {
                        ids[i] = (byte)boards[i].boardId;
                        if (ids[i] == oid)
                        {
                            ids[i] = (byte)id;
                        }
                    }
                    boards.SendParamBoardId(ids);
                }
            }
        }

        private void trBoards_BeforeLabelEdit(object sender, NodeLabelEditEventArgs e)
        {
            if (e.Node != null)
            {
                if (!e.Node.Text.Contains("ID"))
                {
                    e.CancelEdit = true;
                }
            }
        }

        private void udTick_ValueChanged(object sender, EventArgs e)
        {
            int tick = (int)udTick.Value;
            if (tick < 1) tick = 1;
            timer.Interval = tick;
        }

    }
    public class CurrentControl
    {
        public Panel panel;
        public NumericUpDown udTargetCurrent;
        public Label lbCurrent;
        public void Init()
        {
            panel = new Panel();
            lbCurrent = new Label();
            udTargetCurrent = new NumericUpDown();
            lbCurrent.Width = 80;
            lbCurrent.Height = 16;
            udTargetCurrent.Maximum = 1024 * 2;
            udTargetCurrent.Minimum = -1024 * 2;
            udTargetCurrent.Width = lbCurrent.Width;
            udTargetCurrent.Top = lbCurrent.Height;
            panel.Width = udTargetCurrent.Width;
            panel.Height = udTargetCurrent.Height + lbCurrent.Height;
            panel.Controls.Add(lbCurrent);
            panel.Controls.Add(udTargetCurrent);
        }
    }
}
