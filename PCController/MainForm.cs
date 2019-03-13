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
            cmbPortBin.Items.AddRange(SerialPort.GetPortNames());
            if (cmbPortBin.Items.Count > 0)
            {
                cmbPortBin.Text = cmbPortBin.Items[0].ToString();
            }
            motors = new Motors();
            udLoopTime_ValueChanged(udLoopTime, null);
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
            uartBin.Open();
            if (uartBin.IsOpen) {
                trBoards.Nodes.Clear();
                boards.Clear();
                boards.ListBoard();
                foreach (Board b in boards)
                {
                    TreeNode nb = trBoards.Nodes.Add("#" + b.boardId
                        + "M" + b.nMotor + "C" + b.nCurrent + "F" + b.nForce
                        );
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
            boards.SendParam(k, b, a);
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
