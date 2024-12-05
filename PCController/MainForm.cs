//#define USE_THREAD
using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;
using System.Linq;

namespace PCController
{
    public partial class MainForm : Form
    {
        Boards boards;
        Motors motors;
        Haptics haptics;
        private MMTimer mmTimer;

        bool bHaptic = false;
        int[] times = null;
        int count = 0; //単位ms
        int count1000 = 0; //単位s
        int hapticCount = 0; //単位msで3秒測るためのもの
        int diffCount = 50; //タイミング間隔の秒数(ms)
        int v; //trackbarの値代入するメンバ関数
        int t = 1500;//提示時間
        //int td = 5; //何ミリ秒に一回電流値を増加させるか
        
        void mmTimer_Tick(Object sender)   //  Haptic制御
        {
            count ++;
            if (count >= 1000)
            {
                count = 0;
                count1000++;
                System.Diagnostics.Debug.WriteLine("Tick called " + count1000 * 1000 + " times.");//1sごとに文章出力
            }
            //short vib=0; //shortは値の単位指定
            //short [] wave = { 1, 0, -1, 0 }; //sin波で振動を作り出している

            //textBox1.Text = hapticCount.ToString();
            if (bHaptic)
            {
                hapticCount++;
                //System.Diagnostics.Debug.WriteLine("hapticCount " + hapticCount);
                //モーターに送る電流値の最大値と最小値の設定
                short minForce = 35;
                //short hapticMin = 0;
                short hapticMax = 180; //180
                //short diff = 100;//最大値になるまでの秒数

                double vaa = ((double)hapticMax)/(((double)t / 6.0)*(t / 6.0)); //加速度定義→距離が電流値に相当

                //直線なら差をとって５ずつとか，割合でやるなら曲線になる        
                //5秒以内で刺激の提示が終わるようにする

                //力の合計値を一定にしなかった場合，最終的にかかる力が同じになる
                if ((hapticCount <= t) && (haptics.currents[2] < hapticMax + minForce))
                {
                    if((hapticCount >= 0)&&(hapticCount < (t/6)))
                    {
                        haptics.currents[2] = (short)((vaa / 2) * (hapticCount * hapticCount) + minForce);
                    }
                    if ((hapticCount >= (t / 6)) && (hapticCount < (t / 3)))
                    {
                        haptics.currents[2] = (short)(((-vaa / 2) * ((hapticCount- t / 3)* (hapticCount - t / 3)))+ hapticMax + minForce);
                    }
                    if ((hapticCount >= (t / 3)) && (hapticCount < 2*t))
                    {
                        haptics.currents[2] = (short)(hapticMax + minForce);
                    }
                    /*
                    if ((hapticCount >= (2*t / 3)) && (hapticCount <= t))
                    {
                        haptics.currents[2]-= (short)((hapticMax - hapticMin) / diff);
                    }
                    */
                }

                int d = diffCount * v; //提示タイミングの秒差分

                if ((hapticCount <= t) && (hapticCount > d) && (haptics.currents[1] < hapticMax + minForce) && (haptics.currents[3] < hapticMax + minForce))
                {
                    if ((hapticCount >= d) && (hapticCount < ((t / 6) + d)))
                    {
                        haptics.currents[1] = (short)((vaa / 2) * ((hapticCount - d) * (hapticCount - d)) + minForce);
                        haptics.currents[3] = (short)((vaa / 2) * ((hapticCount - d) * (hapticCount - d)) + minForce);
                    }
                    if ((hapticCount >= ((t / 6) + d)) && (hapticCount < ((t / 3) + d)))
                    {
                        haptics.currents[1] = (short)(((-vaa / 2) * (((hapticCount - d) - t / 3) * ((hapticCount - d) - t / 3))) + hapticMax + minForce);
                        haptics.currents[3] = (short)(((-vaa / 2) * (((hapticCount - d) - t / 3) * ((hapticCount - d) - t / 3))) + hapticMax + minForce);
                    }
                    if ((hapticCount >= ((t / 3) + d)) && (hapticCount < (2*t + d)))
                    {
                        haptics.currents[1] = (short)(hapticMax + minForce);
                        haptics.currents[3] = (short)(hapticMax + minForce);
                    }
                    /*
                    if ((hapticCount >= (2 * t / 3) + d) && (hapticCount <= t + d))
                    {
                        haptics.currents[2] -= (short)((hapticMax - hapticMin) / diff);
                    }
                    */
                }
                if ((hapticCount <= t) && (hapticCount > 2 * d) && (haptics.currents[0] < hapticMax + minForce) && (haptics.currents[4] < hapticMax + minForce))
                {
                    if ((hapticCount >= (2 * d)) && (hapticCount < ((t / 6) + (2 * d))))
                    {
                        haptics.currents[0] = (short)((vaa / 2) * ((hapticCount - (2 * d)) * (hapticCount - (2 * d))) + minForce);
                        haptics.currents[4] = (short)((vaa / 2) * ((hapticCount - (2 * d)) * (hapticCount - (2 * d))) + minForce);
                    }
                    if ((hapticCount >= ((t / 6) + (2 * d))) && (hapticCount < ((t / 3) + (2 * d))))
                    {
                        haptics.currents[0] = (short)(((-vaa / 2) * (((hapticCount - 2 * d) - t / 3) * ((hapticCount - 2 * d) - t / 3))) + hapticMax + minForce);
                        haptics.currents[4] = (short)(((-vaa / 2) * (((hapticCount - 2 * d) - t / 3) * ((hapticCount - 2 * d) - t / 3))) + hapticMax + minForce);
                    }
                    if ((hapticCount >= ((t / 3) + (2 * d))) && (hapticCount < (2*t + (2 * d))))
                    {
                        haptics.currents[0] = (short)(hapticMax + minForce);
                        haptics.currents[4] = (short)(hapticMax + minForce);
                    }
                    /*
                    if ((hapticCount >= (2 * t / 3) + (2 * d)) && (hapticCount <= t + (2 * d)))
                    {
                        haptics.currents[2] -= (short)((hapticMax - hapticMin) / diff);
                    }
                    */
                }

                /*
                //案1 力の合計値を一定にしなかった場合，最終的にかかる力が同じになる
                if ((hapticCount <= t) && (haptics.currents[2] < hapticMax) && (hapticCount % td == 0))
                {
                    haptics.currents[2] += (short)((hapticMax - hapticMin) / diff);//モーターに送る電流値の線形増加
                }

                if ((hapticCount <= t) && (hapticCount > (diffCount * v)) && (haptics.currents[1] < hapticMax) && (haptics.currents[3] < hapticMax) && (hapticCount % td == 0))
                {
                    //haptics.currents[1] += (short)((hapticMax - hapticMin) / diff);
                    //haptics.currents[3] += (short)((hapticMax - hapticMin) / diff);
                }
                if ((hapticCount <= t) && (hapticCount > ((diffCount * v) + (diffCount * v))) && (haptics.currents[0] < hapticMax) && (haptics.currents[4] < hapticMax) && (hapticCount % td == 0))
                {
                    //haptics.currents[0] += (short)((hapticMax - hapticMin) / diff);
                    //haptics.currents[4] += (short)((hapticMax - hapticMin) / diff);
                }
                */

                //案2 ここから力の合計値を設定したときのプログラム
                /*
                short hapticMax = 900; 
                int sumForce = haptics.currents[0] + haptics.currents[1] + haptics.currents[2] + haptics.currents[3] + haptics.currents[4];

                if ((hapticCount <= t) && (sumForce < hapticMax) && (hapticCount % td == 0))
                {
                    haptics.currents[2] += (short)((hapticMax - hapticMin) / diff);//モーターに送る電流値の線形増加
                }

                if ((hapticCount <= t) && (hapticCount > (diffCount * v)) && (sumForce < hapticMax) && (hapticCount % td == 0))
                {
                    haptics.currents[1] += (short)((hapticMax - hapticMin) / diff);
                    haptics.currents[3] += (short)((hapticMax - hapticMin) / diff);
                }
                if ((hapticCount <= t) && (hapticCount > ((diffCount * v) + (diffCount * v))) && (sumForce < hapticMax) && (hapticCount % td == 0))
                {
                    haptics.currents[0] += (short)((hapticMax - hapticMin) / diff);
                    haptics.currents[4] += (short)((hapticMax - hapticMin) / diff);
                }
                */

                //System.Diagnostics.Debug.WriteLine(haptics.currents[0]);//確認用

                //ここで刺激を提示していないときの糸のたわみがないような電流値を入れておく
                if (hapticCount > 2*t)
                {
                    haptics.currents[0] = minForce;
                    haptics.currents[1] = minForce;
                    haptics.currents[2] = minForce;
                    haptics.currents[3] = minForce;
                    haptics.currents[4] = minForce;
                    bHaptic = false;
                    System.Diagnostics.Debug.WriteLine("3秒経過");
                    hapticCount = 0;
                }
                /*
                for (int i = 0; i < boards.NMotor; ++i) {
                    int diff = haptics[i].T - boards.GetPos(i);//差をとって振動付与に使っている
                    if (diff > SDEC.ONE) diff = SDEC.ONE;
                    if (diff < 0)
                    {
                        diff = 0;
                        times[i] = 0;
                    }
                    else {
                        //振動計算
                        times[i] ++;
                        vib = (short)((short)udAmp.Value * wave[times[i] % 4]);
                        vib = (short)(vib * Math.Exp(-times[i] * (double)udDamp.Value));
                    }
                    short c = (short)(diff * haptics[i].K / SDEC.ONE);//ハード内で整数計算で行うために1024倍してるのを二回やってるから1回分割ってる
                    if (c < haptics[i].M) c = haptics[i].M; //最小張力
                    c += vib; //振動追加
                    haptics.currents[i] = c; //ここでモーター1つずつに対して定義して↓
                }
            */
                boards.SendCurrent(haptics.currents); //ここで一気に電流値を送ってる, 8/11→",true"消した      
            }
        }
        
