namespace PRO190726
{
    partial class frmExperment
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
            this.components = new System.ComponentModel.Container();
            this.lbTitle = new System.Windows.Forms.Label();
            this.lbHour = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.lbMin = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.lbSec = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.cmbExpermentASK = new System.Windows.Forms.ComboBox();
            this.ddbYBSelect = new DevExpress.XtraEditors.DropDownButton();
            this.panel1 = new System.Windows.Forms.Panel();
            this.simpleButton09 = new DevExpress.XtraEditors.SimpleButton();
            this.simpleButton05 = new DevExpress.XtraEditors.SimpleButton();
            this.simpleButton10 = new DevExpress.XtraEditors.SimpleButton();
            this.simpleButton04 = new DevExpress.XtraEditors.SimpleButton();
            this.simpleButton06 = new DevExpress.XtraEditors.SimpleButton();
            this.simpleButton03 = new DevExpress.XtraEditors.SimpleButton();
            this.simpleButton02 = new DevExpress.XtraEditors.SimpleButton();
            this.simpleButton07 = new DevExpress.XtraEditors.SimpleButton();
            this.simpleButton01 = new DevExpress.XtraEditors.SimpleButton();
            this.simpleButton08 = new DevExpress.XtraEditors.SimpleButton();
            this.panel2 = new System.Windows.Forms.Panel();
            this.panel3 = new System.Windows.Forms.Panel();
            this.lbStart = new System.Windows.Forms.Label();
            this.lbEnd = new System.Windows.Forms.Label();
            this.pictureBox5 = new System.Windows.Forms.PictureBox();
            this.pictureBox4 = new System.Windows.Forms.PictureBox();
            this.pictureBox3 = new System.Windows.Forms.PictureBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox5)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.SuspendLayout();
            // 
            // lbTitle
            // 
            this.lbTitle.AutoSize = true;
            this.lbTitle.Font = new System.Drawing.Font("FontAwesome", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbTitle.Location = new System.Drawing.Point(143, 55);
            this.lbTitle.Name = "lbTitle";
            this.lbTitle.Size = new System.Drawing.Size(114, 20);
            this.lbTitle.TabIndex = 0;
            this.lbTitle.Text = "实验时间：";
            // 
            // lbHour
            // 
            this.lbHour.AutoSize = true;
            this.lbHour.Font = new System.Drawing.Font("FontAwesome", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbHour.Location = new System.Drawing.Point(274, 55);
            this.lbHour.Name = "lbHour";
            this.lbHour.Size = new System.Drawing.Size(20, 20);
            this.lbHour.TabIndex = 1;
            this.lbHour.Text = "0";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("FontAwesome", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label2.Location = new System.Drawing.Point(300, 55);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(20, 20);
            this.label2.TabIndex = 2;
            this.label2.Text = "h";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("FontAwesome", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label3.Location = new System.Drawing.Point(368, 55);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(42, 20);
            this.label3.TabIndex = 4;
            this.label3.Text = "min";
            // 
            // lbMin
            // 
            this.lbMin.AutoSize = true;
            this.lbMin.Font = new System.Drawing.Font("FontAwesome", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbMin.Location = new System.Drawing.Point(342, 55);
            this.lbMin.Name = "lbMin";
            this.lbMin.Size = new System.Drawing.Size(20, 20);
            this.lbMin.TabIndex = 3;
            this.lbMin.Text = "0";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("FontAwesome", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label5.Location = new System.Drawing.Point(443, 55);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(20, 20);
            this.label5.TabIndex = 6;
            this.label5.Text = "s";
            // 
            // lbSec
            // 
            this.lbSec.AutoSize = true;
            this.lbSec.Font = new System.Drawing.Font("FontAwesome", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbSec.Location = new System.Drawing.Point(417, 55);
            this.lbSec.Name = "lbSec";
            this.lbSec.Size = new System.Drawing.Size(20, 20);
            this.lbSec.TabIndex = 5;
            this.lbSec.Text = "0";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("FontAwesome", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.Location = new System.Drawing.Point(581, 55);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(114, 20);
            this.label1.TabIndex = 7;
            this.label1.Text = "实验条件：";
            // 
            // cmbExpermentASK
            // 
            this.cmbExpermentASK.DrawMode = System.Windows.Forms.DrawMode.OwnerDrawFixed;
            this.cmbExpermentASK.FormattingEnabled = true;
            this.cmbExpermentASK.ItemHeight = 20;
            this.cmbExpermentASK.Location = new System.Drawing.Point(690, 51);
            this.cmbExpermentASK.Name = "cmbExpermentASK";
            this.cmbExpermentASK.Size = new System.Drawing.Size(185, 26);
            this.cmbExpermentASK.TabIndex = 8;
            // 
            // ddbYBSelect
            // 
            this.ddbYBSelect.Location = new System.Drawing.Point(61, 111);
            this.ddbYBSelect.Name = "ddbYBSelect";
            this.ddbYBSelect.Size = new System.Drawing.Size(135, 34);
            this.ddbYBSelect.TabIndex = 9;
            this.ddbYBSelect.Text = "样本";
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.MintCream;
            this.panel1.Controls.Add(this.simpleButton09);
            this.panel1.Controls.Add(this.simpleButton05);
            this.panel1.Controls.Add(this.simpleButton10);
            this.panel1.Controls.Add(this.simpleButton04);
            this.panel1.Controls.Add(this.simpleButton06);
            this.panel1.Controls.Add(this.simpleButton03);
            this.panel1.Controls.Add(this.simpleButton02);
            this.panel1.Controls.Add(this.simpleButton07);
            this.panel1.Controls.Add(this.simpleButton01);
            this.panel1.Controls.Add(this.simpleButton08);
            this.panel1.Location = new System.Drawing.Point(61, 146);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(135, 324);
            this.panel1.TabIndex = 10;
            // 
            // simpleButton09
            // 
            this.simpleButton09.Location = new System.Drawing.Point(1, 259);
            this.simpleButton09.Name = "simpleButton09";
            this.simpleButton09.Size = new System.Drawing.Size(132, 31);
            this.simpleButton09.TabIndex = 9;
            this.simpleButton09.Text = "simpleButton9";
            // 
            // simpleButton05
            // 
            this.simpleButton05.Location = new System.Drawing.Point(0, 131);
            this.simpleButton05.Name = "simpleButton05";
            this.simpleButton05.Size = new System.Drawing.Size(132, 31);
            this.simpleButton05.TabIndex = 7;
            this.simpleButton05.Text = "simpleButton5";
            // 
            // simpleButton10
            // 
            this.simpleButton10.Location = new System.Drawing.Point(1, 291);
            this.simpleButton10.Name = "simpleButton10";
            this.simpleButton10.Size = new System.Drawing.Size(132, 31);
            this.simpleButton10.TabIndex = 8;
            this.simpleButton10.Text = "simpleButton10";
            // 
            // simpleButton04
            // 
            this.simpleButton04.Location = new System.Drawing.Point(1, 99);
            this.simpleButton04.Name = "simpleButton04";
            this.simpleButton04.Size = new System.Drawing.Size(132, 31);
            this.simpleButton04.TabIndex = 3;
            this.simpleButton04.Text = "simpleButton4";
            // 
            // simpleButton06
            // 
            this.simpleButton06.Location = new System.Drawing.Point(0, 163);
            this.simpleButton06.Name = "simpleButton06";
            this.simpleButton06.Size = new System.Drawing.Size(132, 31);
            this.simpleButton06.TabIndex = 6;
            this.simpleButton06.Text = "simpleButton6";
            // 
            // simpleButton03
            // 
            this.simpleButton03.Location = new System.Drawing.Point(1, 67);
            this.simpleButton03.Name = "simpleButton03";
            this.simpleButton03.Size = new System.Drawing.Size(132, 31);
            this.simpleButton03.TabIndex = 2;
            this.simpleButton03.Text = "simpleButton3";
            // 
            // simpleButton02
            // 
            this.simpleButton02.Location = new System.Drawing.Point(1, 35);
            this.simpleButton02.Name = "simpleButton02";
            this.simpleButton02.Size = new System.Drawing.Size(132, 31);
            this.simpleButton02.TabIndex = 1;
            this.simpleButton02.Text = "simpleButton2";
            // 
            // simpleButton07
            // 
            this.simpleButton07.Location = new System.Drawing.Point(0, 195);
            this.simpleButton07.Name = "simpleButton07";
            this.simpleButton07.Size = new System.Drawing.Size(132, 31);
            this.simpleButton07.TabIndex = 5;
            this.simpleButton07.Text = "simpleButton7";
            // 
            // simpleButton01
            // 
            this.simpleButton01.Location = new System.Drawing.Point(1, 3);
            this.simpleButton01.Name = "simpleButton01";
            this.simpleButton01.Size = new System.Drawing.Size(132, 31);
            this.simpleButton01.TabIndex = 0;
            this.simpleButton01.Text = "simpleButton1";
            // 
            // simpleButton08
            // 
            this.simpleButton08.Location = new System.Drawing.Point(0, 227);
            this.simpleButton08.Name = "simpleButton08";
            this.simpleButton08.Size = new System.Drawing.Size(132, 31);
            this.simpleButton08.TabIndex = 4;
            this.simpleButton08.Text = "simpleButton8";
            // 
            // panel2
            // 
            this.panel2.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.panel2.Location = new System.Drawing.Point(61, 473);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(816, 129);
            this.panel2.TabIndex = 11;
            // 
            // panel3
            // 
            this.panel3.BackColor = System.Drawing.Color.MintCream;
            this.panel3.Location = new System.Drawing.Point(201, 147);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(675, 323);
            this.panel3.TabIndex = 12;
            // 
            // lbStart
            // 
            this.lbStart.AutoSize = true;
            this.lbStart.Font = new System.Drawing.Font("FontAwesome", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbStart.Location = new System.Drawing.Point(479, 95);
            this.lbStart.Name = "lbStart";
            this.lbStart.Size = new System.Drawing.Size(93, 20);
            this.lbStart.TabIndex = 13;
            this.lbStart.Text = "开始实验";
            this.lbStart.Click += new System.EventHandler(this.lbStart_Click);
            this.lbStart.MouseEnter += new System.EventHandler(this.lbStart_MouseEnter);
            this.lbStart.MouseLeave += new System.EventHandler(this.lbStart_MouseLeave);
            // 
            // lbEnd
            // 
            this.lbEnd.AutoSize = true;
            this.lbEnd.Enabled = false;
            this.lbEnd.Font = new System.Drawing.Font("FontAwesome", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbEnd.Location = new System.Drawing.Point(690, 95);
            this.lbEnd.Name = "lbEnd";
            this.lbEnd.Size = new System.Drawing.Size(93, 20);
            this.lbEnd.TabIndex = 14;
            this.lbEnd.Text = "结束实验";
            this.lbEnd.Click += new System.EventHandler(this.lbEnd_Click);
            this.lbEnd.MouseEnter += new System.EventHandler(this.lbEnd_MouseEnter);
            this.lbEnd.MouseLeave += new System.EventHandler(this.lbEnd_MouseLeave);
            // 
            // pictureBox5
            // 
            this.pictureBox5.Image = global::PRO190726.Properties.Resources._0132;
            this.pictureBox5.Location = new System.Drawing.Point(202, 115);
            this.pictureBox5.Name = "pictureBox5";
            this.pictureBox5.Size = new System.Drawing.Size(35, 30);
            this.pictureBox5.TabIndex = 21;
            this.pictureBox5.TabStop = false;
            // 
            // pictureBox4
            // 
            this.pictureBox4.BackColor = System.Drawing.Color.LightSeaGreen;
            this.pictureBox4.Location = new System.Drawing.Point(26, 602);
            this.pictureBox4.Name = "pictureBox4";
            this.pictureBox4.Size = new System.Drawing.Size(872, 10);
            this.pictureBox4.TabIndex = 19;
            this.pictureBox4.TabStop = false;
            // 
            // pictureBox3
            // 
            this.pictureBox3.BackColor = System.Drawing.Color.LightSeaGreen;
            this.pictureBox3.Location = new System.Drawing.Point(886, 21);
            this.pictureBox3.Name = "pictureBox3";
            this.pictureBox3.Size = new System.Drawing.Size(10, 591);
            this.pictureBox3.TabIndex = 18;
            this.pictureBox3.TabStop = false;
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackColor = System.Drawing.Color.LightSeaGreen;
            this.pictureBox1.Location = new System.Drawing.Point(24, 21);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(872, 10);
            this.pictureBox1.TabIndex = 17;
            this.pictureBox1.TabStop = false;
            // 
            // pictureBox2
            // 
            this.pictureBox2.BackColor = System.Drawing.Color.LightSeaGreen;
            this.pictureBox2.Location = new System.Drawing.Point(24, 21);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(10, 591);
            this.pictureBox2.TabIndex = 16;
            this.pictureBox2.TabStop = false;
            // 
            // timer1
            // 
            this.timer1.Interval = 1000;
            // 
            // frmExperment
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Teal;
            this.ClientSize = new System.Drawing.Size(1077, 708);
            this.Controls.Add(this.pictureBox5);
            this.Controls.Add(this.pictureBox4);
            this.Controls.Add(this.pictureBox3);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.pictureBox2);
            this.Controls.Add(this.lbEnd);
            this.Controls.Add(this.lbStart);
            this.Controls.Add(this.panel3);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.ddbYBSelect);
            this.Controls.Add(this.cmbExpermentASK);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.lbSec);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.lbMin);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.lbHour);
            this.Controls.Add(this.lbTitle);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "frmExperment";
            this.Text = "frmExperment";
            this.panel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox5)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lbTitle;
        private System.Windows.Forms.Label lbHour;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label lbMin;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label lbSec;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox cmbExpermentASK;
        private DevExpress.XtraEditors.DropDownButton ddbYBSelect;
        private System.Windows.Forms.Panel panel1;
        private DevExpress.XtraEditors.SimpleButton simpleButton09;
        private DevExpress.XtraEditors.SimpleButton simpleButton05;
        private DevExpress.XtraEditors.SimpleButton simpleButton10;
        private DevExpress.XtraEditors.SimpleButton simpleButton04;
        private DevExpress.XtraEditors.SimpleButton simpleButton06;
        private DevExpress.XtraEditors.SimpleButton simpleButton03;
        private DevExpress.XtraEditors.SimpleButton simpleButton02;
        private DevExpress.XtraEditors.SimpleButton simpleButton07;
        private DevExpress.XtraEditors.SimpleButton simpleButton01;
        private DevExpress.XtraEditors.SimpleButton simpleButton08;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Label lbStart;
        private System.Windows.Forms.Label lbEnd;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.PictureBox pictureBox3;
        private System.Windows.Forms.PictureBox pictureBox4;
        private System.Windows.Forms.PictureBox pictureBox5;
        private System.Windows.Forms.Timer timer1;
    }
}