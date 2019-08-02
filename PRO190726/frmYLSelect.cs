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
    public partial class frmYLSelect : Form
    {
        public frmYLSelect()
        {
            InitializeComponent();

            InitUI();
        }

        public frmYLSelect(int SelectValue)
        {
            InitializeComponent();
            returnValue = SelectValue;
            InitUI();
        }

        private void InitUI() {

            this.lbYLType.Text = "\uf1cd 应力类型选择";
            this.lbYLType.Font = new Font("FontAwesome", 12);
            this.lbYLType.ForeColor = Color.LightCyan;

            this.lbOK.Text = "\uf00c 确定";
            this.lbOK.Font = new Font("FontAwesome", 12);
            this.lbOK.ForeColor = Color.LightCyan;

            this.ckWD.Checked = ProDefine.GetBit(returnValue,0);
            this.ckSD.Checked = ProDefine.GetBit(returnValue,1);
            this.ckZD.Checked = ProDefine.GetBit(returnValue,2);
            this.ckDYL.Checked = ProDefine.GetBit(returnValue,3);


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
            if (ckWD.Checked)
            {
                returnValue = ProDefine.SetBit(returnValue, 0);
            }
            else {
                returnValue = ProDefine.ClearBit(returnValue, 0);
            }
            if (ckSD.Checked) {
                returnValue = ProDefine.SetBit(returnValue,1);
            }
            else
            {
                returnValue = ProDefine.ClearBit(returnValue, 1);
            }
            if (ckZD.Checked) {
                returnValue = ProDefine.SetBit(returnValue,2);
            }
            else
            {
                returnValue = ProDefine.ClearBit(returnValue, 2);
            }
            if (ckDYL.Checked) {
                returnValue = ProDefine.SetBit(returnValue, 3);
            }
            else
            {
                returnValue = ProDefine.ClearBit(returnValue, 3);
            }
            this.DialogResult = DialogResult.OK;
            this.Close();
        }
    }
}
