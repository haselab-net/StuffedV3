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
            this.cmbPortBin = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.btListBoards = new System.Windows.Forms.Button();
            this.trBoards = new System.Windows.Forms.TreeView();
            this.tbControl = new System.Windows.Forms.TabControl();
            this.tpCurrent = new System.Windows.Forms.TabPage();
            this.flCurrent = new System.Windows.Forms.FlowLayoutPanel();
            this.panel1 = new System.Windows.Forms.Panel();
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.tpParam = new System.Windows.Forms.TabPage();
            this.flParam = new System.Windows.Forms.FlowLayoutPanel();
            this.tbControl.SuspendLayout();
            this.tpCurrent.SuspendLayout();
            this.panel1.SuspendLayout();
            this.tpParam.SuspendLayout();
            this.SuspendLayout();
            // 
            // uartBin
            // 
            this.uartBin.BaudRate = 2000000;
            // 
            // cmbPortBin
            // 
            this.cmbPortBin.FormattingEnabled = true;
            this.cmbPortBin.Location = new System.Drawing.Point(3, 25);
            this.cmbPortBin.Name = "cmbPortBin";
            this.cmbPortBin.Size = new System.Drawing.Size(121, 23);
            this.cmbPortBin.TabIndex = 0;
            this.cmbPortBin.TextChanged += new System.EventHandler(this.cmbPortBin_TextChanged);
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
            this.trBoards.Location = new System.Drawing.Point(405, 0);
            this.trBoards.Name = "trBoards";
            this.trBoards.Size = new System.Drawing.Size(153, 376);
            this.trBoards.TabIndex = 3;
            // 
            // tbControl
            // 
            this.tbControl.Controls.Add(this.tpCurrent);
            this.tbControl.Controls.Add(this.tpParam);
            this.tbControl.Dock = System.Windows.Forms.DockStyle.Left;
            this.tbControl.Location = new System.Drawing.Point(0, 0);
            this.tbControl.Name = "tbControl";
            this.tbControl.SelectedIndex = 0;
            this.tbControl.Size = new System.Drawing.Size(405, 376);
            this.tbControl.TabIndex = 4;
            // 
            // tpCurrent
            // 
            this.tpCurrent.Controls.Add(this.flCurrent);
            this.tpCurrent.Location = new System.Drawing.Point(4, 25);
            this.tpCurrent.Name = "tpCurrent";
            this.tpCurrent.Padding = new System.Windows.Forms.Padding(3);
            this.tpCurrent.Size = new System.Drawing.Size(397, 347);
            this.tpCurrent.TabIndex = 1;
            this.tpCurrent.Text = "Current";
            this.tpCurrent.UseVisualStyleBackColor = true;
            // 
            // flCurrent
            // 
            this.flCurrent.Dock = System.Windows.Forms.DockStyle.Fill;
            this.flCurrent.Location = new System.Drawing.Point(3, 3);
            this.flCurrent.Name = "flCurrent";
            this.flCurrent.Size = new System.Drawing.Size(391, 341);
            this.flCurrent.TabIndex = 0;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.cmbPortBin);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Controls.Add(this.btListBoards);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Right;
            this.panel1.Location = new System.Drawing.Point(558, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(129, 376);
            this.panel1.TabIndex = 5;
            // 
            // timer
            // 
            this.timer.Enabled = true;
            this.timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // tpParam
            // 
            this.tpParam.Controls.Add(this.flParam);
            this.tpParam.Location = new System.Drawing.Point(4, 25);
            this.tpParam.Name = "tpParam";
            this.tpParam.Padding = new System.Windows.Forms.Padding(3);
            this.tpParam.Size = new System.Drawing.Size(397, 347);
            this.tpParam.TabIndex = 2;
            this.tpParam.Text = "Param";
            this.tpParam.UseVisualStyleBackColor = true;
            // 
            // flParam
            // 
            this.flParam.Dock = System.Windows.Forms.DockStyle.Fill;
            this.flParam.Location = new System.Drawing.Point(3, 3);
            this.flParam.Name = "flParam";
            this.flParam.Size = new System.Drawing.Size(391, 341);
            this.flParam.TabIndex = 0;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(687, 376);
            this.Controls.Add(this.trBoards);
            this.Controls.Add(this.tbControl);
            this.Controls.Add(this.panel1);
            this.Name = "MainForm";
            this.Text = "PCController";
            this.tbControl.ResumeLayout(false);
            this.tpCurrent.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.tpParam.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion
        private System.IO.Ports.SerialPort uartBin;
        private System.Windows.Forms.ComboBox cmbPortBin;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btListBoards;
        private System.Windows.Forms.TreeView trBoards;
        private System.Windows.Forms.TabControl tbControl;
        private System.Windows.Forms.TabPage tpCurrent;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.FlowLayoutPanel flCurrent;
        private System.Windows.Forms.Timer timer;
        private System.Windows.Forms.TabPage tpParam;
        private System.Windows.Forms.FlowLayoutPanel flParam;
    }
}

