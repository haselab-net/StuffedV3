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
            this.picLeft = new System.Windows.Forms.PictureBox();
            this.pnForce = new System.Windows.Forms.Panel();
            this.numericUpDown4 = new System.Windows.Forms.NumericUpDown();
            this.numericUpDown5 = new System.Windows.Forms.NumericUpDown();
            this.numericUpDown6 = new System.Windows.Forms.NumericUpDown();
            this.numericUpDown3 = new System.Windows.Forms.NumericUpDown();
            this.numericUpDown2 = new System.Windows.Forms.NumericUpDown();
            this.numericUpDown1 = new System.Windows.Forms.NumericUpDown();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.lbWire = new System.Windows.Forms.Label();
            this.picRight = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.picLeft)).BeginInit();
            this.pnForce.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown5)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown6)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picRight)).BeginInit();
            this.SuspendLayout();
            // 
            // picLeft
            // 
            this.picLeft.Dock = System.Windows.Forms.DockStyle.Left;
            this.picLeft.Location = new System.Drawing.Point(0, 117);
            this.picLeft.Name = "picLeft";
            this.picLeft.Size = new System.Drawing.Size(215, 319);
            this.picLeft.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.picLeft.TabIndex = 0;
            this.picLeft.TabStop = false;
            this.picLeft.Paint += new System.Windows.Forms.PaintEventHandler(this.pic_Paint);
            // 
            // pnForce
            // 
            this.pnForce.Controls.Add(this.numericUpDown4);
            this.pnForce.Controls.Add(this.numericUpDown5);
            this.pnForce.Controls.Add(this.numericUpDown6);
            this.pnForce.Controls.Add(this.numericUpDown3);
            this.pnForce.Controls.Add(this.numericUpDown2);
            this.pnForce.Controls.Add(this.numericUpDown1);
            this.pnForce.Controls.Add(this.label3);
            this.pnForce.Controls.Add(this.label2);
            this.pnForce.Controls.Add(this.label1);
            this.pnForce.Controls.Add(this.lbWire);
            this.pnForce.Dock = System.Windows.Forms.DockStyle.Top;
            this.pnForce.Location = new System.Drawing.Point(0, 0);
            this.pnForce.Name = "pnForce";
            this.pnForce.Size = new System.Drawing.Size(465, 117);
            this.pnForce.TabIndex = 1;
            this.pnForce.Paint += new System.Windows.Forms.PaintEventHandler(this.pnForce_Paint);
            // 
            // numericUpDown4
            // 
            this.numericUpDown4.Location = new System.Drawing.Point(118, 87);
            this.numericUpDown4.Name = "numericUpDown4";
            this.numericUpDown4.Size = new System.Drawing.Size(78, 25);
            this.numericUpDown4.TabIndex = 9;
            // 
            // numericUpDown5
            // 
            this.numericUpDown5.Location = new System.Drawing.Point(118, 56);
            this.numericUpDown5.Name = "numericUpDown5";
            this.numericUpDown5.Size = new System.Drawing.Size(78, 25);
            this.numericUpDown5.TabIndex = 8;
            // 
            // numericUpDown6
            // 
            this.numericUpDown6.Location = new System.Drawing.Point(118, 25);
            this.numericUpDown6.Name = "numericUpDown6";
            this.numericUpDown6.Size = new System.Drawing.Size(78, 25);
            this.numericUpDown6.TabIndex = 7;
            // 
            // numericUpDown3
            // 
            this.numericUpDown3.Location = new System.Drawing.Point(34, 88);
            this.numericUpDown3.Name = "numericUpDown3";
            this.numericUpDown3.Size = new System.Drawing.Size(78, 25);
            this.numericUpDown3.TabIndex = 6;
            // 
            // numericUpDown2
            // 
            this.numericUpDown2.Location = new System.Drawing.Point(34, 57);
            this.numericUpDown2.Name = "numericUpDown2";
            this.numericUpDown2.Size = new System.Drawing.Size(78, 25);
            this.numericUpDown2.TabIndex = 5;
            // 
            // numericUpDown1
            // 
            this.numericUpDown1.Location = new System.Drawing.Point(34, 26);
            this.numericUpDown1.Name = "numericUpDown1";
            this.numericUpDown1.Size = new System.Drawing.Size(78, 25);
            this.numericUpDown1.TabIndex = 4;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.ForeColor = System.Drawing.Color.Blue;
            this.label3.Location = new System.Drawing.Point(7, 90);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(21, 18);
            this.label3.TabIndex = 3;
            this.label3.Text = "3:";
            this.label3.Click += new System.EventHandler(this.label3_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.ForeColor = System.Drawing.Color.Green;
            this.label2.Location = new System.Drawing.Point(7, 59);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(21, 18);
            this.label2.TabIndex = 2;
            this.label2.Text = "2:";
            this.label2.Click += new System.EventHandler(this.label2_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ForeColor = System.Drawing.Color.Red;
            this.label1.Location = new System.Drawing.Point(7, 28);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(21, 18);
            this.label1.TabIndex = 1;
            this.label1.Text = "1:";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // lbWire
            // 
            this.lbWire.AutoSize = true;
            this.lbWire.Location = new System.Drawing.Point(4, 4);
            this.lbWire.Name = "lbWire";
            this.lbWire.Size = new System.Drawing.Size(180, 18);
            this.lbWire.TabIndex = 0;
            this.lbWire.Text = "Wire Angle      Motor ID";
            this.lbWire.Click += new System.EventHandler(this.lbWire_Click);
            // 
            // picRight
            // 
            this.picRight.Dock = System.Windows.Forms.DockStyle.Right;
            this.picRight.Location = new System.Drawing.Point(250, 117);
            this.picRight.Name = "picRight";
            this.picRight.Size = new System.Drawing.Size(215, 319);
            this.picRight.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.picRight.TabIndex = 2;
            this.picRight.TabStop = false;
            // 
            // UCJacobianEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(10F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.picRight);
            this.Controls.Add(this.picLeft);
            this.Controls.Add(this.pnForce);
            this.Name = "UCJacobianEditor";
            this.Size = new System.Drawing.Size(465, 436);
            this.Load += new System.EventHandler(this.UCJacobianEditor_Load);
            this.Resize += new System.EventHandler(this.UCJacobianEditor_Resize);
            ((System.ComponentModel.ISupportInitialize)(this.picLeft)).EndInit();
            this.pnForce.ResumeLayout(false);
            this.pnForce.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown5)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown6)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picRight)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox picLeft;
        private System.Windows.Forms.Panel pnForce;
        private System.Windows.Forms.Label lbWire;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown numericUpDown3;
        private System.Windows.Forms.NumericUpDown numericUpDown2;
        private System.Windows.Forms.NumericUpDown numericUpDown1;
        private System.Windows.Forms.NumericUpDown numericUpDown4;
        private System.Windows.Forms.NumericUpDown numericUpDown5;
        private System.Windows.Forms.NumericUpDown numericUpDown6;
        private System.Windows.Forms.PictureBox picRight;
    }
}
