﻿namespace PRO190726
{
    partial class frmDataAalrmSet
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
            this.rabBZData = new System.Windows.Forms.RadioButton();
            this.rabAlarmData = new System.Windows.Forms.RadioButton();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.lbYBSelect = new System.Windows.Forms.Label();
            this.lbSave = new System.Windows.Forms.Label();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.Column1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column3 = new System.Windows.Forms.DataGridViewImageColumn();
            this.panel2 = new System.Windows.Forms.Panel();
            this.dataGridView2 = new System.Windows.Forms.DataGridView();
            this.lbSave2 = new System.Windows.Forms.Label();
            this.Column4 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column5 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column6 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column7 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column8 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.groupBox1.SuspendLayout();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.panel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).BeginInit();
            this.SuspendLayout();
            // 
            // rabBZData
            // 
            this.rabBZData.AutoSize = true;
            this.rabBZData.Checked = true;
            this.rabBZData.Location = new System.Drawing.Point(32, 20);
            this.rabBZData.Name = "rabBZData";
            this.rabBZData.Size = new System.Drawing.Size(71, 16);
            this.rabBZData.TabIndex = 0;
            this.rabBZData.TabStop = true;
            this.rabBZData.Text = "标准数据";
            this.rabBZData.UseVisualStyleBackColor = true;
            this.rabBZData.CheckedChanged += new System.EventHandler(this.rabBZData_CheckedChanged);
            this.rabBZData.Click += new System.EventHandler(this.rabBZData_Click);
            // 
            // rabAlarmData
            // 
            this.rabAlarmData.AutoSize = true;
            this.rabAlarmData.BackColor = System.Drawing.Color.Teal;
            this.rabAlarmData.Location = new System.Drawing.Point(246, 20);
            this.rabAlarmData.Name = "rabAlarmData";
            this.rabAlarmData.Size = new System.Drawing.Size(71, 16);
            this.rabAlarmData.TabIndex = 1;
            this.rabAlarmData.Text = "报警设置";
            this.rabAlarmData.UseVisualStyleBackColor = false;
            this.rabAlarmData.Click += new System.EventHandler(this.rabAlarmData_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.rabBZData);
            this.groupBox1.Controls.Add(this.rabAlarmData);
            this.groupBox1.Location = new System.Drawing.Point(50, 34);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(374, 49);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.lbYBSelect);
            this.panel1.Controls.Add(this.lbSave);
            this.panel1.Controls.Add(this.comboBox1);
            this.panel1.Controls.Add(this.pictureBox2);
            this.panel1.Controls.Add(this.pictureBox1);
            this.panel1.Controls.Add(this.dataGridView1);
            this.panel1.Location = new System.Drawing.Point(50, 126);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(936, 507);
            this.panel1.TabIndex = 3;
            // 
            // lbYBSelect
            // 
            this.lbYBSelect.AutoSize = true;
            this.lbYBSelect.Font = new System.Drawing.Font("FontAwesome", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbYBSelect.ForeColor = System.Drawing.Color.LightCyan;
            this.lbYBSelect.Location = new System.Drawing.Point(14, 13);
            this.lbYBSelect.Name = "lbYBSelect";
            this.lbYBSelect.Size = new System.Drawing.Size(72, 16);
            this.lbYBSelect.TabIndex = 13;
            this.lbYBSelect.Text = "样本选择";
            this.lbYBSelect.Click += new System.EventHandler(this.lbYBSelect_Click);
            this.lbYBSelect.MouseEnter += new System.EventHandler(this.lbYBSelect_MouseEnter);
            this.lbYBSelect.MouseLeave += new System.EventHandler(this.lbYBSelect_MouseLeave);
            // 
            // lbSave
            // 
            this.lbSave.AutoSize = true;
            this.lbSave.Location = new System.Drawing.Point(691, 26);
            this.lbSave.Name = "lbSave";
            this.lbSave.Size = new System.Drawing.Size(29, 12);
            this.lbSave.TabIndex = 9;
            this.lbSave.Text = "保存";
            this.lbSave.Click += new System.EventHandler(this.lbSave_Click);
            this.lbSave.MouseEnter += new System.EventHandler(this.lbSave_MouseEnter);
            this.lbSave.MouseLeave += new System.EventHandler(this.lbSave_MouseLeave);
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "恒定值",
            "循环信号",
            "不循环变化信号"});
            this.comboBox1.Location = new System.Drawing.Point(771, 307);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(75, 20);
            this.comboBox1.TabIndex = 12;
            this.comboBox1.DrawItem += new System.Windows.Forms.DrawItemEventHandler(this.comboBox1_DrawItem);
            this.comboBox1.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // pictureBox2
            // 
            this.pictureBox2.Image = global::PRO190726.Properties.Resources.微信截图_20190804075341;
            this.pictureBox2.Location = new System.Drawing.Point(771, 191);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(68, 29);
            this.pictureBox2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox2.TabIndex = 11;
            this.pictureBox2.TabStop = false;
            this.pictureBox2.Visible = false;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::PRO190726.Properties.Resources.player_icons_40px_1137045_easyicon_net;
            this.pictureBox1.Location = new System.Drawing.Point(771, 236);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(68, 29);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox1.TabIndex = 10;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.Visible = false;
            // 
            // dataGridView1
            // 
            this.dataGridView1.BackgroundColor = System.Drawing.Color.Teal;
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Column1,
            this.Column2,
            this.Column3});
            this.dataGridView1.Location = new System.Drawing.Point(3, 55);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowTemplate.Height = 23;
            this.dataGridView1.Size = new System.Drawing.Size(734, 398);
            this.dataGridView1.TabIndex = 8;
            this.dataGridView1.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView1_CellClick);
            this.dataGridView1.CurrentCellChanged += new System.EventHandler(this.dataGridView1_CurrentCellChanged);
            // 
            // Column1
            // 
            this.Column1.HeaderText = "样本输出信号";
            this.Column1.Name = "Column1";
            // 
            // Column2
            // 
            this.Column2.HeaderText = "信号形式";
            this.Column2.Name = "Column2";
            this.Column2.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            // 
            // Column3
            // 
            this.Column3.HeaderText = " ";
            this.Column3.Image = global::PRO190726.Properties.Resources.player_icons_40px_1137045_easyicon_net;
            this.Column3.ImageLayout = System.Windows.Forms.DataGridViewImageCellLayout.Zoom;
            this.Column3.Name = "Column3";
            this.Column3.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.Column3.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.dataGridView2);
            this.panel2.Controls.Add(this.lbSave2);
            this.panel2.Location = new System.Drawing.Point(49, 126);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(936, 507);
            this.panel2.TabIndex = 14;
            // 
            // dataGridView2
            // 
            this.dataGridView2.BackgroundColor = System.Drawing.Color.Teal;
            this.dataGridView2.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView2.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Column4,
            this.Column5,
            this.Column6,
            this.Column7,
            this.Column8});
            this.dataGridView2.Location = new System.Drawing.Point(3, 40);
            this.dataGridView2.Name = "dataGridView2";
            this.dataGridView2.RowTemplate.Height = 23;
            this.dataGridView2.Size = new System.Drawing.Size(544, 378);
            this.dataGridView2.TabIndex = 14;
            // 
            // lbSave2
            // 
            this.lbSave2.AutoSize = true;
            this.lbSave2.Location = new System.Drawing.Point(681, 19);
            this.lbSave2.Name = "lbSave2";
            this.lbSave2.Size = new System.Drawing.Size(29, 12);
            this.lbSave2.TabIndex = 9;
            this.lbSave2.Text = "保存";
            this.lbSave2.Click += new System.EventHandler(this.lbSave2_Click);
            this.lbSave2.MouseEnter += new System.EventHandler(this.lbSave2_MouseEnter);
            this.lbSave2.MouseLeave += new System.EventHandler(this.lbSave2_MouseLeave);
            // 
            // Column4
            // 
            this.Column4.HeaderText = "样本输入信号";
            this.Column4.Name = "Column4";
            // 
            // Column5
            // 
            this.Column5.HeaderText = "报警上限";
            this.Column5.Name = "Column5";
            // 
            // Column6
            // 
            this.Column6.HeaderText = "报警下限";
            this.Column6.Name = "Column6";
            // 
            // Column7
            // 
            this.Column7.HeaderText = "报警绝对误差";
            this.Column7.Name = "Column7";
            // 
            // Column8
            // 
            this.Column8.HeaderText = "报警时间误差";
            this.Column8.Name = "Column8";
            // 
            // frmDataAalrmSet
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Teal;
            this.ClientSize = new System.Drawing.Size(1036, 655);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.panel2);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "frmDataAalrmSet";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "frmDataAalrmSet";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.RadioButton rabBZData;
        private System.Windows.Forms.RadioButton rabAlarmData;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label lbSave;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.Label lbYBSelect;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column1;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column2;
        private System.Windows.Forms.DataGridViewImageColumn Column3;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Label lbSave2;
        private System.Windows.Forms.DataGridView dataGridView2;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column4;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column5;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column6;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column7;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column8;

    }
}