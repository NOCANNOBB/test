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
    public partial class frmExpermentTH : Form
    {
        public frmExpermentTH()
        {
            InitializeComponent();
            initUI();
        }


        private void initUI()
        {//f040
            this.lbtitle.Text = "\uf2dd 项目--实验方案设计";
            this.lbtitle.Font = new Font("FontAwesome", 13, FontStyle.Bold);
            this.lbtitle.ForeColor = Color.Lavender;

            this.lbSubtitle.Text = "\uf040 实验基本信息填写";
            this.lbSubtitle.Font = new Font("FontAwesome", 13);
            this.lbSubtitle.ForeColor = Color.Lavender;

            this.lbSave.Text = "\uf0c7 保存";
            this.lbSave.Font = new Font("FontAwesome", 12);
            this.lbSave.ForeColor = Color.Lavender;//

            this.lbExpSave.Text = "\uf0c7 保存";
            this.lbExpSave.Font = new Font("FontAwesome", 12);
            this.lbExpSave.ForeColor = Color.Lavender;//

            this.lbCreateExp.Text = "\uf202 生成实验方案";
            this.lbCreateExp.Font = new Font("FontAwesome", 12);
            this.lbCreateExp.ForeColor = Color.Lavender;//

            this.lbExp.Text = "\uf14b 实验方案要素设计";
            this.lbExp.Font = new Font("FontAwesome", 13);
            this.lbExp.ForeColor = Color.Lavender;//

        }

        private void lbSave_MouseEnter(object sender, EventArgs e)
        {

            this.lbSave.ForeColor = Color.LightCoral;
        }

        private void lbSave_MouseLeave(object sender, EventArgs e)
        {
            this.lbSave.ForeColor = Color.Lavender;
        }

        private void lbexpSave_MouseEnter(object sender, EventArgs e)
        {
            this.lbExpSave.ForeColor = Color.LightCoral;
        }

        private void lbexpSave_MouseLeave(object sender, EventArgs e)
        {
            this.lbExpSave.ForeColor = Color.Lavender;
        }

        private void lbCreateExp_MouseEnter(object sender, EventArgs e)
        {
            this.lbCreateExp.ForeColor = Color.LightCoral;//
        }

        private void lbCreateExp_MouseLeave(object sender, EventArgs e)
        {
            this.lbCreateExp.ForeColor = Color.Lavender;//
        }
    }
}
