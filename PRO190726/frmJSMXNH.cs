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
    public partial class frmJSMXNH : Form
    {
        public frmJSMXNH()
        {
            InitializeComponent();
            InitUI();
        }

        private void InitUI()
        {

            this.lb_Close.Text = "\uf00d";
            this.lb_Close.Font = new Font("FontAwesome", 12);
            this.lb_Close.ForeColor = Color.Black;
        }


        private void lb_Close_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void lb_Close_MouseEnter(object sender, EventArgs e)
        {
            this.lb_Close.ForeColor = Color.Red;
        }

        private void lb_Close_MouseLeave(object sender, EventArgs e)
        {
            this.lb_Close.ForeColor = Color.Black;
        }
    }
}
