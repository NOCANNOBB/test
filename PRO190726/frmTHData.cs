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
    public partial class frmTHData : Form
    {
        public frmTHData()
        {
            InitializeComponent();
            InitUI();
        }


        private void InitUI()
        {
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

            this.lbJSMOD.Text = "\uf2b8 寿命分布拟合";
            this.lbJSMOD.Font = new Font("FontAwesome", 12, FontStyle.Bold);
            this.lbJSMOD.ForeColor = Color.LightCyan;

            this.lbTHGJ.Text = "\uf2b8 加速模型拟合";
            this.lbTHGJ.Font = new Font("FontAwesome", 12, FontStyle.Bold);
            this.lbTHGJ.ForeColor = Color.LightCyan;

            this.lbWSMFB.Text = "\uf2b8 加速模型拟合";
            this.lbWSMFB.Font = new Font("FontAwesome", 12, FontStyle.Bold);
            this.lbWSMFB.ForeColor = Color.LightCyan;

            //f110
            this.lbDataResult.Text = "\uf110 数据处理结果";
            this.lbDataResult.Font = new Font("FontAwesome", 14, FontStyle.Bold);
            this.lbDataResult.ForeColor = Color.LightCyan;
        }



        private void label17_Click(object sender, EventArgs e)
        {
            frmTHGJNH frmTH = new frmTHGJNH();
            frmTH.Show();
        }

        private void frmTHData_Load(object sender, EventArgs e)
        {

        }

        private void label16_Click(object sender, EventArgs e)
        {
            frmWSMFBNH frmWS = new frmWSMFBNH();
            frmWS.Show();
        }

        private void label15_Click(object sender, EventArgs e)
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

        private void lbTHGJ_MouseEnter(object sender, EventArgs e)
        {
            this.lbTHGJ.ForeColor = Color.Blue;
        }

        private void lbTHGJ_MouseLeave(object sender, EventArgs e)
        {
            this.lbTHGJ.ForeColor = Color.LightCyan;
        }

        private void lbWSMFB_MouseEnter(object sender, EventArgs e)
        {
            this.lbWSMFB.ForeColor = Color.Blue;
        }

        private void lbWSMFB_MouseLeave(object sender, EventArgs e)
        {
            this.lbWSMFB.ForeColor = Color.LightCyan;
        }

        private void lbJSMOD_MouseEnter(object sender, EventArgs e)
        {
            this.lbJSMOD.ForeColor = Color.Blue;
        }

        private void lbJSMOD_MouseLeave(object sender, EventArgs e)
        {
            this.lbJSMOD.ForeColor = Color.LightCyan;
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
