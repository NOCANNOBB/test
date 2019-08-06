using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PRO190726
{
    public partial class frmExperment : Form
    {
        public frmExperment()
        {
            InitializeComponent();
            InitUI();
        }

        private void InitUI() {
            this.lbStart.Text = "\uf04b 开始实验";
            this.lbStart.Font = new Font("FontAwesome", 15, FontStyle.Bold);
            this.lbStart.ForeColor = Color.White;


            this.lbEnd.Text = "\uf04d 停止实验";
            this.lbEnd.Font = new Font("FontAwesome", 15, FontStyle.Bold);
            this.lbEnd.ForeColor = Color.White;
        }

        private void lbStart_Click(object sender, EventArgs e)
        {
            this.lbStart.Enabled = false;
            this.lbEnd.Enabled = true;
        }

        private void lbStart_MouseEnter(object sender, EventArgs e)
        {
            this.lbStart.ForeColor = Color.Blue;
        }

        private void lbStart_MouseLeave(object sender, EventArgs e)
        {
            this.lbStart.ForeColor = Color.White;
        }

        private void lbEnd_Click(object sender, EventArgs e)
        {
            this.lbEnd.Enabled = false ;
            this.lbStart.Enabled = true;
        }

        private void lbEnd_MouseEnter(object sender, EventArgs e)
        {
            this.lbEnd.ForeColor = Color.Blue;
        }

        private void lbEnd_MouseLeave(object sender, EventArgs e)
        {
            this.lbEnd.ForeColor = Color.White;
        }
    }
}
