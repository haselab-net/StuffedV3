namespace PCController
{
    partial class MainForm
    {
        /// <summary>
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージ リソースを破棄する場合は true を指定し、その他の場合は false を指定します。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows フォーム デザイナーで生成されたコード

        /// <summary>
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.uartBin = new System.IO.Ports.SerialPort(this.components);
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.openPose = new System.Windows.Forms.OpenFileDialog();
            this.savePose = new System.Windows.Forms.SaveFileDialog();
            this.splitContainerHoriz = new System.Windows.Forms.SplitContainer();
            this.tbControl = new System.Windows.Forms.TabControl();
            this.tpMagnet = new System.Windows.Forms.TabPage();
            this.pnMagnet = new System.Windows.Forms.Panel();
            this.panel3 = new System.Windows.Forms.Panel();
            this.button1 = new System.Windows.Forms.Button();
            this.btMeasure = new System.Windows.Forms.Button();
            this.tpHaptic = new System.Windows.Forms.TabPage();
            this.textBox6 = new System.Windows.Forms.TextBox();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.textBox4 = new System.Windows.Forms.TextBox();
            this.textBox5 = new System.Windows.Forms.TextBox();
            this.textBox0 = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.btStart = new System.Windows.Forms.Button();
            this.hapticTrackBar = new System.Windows.Forms.TrackBar();
            this.flHaptic = new System.Windows.Forms.FlowLayoutPanel();
            this.tpPos = new System.Windows.Forms.TabPage();
            this.flPos = new System.Windows.Forms.FlowLayoutPanel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.btCopy = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.btSave = new System.Windows.Forms.Button();
            this.btLoad = new System.Windows.Forms.Button();
            this.udkeyTime = new System.Windows.Forms.NumericUpDown();
            this.del = new System.Windows.Forms.Button();
            this.add = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.udTick = new System.Windows.Forms.NumericUpDown();
            this.udLoopTime = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.udStep = new System.Windows.Forms.NumericUpDown();
            this.label10 = new System.Windows.Forms.Label();
            this.lbCurTime = new System.Windows.Forms.Label();
            this.ckRun = new System.Windows.Forms.CheckBox();
            this.ckRunOnce = new System.Windows.Forms.CheckBox();
            this.laCurTime = new System.Windows.Forms.Label();
            this.track = new System.Windows.Forms.TrackBar();
            this.tpCurrent = new System.Windows.Forms.TabPage();
            this.flCurrent = new System.Windows.Forms.FlowLayoutPanel();
            this.tpParam = new System.Windows.Forms.TabPage();
            this.flParam = new System.Windows.Forms.FlowLayoutPanel();
            this.panel4 = new System.Windows.Forms.Panel();
            this.btLoadSpidar = new System.Windows.Forms.Button();
            this.btLoadNuibot = new System.Windows.Forms.Button();
            this.btRecvPd = new System.Windows.Forms.Button();
            this.btSendPd = new System.Windows.Forms.Button();
            this.tpHeat = new System.Windows.Forms.TabPage();
            this.flHeat = new System.Windows.Forms.FlowLayoutPanel();
            this.panel5 = new System.Windows.Forms.Panel();
            this.btLoadSpidarHeat = new System.Windows.Forms.Button();
            this.btLoadNubotiHeat = new System.Windows.Forms.Button();
            this.btRecvHeat = new System.Windows.Forms.Button();
            this.btSendHeat = new System.Windows.Forms.Button();
            this.splitContainerTop = new System.Windows.Forms.SplitContainer();
            this.panel1 = new System.Windows.Forms.Panel();
            this.btReset = new System.Windows.Forms.Button();
            this.cmbPortBin = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.btListBoards = new System.Windows.Forms.Button();
            this.splitContainerBottom = new System.Windows.Forms.SplitContainer();
            this.trBoards = new System.Windows.Forms.TreeView();
            this.txMsg = new System.Windows.Forms.TextBox();
            this.A = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainerHoriz)).BeginInit();
            this.splitContainerHoriz.Panel1.SuspendLayout();
            this.splitContainerHoriz.Panel2.SuspendLayout();
            this.splitContainerHoriz.SuspendLayout();
            this.tbControl.SuspendLayout();
            this.tpMagnet.SuspendLayout();
            this.panel3.SuspendLayout();
            this.tpHaptic.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.hapticTrackBar)).BeginInit();
            this.flHaptic.SuspendLayout();
            this.tpPos.SuspendLayout();
            this.panel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.udkeyTime)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udTick)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udLoopTime)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udStep)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.track)).BeginInit();
            this.tpCurrent.SuspendLayout();
            this.tpParam.SuspendLayout();
            this.panel4.SuspendLayout();
            this.tpHeat.SuspendLayout();
            this.panel5.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainerTop)).BeginInit();
            this.splitContainerTop.Panel1.SuspendLayout();
            this.splitContainerTop.Panel2.SuspendLayout();
            this.splitContainerTop.SuspendLayout();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainerBottom)).BeginInit();
            this.splitContainerBottom.Panel1.SuspendLayout();
            this.splitContainerBottom.Panel2.SuspendLayout();
            this.splitContainerBottom.SuspendLayout();
            this.SuspendLayout();
            // 
            // uartBin
            // 
            this.uartBin.BaudRate = 2000000;
            // 
            // timer
            // 
            this.timer.Enabled = true;
            this.timer.Interval = 1000;
            this.timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // openPose
            // 
            this.openPose.FileName = "pose.txt";
            this.openPose.Filter = "姿勢ファイル|*.txt|姿勢CSV|*.csv|すべてのファイル|*.*";
            this.openPose.FileOk += new System.ComponentModel.CancelEventHandler(this.openPose_FileOk);
            // 
            // savePose
            // 
            this.savePose.DefaultExt = "txt";
            this.savePose.FileName = "pose.txt";
            this.savePose.Filter = "姿勢ファイル|*.txt|姿勢ファイル(csv)|*.csv|すべてのファイル|*.*";
            this.savePose.FileOk += new System.ComponentModel.CancelEventHandler(this.savePose_FileOk);
            // 
            // splitContainerHoriz
            // 
            this.splitContainerHoriz.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainerHoriz.Location = new System.Drawing.Point(0, 0);
            this.splitContainerHoriz.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.splitContainerHoriz.Name = "splitContainerHoriz";
            // 
            // splitContainerHoriz.Panel1
            // 
            this.splitContainerHoriz.Panel1.Controls.Add(this.tbControl);
            // 
            // splitContainerHoriz.Panel2
            // 
            this.splitContainerHoriz.Panel2.Controls.Add(this.splitContainerTop);
            this.splitContainerHoriz.Size = new System.Drawing.Size(984, 592);
            this.splitContainerHoriz.SplitterDistance = 750;
            this.splitContainerHoriz.TabIndex = 4;
            // 
            // tbControl
            // 
            this.tbControl.Controls.Add(this.tpMagnet);
            this.tbControl.Controls.Add(this.tpHaptic);
            this.tbControl.Controls.Add(this.tpPos);
            this.tbControl.Controls.Add(this.tpCurrent);
            this.tbControl.Controls.Add(this.tpParam);
            this.tbControl.Controls.Add(this.tpHeat);
            this.tbControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tbControl.Location = new System.Drawing.Point(0, 0);
            this.tbControl.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tbControl.Name = "tbControl";
            this.tbControl.SelectedIndex = 0;
            this.tbControl.Size = new System.Drawing.Size(750, 592);
            this.tbControl.TabIndex = 5;
            this.tbControl.Click += new System.EventHandler(this.btListBoards_Click);
            // 
            // tpMagnet
            // 
            this.tpMagnet.BackColor = System.Drawing.SystemColors.Control;
            this.tpMagnet.Controls.Add(this.pnMagnet);
            this.tpMagnet.Controls.Add(this.panel3);
            this.tpMagnet.Location = new System.Drawing.Point(4, 25);
            this.tpMagnet.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tpMagnet.Name = "tpMagnet";
            this.tpMagnet.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tpMagnet.Size = new System.Drawing.Size(742, 563);
            this.tpMagnet.TabIndex = 5;
            this.tpMagnet.Text = "Magnet";
            // 
            // pnMagnet
            // 
            this.pnMagnet.AutoScroll = true;
            this.pnMagnet.AutoSize = true;
            this.pnMagnet.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnMagnet.Location = new System.Drawing.Point(3, 34);
            this.pnMagnet.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.pnMagnet.Name = "pnMagnet";
            this.pnMagnet.Size = new System.Drawing.Size(736, 527);
            this.pnMagnet.TabIndex = 3;
            this.pnMagnet.Resize += new System.EventHandler(this.pnMagnet_Resize);
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.button1);
            this.panel3.Controls.Add(this.btMeasure);
            this.panel3.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel3.Location = new System.Drawing.Point(3, 2);
            this.panel3.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(736, 32);
            this.panel3.TabIndex = 2;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(191, 2);
            this.button1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(101, 22);
            this.button1.TabIndex = 1;
            this.button1.Text = "Measure";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.btMeasure_Click);
            // 
            // btMeasure
            // 
            this.btMeasure.Location = new System.Drawing.Point(3, 2);
            this.btMeasure.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btMeasure.Name = "btMeasure";
            this.btMeasure.Size = new System.Drawing.Size(163, 22);
            this.btMeasure.TabIndex = 0;
            this.btMeasure.Text = "Drive and Measure";
            this.btMeasure.UseVisualStyleBackColor = true;
            this.btMeasure.Click += new System.EventHandler(this.btDriveMeasure_Click);
            // 
            // tpHaptic
            // 
            this.tpHaptic.Controls.Add(this.label16);
            this.tpHaptic.Controls.Add(this.label15);
            this.tpHaptic.Controls.Add(this.label14);
            this.tpHaptic.Controls.Add(this.label13);
            this.tpHaptic.Controls.Add(this.label12);
            this.tpHaptic.Controls.Add(this.label11);
            this.tpHaptic.Controls.Add(this.label9);
            this.tpHaptic.Controls.Add(this.label8);
            this.tpHaptic.Controls.Add(this.label7);
            this.tpHaptic.Controls.Add(this.label6);
            this.tpHaptic.Controls.Add(this.A);
            this.tpHaptic.Controls.Add(this.textBox6);
            this.tpHaptic.Controls.Add(this.label5);
            this.tpHaptic.Controls.Add(this.btStart);
            this.tpHaptic.Controls.Add(this.hapticTrackBar);
            this.tpHaptic.Controls.Add(this.flHaptic);
            this.tpHaptic.Location = new System.Drawing.Point(4, 25);
            this.tpHaptic.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tpHaptic.Name = "tpHaptic";
            this.tpHaptic.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tpHaptic.Size = new System.Drawing.Size(742, 563);
            this.tpHaptic.TabIndex = 5;
            this.tpHaptic.Text = "Haptic";
            this.tpHaptic.UseVisualStyleBackColor = true;
            // 
            // textBox6
            // 
            this.textBox6.Font = new System.Drawing.Font("MS UI Gothic", 15F);
            this.textBox6.Location = new System.Drawing.Point(512, 155);
            this.textBox6.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.textBox6.Multiline = true;
            this.textBox6.Name = "textBox6";
            this.textBox6.Size = new System.Drawing.Size(148, 59);
            this.textBox6.TabIndex = 17;
            this.textBox6.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(3, 2);
            this.textBox1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(77, 22);
            this.textBox1.TabIndex = 12;
            this.textBox1.Text = "0";
            this.textBox1.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(86, 2);
            this.textBox2.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(73, 22);
            this.textBox2.TabIndex = 13;
            this.textBox2.Text = "0";
            this.textBox2.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // textBox3
            // 
            this.textBox3.Location = new System.Drawing.Point(165, 2);
            this.textBox3.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(73, 22);
            this.textBox3.TabIndex = 14;
            this.textBox3.Text = "0";
            this.textBox3.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // textBox4
            // 
            this.textBox4.Location = new System.Drawing.Point(244, 2);
            this.textBox4.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBox4.Name = "textBox4";
            this.textBox4.Size = new System.Drawing.Size(73, 22);
            this.textBox4.TabIndex = 15;
            this.textBox4.Text = "0";
            this.textBox4.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // textBox5
            // 
            this.textBox5.Location = new System.Drawing.Point(323, 2);
            this.textBox5.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBox5.Name = "textBox5";
            this.textBox5.Size = new System.Drawing.Size(73, 22);
            this.textBox5.TabIndex = 16;
            this.textBox5.Text = "0";
            this.textBox5.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // textBox0
            // 
            this.textBox0.Location = new System.Drawing.Point(402, 2);
            this.textBox0.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBox0.Name = "textBox0";
            this.textBox0.Size = new System.Drawing.Size(100, 22);
            this.textBox0.TabIndex = 6;
            this.textBox0.Text = "0";
            this.textBox0.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label5
            // 
            this.label5.Location = new System.Drawing.Point(0, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(100, 22);
            this.label5.TabIndex = 0;
            // 
            // btStart
            // 
            this.btStart.Font = new System.Drawing.Font("MS UI Gothic", 20F);
            this.btStart.Location = new System.Drawing.Point(312, 155);
            this.btStart.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btStart.Name = "btStart";
            this.btStart.Size = new System.Drawing.Size(117, 59);
            this.btStart.TabIndex = 5;
            this.btStart.Text = "start";
            this.btStart.UseVisualStyleBackColor = true;
            this.btStart.Click += new System.EventHandler(this.btStart_Click);
            // 
            // hapticTrackBar
            // 
            this.hapticTrackBar.AutoSize = false;
            this.hapticTrackBar.LargeChange = 1;
            this.hapticTrackBar.Location = new System.Drawing.Point(49, 41);
            this.hapticTrackBar.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.hapticTrackBar.Name = "hapticTrackBar";
            this.hapticTrackBar.Size = new System.Drawing.Size(636, 95);
            this.hapticTrackBar.TabIndex = 2;
            this.hapticTrackBar.ValueChanged += new System.EventHandler(this.hapticTrackBar_ValueChanged);
            // 
            // flHaptic
            // 
            this.flHaptic.AutoScroll = true;
            this.flHaptic.BackColor = System.Drawing.SystemColors.Window;
            this.flHaptic.Controls.Add(this.textBox1);
            this.flHaptic.Controls.Add(this.textBox2);
            this.flHaptic.Controls.Add(this.textBox3);
            this.flHaptic.Controls.Add(this.textBox4);
            this.flHaptic.Controls.Add(this.textBox5);
            this.flHaptic.Controls.Add(this.textBox0);
            this.flHaptic.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.flHaptic.Location = new System.Drawing.Point(3, 346);
            this.flHaptic.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.flHaptic.Name = "flHaptic";
            this.flHaptic.Size = new System.Drawing.Size(736, 215);
            this.flHaptic.TabIndex = 1;
            // 
            // tpPos
            // 
            this.tpPos.Controls.Add(this.flPos);
            this.tpPos.Controls.Add(this.panel2);
            this.tpPos.Controls.Add(this.laCurTime);
            this.tpPos.Controls.Add(this.track);
            this.tpPos.Location = new System.Drawing.Point(4, 25);
            this.tpPos.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tpPos.Name = "tpPos";
            this.tpPos.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tpPos.Size = new System.Drawing.Size(743, 563);
            this.tpPos.TabIndex = 3;
            this.tpPos.Text = "Pos";
            this.tpPos.UseVisualStyleBackColor = true;
            // 
            // flPos
            // 
            this.flPos.Dock = System.Windows.Forms.DockStyle.Fill;
            this.flPos.Location = new System.Drawing.Point(3, 97);
            this.flPos.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.flPos.Name = "flPos";
            this.flPos.Size = new System.Drawing.Size(737, 464);
            this.flPos.TabIndex = 98;
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.btCopy);
            this.panel2.Controls.Add(this.label4);
            this.panel2.Controls.Add(this.btSave);
            this.panel2.Controls.Add(this.btLoad);
            this.panel2.Controls.Add(this.udkeyTime);
            this.panel2.Controls.Add(this.del);
            this.panel2.Controls.Add(this.add);
            this.panel2.Controls.Add(this.label3);
            this.panel2.Controls.Add(this.udTick);
            this.panel2.Controls.Add(this.udLoopTime);
            this.panel2.Controls.Add(this.label2);
            this.panel2.Controls.Add(this.udStep);
            this.panel2.Controls.Add(this.label10);
            this.panel2.Controls.Add(this.lbCurTime);
            this.panel2.Controls.Add(this.ckRun);
            this.panel2.Controls.Add(this.ckRunOnce);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel2.Location = new System.Drawing.Point(3, 41);
            this.panel2.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(737, 56);
            this.panel2.TabIndex = 99;
            // 
            // btCopy
            // 
            this.btCopy.AutoSize = true;
            this.btCopy.Location = new System.Drawing.Point(275, 25);
            this.btCopy.Margin = new System.Windows.Forms.Padding(4, 2, 4, 2);
            this.btCopy.Name = "btCopy";
            this.btCopy.Size = new System.Drawing.Size(56, 31);
            this.btCopy.TabIndex = 113;
            this.btCopy.Text = "&Clip";
            this.btCopy.UseVisualStyleBackColor = true;
            this.btCopy.Click += new System.EventHandler(this.btCopy_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(3, 31);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(38, 15);
            this.label4.TabIndex = 112;
            this.label4.Text = "Time";
            // 
            // btSave
            // 
            this.btSave.Location = new System.Drawing.Point(211, 25);
            this.btSave.Margin = new System.Windows.Forms.Padding(4, 2, 4, 2);
            this.btSave.Name = "btSave";
            this.btSave.Size = new System.Drawing.Size(56, 26);
            this.btSave.TabIndex = 110;
            this.btSave.Text = "&Save";
            this.btSave.UseVisualStyleBackColor = true;
            this.btSave.Click += new System.EventHandler(this.btSave_Click);
            // 
            // btLoad
            // 
            this.btLoad.Location = new System.Drawing.Point(151, 25);
            this.btLoad.Margin = new System.Windows.Forms.Padding(4, 2, 4, 2);
            this.btLoad.Name = "btLoad";
            this.btLoad.Size = new System.Drawing.Size(56, 26);
            this.btLoad.TabIndex = 109;
            this.btLoad.Text = "&Load";
            this.btLoad.UseVisualStyleBackColor = true;
            this.btLoad.Click += new System.EventHandler(this.btLoad_Click);
            // 
            // udkeyTime
            // 
            this.udkeyTime.Location = new System.Drawing.Point(40, 28);
            this.udkeyTime.Margin = new System.Windows.Forms.Padding(4, 2, 4, 2);
            this.udkeyTime.Name = "udkeyTime";
            this.udkeyTime.Size = new System.Drawing.Size(103, 22);
            this.udkeyTime.TabIndex = 111;
            // 
            // del
            // 
            this.del.Location = new System.Drawing.Point(391, 25);
            this.del.Margin = new System.Windows.Forms.Padding(4, 2, 4, 2);
            this.del.Name = "del";
            this.del.Size = new System.Drawing.Size(56, 26);
            this.del.TabIndex = 99;
            this.del.Text = "&Del";
            this.del.UseVisualStyleBackColor = true;
            this.del.Click += new System.EventHandler(this.del_Click);
            // 
            // add
            // 
            this.add.Location = new System.Drawing.Point(333, 25);
            this.add.Margin = new System.Windows.Forms.Padding(4, 2, 4, 2);
            this.add.Name = "add";
            this.add.Size = new System.Drawing.Size(56, 26);
            this.add.TabIndex = 98;
            this.add.Text = "&Add";
            this.add.UseVisualStyleBackColor = true;
            this.add.Click += new System.EventHandler(this.add_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(181, 2);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(25, 15);
            this.label3.TabIndex = 108;
            this.label3.Text = "ms";
            // 
            // udTick
            // 
            this.udTick.Location = new System.Drawing.Point(123, 0);
            this.udTick.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.udTick.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.udTick.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.udTick.Name = "udTick";
            this.udTick.Size = new System.Drawing.Size(59, 22);
            this.udTick.TabIndex = 107;
            this.udTick.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.udTick.ValueChanged += new System.EventHandler(this.udTick_ValueChanged);
            // 
            // udLoopTime
            // 
            this.udLoopTime.Location = new System.Drawing.Point(365, 0);
            this.udLoopTime.Margin = new System.Windows.Forms.Padding(4, 2, 4, 2);
            this.udLoopTime.Maximum = new decimal(new int[] {
            1000000,
            0,
            0,
            0});
            this.udLoopTime.Minimum = new decimal(new int[] {
            3,
            0,
            0,
            0});
            this.udLoopTime.Name = "udLoopTime";
            this.udLoopTime.Size = new System.Drawing.Size(80, 22);
            this.udLoopTime.TabIndex = 100;
            this.udLoopTime.Value = new decimal(new int[] {
            4000,
            0,
            0,
            0});
            this.udLoopTime.ValueChanged += new System.EventHandler(this.udLoopTime_ValueChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(355, 2);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(15, 15);
            this.label2.TabIndex = 106;
            this.label2.Text = "/";
            // 
            // udStep
            // 
            this.udStep.Location = new System.Drawing.Point(255, 0);
            this.udStep.Margin = new System.Windows.Forms.Padding(4, 2, 4, 2);
            this.udStep.Name = "udStep";
            this.udStep.Size = new System.Drawing.Size(40, 22);
            this.udStep.TabIndex = 104;
            this.udStep.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(208, 2);
            this.label10.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(46, 15);
            this.label10.TabIndex = 103;
            this.label10.Text = "Speed";
            // 
            // lbCurTime
            // 
            this.lbCurTime.Location = new System.Drawing.Point(309, 2);
            this.lbCurTime.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lbCurTime.Name = "lbCurTime";
            this.lbCurTime.Size = new System.Drawing.Size(45, 16);
            this.lbCurTime.TabIndex = 102;
            this.lbCurTime.Text = "0";
            this.lbCurTime.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // ckRun
            // 
            this.ckRun.AutoSize = true;
            this.ckRun.Location = new System.Drawing.Point(67, 2);
            this.ckRun.Margin = new System.Windows.Forms.Padding(4, 2, 4, 2);
            this.ckRun.Name = "ckRun";
            this.ckRun.Size = new System.Drawing.Size(51, 19);
            this.ckRun.TabIndex = 101;
            this.ckRun.Text = "R&un";
            this.ckRun.UseVisualStyleBackColor = true;
            // 
            // ckRunOnce
            // 
            this.ckRunOnce.AutoSize = true;
            this.ckRunOnce.Location = new System.Drawing.Point(4, 2);
            this.ckRunOnce.Margin = new System.Windows.Forms.Padding(4, 2, 4, 2);
            this.ckRunOnce.Name = "ckRunOnce";
            this.ckRunOnce.Size = new System.Drawing.Size(61, 19);
            this.ckRunOnce.TabIndex = 105;
            this.ckRunOnce.Text = "Once";
            this.ckRunOnce.UseVisualStyleBackColor = true;
            // 
            // laCurTime
            // 
            this.laCurTime.BackColor = System.Drawing.Color.Red;
            this.laCurTime.Location = new System.Drawing.Point(196, 35);
            this.laCurTime.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.laCurTime.Name = "laCurTime";
            this.laCurTime.Size = new System.Drawing.Size(4, 8);
            this.laCurTime.TabIndex = 13;
            // 
            // track
            // 
            this.track.AutoSize = false;
            this.track.Dock = System.Windows.Forms.DockStyle.Top;
            this.track.LargeChange = 20;
            this.track.Location = new System.Drawing.Point(3, 2);
            this.track.Margin = new System.Windows.Forms.Padding(0);
            this.track.Maximum = 10000;
            this.track.Name = "track";
            this.track.Size = new System.Drawing.Size(737, 39);
            this.track.TabIndex = 1;
            this.track.TickStyle = System.Windows.Forms.TickStyle.None;
            this.track.ValueChanged += new System.EventHandler(this.track_ValueChanged);
            // 
            // tpCurrent
            // 
            this.tpCurrent.Controls.Add(this.flCurrent);
            this.tpCurrent.Location = new System.Drawing.Point(4, 25);
            this.tpCurrent.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tpCurrent.Name = "tpCurrent";
            this.tpCurrent.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tpCurrent.Size = new System.Drawing.Size(743, 563);
            this.tpCurrent.TabIndex = 1;
            this.tpCurrent.Text = "Current";
            this.tpCurrent.UseVisualStyleBackColor = true;
            // 
            // flCurrent
            // 
            this.flCurrent.Dock = System.Windows.Forms.DockStyle.Fill;
            this.flCurrent.Location = new System.Drawing.Point(3, 2);
            this.flCurrent.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.flCurrent.Name = "flCurrent";
            this.flCurrent.Size = new System.Drawing.Size(737, 559);
            this.flCurrent.TabIndex = 0;
            // 
            // tpParam
            // 
            this.tpParam.Controls.Add(this.flParam);
            this.tpParam.Controls.Add(this.panel4);
            this.tpParam.Location = new System.Drawing.Point(4, 25);
            this.tpParam.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tpParam.Name = "tpParam";
            this.tpParam.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tpParam.Size = new System.Drawing.Size(743, 563);
            this.tpParam.TabIndex = 2;
            this.tpParam.Text = "Param";
            this.tpParam.UseVisualStyleBackColor = true;
            // 
            // flParam
            // 
            this.flParam.AutoScroll = true;
            this.flParam.Dock = System.Windows.Forms.DockStyle.Fill;
            this.flParam.ForeColor = System.Drawing.Color.CadetBlue;
            this.flParam.Location = new System.Drawing.Point(3, 31);
            this.flParam.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.flParam.Name = "flParam";
            this.flParam.Size = new System.Drawing.Size(737, 530);
            this.flParam.TabIndex = 0;
            // 
            // panel4
            // 
            this.panel4.Controls.Add(this.btLoadSpidar);
            this.panel4.Controls.Add(this.btLoadNuibot);
            this.panel4.Controls.Add(this.btRecvPd);
            this.panel4.Controls.Add(this.btSendPd);
            this.panel4.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel4.Location = new System.Drawing.Point(3, 2);
            this.panel4.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(737, 29);
            this.panel4.TabIndex = 3;
            // 
            // btLoadSpidar
            // 
            this.btLoadSpidar.Location = new System.Drawing.Point(615, 2);
            this.btLoadSpidar.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btLoadSpidar.Name = "btLoadSpidar";
            this.btLoadSpidar.Size = new System.Drawing.Size(119, 22);
            this.btLoadSpidar.TabIndex = 4;
            this.btLoadSpidar.Text = "Load SPIDAR";
            this.btLoadSpidar.UseVisualStyleBackColor = true;
            this.btLoadSpidar.Click += new System.EventHandler(this.btLoadSpidar_Click);
            // 
            // btLoadNuibot
            // 
            this.btLoadNuibot.Location = new System.Drawing.Point(497, 2);
            this.btLoadNuibot.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btLoadNuibot.Name = "btLoadNuibot";
            this.btLoadNuibot.Size = new System.Drawing.Size(112, 22);
            this.btLoadNuibot.TabIndex = 3;
            this.btLoadNuibot.Text = "Load Nuibot";
            this.btLoadNuibot.UseVisualStyleBackColor = true;
            this.btLoadNuibot.Click += new System.EventHandler(this.btLoadNuibot_Click);
            // 
            // btRecvPd
            // 
            this.btRecvPd.Location = new System.Drawing.Point(85, 2);
            this.btRecvPd.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btRecvPd.Name = "btRecvPd";
            this.btRecvPd.Size = new System.Drawing.Size(75, 22);
            this.btRecvPd.TabIndex = 2;
            this.btRecvPd.Text = "Receive";
            this.btRecvPd.UseVisualStyleBackColor = true;
            this.btRecvPd.Click += new System.EventHandler(this.btRecvPd_Click);
            // 
            // btSendPd
            // 
            this.btSendPd.Location = new System.Drawing.Point(5, 2);
            this.btSendPd.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btSendPd.Name = "btSendPd";
            this.btSendPd.Size = new System.Drawing.Size(75, 22);
            this.btSendPd.TabIndex = 1;
            this.btSendPd.Text = "Send";
            this.btSendPd.UseVisualStyleBackColor = true;
            this.btSendPd.Click += new System.EventHandler(this.btSendPd_Click);
            // 
            // tpHeat
            // 
            this.tpHeat.Controls.Add(this.flHeat);
            this.tpHeat.Controls.Add(this.panel5);
            this.tpHeat.Location = new System.Drawing.Point(4, 25);
            this.tpHeat.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tpHeat.Name = "tpHeat";
            this.tpHeat.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tpHeat.Size = new System.Drawing.Size(743, 563);
            this.tpHeat.TabIndex = 4;
            this.tpHeat.Text = "Heat";
            this.tpHeat.UseVisualStyleBackColor = true;
            // 
            // flHeat
            // 
            this.flHeat.Dock = System.Windows.Forms.DockStyle.Fill;
            this.flHeat.Location = new System.Drawing.Point(3, 34);
            this.flHeat.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.flHeat.Name = "flHeat";
            this.flHeat.Size = new System.Drawing.Size(737, 527);
            this.flHeat.TabIndex = 3;
            // 
            // panel5
            // 
            this.panel5.Controls.Add(this.btLoadSpidarHeat);
            this.panel5.Controls.Add(this.btLoadNubotiHeat);
            this.panel5.Controls.Add(this.btRecvHeat);
            this.panel5.Controls.Add(this.btSendHeat);
            this.panel5.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel5.Location = new System.Drawing.Point(3, 2);
            this.panel5.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.panel5.Name = "panel5";
            this.panel5.Size = new System.Drawing.Size(737, 32);
            this.panel5.TabIndex = 5;
            // 
            // btLoadSpidarHeat
            // 
            this.btLoadSpidarHeat.Location = new System.Drawing.Point(615, 6);
            this.btLoadSpidarHeat.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btLoadSpidarHeat.Name = "btLoadSpidarHeat";
            this.btLoadSpidarHeat.Size = new System.Drawing.Size(119, 22);
            this.btLoadSpidarHeat.TabIndex = 6;
            this.btLoadSpidarHeat.Text = "Load SPIDAR";
            this.btLoadSpidarHeat.UseVisualStyleBackColor = true;
            this.btLoadSpidarHeat.Click += new System.EventHandler(this.btLoadSpidarHeat_Click);
            // 
            // btLoadNubotiHeat
            // 
            this.btLoadNubotiHeat.Location = new System.Drawing.Point(497, 6);
            this.btLoadNubotiHeat.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btLoadNubotiHeat.Name = "btLoadNubotiHeat";
            this.btLoadNubotiHeat.Size = new System.Drawing.Size(112, 22);
            this.btLoadNubotiHeat.TabIndex = 5;
            this.btLoadNubotiHeat.Text = "Load Nuibot";
            this.btLoadNubotiHeat.UseVisualStyleBackColor = true;
            this.btLoadNubotiHeat.Click += new System.EventHandler(this.btLoadNubotiHeat_Click);
            // 
            // btRecvHeat
            // 
            this.btRecvHeat.Location = new System.Drawing.Point(87, 2);
            this.btRecvHeat.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btRecvHeat.Name = "btRecvHeat";
            this.btRecvHeat.Size = new System.Drawing.Size(75, 22);
            this.btRecvHeat.TabIndex = 4;
            this.btRecvHeat.Text = "Receive";
            this.btRecvHeat.UseVisualStyleBackColor = true;
            this.btRecvHeat.Click += new System.EventHandler(this.btRecvHeat_Click);
            // 
            // btSendHeat
            // 
            this.btSendHeat.Location = new System.Drawing.Point(5, 2);
            this.btSendHeat.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btSendHeat.Name = "btSendHeat";
            this.btSendHeat.Size = new System.Drawing.Size(75, 22);
            this.btSendHeat.TabIndex = 2;
            this.btSendHeat.Text = "Send";
            this.btSendHeat.UseVisualStyleBackColor = true;
            this.btSendHeat.Click += new System.EventHandler(this.btSendHeat_Click);
            // 
            // splitContainerTop
            // 
            this.splitContainerTop.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainerTop.Location = new System.Drawing.Point(0, 0);
            this.splitContainerTop.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.splitContainerTop.Name = "splitContainerTop";
            this.splitContainerTop.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainerTop.Panel1
            // 
            this.splitContainerTop.Panel1.Controls.Add(this.panel1);
            // 
            // splitContainerTop.Panel2
            // 
            this.splitContainerTop.Panel2.Controls.Add(this.splitContainerBottom);
            this.splitContainerTop.Size = new System.Drawing.Size(230, 592);
            this.splitContainerTop.SplitterDistance = 133;
            this.splitContainerTop.TabIndex = 4;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.btReset);
            this.panel1.Controls.Add(this.cmbPortBin);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Controls.Add(this.btListBoards);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(230, 133);
            this.panel1.TabIndex = 6;
            // 
            // btReset
            // 
            this.btReset.Location = new System.Drawing.Point(5, 81);
            this.btReset.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btReset.Name = "btReset";
            this.btReset.Size = new System.Drawing.Size(121, 22);
            this.btReset.TabIndex = 3;
            this.btReset.Text = "Reset Motor";
            this.btReset.UseVisualStyleBackColor = true;
            this.btReset.Click += new System.EventHandler(this.btReset_Click);
            // 
            // cmbPortBin
            // 
            this.cmbPortBin.FormattingEnabled = true;
            this.cmbPortBin.Location = new System.Drawing.Point(5, 22);
            this.cmbPortBin.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.cmbPortBin.Name = "cmbPortBin";
            this.cmbPortBin.Size = new System.Drawing.Size(121, 23);
            this.cmbPortBin.TabIndex = 0;
            this.cmbPortBin.DropDown += new System.EventHandler(this.cmbPortBin_DropDown);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(5, 6);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(82, 15);
            this.label1.TabIndex = 1;
            this.label1.Text = "UART port#";
            // 
            // btListBoards
            // 
            this.btListBoards.Location = new System.Drawing.Point(5, 52);
            this.btListBoards.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btListBoards.Name = "btListBoards";
            this.btListBoards.Size = new System.Drawing.Size(121, 22);
            this.btListBoards.TabIndex = 2;
            this.btListBoards.Text = "List boards";
            this.btListBoards.UseVisualStyleBackColor = true;
            this.btListBoards.Click += new System.EventHandler(this.btListBoards_Click);
            // 
            // splitContainerBottom
            // 
            this.splitContainerBottom.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainerBottom.Location = new System.Drawing.Point(0, 0);
            this.splitContainerBottom.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.splitContainerBottom.Name = "splitContainerBottom";
            this.splitContainerBottom.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainerBottom.Panel1
            // 
            this.splitContainerBottom.Panel1.Controls.Add(this.trBoards);
            // 
            // splitContainerBottom.Panel2
            // 
            this.splitContainerBottom.Panel2.Controls.Add(this.txMsg);
            this.splitContainerBottom.Size = new System.Drawing.Size(230, 455);
            this.splitContainerBottom.SplitterDistance = 207;
            this.splitContainerBottom.TabIndex = 5;
            // 
            // trBoards
            // 
            this.trBoards.Dock = System.Windows.Forms.DockStyle.Fill;
            this.trBoards.LabelEdit = true;
            this.trBoards.Location = new System.Drawing.Point(0, 0);
            this.trBoards.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.trBoards.Name = "trBoards";
            this.trBoards.Size = new System.Drawing.Size(230, 207);
            this.trBoards.TabIndex = 4;
            this.trBoards.BeforeLabelEdit += new System.Windows.Forms.NodeLabelEditEventHandler(this.trBoards_BeforeLabelEdit);
            this.trBoards.AfterLabelEdit += new System.Windows.Forms.NodeLabelEditEventHandler(this.trBoards_AfterLabelEdit);
            // 
            // txMsg
            // 
            this.txMsg.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txMsg.Location = new System.Drawing.Point(0, 0);
            this.txMsg.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.txMsg.Multiline = true;
            this.txMsg.Name = "txMsg";
            this.txMsg.ReadOnly = true;
            this.txMsg.Size = new System.Drawing.Size(230, 244);
            this.txMsg.TabIndex = 0;
            // 
            // A
            // 
            this.A.Font = new System.Drawing.Font("MS UI Gothic", 17F);
            this.A.Location = new System.Drawing.Point(56, 89);
            this.A.Name = "A";
            this.A.Size = new System.Drawing.Size(27, 28);
            this.A.TabIndex = 18;
            this.A.Text = "A";
            this.A.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label6
            // 
            this.label6.Font = new System.Drawing.Font("MS UI Gothic", 17F);
            this.label6.Location = new System.Drawing.Point(116, 89);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(27, 28);
            this.label6.TabIndex = 19;
            this.label6.Text = "B";
            this.label6.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label7
            // 
            this.label7.Font = new System.Drawing.Font("MS UI Gothic", 17F);
            this.label7.Location = new System.Drawing.Point(173, 89);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(27, 28);
            this.label7.TabIndex = 20;
            this.label7.Text = "C";
            this.label7.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label8
            // 
            this.label8.Font = new System.Drawing.Font("MS UI Gothic", 17F);
            this.label8.Location = new System.Drawing.Point(232, 89);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(27, 28);
            this.label8.TabIndex = 21;
            this.label8.Text = "D";
            this.label8.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label9
            // 
            this.label9.Font = new System.Drawing.Font("MS UI Gothic", 17F);
            this.label9.Location = new System.Drawing.Point(293, 89);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(27, 28);
            this.label9.TabIndex = 22;
            this.label9.Text = "E";
            this.label9.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label11
            // 
            this.label11.Font = new System.Drawing.Font("MS UI Gothic", 17F);
            this.label11.Location = new System.Drawing.Point(353, 89);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(27, 28);
            this.label11.TabIndex = 23;
            this.label11.Text = "F";
            this.label11.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label12
            // 
            this.label12.Font = new System.Drawing.Font("MS UI Gothic", 17F);
            this.label12.Location = new System.Drawing.Point(415, 89);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(27, 28);
            this.label12.TabIndex = 24;
            this.label12.Text = "G";
            this.label12.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label13
            // 
            this.label13.Font = new System.Drawing.Font("MS UI Gothic", 17F);
            this.label13.Location = new System.Drawing.Point(478, 89);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(27, 28);
            this.label13.TabIndex = 25;
            this.label13.Text = "H";
            this.label13.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label14
            // 
            this.label14.Font = new System.Drawing.Font("MS UI Gothic", 17F);
            this.label14.Location = new System.Drawing.Point(538, 89);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(27, 28);
            this.label14.TabIndex = 26;
            this.label14.Text = "I";
            this.label14.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label15
            // 
            this.label15.Font = new System.Drawing.Font("MS UI Gothic", 17F);
            this.label15.Location = new System.Drawing.Point(596, 89);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(27, 28);
            this.label15.TabIndex = 27;
            this.label15.Text = "J";
            this.label15.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label16
            // 
            this.label16.Font = new System.Drawing.Font("MS UI Gothic", 17F);
            this.label16.Location = new System.Drawing.Point(649, 89);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(27, 28);
            this.label16.TabIndex = 28;
            this.label16.Text = "K";
            this.label16.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(984, 592);
            this.Controls.Add(this.splitContainerHoriz);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "MainForm";
            this.Text = "PCController";
            this.splitContainerHoriz.Panel1.ResumeLayout(false);
            this.splitContainerHoriz.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainerHoriz)).EndInit();
            this.splitContainerHoriz.ResumeLayout(false);
            this.tbControl.ResumeLayout(false);
            this.tpMagnet.ResumeLayout(false);
            this.tpMagnet.PerformLayout();
            this.panel3.ResumeLayout(false);
            this.tpHaptic.ResumeLayout(false);
            this.tpHaptic.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.hapticTrackBar)).EndInit();
            this.flHaptic.ResumeLayout(false);
            this.flHaptic.PerformLayout();
            this.tpPos.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.udkeyTime)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udTick)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udLoopTime)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udStep)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.track)).EndInit();
            this.tpCurrent.ResumeLayout(false);
            this.tpParam.ResumeLayout(false);
            this.panel4.ResumeLayout(false);
            this.tpHeat.ResumeLayout(false);
            this.panel5.ResumeLayout(false);
            this.splitContainerTop.Panel1.ResumeLayout(false);
            this.splitContainerTop.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainerTop)).EndInit();
            this.splitContainerTop.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.splitContainerBottom.Panel1.ResumeLayout(false);
            this.splitContainerBottom.Panel2.ResumeLayout(false);
            this.splitContainerBottom.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainerBottom)).EndInit();
            this.splitContainerBottom.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion
        private System.IO.Ports.SerialPort uartBin;
        private System.Windows.Forms.Timer timer;
        private System.Windows.Forms.OpenFileDialog openPose;
        private System.Windows.Forms.SaveFileDialog savePose;
        private System.Windows.Forms.SplitContainer splitContainerHoriz;
        private System.Windows.Forms.SplitContainer splitContainerTop;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.ComboBox cmbPortBin;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btListBoards;
        private System.Windows.Forms.SplitContainer splitContainerBottom;
        private System.Windows.Forms.TreeView trBoards;
        private System.Windows.Forms.TextBox txMsg;
        private System.Windows.Forms.TabControl tbControl;
        private System.Windows.Forms.TabPage tpPos;
        private System.Windows.Forms.FlowLayoutPanel flPos;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Button btCopy;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button btSave;
        private System.Windows.Forms.Button btLoad;
        private System.Windows.Forms.NumericUpDown udkeyTime;
        private System.Windows.Forms.Button del;
        private System.Windows.Forms.Button add;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.NumericUpDown udTick;
        private System.Windows.Forms.NumericUpDown udLoopTime;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown udStep;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label lbCurTime;
        private System.Windows.Forms.CheckBox ckRun;
        private System.Windows.Forms.CheckBox ckRunOnce;
        private System.Windows.Forms.Label laCurTime;
        private System.Windows.Forms.TrackBar track;
        private System.Windows.Forms.TabPage tpCurrent;
        private System.Windows.Forms.FlowLayoutPanel flCurrent;
        private System.Windows.Forms.TabPage tpParam;
        private System.Windows.Forms.Button btRecvPd;
        private System.Windows.Forms.Button btSendPd;
        private System.Windows.Forms.FlowLayoutPanel flParam;
        private System.Windows.Forms.TabPage tpHeat;
        private System.Windows.Forms.Button btRecvHeat;
        private System.Windows.Forms.Button btSendHeat;
        private System.Windows.Forms.FlowLayoutPanel flHeat;
        private System.Windows.Forms.TabPage tpMagnet;
        private System.Windows.Forms.Button btMeasure;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Panel panel5;
        private System.Windows.Forms.Panel panel4;
        private System.Windows.Forms.Button btLoadSpidar;
        private System.Windows.Forms.Button btLoadNuibot;
        private System.Windows.Forms.Panel pnMagnet;
        private System.Windows.Forms.TabPage tpHaptic;
        private System.Windows.Forms.FlowLayoutPanel flHaptic;
        private System.Windows.Forms.Button btReset;
        private System.Windows.Forms.Button btLoadSpidarHeat;
        private System.Windows.Forms.Button btLoadNubotiHeat;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TrackBar hapticTrackBar;
        private System.Windows.Forms.Button btStart;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textBox0;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.TextBox textBox4;
        private System.Windows.Forms.TextBox textBox5;
        private System.Windows.Forms.TextBox textBox6;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label A;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
    }
}

