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
    public partial class frmSMData : Form
    {
        public frmSMData()
        {
            InitializeComponent();
            InitUI();
        }

        private void InitUI() {
            this.lbDataIn.Text = "\uf149 数据导入";
            this.lbDataIn.Font = new Font("FontAwesome", 14, FontStyle.Bold);
            this.lbDataIn.ForeColor = Color.LightCyan;

            this.lbHandIn.Text = "\uf044 手动输入";
            this.lbHandIn.Font = new Font("FontAwesome", 14, FontStyle.Bold);
            this.lbHandIn.ForeColor = Color.LightCyan;

            this.lbSave.Text = "\uf0c7 保存";
            this.lbSave.Font = new Font("FontAwesome", 14, FontStyle.Bold);
            this.lbSave.ForeColor = Color.LightCyan;

            //lbChart

            this.lbChart.Text = "\uf1fe 图表";
            this.lbChart.Font = new Font("FontAwesome", 14, FontStyle.Bold);
            this.lbChart.ForeColor = Color.LightCyan;

            this.lbSMNH.Text = "\uf2b8 寿命分布拟合";
            this.lbSMNH.Font = new Font("FontAwesome", 14, FontStyle.Bold);
            this.lbSMNH.ForeColor = Color.LightCyan;

            this.lbJSNH.Text = "\uf2b8 加速模型拟合";
            this.lbJSNH.Font = new Font("FontAwesome", 14, FontStyle.Bold);
            this.lbJSNH.ForeColor = Color.LightCyan;

            //f110
            this.lbDataResult.Text = "\uf110 数据处理结果";
            this.lbDataResult.Font = new Font("FontAwesome", 14, FontStyle.Bold);
            this.lbDataResult.ForeColor = Color.LightCyan;
        }

        private void lbSMNH_MouseEnter(object sender, EventArgs e)
        {
            this.lbSMNH.ForeColor = Color.Blue;
        }

        private void lbSMNH_MouseLeave(object sender, EventArgs e)
        {
            this.lbSMNH.ForeColor = Color.LightCyan;
        }

        private void lbJSNH_MouseLeave(object sender, EventArgs e)
        {
            this.lbJSNH.ForeColor = Color.LightCyan;
        }

        private void lbJSNH_MouseEnter(object sender, EventArgs e)
        {
            this.lbJSNH.ForeColor = Color.Blue;
        }

        private void lbSMNH_Click(object sender, EventArgs e)
        {
            frmFBNH frmFB = new frmFBNH();
            frmFB.Show();
        }

        private void lbJSNH_Click(object sender, EventArgs e)
        {
            frmJSMXNH frmJS = new frmJSMXNH();
            frmJS.Show();
        }

        private void lbDataIn_MouseEnter(object sender, EventArgs e)
        {
            this.lbDataIn.ForeColor = Color.Blue;
        }

        private void lbDataIn_MouseLeave(object sender, EventArgs e)
        {
            this.lbDataIn.ForeColor = Color.LightCyan;
        }

        private void lbHandIn_MouseEnter(object sender, EventArgs e)
        {
            this.lbHandIn.ForeColor = Color.Blue;
        }

        private void lbHandIn_MouseLeave(object sender, EventArgs e)
        {
            this.lbHandIn.ForeColor = Color.LightCyan;
        }

        private void lbSave_MouseEnter(object sender, EventArgs e)
        {
            this.lbSave.ForeColor = Color.Blue;
        }

        private void lbSave_MouseLeave(object sender, EventArgs e)
        {
            this.lbSave.ForeColor = Color.LightCyan;
        }

        private void lbChart_MouseEnter(object sender, EventArgs e)
        {
            this.lbChart.ForeColor = Color.Blue;
        }

        private void lbChart_MouseLeave(object sender, EventArgs e)
        {
            this.lbChart.ForeColor = Color.LightCyan;
        }
    }
}
