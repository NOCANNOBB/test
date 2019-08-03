using Define;
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
    public partial class frmYHExperienceSM : Form
    {
        public frmYHExperienceSM()
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


        private int YLReturnValue = 0;
        private int JSModReturnValue = 0;
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

        private void cmbYLType_Click(object sender, EventArgs e)
        {
            int ValueParam = GetYLValue(this.cmbYLType.Text.Trim());
            frmYLSelect frmYL = new frmYLSelect(ValueParam);
            frmYL.ShowDialog();
            if (frmYL.DialogResult == System.Windows.Forms.DialogResult.OK)
            {
                int returnValue = frmYL.returnValue;
                YLReturnValue = returnValue;
                SetYLValue(returnValue);

            }
        }

        private int GetYLValue(string YLText)
        {
            int returnValue = 0;
            if (YLText.Contains("温度"))
            {
                returnValue = ProDefine.SetBit(returnValue, 0);
            }
            if (YLText.Contains("湿度"))
            {
                returnValue = ProDefine.SetBit(returnValue, 1);
            }

            if (YLText.Contains("震动"))
            {
                returnValue = ProDefine.SetBit(returnValue, 2);
            }
            if (YLText.Contains("电应力"))
            {
                returnValue = ProDefine.SetBit(returnValue, 3);
            }
            return returnValue;
        }

        private void SetYLValue(int ValueParam)
        {
            string YLText = "";
            if (ProDefine.GetBit(ValueParam, 0))
            {
                YLText += "温度+";
            }
            if (ProDefine.GetBit(ValueParam, 1))
            {
                YLText += "湿度+";
            }
            if (ProDefine.GetBit(ValueParam, 2))
            {
                YLText += "震动+";
            }
            if (ProDefine.GetBit(ValueParam, 2))
            {
                YLText += "电应力+";
            }
            if (YLText != "")
            {
                YLText = YLText.Substring(0, YLText.Length - 1);
            }

            this.cmbYLType.Text = YLText;
        }
    }
}
