﻿namespace PRO190726
{
    partial class frmYHExperienceSM
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
            this.lbCreateExp = new System.Windows.Forms.Label();
            this.lbSave = new System.Windows.Forms.Label();
            this.columnHeader4 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.listView1 = new System.Windows.Forms.ListView();
            this.textBox6 = new System.Windows.Forms.TextBox();
            this.label14 = new System.Windows.Forms.Label();
            this.lbExpSave = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.panel2 = new System.Windows.Forms.Panel();
            this.label19 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.comboBox6 = new System.Windows.Forms.ComboBox();
            this.label11 = new System.Windows.Forms.Label();
            this.textBox4 = new System.Windows.Forms.TextBox();
            this.comboBox7 = new System.Windows.Forms.ComboBox();
            this.label12 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.comboBox5 = new System.Windows.Forms.ComboBox();
            this.label8 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.comboBox4 = new System.Windows.Forms.ComboBox();
            this.label7 = new System.Windows.Forms.Label();
            this.comboBox2 = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.lbSubtitle = new System.Windows.Forms.Label();
            this.lbtitle = new System.Windows.Forms.Label();
            this.panel3 = new System.Windows.Forms.Panel();
            this.lbExp = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel2.SuspendLayout();
            this.panel3.SuspendLayout();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // lbCreateExp
            // 
            this.lbCreateExp.AutoSize = true;
            this.lbCreateExp.Location = new System.Drawing.Point(414, 238);
            this.lbCreateExp.Name = "lbCreateExp";
            this.lbCreateExp.Size = new System.Drawing.Size(77, 12);
            this.lbCreateExp.TabIndex = 30;
            this.lbCreateExp.Text = "生成实验方案";
            this.lbCreateExp.MouseEnter += new System.EventHandler(this.lbCreateExp_MouseEnter);
            this.lbCreateExp.MouseLeave += new System.EventHandler(this.lbCreateExp_MouseLeave);
            // 
            // lbSave
            // 
            this.lbSave.AutoSize = true;
            this.lbSave.Location = new System.Drawing.Point(402, 292);
            this.lbSave.Name = "lbSave";
            this.lbSave.Size = new System.Drawing.Size(29, 12);
            this.lbSave.TabIndex = 28;
            this.lbSave.Text = "保存";
            this.lbSave.MouseEnter += new System.EventHandler(this.lbSave_MouseEnter);
            this.lbSave.MouseLeave += new System.EventHandler(this.lbSave_MouseLeave);
            // 
            // columnHeader4
            // 
            this.columnHeader4.Text = "实验时间(h)";
            this.columnHeader4.Width = 182;
            // 
            // columnHeader3
            // 
            this.columnHeader3.Text = "实验样本量";
            this.columnHeader3.Width = 155;
            // 
            // columnHeader2
            // 
            this.columnHeader2.Text = "湿度(％)";
            this.columnHeader2.Width = 133;
            // 
            // columnHeader1
            // 
            this.columnHeader1.Text = "温度(℃)";
            this.columnHeader1.Width = 160;
            // 
            // listView1
            // 
            this.listView1.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2,
            this.columnHeader3,
            this.columnHeader4});
            this.listView1.Location = new System.Drawing.Point(129, 51);
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(636, 161);
            this.listView1.TabIndex = 3;
            this.listView1.UseCompatibleStateImageBehavior = false;
            this.listView1.View = System.Windows.Forms.View.Details;
            // 
            // textBox6
            // 
            this.textBox6.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.textBox6.ForeColor = System.Drawing.Color.Navy;
            this.textBox6.Location = new System.Drawing.Point(633, 83);
            this.textBox6.Name = "textBox6";
            this.textBox6.Size = new System.Drawing.Size(100, 21);
            this.textBox6.TabIndex = 25;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label14.ForeColor = System.Drawing.Color.Navy;
            this.label14.Location = new System.Drawing.Point(562, 90);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(77, 14);
            this.label14.TabIndex = 24;
            this.label14.Text = "样本总量：";
            // 
            // lbExpSave
            // 
            this.lbExpSave.AutoSize = true;
            this.lbExpSave.Location = new System.Drawing.Point(305, 238);
            this.lbExpSave.Name = "lbExpSave";
            this.lbExpSave.Size = new System.Drawing.Size(29, 12);
            this.lbExpSave.TabIndex = 29;
            this.lbExpSave.Text = "保存";
            this.lbExpSave.MouseEnter += new System.EventHandler(this.lbexpSave_MouseEnter);
            this.lbExpSave.MouseLeave += new System.EventHandler(this.lbexpSave_MouseLeave);
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label10.ForeColor = System.Drawing.Color.Navy;
            this.label10.Location = new System.Drawing.Point(727, 212);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(21, 14);
            this.label10.TabIndex = 21;
            this.label10.Text = "％";
            // 
            // panel2
            // 
            this.panel2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel2.BackColor = System.Drawing.Color.CadetBlue;
            this.panel2.Controls.Add(this.label19);
            this.panel2.Controls.Add(this.label15);
            this.panel2.Controls.Add(this.label13);
            this.panel2.Controls.Add(this.label6);
            this.panel2.Controls.Add(this.lbSave);
            this.panel2.Controls.Add(this.textBox6);
            this.panel2.Controls.Add(this.label14);
            this.panel2.Controls.Add(this.label10);
            this.panel2.Controls.Add(this.textBox3);
            this.panel2.Controls.Add(this.comboBox6);
            this.panel2.Controls.Add(this.label11);
            this.panel2.Controls.Add(this.textBox4);
            this.panel2.Controls.Add(this.comboBox7);
            this.panel2.Controls.Add(this.label12);
            this.panel2.Controls.Add(this.label9);
            this.panel2.Controls.Add(this.textBox2);
            this.panel2.Controls.Add(this.comboBox5);
            this.panel2.Controls.Add(this.label8);
            this.panel2.Controls.Add(this.textBox1);
            this.panel2.Controls.Add(this.comboBox4);
            this.panel2.Controls.Add(this.label7);
            this.panel2.Controls.Add(this.comboBox2);
            this.panel2.Controls.Add(this.label5);
            this.panel2.Controls.Add(this.comboBox1);
            this.panel2.Controls.Add(this.label4);
            this.panel2.Controls.Add(this.lbSubtitle);
            this.panel2.Location = new System.Drawing.Point(22, 40);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(1105, 332);
            this.panel2.TabIndex = 5;
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label19.ForeColor = System.Drawing.Color.Navy;
            this.label19.Location = new System.Drawing.Point(598, 211);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(21, 14);
            this.label19.TabIndex = 32;
            this.label19.Text = "--";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label15.ForeColor = System.Drawing.Color.Navy;
            this.label15.Location = new System.Drawing.Point(598, 155);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(21, 14);
            this.label15.TabIndex = 31;
            this.label15.Text = "--";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label13.ForeColor = System.Drawing.Color.Navy;
            this.label13.Location = new System.Drawing.Point(295, 214);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(21, 14);
            this.label13.TabIndex = 30;
            this.label13.Text = "--";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label6.ForeColor = System.Drawing.Color.Navy;
            this.label6.Location = new System.Drawing.Point(295, 155);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(21, 14);
            this.label6.TabIndex = 29;
            this.label6.Text = "--";
            // 
            // textBox3
            // 
            this.textBox3.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.textBox3.ForeColor = System.Drawing.Color.Navy;
            this.textBox3.Location = new System.Drawing.Point(621, 205);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(100, 21);
            this.textBox3.TabIndex = 20;
            // 
            // comboBox6
            // 
            this.comboBox6.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.comboBox6.ForeColor = System.Drawing.Color.Navy;
            this.comboBox6.FormattingEnabled = true;
            this.comboBox6.Location = new System.Drawing.Point(517, 206);
            this.comboBox6.Name = "comboBox6";
            this.comboBox6.Size = new System.Drawing.Size(75, 21);
            this.comboBox6.TabIndex = 19;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label11.ForeColor = System.Drawing.Color.Navy;
            this.label11.Location = new System.Drawing.Point(424, 212);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(21, 14);
            this.label11.TabIndex = 18;
            this.label11.Text = "℃";
            // 
            // textBox4
            // 
            this.textBox4.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.textBox4.ForeColor = System.Drawing.Color.Navy;
            this.textBox4.Location = new System.Drawing.Point(318, 207);
            this.textBox4.Name = "textBox4";
            this.textBox4.Size = new System.Drawing.Size(100, 21);
            this.textBox4.TabIndex = 17;
            // 
            // comboBox7
            // 
            this.comboBox7.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.comboBox7.ForeColor = System.Drawing.Color.Navy;
            this.comboBox7.FormattingEnabled = true;
            this.comboBox7.Location = new System.Drawing.Point(172, 208);
            this.comboBox7.Name = "comboBox7";
            this.comboBox7.Size = new System.Drawing.Size(121, 21);
            this.comboBox7.TabIndex = 16;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label12.ForeColor = System.Drawing.Color.Navy;
            this.label12.Location = new System.Drawing.Point(65, 212);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(105, 14);
            this.label12.TabIndex = 15;
            this.label12.Text = "产品工作极限：";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label9.ForeColor = System.Drawing.Color.Navy;
            this.label9.Location = new System.Drawing.Point(727, 155);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(21, 14);
            this.label9.TabIndex = 14;
            this.label9.Text = "％";
            // 
            // textBox2
            // 
            this.textBox2.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.textBox2.ForeColor = System.Drawing.Color.Navy;
            this.textBox2.Location = new System.Drawing.Point(621, 150);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(100, 21);
            this.textBox2.TabIndex = 13;
            // 
            // comboBox5
            // 
            this.comboBox5.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.comboBox5.ForeColor = System.Drawing.Color.Navy;
            this.comboBox5.FormattingEnabled = true;
            this.comboBox5.Location = new System.Drawing.Point(517, 151);
            this.comboBox5.Name = "comboBox5";
            this.comboBox5.Size = new System.Drawing.Size(75, 21);
            this.comboBox5.TabIndex = 12;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label8.ForeColor = System.Drawing.Color.Navy;
            this.label8.Location = new System.Drawing.Point(424, 155);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(21, 14);
            this.label8.TabIndex = 11;
            this.label8.Text = "℃";
            // 
            // textBox1
            // 
            this.textBox1.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.textBox1.ForeColor = System.Drawing.Color.Navy;
            this.textBox1.Location = new System.Drawing.Point(318, 150);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(100, 21);
            this.textBox1.TabIndex = 10;
            // 
            // comboBox4
            // 
            this.comboBox4.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.comboBox4.ForeColor = System.Drawing.Color.Navy;
            this.comboBox4.FormattingEnabled = true;
            this.comboBox4.Location = new System.Drawing.Point(172, 151);
            this.comboBox4.Name = "comboBox4";
            this.comboBox4.Size = new System.Drawing.Size(121, 21);
            this.comboBox4.TabIndex = 9;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label7.ForeColor = System.Drawing.Color.Navy;
            this.label7.Location = new System.Drawing.Point(65, 155);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(105, 14);
            this.label7.TabIndex = 8;
            this.label7.Text = "常规使用条件：";
            // 
            // comboBox2
            // 
            this.comboBox2.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.comboBox2.ForeColor = System.Drawing.Color.Navy;
            this.comboBox2.FormattingEnabled = true;
            this.comboBox2.Location = new System.Drawing.Point(398, 85);
            this.comboBox2.Name = "comboBox2";
            this.comboBox2.Size = new System.Drawing.Size(121, 21);
            this.comboBox2.TabIndex = 5;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label5.ForeColor = System.Drawing.Color.Navy;
            this.label5.Location = new System.Drawing.Point(329, 90);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(77, 14);
            this.label5.TabIndex = 4;
            this.label5.Text = "加速模型：";
            // 
            // comboBox1
            // 
            this.comboBox1.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.comboBox1.ForeColor = System.Drawing.Color.Navy;
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(172, 85);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(121, 21);
            this.comboBox1.TabIndex = 3;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label4.ForeColor = System.Drawing.Color.Navy;
            this.label4.Location = new System.Drawing.Point(89, 90);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(77, 14);
            this.label4.TabIndex = 2;
            this.label4.Text = "应力类型：";
            // 
            // lbSubtitle
            // 
            this.lbSubtitle.AutoSize = true;
            this.lbSubtitle.Location = new System.Drawing.Point(18, 10);
            this.lbSubtitle.Name = "lbSubtitle";
            this.lbSubtitle.Size = new System.Drawing.Size(101, 12);
            this.lbSubtitle.TabIndex = 1;
            this.lbSubtitle.Text = "实验基本信息填写";
            // 
            // lbtitle
            // 
            this.lbtitle.AutoSize = true;
            this.lbtitle.Location = new System.Drawing.Point(28, 9);
            this.lbtitle.Name = "lbtitle";
            this.lbtitle.Size = new System.Drawing.Size(113, 12);
            this.lbtitle.TabIndex = 0;
            this.lbtitle.Text = "项目--优化方案推荐";
            // 
            // panel3
            // 
            this.panel3.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel3.BackColor = System.Drawing.Color.CadetBlue;
            this.panel3.Controls.Add(this.lbCreateExp);
            this.panel3.Controls.Add(this.lbExpSave);
            this.panel3.Controls.Add(this.listView1);
            this.panel3.Controls.Add(this.lbExp);
            this.panel3.Location = new System.Drawing.Point(22, 391);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(1105, 278);
            this.panel3.TabIndex = 6;
            // 
            // lbExp
            // 
            this.lbExp.AutoSize = true;
            this.lbExp.Location = new System.Drawing.Point(18, 10);
            this.lbExp.Name = "lbExp";
            this.lbExp.Size = new System.Drawing.Size(101, 12);
            this.lbExp.TabIndex = 2;
            this.lbExp.Text = "实验方案要素设计";
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.BackColor = System.Drawing.Color.CornflowerBlue;
            this.panel1.Controls.Add(this.lbtitle);
            this.panel1.Location = new System.Drawing.Point(1, 1);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(1137, 31);
            this.panel1.TabIndex = 4;
            // 
            // frmYHExperienceSM
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Teal;
            this.ClientSize = new System.Drawing.Size(1139, 706);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel3);
            this.Controls.Add(this.panel1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "frmYHExperienceSM";
            this.Text = "frmYHExperienceSM";
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label lbCreateExp;
        private System.Windows.Forms.Label lbSave;
        private System.Windows.Forms.ColumnHeader columnHeader4;
        private System.Windows.Forms.ColumnHeader columnHeader3;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ListView listView1;
        private System.Windows.Forms.TextBox textBox6;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label lbExpSave;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.ComboBox comboBox6;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox textBox4;
        private System.Windows.Forms.ComboBox comboBox7;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.ComboBox comboBox5;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.ComboBox comboBox4;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ComboBox comboBox2;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label lbSubtitle;
        private System.Windows.Forms.Label lbtitle;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Label lbExp;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label6;
    }
}