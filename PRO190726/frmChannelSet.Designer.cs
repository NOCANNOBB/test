namespace PRO190726
{
    partial class frmChannelSet
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.lbIn = new System.Windows.Forms.Label();
            this.lbOut = new System.Windows.Forms.Label();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.lbSave = new System.Windows.Forms.Label();
            this.Column1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column3 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column4 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column5 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column6 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column7 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.SuspendLayout();
            // 
            // lbIn
            // 
            this.lbIn.AutoSize = true;
            this.lbIn.Location = new System.Drawing.Point(87, 40);
            this.lbIn.Name = "lbIn";
            this.lbIn.Size = new System.Drawing.Size(77, 12);
            this.lbIn.TabIndex = 0;
            this.lbIn.Text = "导入通道设置";
            this.lbIn.Click += new System.EventHandler(this.lbIn_Click);
            this.lbIn.MouseEnter += new System.EventHandler(this.lbIn_MouseEnter);
            this.lbIn.MouseLeave += new System.EventHandler(this.lbIn_MouseLeave);
            // 
            // lbOut
            // 
            this.lbOut.AutoSize = true;
            this.lbOut.Location = new System.Drawing.Point(355, 40);
            this.lbOut.Name = "lbOut";
            this.lbOut.Size = new System.Drawing.Size(77, 12);
            this.lbOut.TabIndex = 1;
            this.lbOut.Text = "导出通道设置";
            this.lbOut.Click += new System.EventHandler(this.lbOut_Click);
            this.lbOut.MouseEnter += new System.EventHandler(this.lbOut_MouseEnter);
            this.lbOut.MouseLeave += new System.EventHandler(this.lbOut_MouseLeave);
            // 
            // dataGridView1
            // 
            this.dataGridView1.BackgroundColor = System.Drawing.Color.CadetBlue;
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Column1,
            this.Column2,
            this.Column3,
            this.Column4,
            this.Column5,
            this.Column6,
            this.Column7});
            this.dataGridView1.Location = new System.Drawing.Point(7, 91);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowTemplate.Height = 23;
            this.dataGridView1.Size = new System.Drawing.Size(843, 468);
            this.dataGridView1.TabIndex = 2;
            this.dataGridView1.CurrentCellChanged += new System.EventHandler(this.dataGridView1_CurrentCellChanged);
            // 
            // lbSave
            // 
            this.lbSave.AutoSize = true;
            this.lbSave.Location = new System.Drawing.Point(707, 40);
            this.lbSave.Name = "lbSave";
            this.lbSave.Size = new System.Drawing.Size(53, 12);
            this.lbSave.TabIndex = 3;
            this.lbSave.Text = "保存配置";
            this.lbSave.Click += new System.EventHandler(this.lbSave_Click);
            this.lbSave.MouseEnter += new System.EventHandler(this.lbSave_MouseEnter);
            this.lbSave.MouseLeave += new System.EventHandler(this.lbSave_MouseLeave);
            // 
            // Column1
            // 
            this.Column1.HeaderText = "命名";
            this.Column1.Name = "Column1";
            // 
            // Column2
            // 
            this.Column2.HeaderText = "端子";
            this.Column2.Name = "Column2";
            // 
            // Column3
            // 
            this.Column3.HeaderText = "线号";
            this.Column3.Name = "Column3";
            // 
            // Column4
            // 
            this.Column4.HeaderText = "采样周期";
            this.Column4.Name = "Column4";
            // 
            // Column5
            // 
            this.Column5.HeaderText = "每周期采样点";
            this.Column5.Name = "Column5";
            // 
            // Column6
            // 
            this.Column6.HeaderText = "信号类型";
            this.Column6.Name = "Column6";
            // 
            // Column7
            // 
            this.Column7.HeaderText = "通道号";
            this.Column7.Name = "Column7";
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "AI",
            "AO",
            "DO",
            "CNT"});
            this.comboBox1.Location = new System.Drawing.Point(754, 65);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(75, 20);
            this.comboBox1.TabIndex = 9;
            this.comboBox1.Visible = false;
            this.comboBox1.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // frmChannelSet
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Teal;
            this.ClientSize = new System.Drawing.Size(856, 689);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.lbSave);
            this.Controls.Add(this.dataGridView1);
            this.Controls.Add(this.lbOut);
            this.Controls.Add(this.lbIn);
            this.ForeColor = System.Drawing.SystemColors.ControlText;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "frmChannelSet";
            this.Text = "frmChannelSet";
            this.Load += new System.EventHandler(this.frmChannelSet_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lbIn;
        private System.Windows.Forms.Label lbOut;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.Label lbSave;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column1;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column2;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column3;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column4;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column5;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column6;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column7;
        private System.Windows.Forms.ComboBox comboBox1;
    }
}