        private void btStart_Click(object sender, EventArgs e)
        {
            //currentControls[0].udTargetCurrent.Value = hapticTrackBar.Value*100;
            hapticTrackBar.Minimum = 0;
            hapticTrackBar.Maximum = 10;
            bHaptic = true;

        }

        private void hapticTrackBar_ValueChanged(object sender, EventArgs e) //trackbarをスライドしたときの値を表示
        {
            v = hapticTrackBar.Value;
            textBox0.Text = v.ToString();
            //System.Diagnostics.Debug.WriteLine(v);
        }

        public MainForm()
        {
            mmTimer = new MMTimer();
            mmTimer.Interval = 1;
            mmTimer.Resolution = 1;
            mmTimer.Enabled = true; //変更
            mmTimer.OnTimer += mmTimer_Tick;

            System.Diagnostics.Debug.Assert(CommandId.CI_NCOMMAND <= CommandId.CI_NCOMMAND_MAX);
            InitializeComponent();
            boards = new Boards();
            boards.Serial = uartBin;
            motors = new Motors();
            haptics = new Haptics();
            udLoopTime_ValueChanged(udLoopTime, null);
            ResetMagnet();
        }


        void SetTextMessage(string msg)
        {
            txMsg.Text = msg;
        }
        private void ResetPanels() {
            ResetHapticTab();
            ResetCurrentTab();
            ResetMotor();
            ResetMagnet();
        }
        private void ResetHapticTab() {
            flHaptic.Controls.Clear();
            haptics.Clear();
            for (int i = 0; i < boards.NMotor; ++i)
            {
                Haptic h = new Haptic();
                flHaptic.Controls.Add(h.panel);
                haptics.Add(h);
            }
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
                flPos.Controls.Add(m.position.panel);
                flParam.Controls.Add(m.pd.panel);
                flHeat.Controls.Add(m.heat.panel);
                m.position.ValueChanged += GetEditedValue;
            }
            short[] k = new short[boards.NMotor];
            short[] b = new short[boards.NMotor];
            short[] a = new short[boards.NMotor];
            short[] limit = new short[boards.NMotor];
            short[] release = new short[boards.NMotor];
            short[] torqueMin = new short[boards.NMotor];
            short[] torqueMax = new short[boards.NMotor];
            bool[] encoder = new bool[boards.NMotor];
            boards.RecvParamPd(ref k, ref b);
            boards.RecvParamCurrent(ref a);
            boards.RecvParamTorque(ref torqueMin, ref torqueMax);
            boards.RecvParamHeat(ref limit, ref release);
            boards.RecvParamEncoder(ref encoder);
            for (int i = 0; i < boards.NMotor; ++i)
            {
                motors[i].pd.K = k[i];
                motors[i].pd.B = b[i];
                motors[i].pd.A = a[i];
                motors[i].pd.Enc = encoder[i];
                if (limit[i] > 32000) limit[i] = 32000;
                if (limit[i] < 0) limit[i] = 0;
                motors[i].heat.HeatLimit = limit[i] * release[i];
                motors[i].heat.HeatRelease = release[i];
                motors[i].torque.Minimum = torqueMin[i];
                motors[i].torque.Maximum = torqueMax[i];
            }
        }
        private void btListBoards_Click(object sender, EventArgs e)
        {
            if (uartBin.IsOpen) uartBin.Close();
            if (cmbPortBin.Text.Length == 0) return;
            uartBin.PortName = cmbPortBin.Text;
            uartBin.BaudRate = 2000*1000;   //  baudrate:2M
            try
            {
                uartBin.Open();
            }
            catch
            {
                return;
            }
            if (uartBin.IsOpen)
            {
                trBoards.Nodes.Clear();
                boards.Clear();
                boards.EnumerateBoard();
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
                    nb.Nodes.Add("PWM res " + b.pwmResolution);
                }
                times = Enumerable.Repeat(0, boards.NMotor).ToArray();
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
            
            boards.SendCurrent(currents);
            boards.SendSense();
            for (int i = 0; i < currentControls.Count && i < boards.NCurrent; ++i)
            {
                currentControls[i].lbCurrent.Text = "" + boards.GetCurrent(i);
            }
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            txMsg.Text = "";
	        if (bHaptic) {
	            haptics.Update();
                //電流値の表示→mmtimer.Tickでいじると壊れそうだから，マルチメディアじゃない方のタイマーで実装しようねってことでここに記載
                textBox1.Text = haptics.currents[0].ToString();
                textBox2.Text = haptics.currents[1].ToString();
                textBox3.Text = haptics.currents[2].ToString();
                textBox4.Text = haptics.currents[3].ToString();
                textBox5.Text = haptics.currents[4].ToString();
                textBox6.Text = "実行中";
            }
            else if (tbControl.SelectedTab == tpPos)
			{
                UpdatePos();
            }
			else if (tbControl.SelectedTab == tpCurrent)
            {
                UpdateCurrent();
            }
			else if (tbControl.SelectedTab == tpMagnet) {
                UpdateMagnet();
            }
            else
            {
                textBox6.Text = "準備中";
            }
            txMsg.Text += "Pos:";
            for (int i = 0; i < boards.NMotor; ++i)
            {
                txMsg.Text += " ";
                txMsg.Text += boards.GetPos(i);
            }
            if (boards.NForce != 0)
            {
                txMsg.Text += "\r\nForce:";
                for (int i = 0; i < boards.NForce; ++i)
                {
                    txMsg.Text += " ";
                    txMsg.Text += boards.GetForce(i);
                }
            }
        }

