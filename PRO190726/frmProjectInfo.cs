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
using DLLProjectInfo;

namespace PRO190726
{
    public partial class frmProjectInfo : Form
    {
        public frmProjectInfo()
        {
            InitializeComponent();
            UIInit();
        }

        ToolStripStatusLabel m_stlb = null;
        public frmProjectInfo(ToolStripStatusLabel stlb)
        {
            InitializeComponent();
            UIInit();
            m_stlb = stlb;
        }

        DoProjectInfo m_Pro = null;
        //f288
        public void UIInit() {
            this.lbProjectInfotxt.Text = "\uf288 项目信息填写：";
            this.lbProjectInfotxt.Font = new Font("FontAwesome", 13,FontStyle.Bold);
            this.lbProjectInfotxt.ForeColor = Color.White;

            //f1c4

            this.lbProjectName.Text = "\uf1c4 项目名称：";
            this.lbProjectName.Font = new Font("FontAwesome", 12);
            this.lbProjectName.ForeColor = Color.White;

            //f1c4

            this.lbProductName.Text = "\uf1b3 产品名称：";
            this.lbProductName.Font = new Font("FontAwesome", 12);
            this.lbProductName.ForeColor = Color.White;

            //f02d
            this.lbProductGN.Text = "\uf02d 产品功能概述：";
            this.lbProductGN.Font = new Font("FontAwesome", 12);
            this.lbProductGN.ForeColor = Color.White;


            //f0b1
            this.lbProductUse.Text = "\uf0b1 产品应用领域：";
            this.lbProductUse.Font = new Font("FontAwesome", 12);
            this.lbProductUse.ForeColor = Color.White;

            //f0b1
            this.lbExpTime.Text = "\uf073 实验时间：";
            this.lbExpTime.Font = new Font("FontAwesome", 12);
            this.lbExpTime.ForeColor = Color.White;

            //f041
            this.lbExpAddress.Text = "\uf041 实验地点：";
            this.lbExpAddress.Font = new Font("FontAwesome", 12);
            this.lbExpAddress.ForeColor = Color.White;

            //f041
            this.lbSave.Text = "\uf0c7 保存";
            this.lbSave.Font = new Font("FontAwesome", 15,FontStyle.Bold);
            this.lbSave.ForeColor = Color.Blue;
        }

        private void lbProjectName_Click(object sender, EventArgs e)
        {

        }

        private void lbSave_MouseEnter(object sender, EventArgs e)
        {
            this.lbSave.ForeColor = Color.White;
            this.Cursor = Cursors.Hand;
           
        }

        private void lbSave_MouseLeave(object sender, EventArgs e)
        {
            this.lbSave.ForeColor = Color.Blue;
            this.Cursor = Cursors.Default;
        }

        private void lbSave_Click(object sender, EventArgs e)
        {
            if (m_Pro == null) {
                m_Pro = new DoProjectInfo();
            }

            string ProjectName = this.txtProjectName.Text.Trim();
            Guid guid = Guid.NewGuid();
            if (m_Pro.SaveProjectInfo(ProjectName, guid))
            {
                ProDefine.NowProjectName = ProjectName;
                m_stlb.Text = ProjectName;
                MessageBox.Show("保存成功");
            }
            else {
                MessageBox.Show("保存失败");
            }

        }
    }
}
