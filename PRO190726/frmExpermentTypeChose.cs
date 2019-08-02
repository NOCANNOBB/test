using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Define;

namespace PRO190726
{
    public partial class frmExpermentTypeChose : Form
    {
        public frmExpermentTypeChose()
        {
            InitializeComponent();

            this.lbOK.Text = "\uf00c 确定";
            this.lbOK.Font = new Font("FontAwesome", 12);
            this.lbOK.ForeColor = Color.LightBlue;


            this.lbCancle.Text = "\uf057 取消";
            this.lbCancle.Font = new Font("FontAwesome", 12);
            this.lbCancle.ForeColor = Color.LightBlue;
        }

        private void lbCancle_Click(object sender, EventArgs e)
        {
            DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.Close();
        }

        private void lbOK_MouseEnter(object sender, EventArgs e)
        {
            this.lbOK.ForeColor = Color.Blue;
        }

        private void lbOK_MouseLeave(object sender, EventArgs e)
        {
            this.lbOK.ForeColor = Color.LightBlue;
        }

        private void lbCancle_MouseEnter(object sender, EventArgs e)
        {
            this.lbCancle.ForeColor = Color.Blue;
        }

        private void lbCancle_MouseLeave(object sender, EventArgs e)
        {
            this.lbCancle.ForeColor = Color.LightBlue;
        }

        private void lbOK_Click(object sender, EventArgs e)
        {
            DialogResult = System.Windows.Forms.DialogResult.OK;
            frmSetInfo.ExpermentType = this.radioGroup1.SelectedIndex;
            this.Close();
        }
    }
}
