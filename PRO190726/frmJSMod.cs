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
    public partial class frmJSMod : Form
    {
        public frmJSMod()
        {
            InitializeComponent();
            InitUI();
        }

        public frmJSMod(int ValueParam)
        {
            returnValue = ValueParam;
            InitializeComponent();
            InitUI();
        }

        private void InitUI()
        {

            this.lbTitle.Text = "\uf1cd 应力类型选择";
            this.lbTitle.Font = new Font("FontAwesome", 12);
            this.lbTitle.ForeColor = Color.LightCyan;

            this.lbOK.Text = "\uf00c 确定";
            this.lbOK.Font = new Font("FontAwesome", 12);
            this.lbOK.ForeColor = Color.LightCyan;

        }

        private void lbOK_MouseEnter(object sender, EventArgs e)
        {
            this.lbOK.ForeColor = Color.DeepSkyBlue;
        }

        private void lbOK_MouseLeave(object sender, EventArgs e)
        {
            this.lbOK.ForeColor = Color.LightCyan;
        }

        public int returnValue = 0; 
        private void lbOK_Click(object sender, EventArgs e)
        {

            this.DialogResult = DialogResult.OK;
            this.Close();
        }
    }
}
