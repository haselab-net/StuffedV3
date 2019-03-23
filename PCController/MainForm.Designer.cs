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
            this.tbControl = new System.Windows.Forms.TabControl();
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
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.panel1 = new System.Windows.Forms.Panel();
            this.cmbPortBin = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.btListBoards = new System.Windows.Forms.Button();
            this.trBoards = new System.Windows.Forms.TreeView();
            this.openPose = new System.Windows.Forms.OpenFileDialog();
            this.savePose = new System.Windows.Forms.SaveFileDialog();
            this.tbControl.SuspendLayout();
            this.tpPos.SuspendLayout();
            this.panel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.udkeyTime)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udTick)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udLoopTime)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udStep)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.track)).BeginInit();
            this.tpCurrent.SuspendLayout();
            this.tpParam.SuspendLayout();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // uartBin
            // 
            this.uartBin.BaudRate = 2000000;
            // 
            // tbControl
            // 
            this.tbControl.Controls.Add(this.tpPos);
            this.tbControl.Controls.Add(this.tpCurrent);
            this.tbControl.Controls.Add(this.tpParam);
            this.tbControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tbControl.Location = new System.Drawing.Point(0, 0);
            this.tbControl.Name = "tbControl";
            this.tbControl.SelectedIndex = 0;
            this.tbControl.Size = new System.Drawing.Size(463, 464);
            this.tbControl.TabIndex = 4;
            // 
            // tpPos
            // 
            this.tpPos.Controls.Add(this.flPos);
            this.tpPos.Controls.Add(this.panel2);
            this.tpPos.Controls.Add(this.laCurTime);
            this.tpPos.Controls.Add(this.track);
            this.tpPos.Location = new System.Drawing.Point(4, 25);
            this.tpPos.Name = "tpPos";
            this.tpPos.Padding = new System.Windows.Forms.Padding(3);
            this.tpPos.Size = new System.Drawing.Size(455, 435);
            this.tpPos.TabIndex = 3;
            this.tpPos.Text = "Pos";
            this.tpPos.UseVisualStyleBackColor = true;
            // 
            // flPos
            // 
            this.flPos.Dock = System.Windows.Forms.DockStyle.Fill;
            this.flPos.Location = new System.Drawing.Point(3, 98);
            this.flPos.Name = "flPos";
            this.flPos.Size = new System.Drawing.Size(449, 334);
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
            this.panel2.Location = new System.Drawing.Point(3, 42);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(449, 56);
            this.panel2.TabIndex = 99;
            // 
            // btCopy
            // 
            this.btCopy.AutoSize = true;
            this.btCopy.Location = new System.Drawing.Point(271, 25);
            this.btCopy.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.btCopy.Name = "btCopy";
            this.btCopy.Size = new System.Drawing.Size(56, 26);
            this.btCopy.TabIndex = 113;
            this.btCopy.Text = "&Copy";
            this.btCopy.UseVisualStyleBackColor = true;
            this.btCopy.Click += new System.EventHandler(this.btCopy_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(2, 31);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(38, 15);
            this.label4.TabIndex = 112;
            this.label4.Text = "Time";
            // 
            // btSave
            // 
            this.btSave.Location = new System.Drawing.Point(211, 25);
            this.btSave.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
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
            this.btLoad.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.btLoad.Name = "btLoad";
            this.btLoad.Size = new System.Drawing.Size(56, 26);
            this.btLoad.TabIndex = 109;
            this.btLoad.Text = "&Load";
            this.btLoad.UseVisualStyleBackColor = true;
            this.btLoad.Click += new System.EventHandler(this.btLoad_Click);
            // 
            // udkeyTime
            // 
            this.udkeyTime.Location = new System.Drawing.Point(40, 27);
            this.udkeyTime.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.udkeyTime.Name = "udkeyTime";
            this.udkeyTime.Size = new System.Drawing.Size(103, 22);
            this.udkeyTime.TabIndex = 111;
            // 
            // del
            // 
            this.del.Location = new System.Drawing.Point(391, 25);
            this.del.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.del.Name = "del";
            this.del.Size = new System.Drawing.Size(56, 26);
            this.del.TabIndex = 99;
            this.del.Text = "&Del";
            this.del.UseVisualStyleBackColor = true;
            this.del.Click += new System.EventHandler(this.del_Click);
            // 
            // add
            // 
            this.add.Location = new System.Drawing.Point(331, 25);
            this.add.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
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
            this.label3.Location = new System.Drawing.Point(181, 3);
            this.label3.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(25, 15);
            this.label3.TabIndex = 108;
            this.label3.Text = "ms";
            // 
            // udTick
            // 
            this.udTick.Location = new System.Drawing.Point(122, 0);
            this.udTick.Margin = new System.Windows.Forms.Padding(2);
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
            this.udTick.Size = new System.Drawing.Size(58, 22);
            this.udTick.TabIndex = 107;
            this.udTick.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            // 
            // udLoopTime
            // 
            this.udLoopTime.Location = new System.Drawing.Point(366, 0);
            this.udLoopTime.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
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
            this.label2.Location = new System.Drawing.Point(354, 3);
            this.label2.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(15, 15);
            this.label2.TabIndex = 106;
            this.label2.Text = "/";
            // 
            // udStep
            // 
            this.udStep.Location = new System.Drawing.Point(255, 0);
            this.udStep.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
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
            this.label10.Location = new System.Drawing.Point(208, 3);
            this.label10.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(46, 15);
            this.label10.TabIndex = 103;
            this.label10.Text = "Speed";
            // 
            // lbCurTime
            // 
            this.lbCurTime.Location = new System.Drawing.Point(310, 2);
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
            this.ckRun.Location = new System.Drawing.Point(66, 3);
            this.ckRun.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.ckRun.Name = "ckRun";
            this.ckRun.Size = new System.Drawing.Size(54, 19);
            this.ckRun.TabIndex = 101;
            this.ckRun.Text = "R&un";
            this.ckRun.UseVisualStyleBackColor = true;
            // 
            // ckRunOnce
            // 
            this.ckRunOnce.AutoSize = true;
            this.ckRunOnce.Location = new System.Drawing.Point(4, 3);
            this.ckRunOnce.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.ckRunOnce.Name = "ckRunOnce";
            this.ckRunOnce.Size = new System.Drawing.Size(64, 19);
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
            this.laCurTime.Size = new System.Drawing.Size(4, 7);
            this.laCurTime.TabIndex = 13;
            // 
            // track
            // 
            this.track.AutoSize = false;
            this.track.Dock = System.Windows.Forms.DockStyle.Top;
            this.track.LargeChange = 20;
            this.track.Location = new System.Drawing.Point(3, 3);
            this.track.Margin = new System.Windows.Forms.Padding(0);
            this.track.Maximum = 10000;
            this.track.Name = "track";
            this.track.Size = new System.Drawing.Size(449, 39);
            this.track.TabIndex = 1;
            this.track.TickStyle = System.Windows.Forms.TickStyle.None;
            this.track.ValueChanged += new System.EventHandler(this.track_ValueChanged);
            // 
            // tpCurrent
            // 
            this.tpCurrent.Controls.Add(this.flCurrent);
            this.tpCurrent.Location = new System.Drawing.Point(4, 25);
            this.tpCurrent.Name = "tpCurrent";
            this.tpCurrent.Padding = new System.Windows.Forms.Padding(3);
            this.tpCurrent.Size = new System.Drawing.Size(455, 435);
            this.tpCurrent.TabIndex = 1;
            this.tpCurrent.Text = "Current";
            this.tpCurrent.UseVisualStyleBackColor = true;
            // 
            // flCurrent
            // 
            this.flCurrent.Dock = System.Windows.Forms.DockStyle.Fill;
            this.flCurrent.Location = new System.Drawing.Point(3, 3);
            this.flCurrent.Name = "flCurrent";
            this.flCurrent.Size = new System.Drawing.Size(449, 429);
            this.flCurrent.TabIndex = 0;
            // 
            // tpParam
            // 
            this.tpParam.Controls.Add(this.flParam);
            this.tpParam.Location = new System.Drawing.Point(4, 25);
            this.tpParam.Name = "tpParam";
            this.tpParam.Padding = new System.Windows.Forms.Padding(3);
            this.tpParam.Size = new System.Drawing.Size(455, 435);
            this.tpParam.TabIndex = 2;
            this.tpParam.Text = "Param";
            this.tpParam.UseVisualStyleBackColor = true;
            // 
            // flParam
            // 
            this.flParam.Dock = System.Windows.Forms.DockStyle.Fill;
            this.flParam.Location = new System.Drawing.Point(3, 3);
            this.flParam.Name = "flParam";
            this.flParam.Size = new System.Drawing.Size(449, 429);
            this.flParam.TabIndex = 0;
            // 
            // timer
            // 
            this.timer.Enabled = true;
            this.timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Right;
            this.splitContainer1.Location = new System.Drawing.Point(463, 0);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.panel1);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.trBoards);
            this.splitContainer1.Size = new System.Drawing.Size(127, 464);
            this.splitContainer1.SplitterDistance = 232;
            this.splitContainer1.TabIndex = 3;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.cmbPortBin);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Controls.Add(this.btListBoards);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(127, 232);
            this.panel1.TabIndex = 6;
            // 
            // cmbPortBin
            // 
            this.cmbPortBin.FormattingEnabled = true;
            this.cmbPortBin.Location = new System.Drawing.Point(3, 25);
            this.cmbPortBin.Name = "cmbPortBin";
            this.cmbPortBin.Size = new System.Drawing.Size(121, 23);
            this.cmbPortBin.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 7);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(82, 15);
            this.label1.TabIndex = 1;
            this.label1.Text = "UART port#";
            // 
            // btListBoards
            // 
            this.btListBoards.Location = new System.Drawing.Point(3, 55);
            this.btListBoards.Name = "btListBoards";
            this.btListBoards.Size = new System.Drawing.Size(121, 23);
            this.btListBoards.TabIndex = 2;
            this.btListBoards.Text = "List boards";
            this.btListBoards.UseVisualStyleBackColor = true;
            this.btListBoards.Click += new System.EventHandler(this.btListBoards_Click);
            // 
            // trBoards
            // 
            this.trBoards.Dock = System.Windows.Forms.DockStyle.Fill;
            this.trBoards.LabelEdit = true;
            this.trBoards.Location = new System.Drawing.Point(0, 0);
            this.trBoards.Name = "trBoards";
            this.trBoards.Size = new System.Drawing.Size(127, 228);
            this.trBoards.TabIndex = 4;
            this.trBoards.BeforeLabelEdit += new System.Windows.Forms.NodeLabelEditEventHandler(this.trBoards_BeforeLabelEdit);
            this.trBoards.AfterLabelEdit += new System.Windows.Forms.NodeLabelEditEventHandler(this.trBoards_AfterLabelEdit);
            // 
            // openPose
            // 
            this.openPose.FileName = "pose.txt";
            this.openPose.Filter = "姿勢ファイル|*.txt|姿勢CSV|*.csv|すべてのファイル|*.*";
            // 
            // savePose
            // 
            this.savePose.DefaultExt = "txt";
            this.savePose.FileName = "pose.txt";
            this.savePose.Filter = "姿勢ファイル|*.txt|姿勢ファイル(csv)|*.csv|すべてのファイル|*.*";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(590, 464);
            this.Controls.Add(this.tbControl);
            this.Controls.Add(this.splitContainer1);
            this.Name = "MainForm";
            this.Text = "PCController";
            this.tbControl.ResumeLayout(false);
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
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.IO.Ports.SerialPort uartBin;
        private System.Windows.Forms.TabControl tbControl;
        private System.Windows.Forms.TabPage tpCurrent;
        private System.Windows.Forms.FlowLayoutPanel flCurrent;
        private System.Windows.Forms.Timer timer;
        private System.Windows.Forms.TabPage tpParam;
        private System.Windows.Forms.FlowLayoutPanel flParam;
        private System.Windows.Forms.TabPage tpPos;
        private System.Windows.Forms.Label laCurTime;
        private System.Windows.Forms.TrackBar track;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.ComboBox cmbPortBin;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btListBoards;
        private System.Windows.Forms.TreeView trBoards;
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
        private System.Windows.Forms.OpenFileDialog openPose;
        private System.Windows.Forms.SaveFileDialog savePose;
    }
}

