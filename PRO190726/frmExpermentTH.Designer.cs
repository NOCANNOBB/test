namespace PRO190726
{
    partial class frmExpermentTH
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
            this.cmbJW = new System.Windows.Forms.ComboBox();
            this.label15 = new System.Windows.Forms.Label();
            this.txtYBNumber = new System.Windows.Forms.TextBox();
            this.label14 = new System.Windows.Forms.Label();
            this.txtYLNumber = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.lbExpSave = new System.Windows.Forms.Label();
            this.panel2 = new System.Windows.Forms.Panel();
            this.txtJXDYL = new System.Windows.Forms.TextBox();
            this.cmbJXDYL = new System.Windows.Forms.ComboBox();
            this.txtDYL = new System.Windows.Forms.TextBox();
            this.cmbDYL = new System.Windows.Forms.ComboBox();
            this.txtJXZD = new System.Windows.Forms.TextBox();
            this.cmbJZZD = new System.Windows.Forms.ComboBox();
            this.txtZD = new System.Windows.Forms.TextBox();
            this.cmbZD = new System.Windows.Forms.ComboBox();
            this.label10 = new System.Windows.Forms.Label();
            this.txtJXSD = new System.Windows.Forms.TextBox();
            this.cmbJXSD = new System.Windows.Forms.ComboBox();
            this.label11 = new System.Windows.Forms.Label();
            this.txtJX = new System.Windows.Forms.TextBox();
            this.cmbJX = new System.Windows.Forms.ComboBox();
            this.label12 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.txtCGSD = new System.Windows.Forms.TextBox();
            this.cmbSD = new System.Windows.Forms.ComboBox();
            this.label8 = new System.Windows.Forms.Label();
            this.txtCG = new System.Windows.Forms.TextBox();
            this.cmbCG = new System.Windows.Forms.ComboBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label21 = new System.Windows.Forms.Label();
            this.txtTHYZ = new System.Windows.Forms.TextBox();
            this.label20 = new System.Windows.Forms.Label();
            this.txtXNTHCS = new System.Windows.Forms.TextBox();
            this.label19 = new System.Windows.Forms.Label();
            this.cbTLSetType = new System.Windows.Forms.ComboBox();
            this.label6 = new System.Windows.Forms.Label();
            this.cbJsMode = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.cmbYLType = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.lbSubtitle = new System.Windows.Forms.Label();
            this.lbtitle = new System.Windows.Forms.Label();
            this.panel3 = new System.Windows.Forms.Panel();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.Column1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column3 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column4 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.lbExp = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel2.SuspendLayout();
            this.panel3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // lbCreateExp
            // 
            this.lbCreateExp.AutoSize = true;
            this.lbCreateExp.Location = new System.Drawing.Point(410, 209);
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
            this.lbSave.Click += new System.EventHandler(this.lbSave_Click);
            this.lbSave.MouseEnter += new System.EventHandler(this.lbSave_MouseEnter);
            this.lbSave.MouseLeave += new System.EventHandler(this.lbSave_MouseLeave);
            // 
            // cmbJW
            // 
            this.cmbJW.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.cmbJW.ForeColor = System.Drawing.Color.Navy;
            this.cmbJW.FormattingEnabled = true;
            this.cmbJW.Items.AddRange(new object[] {
            "全数截尾",
            "定时截尾",
            "定数截尾",
            "尾序贯截尾"});
            this.cmbJW.Location = new System.Drawing.Point(655, 232);
            this.cmbJW.Name = "cmbJW";
            this.cmbJW.Size = new System.Drawing.Size(121, 21);
            this.cmbJW.TabIndex = 27;
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label15.ForeColor = System.Drawing.Color.Navy;
            this.label15.Location = new System.Drawing.Point(544, 237);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(105, 14);
            this.label15.TabIndex = 26;
            this.label15.Text = "实验截尾方式：";
            // 
            // txtYBNumber
            // 
            this.txtYBNumber.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtYBNumber.ForeColor = System.Drawing.Color.Navy;
            this.txtYBNumber.Location = new System.Drawing.Point(387, 232);
            this.txtYBNumber.Name = "txtYBNumber";
            this.txtYBNumber.Size = new System.Drawing.Size(100, 21);
            this.txtYBNumber.TabIndex = 25;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label14.ForeColor = System.Drawing.Color.Navy;
            this.label14.Location = new System.Drawing.Point(300, 237);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(77, 14);
            this.label14.TabIndex = 24;
            this.label14.Text = "样本总量：";
            // 
            // txtYLNumber
            // 
            this.txtYLNumber.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtYLNumber.ForeColor = System.Drawing.Color.Navy;
            this.txtYLNumber.Location = new System.Drawing.Point(160, 234);
            this.txtYLNumber.Name = "txtYLNumber";
            this.txtYLNumber.Size = new System.Drawing.Size(121, 21);
            this.txtYLNumber.TabIndex = 23;
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label13.ForeColor = System.Drawing.Color.Navy;
            this.label13.Location = new System.Drawing.Point(65, 238);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(91, 14);
            this.label13.TabIndex = 22;
            this.label13.Text = "应力水平数：";
            // 
            // lbExpSave
            // 
            this.lbExpSave.AutoSize = true;
            this.lbExpSave.Location = new System.Drawing.Point(312, 209);
            this.lbExpSave.Name = "lbExpSave";
            this.lbExpSave.Size = new System.Drawing.Size(29, 12);
            this.lbExpSave.TabIndex = 29;
            this.lbExpSave.Text = "保存";
            this.lbExpSave.Click += new System.EventHandler(this.lbExpSave_Click);
            this.lbExpSave.MouseEnter += new System.EventHandler(this.lbexpSave_MouseEnter);
            this.lbExpSave.MouseLeave += new System.EventHandler(this.lbexpSave_MouseLeave);
            // 
            // panel2
            // 
            this.panel2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel2.BackColor = System.Drawing.Color.CadetBlue;
            this.panel2.Controls.Add(this.txtJXDYL);
            this.panel2.Controls.Add(this.cmbJXDYL);
            this.panel2.Controls.Add(this.txtDYL);
            this.panel2.Controls.Add(this.cmbDYL);
            this.panel2.Controls.Add(this.txtJXZD);
            this.panel2.Controls.Add(this.cmbJZZD);
            this.panel2.Controls.Add(this.txtZD);
            this.panel2.Controls.Add(this.cmbZD);
            this.panel2.Controls.Add(this.label10);
            this.panel2.Controls.Add(this.txtJXSD);
            this.panel2.Controls.Add(this.cmbJXSD);
            this.panel2.Controls.Add(this.label11);
            this.panel2.Controls.Add(this.txtJX);
            this.panel2.Controls.Add(this.cmbJX);
            this.panel2.Controls.Add(this.label12);
            this.panel2.Controls.Add(this.label9);
            this.panel2.Controls.Add(this.txtCGSD);
            this.panel2.Controls.Add(this.cmbSD);
            this.panel2.Controls.Add(this.label8);
            this.panel2.Controls.Add(this.txtCG);
            this.panel2.Controls.Add(this.cmbCG);
            this.panel2.Controls.Add(this.label7);
            this.panel2.Controls.Add(this.label21);
            this.panel2.Controls.Add(this.txtTHYZ);
            this.panel2.Controls.Add(this.label20);
            this.panel2.Controls.Add(this.txtXNTHCS);
            this.panel2.Controls.Add(this.label19);
            this.panel2.Controls.Add(this.lbSave);
            this.panel2.Controls.Add(this.cmbJW);
            this.panel2.Controls.Add(this.label15);
            this.panel2.Controls.Add(this.txtYBNumber);
            this.panel2.Controls.Add(this.label14);
            this.panel2.Controls.Add(this.txtYLNumber);
            this.panel2.Controls.Add(this.label13);
            this.panel2.Controls.Add(this.cbTLSetType);
            this.panel2.Controls.Add(this.label6);
            this.panel2.Controls.Add(this.cbJsMode);
            this.panel2.Controls.Add(this.label5);
            this.panel2.Controls.Add(this.cmbYLType);
            this.panel2.Controls.Add(this.label4);
            this.panel2.Controls.Add(this.lbSubtitle);
            this.panel2.Location = new System.Drawing.Point(12, 39);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(953, 332);
            this.panel2.TabIndex = 5;
            // 
            // txtJXDYL
            // 
            this.txtJXDYL.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtJXDYL.Location = new System.Drawing.Point(820, 180);
            this.txtJXDYL.Name = "txtJXDYL";
            this.txtJXDYL.Size = new System.Drawing.Size(54, 21);
            this.txtJXDYL.TabIndex = 58;
            this.txtJXDYL.Visible = false;
            // 
            // cmbJXDYL
            // 
            this.cmbJXDYL.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.cmbJXDYL.FormattingEnabled = true;
            this.cmbJXDYL.Location = new System.Drawing.Point(739, 179);
            this.cmbJXDYL.Name = "cmbJXDYL";
            this.cmbJXDYL.Size = new System.Drawing.Size(75, 21);
            this.cmbJXDYL.TabIndex = 57;
            this.cmbJXDYL.Text = "电应力";
            this.cmbJXDYL.Visible = false;
            // 
            // txtDYL
            // 
            this.txtDYL.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtDYL.Location = new System.Drawing.Point(820, 129);
            this.txtDYL.Name = "txtDYL";
            this.txtDYL.Size = new System.Drawing.Size(54, 21);
            this.txtDYL.TabIndex = 56;
            this.txtDYL.Visible = false;
            // 
            // cmbDYL
            // 
            this.cmbDYL.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.cmbDYL.FormattingEnabled = true;
            this.cmbDYL.Location = new System.Drawing.Point(739, 129);
            this.cmbDYL.Name = "cmbDYL";
            this.cmbDYL.Size = new System.Drawing.Size(75, 21);
            this.cmbDYL.TabIndex = 55;
            this.cmbDYL.Text = "电应力";
            this.cmbDYL.Visible = false;
            // 
            // txtJXZD
            // 
            this.txtJXZD.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtJXZD.Location = new System.Drawing.Point(655, 183);
            this.txtJXZD.Name = "txtJXZD";
            this.txtJXZD.Size = new System.Drawing.Size(54, 21);
            this.txtJXZD.TabIndex = 54;
            this.txtJXZD.Visible = false;
            // 
            // cmbJZZD
            // 
            this.cmbJZZD.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.cmbJZZD.FormattingEnabled = true;
            this.cmbJZZD.Location = new System.Drawing.Point(574, 184);
            this.cmbJZZD.Name = "cmbJZZD";
            this.cmbJZZD.Size = new System.Drawing.Size(75, 21);
            this.cmbJZZD.TabIndex = 53;
            this.cmbJZZD.Text = "震动";
            this.cmbJZZD.Visible = false;
            // 
            // txtZD
            // 
            this.txtZD.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtZD.Location = new System.Drawing.Point(655, 128);
            this.txtZD.Name = "txtZD";
            this.txtZD.Size = new System.Drawing.Size(54, 21);
            this.txtZD.TabIndex = 52;
            this.txtZD.Visible = false;
            // 
            // cmbZD
            // 
            this.cmbZD.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.cmbZD.FormattingEnabled = true;
            this.cmbZD.Location = new System.Drawing.Point(574, 128);
            this.cmbZD.Name = "cmbZD";
            this.cmbZD.Size = new System.Drawing.Size(75, 21);
            this.cmbZD.TabIndex = 51;
            this.cmbZD.Text = "震动";
            this.cmbZD.Visible = false;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label10.ForeColor = System.Drawing.Color.Navy;
            this.label10.Location = new System.Drawing.Point(530, 187);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(21, 14);
            this.label10.TabIndex = 50;
            this.label10.Text = "％";
            // 
            // txtJXSD
            // 
            this.txtJXSD.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtJXSD.Location = new System.Drawing.Point(467, 186);
            this.txtJXSD.Name = "txtJXSD";
            this.txtJXSD.Size = new System.Drawing.Size(54, 21);
            this.txtJXSD.TabIndex = 49;
            // 
            // cmbJXSD
            // 
            this.cmbJXSD.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.cmbJXSD.FormattingEnabled = true;
            this.cmbJXSD.Location = new System.Drawing.Point(387, 186);
            this.cmbJXSD.Name = "cmbJXSD";
            this.cmbJXSD.Size = new System.Drawing.Size(75, 21);
            this.cmbJXSD.TabIndex = 48;
            this.cmbJXSD.Text = "相对湿度";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label11.ForeColor = System.Drawing.Color.Navy;
            this.label11.Location = new System.Drawing.Point(347, 189);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(21, 14);
            this.label11.TabIndex = 47;
            this.label11.Text = "℃";
            // 
            // txtJX
            // 
            this.txtJX.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtJX.Location = new System.Drawing.Point(287, 185);
            this.txtJX.Name = "txtJX";
            this.txtJX.Size = new System.Drawing.Size(54, 21);
            this.txtJX.TabIndex = 46;
            // 
            // cmbJX
            // 
            this.cmbJX.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.cmbJX.FormattingEnabled = true;
            this.cmbJX.Location = new System.Drawing.Point(160, 185);
            this.cmbJX.Name = "cmbJX";
            this.cmbJX.Size = new System.Drawing.Size(121, 21);
            this.cmbJX.TabIndex = 45;
            this.cmbJX.Text = "温度";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label12.ForeColor = System.Drawing.Color.Navy;
            this.label12.Location = new System.Drawing.Point(53, 186);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(105, 14);
            this.label12.TabIndex = 44;
            this.label12.Text = "产品工作极限：";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label9.ForeColor = System.Drawing.Color.Navy;
            this.label9.Location = new System.Drawing.Point(530, 132);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(21, 14);
            this.label9.TabIndex = 43;
            this.label9.Text = "％";
            // 
            // txtCGSD
            // 
            this.txtCGSD.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtCGSD.Location = new System.Drawing.Point(467, 128);
            this.txtCGSD.Name = "txtCGSD";
            this.txtCGSD.Size = new System.Drawing.Size(54, 21);
            this.txtCGSD.TabIndex = 42;
            // 
            // cmbSD
            // 
            this.cmbSD.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.cmbSD.FormattingEnabled = true;
            this.cmbSD.Location = new System.Drawing.Point(386, 128);
            this.cmbSD.Name = "cmbSD";
            this.cmbSD.Size = new System.Drawing.Size(75, 21);
            this.cmbSD.TabIndex = 41;
            this.cmbSD.Text = "相对湿度";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label8.ForeColor = System.Drawing.Color.Navy;
            this.label8.Location = new System.Drawing.Point(347, 133);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(21, 14);
            this.label8.TabIndex = 40;
            this.label8.Text = "℃";
            // 
            // txtCG
            // 
            this.txtCG.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtCG.Location = new System.Drawing.Point(287, 129);
            this.txtCG.Name = "txtCG";
            this.txtCG.Size = new System.Drawing.Size(54, 21);
            this.txtCG.TabIndex = 39;
            // 
            // cmbCG
            // 
            this.cmbCG.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.cmbCG.FormattingEnabled = true;
            this.cmbCG.Location = new System.Drawing.Point(160, 128);
            this.cmbCG.Name = "cmbCG";
            this.cmbCG.Size = new System.Drawing.Size(121, 21);
            this.cmbCG.TabIndex = 38;
            this.cmbCG.Text = "温度";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label7.ForeColor = System.Drawing.Color.Navy;
            this.label7.Location = new System.Drawing.Point(53, 129);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(105, 14);
            this.label7.TabIndex = 37;
            this.label7.Text = "常规使用条件：";
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label21.ForeColor = System.Drawing.Color.Navy;
            this.label21.Location = new System.Drawing.Point(491, 87);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(14, 14);
            this.label21.TabIndex = 33;
            this.label21.Text = "V";
            // 
            // txtTHYZ
            // 
            this.txtTHYZ.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtTHYZ.ForeColor = System.Drawing.Color.Navy;
            this.txtTHYZ.Location = new System.Drawing.Point(386, 83);
            this.txtTHYZ.Name = "txtTHYZ";
            this.txtTHYZ.Size = new System.Drawing.Size(101, 21);
            this.txtTHYZ.TabIndex = 32;
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label20.ForeColor = System.Drawing.Color.Navy;
            this.label20.Location = new System.Drawing.Point(301, 86);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(77, 14);
            this.label20.TabIndex = 31;
            this.label20.Text = "退化阈值：";
            // 
            // txtXNTHCS
            // 
            this.txtXNTHCS.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtXNTHCS.ForeColor = System.Drawing.Color.Navy;
            this.txtXNTHCS.Location = new System.Drawing.Point(160, 83);
            this.txtXNTHCS.Name = "txtXNTHCS";
            this.txtXNTHCS.Size = new System.Drawing.Size(121, 21);
            this.txtXNTHCS.TabIndex = 30;
            this.txtXNTHCS.Text = "三极管浮压";
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label19.ForeColor = System.Drawing.Color.Navy;
            this.label19.Location = new System.Drawing.Point(53, 86);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(105, 14);
            this.label19.TabIndex = 29;
            this.label19.Text = "性能退化参数：";
            // 
            // cbTLSetType
            // 
            this.cbTLSetType.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.cbTLSetType.ForeColor = System.Drawing.Color.Navy;
            this.cbTLSetType.FormattingEnabled = true;
            this.cbTLSetType.Items.AddRange(new object[] {
            "恒定应力",
            "步进应力",
            "步降应力"});
            this.cbTLSetType.Location = new System.Drawing.Point(655, 46);
            this.cbTLSetType.Name = "cbTLSetType";
            this.cbTLSetType.Size = new System.Drawing.Size(121, 21);
            this.cbTLSetType.TabIndex = 7;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label6.ForeColor = System.Drawing.Color.Navy;
            this.label6.Location = new System.Drawing.Point(544, 49);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(105, 14);
            this.label6.TabIndex = 6;
            this.label6.Text = "应力施加方式：";
            // 
            // cbJsMode
            // 
            this.cbJsMode.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.cbJsMode.ForeColor = System.Drawing.Color.Navy;
            this.cbJsMode.FormattingEnabled = true;
            this.cbJsMode.Location = new System.Drawing.Point(386, 46);
            this.cbJsMode.Name = "cbJsMode";
            this.cbJsMode.Size = new System.Drawing.Size(121, 21);
            this.cbJsMode.TabIndex = 5;
            this.cbJsMode.Click += new System.EventHandler(this.cbJsMode_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label5.ForeColor = System.Drawing.Color.Navy;
            this.label5.Location = new System.Drawing.Point(301, 49);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(77, 14);
            this.label5.TabIndex = 4;
            this.label5.Text = "加速模型：";
            // 
            // cmbYLType
            // 
            this.cmbYLType.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.cmbYLType.ForeColor = System.Drawing.Color.Navy;
            this.cmbYLType.FormattingEnabled = true;
            this.cmbYLType.Location = new System.Drawing.Point(160, 46);
            this.cmbYLType.Name = "cmbYLType";
            this.cmbYLType.Size = new System.Drawing.Size(121, 21);
            this.cmbYLType.TabIndex = 3;
            this.cmbYLType.Click += new System.EventHandler(this.cmbYLType_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("FontAwesome", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label4.ForeColor = System.Drawing.Color.Navy;
            this.label4.Location = new System.Drawing.Point(77, 49);
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
            this.lbtitle.Text = "项目--实验方案设计";
            // 
            // panel3
            // 
            this.panel3.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel3.BackColor = System.Drawing.Color.CadetBlue;
            this.panel3.Controls.Add(this.dataGridView1);
            this.panel3.Controls.Add(this.lbCreateExp);
            this.panel3.Controls.Add(this.lbExpSave);
            this.panel3.Controls.Add(this.lbExp);
            this.panel3.Location = new System.Drawing.Point(12, 377);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(953, 242);
            this.panel3.TabIndex = 6;
            // 
            // dataGridView1
            // 
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Column1,
            this.Column2,
            this.Column3,
            this.Column4});
            this.dataGridView1.Location = new System.Drawing.Point(148, 32);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowTemplate.Height = 23;
            this.dataGridView1.Size = new System.Drawing.Size(644, 150);
            this.dataGridView1.TabIndex = 32;
            // 
            // Column1
            // 
            this.Column1.HeaderText = "温度(℃)";
            this.Column1.Name = "Column1";
            this.Column1.Width = 150;
            // 
            // Column2
            // 
            this.Column2.HeaderText = "湿度(％)";
            this.Column2.Name = "Column2";
            this.Column2.Width = 150;
            // 
            // Column3
            // 
            this.Column3.HeaderText = "实验样本量";
            this.Column3.Name = "Column3";
            this.Column3.Width = 150;
            // 
            // Column4
            // 
            this.Column4.HeaderText = "实验时间(h)";
            this.Column4.Name = "Column4";
            this.Column4.Width = 150;
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
            this.panel1.Location = new System.Drawing.Point(2, 3);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(975, 31);
            this.panel1.TabIndex = 4;
            // 
            // frmExpermentTH
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Teal;
            this.ClientSize = new System.Drawing.Size(977, 720);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel3);
            this.Controls.Add(this.panel1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "frmExpermentTH";
            this.Text = "frmExpermentTH";
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label lbCreateExp;
        private System.Windows.Forms.Label lbSave;
        private System.Windows.Forms.ComboBox cmbJW;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.TextBox txtYBNumber;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.TextBox txtYLNumber;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label lbExpSave;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Label label21;
        private System.Windows.Forms.TextBox txtTHYZ;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.TextBox txtXNTHCS;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.ComboBox cbTLSetType;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ComboBox cbJsMode;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox cmbYLType;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label lbSubtitle;
        private System.Windows.Forms.Label lbtitle;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Label lbExp;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.TextBox txtJXDYL;
        private System.Windows.Forms.ComboBox cmbJXDYL;
        private System.Windows.Forms.TextBox txtDYL;
        private System.Windows.Forms.ComboBox cmbDYL;
        private System.Windows.Forms.TextBox txtJXZD;
        private System.Windows.Forms.ComboBox cmbJZZD;
        private System.Windows.Forms.TextBox txtZD;
        private System.Windows.Forms.ComboBox cmbZD;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox txtJXSD;
        private System.Windows.Forms.ComboBox cmbJXSD;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox txtJX;
        private System.Windows.Forms.ComboBox cmbJX;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox txtCGSD;
        private System.Windows.Forms.ComboBox cmbSD;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox txtCG;
        private System.Windows.Forms.ComboBox cmbCG;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column1;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column2;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column3;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column4;
    }
}