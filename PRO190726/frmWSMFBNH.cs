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
    public partial class frmWSMFBNH : Form
    {
        public frmWSMFBNH()
        {
            InitializeComponent();
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {


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