        private void trBoards_AfterLabelEdit(object sender, NodeLabelEditEventArgs e)
        {
            e.CancelEdit = true;
            if (e.Label != null)
            {
                int newNumber;
                if (!int.TryParse(e.Label, out newNumber)) {
                    if (!int.TryParse(e.Label.Split(' ').Last(), out newNumber)) return;
                }
                TreeNodeCollection nodes = e.Node.Parent.Nodes;
                int idOrg = -1;
                foreach(TreeNode node in nodes)
                {
                    if (node.Text.Contains("ID")) {
                        idOrg = int.Parse(node.Text.Split(' ').Last());
                    }
                }
                if (idOrg == -1) return;
                if (e.Node.Text.Contains("ID"))
                {
                    foreach (Board b in boards)
                    {
                        if (b.boardId == newNumber) return; //  The same id is already used.
                    }
                    e.Node.Text = "ID " + newNumber;
                    byte[] ids = new byte[boards.Count];
                    int boardPos = -1;
                    for (int i = 0; i < boards.Count; ++i)
                    {
                        ids[i] = (byte)boards[i].boardId;
                        if (ids[i] == idOrg)
                        {
                            ids[i] = (byte)newNumber;
                            boardPos = i;
                        }
                    }
                    boards.SendParamBoardId(ids);
                    boards[boardPos].boardId = (byte) newNumber;
                }
                if (e.Node.Text.Contains("PWM"))
                {
                    e.Node.Text = "PWM res " + newNumber;
                    byte[] ids = new byte[boards.Count];
                    ushort[] pwms = new ushort[boards.Count];
                    for (int i = 0; i < boards.Count; ++i)
                    {
                        pwms[i] = boards[i].pwmResolution;
                        if (boards[i].boardId == idOrg)
                        {
                            pwms[i] = (ushort)newNumber;
                            boards[i].pwmResolution = (ushort)newNumber;
                        }
                    }
                    boards.SendParamPwmResolution(pwms);
                }
            }
        }

