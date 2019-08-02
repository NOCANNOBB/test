namespace PRO190726
{
    partial class frmYLSelect
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
            this.lbYLType = new System.Windows.Forms.Label();
            this.ckWD = new System.Windows.Forms.CheckBox();
            this.ckSD = new System.Windows.Forms.CheckBox();
            this.ckZD = new System.Windows.Forms.CheckBox();
            this.ckDYL = new System.Windows.Forms.CheckBox();
            this.lbOK = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // lbYLType
            // 
            this.lbYLType.AutoSize = true;
            this.lbYLType.BackColor = System.Drawing.Color.SteelBlue;
            this.lbYLType.ForeColor = System.Drawing.Color.LightCyan;
            this.lbYLType.Location = new System.Drawing.Point(13, 13);
            this.lbYLType.Name = "lbYLType";
            this.lbYLType.Size = new System.Drawing.Size(77, 12);
            this.lbYLType.TabIndex = 0;
            this.lbYLType.Text = "应力类型选择";
            // 
            // ckWD
            // 
            this.ckWD.AutoSize = true;
            this.ckWD.BackColor = System.Drawing.Color.LightBlue;
            this.ckWD.Font = new System.Drawing.Font("FontAwesome", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.ckWD.Location = new System.Drawing.Point(38, 57);
            this.ckWD.Name = "ckWD";
            this.ckWD.Size = new System.Drawing.Size(192, 19);
            this.ckWD.TabIndex = 1;
            this.ckWD.Text = "        温度         ";
            this.ckWD.UseVisualStyleBackColor = false;
            // 
            // ckSD
            // 
            this.ckSD.AutoSize = true;
            this.ckSD.BackColor = System.Drawing.Color.LightBlue;
            this.ckSD.Font = new System.Drawing.Font("FontAwesome", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.ckSD.Location = new System.Drawing.Point(38, 94);
            this.ckSD.Name = "ckSD";
            this.ckSD.Size = new System.Drawing.Size(192, 19);
            this.ckSD.TabIndex = 2;
            this.ckSD.Text = "        湿度         ";
            this.ckSD.UseVisualStyleBackColor = false;
            // 
            // ckZD
            // 
            this.ckZD.AutoSize = true;
            this.ckZD.BackColor = System.Drawing.Color.LightBlue;
            this.ckZD.Font = new System.Drawing.Font("FontAwesome", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.ckZD.Location = new System.Drawing.Point(38, 132);
            this.ckZD.Name = "ckZD";
            this.ckZD.Size = new System.Drawing.Size(192, 19);
            this.ckZD.TabIndex = 3;
            this.ckZD.Text = "        震动         ";
            this.ckZD.UseVisualStyleBackColor = false;
            // 
            // ckDYL
            // 
            this.ckDYL.AutoSize = true;
            this.ckDYL.BackColor = System.Drawing.Color.LightBlue;
            this.ckDYL.Font = new System.Drawing.Font("FontAwesome", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.ckDYL.Location = new System.Drawing.Point(38, 174);
            this.ckDYL.Name = "ckDYL";
            this.ckDYL.Size = new System.Drawing.Size(191, 19);
            this.ckDYL.TabIndex = 4;
            this.ckDYL.Text = "       电应力        ";
            this.ckDYL.UseVisualStyleBackColor = false;
            // 
            // lbOK
            // 
            this.lbOK.AutoSize = true;
            this.lbOK.ForeColor = System.Drawing.Color.DeepSkyBlue;
            this.lbOK.Location = new System.Drawing.Point(109, 236);
            this.lbOK.Name = "lbOK";
            this.lbOK.Size = new System.Drawing.Size(29, 12);
            this.lbOK.TabIndex = 5;
            this.lbOK.Text = "确定";
            this.lbOK.Click += new System.EventHandler(this.lbOK_Click);
            this.lbOK.MouseEnter += new System.EventHandler(this.lbOK_MouseEnter);
            this.lbOK.MouseLeave += new System.EventHandler(this.lbOK_MouseLeave);
            // 
            // frmYLSelect
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.SteelBlue;
            this.ClientSize = new System.Drawing.Size(265, 281);
            this.Controls.Add(this.lbOK);
            this.Controls.Add(this.ckDYL);
            this.Controls.Add(this.ckZD);
            this.Controls.Add(this.ckSD);
            this.Controls.Add(this.ckWD);
            this.Controls.Add(this.lbYLType);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "frmYLSelect";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "frmYLSelect";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lbYLType;
        private System.Windows.Forms.CheckBox ckWD;
        private System.Windows.Forms.CheckBox ckSD;
        private System.Windows.Forms.CheckBox ckZD;
        private System.Windows.Forms.CheckBox ckDYL;
        private System.Windows.Forms.Label lbOK;
    }
}