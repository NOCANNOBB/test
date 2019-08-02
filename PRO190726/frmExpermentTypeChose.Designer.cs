namespace PRO190726
{
    partial class frmExpermentTypeChose
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
            this.radioGroup1 = new DevExpress.XtraEditors.RadioGroup();
            this.lbOK = new System.Windows.Forms.Label();
            this.lbCancle = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.radioGroup1.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // radioGroup1
            // 
            this.radioGroup1.EditValue = ((short)(0));
            this.radioGroup1.Location = new System.Drawing.Point(86, 31);
            this.radioGroup1.Name = "radioGroup1";
            this.radioGroup1.Properties.Appearance.BackColor = System.Drawing.Color.LightCyan;
            this.radioGroup1.Properties.Appearance.Options.UseBackColor = true;
            this.radioGroup1.Properties.GlyphAlignment = DevExpress.Utils.HorzAlignment.Default;
            this.radioGroup1.Properties.Items.AddRange(new DevExpress.XtraEditors.Controls.RadioGroupItem[] {
            new DevExpress.XtraEditors.Controls.RadioGroupItem(((short)(0)), "加速寿命实验方案"),
            new DevExpress.XtraEditors.Controls.RadioGroupItem(((short)(1)), "加速退化试验方案")});
            this.radioGroup1.Size = new System.Drawing.Size(315, 129);
            this.radioGroup1.TabIndex = 0;
            // 
            // lbOK
            // 
            this.lbOK.AutoSize = true;
            this.lbOK.Location = new System.Drawing.Point(143, 198);
            this.lbOK.Name = "lbOK";
            this.lbOK.Size = new System.Drawing.Size(41, 12);
            this.lbOK.TabIndex = 1;
            this.lbOK.Text = "label1";
            this.lbOK.Click += new System.EventHandler(this.lbOK_Click);
            this.lbOK.MouseEnter += new System.EventHandler(this.lbOK_MouseEnter);
            this.lbOK.MouseLeave += new System.EventHandler(this.lbOK_MouseLeave);
            // 
            // lbCancle
            // 
            this.lbCancle.AutoSize = true;
            this.lbCancle.Location = new System.Drawing.Point(299, 198);
            this.lbCancle.Name = "lbCancle";
            this.lbCancle.Size = new System.Drawing.Size(41, 12);
            this.lbCancle.TabIndex = 2;
            this.lbCancle.Text = "label2";
            this.lbCancle.Click += new System.EventHandler(this.lbCancle_Click);
            this.lbCancle.MouseEnter += new System.EventHandler(this.lbCancle_MouseEnter);
            this.lbCancle.MouseLeave += new System.EventHandler(this.lbCancle_MouseLeave);
            // 
            // frmExpermentTypeChose
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Azure;
            this.ClientSize = new System.Drawing.Size(475, 239);
            this.Controls.Add(this.lbCancle);
            this.Controls.Add(this.lbOK);
            this.Controls.Add(this.radioGroup1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "frmExpermentTypeChose";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "frmExpermentTypeChose";
            ((System.ComponentModel.ISupportInitialize)(this.radioGroup1.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraEditors.RadioGroup radioGroup1;
        private System.Windows.Forms.Label lbOK;
        private System.Windows.Forms.Label lbCancle;
    }
}