        private void trBoards_BeforeLabelEdit(object sender, NodeLabelEditEventArgs e)
        {
            if (e.Node != null)
            {
                if (!e.Node.Text.Contains("ID") && !e.Node.Text.Contains("PWM"))
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

        private void btSendPd_Click(object sender, EventArgs e)
        {
            short[] k = new short[boards.NMotor];
            short[] b = new short[boards.NMotor];
            short[] a = new short[boards.NMotor];
            bool[] encoder = new bool[boards.NMotor];
            for (int i = 0; i < motors.Count; ++i)
            {
                k[i] = (short)motors[i].pd.K;
                b[i] = (short)motors[i].pd.B;
                a[i] = (short)motors[i].pd.A;
                encoder[i] = motors[i].pd.Enc;
            }
            boards.SendParamPd(k, b);
            boards.SendParamCurrent(a);
            boards.SendParamEncoder(encoder);
        }
        private void btRecvPd_Click(object sender, EventArgs e)
        {
            short[] k = new short[boards.NMotor];
            short[] b = new short[boards.NMotor];
            short[] a = new short[boards.NMotor];
            bool[] encoder = new bool[boards.NMotor];
            boards.RecvParamPd(ref k, ref b);
            boards.RecvParamCurrent(ref a);
            boards.RecvParamEncoder(ref encoder);
            for (int i = 0; i < motors.Count; ++i)
            {
                motors[i].pd.K = k[i];
                motors[i].pd.B = b[i];
                motors[i].pd.A = a[i];
                motors[i].pd.Enc = encoder[i];
            }
        }
        private void btLoadNuibot_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < motors.Count; ++i)
            {
                motors[i].pd.SetNuibotDefault();
            }
        }
        private void btLoadSpidar_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < motors.Count; ++i)
            {
                motors[i].pd.SetSpidarDefault();
            }
        }
        private void btLoadNubotiHeat_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < motors.Count; ++i)
            {
                motors[i].heat.SetNuibotDefault();
            }
        }
        private void btLoadSpidarHeat_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < motors.Count; ++i)
            {
                motors[i].heat.SetSpidarDefault();
            }
        }

        private void btSendHeat_Click(object sender, EventArgs e)
        {
            short[] heatLimit = new short[boards.NMotor];
            short[] heatRelease = new short[boards.NMotor];
            for (int i = 0; i < motors.Count; ++i)
            {
                heatRelease[i] = motors[i].heat.HeatRelease;
                heatLimit[i] = (short)(motors[i].heat.HeatLimit / heatRelease[i]);
            }
            boards.SendParamHeat(heatLimit, heatRelease);
        }

        private void btRecvHeat_Click(object sender, EventArgs e)
        {
            short[] heatLimit = new short[boards.NMotor];
            short[] heatRelease = new short[boards.NMotor];
            boards.RecvParamHeat(ref heatLimit, ref heatRelease);
            for (int i = 0; i < motors.Count; ++i)
            {
                motors[i].heat.HeatRelease = heatRelease[i];
                motors[i].heat.HeatLimit = heatLimit[i] * heatRelease[i];
            }
        }

        private void HapticControl() {
            while (bHaptic)
            {
                mmTimer_Tick(this);
            }
        }

#if USE_THREAD
        Thread hapticThread;
#endif

        private void btReset_Click(object sender, EventArgs e)
        {
            boards.SendResetMotor();
        }

        private void cmbPortBin_DropDown(object sender, EventArgs e)
        {
            cmbPortBin.Items.Clear();
            string[] ports = SerialPort.GetPortNames();
            //string[] ports = { "COM1", "COM2" };
            Array.Sort(ports);
            cmbPortBin.Items.AddRange(ports);
            if (cmbPortBin.Items.Count > 0)
            {
                cmbPortBin.Text = cmbPortBin.Items[0].ToString();
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
