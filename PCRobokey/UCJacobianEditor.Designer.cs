namespace Robokey
{
    partial class UCJacobianEditor
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.picForce = new System.Windows.Forms.PictureBox();
            this.udMotorZ = new System.Windows.Forms.NumericUpDown();
            this.udMotorY = new System.Windows.Forms.NumericUpDown();
            this.udMotorX = new System.Windows.Forms.NumericUpDown();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.flMotor = new System.Windows.Forms.FlowLayoutPanel();
            this.label5 = new System.Windows.Forms.Label();
            this.picPos = new System.Windows.Forms.PictureBox();
            this.pnLeft = new System.Windows.Forms.Panel();
            this.udFScale = new System.Windows.Forms.NumericUpDown();
            this.pnCtrls = new System.Windows.Forms.Panel();
            this.udMScale = new System.Windows.Forms.NumericUpDown();
            this.btLoad = new System.Windows.Forms.Button();
            this.btSave = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.saveDlg = new System.Windows.Forms.SaveFileDialog();
            this.loadDlg = new System.Windows.Forms.OpenFileDialog();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.picForce)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udMotorZ)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udMotorY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udMotorX)).BeginInit();
            this.flMotor.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picPos)).BeginInit();
            this.pnLeft.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.udFScale)).BeginInit();
            this.pnCtrls.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.udMScale)).BeginInit();
            this.SuspendLayout();
            // 
            // picForce
            // 
            this.picForce.Dock = System.Windows.Forms.DockStyle.Fill;
            this.picForce.Location = new System.Drawing.Point(0, 58);
            this.picForce.Margin = new System.Windows.Forms.Padding(2);
            this.picForce.Name = "picForce";
            this.picForce.Size = new System.Drawing.Size(254, 285);
            this.picForce.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.picForce.TabIndex = 0;
            this.picForce.TabStop = false;
            this.picForce.Paint += new System.Windows.Forms.PaintEventHandler(this.picForce_Paint);
            this.picForce.MouseDown += new System.Windows.Forms.MouseEventHandler(this.picForce_MouseDown);
            this.picForce.MouseMove += new System.Windows.Forms.MouseEventHandler(this.picForce_MouseMove);
            // 
            // udMotorZ
            // 
            this.udMotorZ.Location = new System.Drawing.Point(212, 4);
            this.udMotorZ.Margin = new System.Windows.Forms.Padding(2);
            this.udMotorZ.Name = "udMotorZ";
            this.udMotorZ.Size = new System.Drawing.Size(42, 22);
            this.udMotorZ.TabIndex = 9;
            // 
            // udMotorY
            // 
            this.udMotorY.Location = new System.Drawing.Point(149, 4);
            this.udMotorY.Margin = new System.Windows.Forms.Padding(2);
            this.udMotorY.Name = "udMotorY";
            this.udMotorY.Size = new System.Drawing.Size(42, 22);
            this.udMotorY.TabIndex = 8;
            // 
            // udMotorX
            // 
            this.udMotorX.Location = new System.Drawing.Point(82, 4);
            this.udMotorX.Margin = new System.Windows.Forms.Padding(2);
            this.udMotorX.Name = "udMotorX";
            this.udMotorX.Size = new System.Drawing.Size(42, 22);
            this.udMotorX.TabIndex = 7;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.ForeColor = System.Drawing.Color.Blue;
            this.label3.Location = new System.Drawing.Point(193, 7);
            this.label3.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(18, 15);
            this.label3.TabIndex = 3;
            this.label3.Text = "3:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.ForeColor = System.Drawing.Color.Green;
            this.label2.Location = new System.Drawing.Point(129, 7);
            this.label2.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(18, 15);
            this.label2.TabIndex = 2;
            this.label2.Text = "2:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ForeColor = System.Drawing.Color.Red;
            this.label1.Location = new System.Drawing.Point(62, 7);
            this.label1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(18, 15);
            this.label1.TabIndex = 1;
            this.label1.Text = "1:";
            // 
            // flMotor
            // 
            this.flMotor.AutoSize = true;
            this.flMotor.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.flMotor.Controls.Add(this.label5);
            this.flMotor.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.flMotor.Location = new System.Drawing.Point(0, 343);
            this.flMotor.MinimumSize = new System.Drawing.Size(0, 20);
            this.flMotor.Name = "flMotor";
            this.flMotor.Size = new System.Drawing.Size(254, 20);
            this.flMotor.TabIndex = 2;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(3, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(31, 15);
            this.label5.TabIndex = 0;
            this.label5.Text = "Pos";
            // 
            // picPos
            // 
            this.picPos.Dock = System.Windows.Forms.DockStyle.Right;
            this.picPos.Location = new System.Drawing.Point(254, 0);
            this.picPos.Name = "picPos";
            this.picPos.Size = new System.Drawing.Size(118, 363);
            this.picPos.TabIndex = 3;
            this.picPos.TabStop = false;
            this.picPos.Click += new System.EventHandler(this.picPos_Click);
            this.picPos.Paint += new System.Windows.Forms.PaintEventHandler(this.picPos_Paint);
            this.picPos.MouseDown += new System.Windows.Forms.MouseEventHandler(this.picPos_MouseDown);
            this.picPos.MouseMove += new System.Windows.Forms.MouseEventHandler(this.picPos_MouseMove);
            // 
            // pnLeft
            // 
            this.pnLeft.Controls.Add(this.label7);
            this.pnLeft.Controls.Add(this.udFScale);
            this.pnLeft.Controls.Add(this.picForce);
            this.pnLeft.Controls.Add(this.pnCtrls);
            this.pnLeft.Controls.Add(this.flMotor);
            this.pnLeft.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnLeft.Location = new System.Drawing.Point(0, 0);
            this.pnLeft.Name = "pnLeft";
            this.pnLeft.Size = new System.Drawing.Size(254, 363);
            this.pnLeft.TabIndex = 4;
            // 
            // udFScale
            // 
            this.udFScale.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.udFScale.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.udFScale.Location = new System.Drawing.Point(178, 64);
            this.udFScale.Margin = new System.Windows.Forms.Padding(2);
            this.udFScale.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.udFScale.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.udFScale.Name = "udFScale";
            this.udFScale.Size = new System.Drawing.Size(74, 22);
            this.udFScale.TabIndex = 14;
            this.udFScale.Value = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            // 
            // pnCtrls
            // 
            this.pnCtrls.AutoSize = true;
            this.pnCtrls.Controls.Add(this.label6);
            this.pnCtrls.Controls.Add(this.udMScale);
            this.pnCtrls.Controls.Add(this.btLoad);
            this.pnCtrls.Controls.Add(this.btSave);
            this.pnCtrls.Controls.Add(this.label4);
            this.pnCtrls.Controls.Add(this.udMotorZ);
            this.pnCtrls.Controls.Add(this.udMotorY);
            this.pnCtrls.Controls.Add(this.label1);
            this.pnCtrls.Controls.Add(this.udMotorX);
            this.pnCtrls.Controls.Add(this.label2);
            this.pnCtrls.Controls.Add(this.label3);
            this.pnCtrls.Dock = System.Windows.Forms.DockStyle.Top;
            this.pnCtrls.Location = new System.Drawing.Point(0, 0);
            this.pnCtrls.Name = "pnCtrls";
            this.pnCtrls.Size = new System.Drawing.Size(254, 58);
            this.pnCtrls.TabIndex = 3;
            // 
            // udMScale
            // 
            this.udMScale.Increment = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.udMScale.Location = new System.Drawing.Point(47, 32);
            this.udMScale.Margin = new System.Windows.Forms.Padding(2);
            this.udMScale.Maximum = new decimal(new int[] {
            100000,
            0,
            0,
            0});
            this.udMScale.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.udMScale.Name = "udMScale";
            this.udMScale.Size = new System.Drawing.Size(74, 22);
            this.udMScale.TabIndex = 13;
            this.udMScale.Value = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            // 
            // btLoad
            // 
            this.btLoad.Location = new System.Drawing.Point(127, 32);
            this.btLoad.Name = "btLoad";
            this.btLoad.Size = new System.Drawing.Size(52, 23);
            this.btLoad.TabIndex = 12;
            this.btLoad.Text = "&Load";
            this.btLoad.UseVisualStyleBackColor = true;
            this.btLoad.Click += new System.EventHandler(this.btLoad_Click);
            // 
            // btSave
            // 
            this.btSave.Location = new System.Drawing.Point(185, 32);
            this.btSave.Name = "btSave";
            this.btSave.Size = new System.Drawing.Size(52, 23);
            this.btSave.TabIndex = 11;
            this.btSave.Text = "&Save";
            this.btSave.UseVisualStyleBackColor = true;
            this.btSave.Click += new System.EventHandler(this.btSave_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(0, 7);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(52, 15);
            this.label4.TabIndex = 10;
            this.label4.Text = "Motor#";
            // 
            // saveDlg
            // 
            this.saveDlg.DefaultExt = "txt";
            this.saveDlg.FileName = "forces.txt";
            this.saveDlg.FileOk += new System.ComponentModel.CancelEventHandler(this.saveDlg_FileOk);
            // 
            // loadDlg
            // 
            this.loadDlg.DefaultExt = "txt";
            this.loadDlg.FileName = "forces.txt";
            this.loadDlg.FileOk += new System.ComponentModel.CancelEventHandler(this.loadDlg_FileOk);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(3, 36);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(42, 15);
            this.label6.TabIndex = 14;
            this.label6.Text = "Scale";
            // 
            // label7
            // 
            this.label7.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(133, 66);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(42, 15);
            this.label7.TabIndex = 15;
            this.label7.Text = "Scale";
            // 
            // UCJacobianEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.pnLeft);
            this.Controls.Add(this.picPos);
            this.Margin = new System.Windows.Forms.Padding(2);
            this.Name = "UCJacobianEditor";
            this.Size = new System.Drawing.Size(372, 363);
            this.Load += new System.EventHandler(this.UCJacobianEditor_Load);
            this.Resize += new System.EventHandler(this.UCJacobianEditor_Resize);
            ((System.ComponentModel.ISupportInitialize)(this.picForce)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udMotorZ)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udMotorY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udMotorX)).EndInit();
            this.flMotor.ResumeLayout(false);
            this.flMotor.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picPos)).EndInit();
            this.pnLeft.ResumeLayout(false);
            this.pnLeft.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.udFScale)).EndInit();
            this.pnCtrls.ResumeLayout(false);
            this.pnCtrls.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.udMScale)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox picForce;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown udMotorZ;
        private System.Windows.Forms.NumericUpDown udMotorY;
        private System.Windows.Forms.NumericUpDown udMotorX;
        private System.Windows.Forms.FlowLayoutPanel flMotor;
        private System.Windows.Forms.Panel pnLeft;
        private System.Windows.Forms.Panel pnCtrls;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        public System.Windows.Forms.PictureBox picPos;
        private System.Windows.Forms.Button btLoad;
        private System.Windows.Forms.Button btSave;
        private System.Windows.Forms.SaveFileDialog saveDlg;
        private System.Windows.Forms.OpenFileDialog loadDlg;
        private System.Windows.Forms.NumericUpDown udMScale;
        private System.Windows.Forms.NumericUpDown udFScale;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
    }
}
