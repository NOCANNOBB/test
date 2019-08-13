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
    public partial class frmExpermentSM : Form
    {
        public frmExpermentSM()
        {
            InitializeComponent();
            initUI();
        }
        DoProjectInfo m_Pro;
        private void initUI()
        {//f040
            this.lbtitle.Text = "\uf2dd 项目--实验方案设计";
            this.lbtitle.Font = new Font("FontAwesome", 13,FontStyle.Bold);
            this.lbtitle.ForeColor = Color.Lavender;

            this.lbSubtitle.Text = "\uf040 实验基本信息填写";
            this.lbSubtitle.Font = new Font("FontAwesome", 13);
            this.lbSubtitle.ForeColor = Color.Lavender;

            this.lbSave.Text = "\uf0c7 保存";
            this.lbSave.Font = new Font("FontAwesome", 12);
            this.lbSave.ForeColor = Color.Lavender;//

            this.lbexpSave.Text = "\uf0c7 保存";
            this.lbexpSave.Font = new Font("FontAwesome", 12);
            this.lbexpSave.ForeColor = Color.Lavender;//

            this.lbCreateExp.Text = "\uf202 生成实验方案";
            this.lbCreateExp.Font = new Font("FontAwesome", 12);
            this.lbCreateExp.ForeColor = Color.Lavender;//

            this.lbExp.Text = "\uf14b 实验方案要素设计";
            this.lbExp.Font = new Font("FontAwesome", 13);
            this.lbExp.ForeColor = Color.Lavender;//

            m_Pro = new DoProjectInfo();
            DoInitUI();
        
        }


        private void DoInitUI() {
            try {
                m_Pro.GetExpermentInfo(ProDefine.g_MyProject.GUID.ToString());
                if (ProDefine.g_SMExpermentParam != null) {
                    SetYLValue(ProDefine.g_SMExpermentParam.YLType);
                    SetYLModValue(ProDefine.g_SMExpermentParam.JSMode);
                    this.cbTLSetType.SelectedIndex = ProDefine.g_SMExpermentParam.YLSetType;
                    this.txtCG.Text = ProDefine.g_SMExpermentParam.CGTemperature;
                    this.txtCGSD.Text = ProDefine.g_SMExpermentParam.CGXDSD;
                    this.txtZD.Text = ProDefine.g_SMExpermentParam.CGZD;
                    this.txtDYL.Text = ProDefine.g_SMExpermentParam.CGDYL;
                    this.txtJX.Text = ProDefine.g_SMExpermentParam.CPJXTemperature;
                    this.txtJXSD.Text = ProDefine.g_SMExpermentParam.CPJXXDSD;
                    this.txtJXZD.Text = ProDefine.g_SMExpermentParam.JXZD;
                    this.txtJXDYL.Text = ProDefine.g_SMExpermentParam.JXDYL;
                    this.txtYLNumber.Text = ProDefine.g_SMExpermentParam.YLNumber;
                    this.txtYBNumber.Text = ProDefine.g_SMExpermentParam.YBNumber;
                    this.cmbJW.SelectedIndex = ProDefine.g_SMExpermentParam.JWType;
                    this.txtZD.Text = ProDefine.g_SMExpermentParam.CGZD;
                    this.txtDYL.Text = ProDefine.g_SMExpermentParam.CGDYL;
                    this.txtJXZD.Text = ProDefine.g_SMExpermentParam.JXZD;
                    this.txtJXDYL.Text = ProDefine.g_SMExpermentParam.JXDYL;
                }
               

            }
            catch { }
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
            this.lbexpSave.ForeColor = Color.LightCoral;
        }

        private void lbexpSave_MouseLeave(object sender, EventArgs e)
        {
            this.lbexpSave.ForeColor = Color.Lavender;
        }

        private void lbCreateExp_MouseEnter(object sender, EventArgs e)
        {
            this.lbCreateExp.ForeColor = Color.LightCoral;//
        }

        private void lbCreateExp_MouseLeave(object sender, EventArgs e)
        {
            this.lbCreateExp.ForeColor = Color.Lavender;//
        }

        private void comboBox1_Click(object sender, EventArgs e)
        {

        }

        private void cmbYLType_Click(object sender, EventArgs e)
        {
            int ValueParam = GetYLValue(this.cmbYLType.Text.Trim());
            frmYLSelect frmYL = new frmYLSelect(ValueParam);
            frmYL.ShowDialog();
            if (frmYL.DialogResult == System.Windows.Forms.DialogResult.OK) {
                int returnValue = frmYL.returnValue;
                YLReturnValue = returnValue;
                SetYLValue(returnValue);

            }
        }

        private int GetYLValue(string YLText) {
            int returnValue = 0;
            if (YLText.Contains("温度")) {
                returnValue = ProDefine.SetBit(returnValue,0);
            }
            if (YLText.Contains("湿度")) {
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

        private void SetYLValue(int ValueParam) {
            string YLText = "";
            if(ProDefine.GetBit(ValueParam, 0)){
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
            if (ProDefine.GetBit(ValueParam, 3))
            {
                YLText += "电应力+";
            }
            if (YLText != "") {
                YLText = YLText.Substring(0, YLText.Length - 1);
            }
            
            this.cmbYLType.Text = YLText;
            bool ISZD = false;
            bool ISDYL = false;
            string[] YLType = YLText.Split('+');
            foreach (var info in YLType) {
                if (info == "震动") {
                    ISZD = true;
                    
                }
                if (info == "电应力") {
                    ISDYL = true;
                }
            }

            if (ISZD)
            {
                this.cmbZD.Visible = true;
                this.txtZD.Visible = true;
                this.cmbJZZD.Visible = true;
                this.txtJXZD.Visible = true;
            }
            else {
                this.cmbZD.Visible = false;
                this.txtZD.Visible = false;
                this.cmbJZZD.Visible = false;
                this.txtJXZD.Visible = false;
            }

            if (ISDYL)
            {
                this.cmbDYL.Visible = true;
                this.txtDYL.Visible = true;
                this.cmbJXDYL.Visible = true;
                this.txtJXDYL.Visible = true;
            }
            else
            {
                this.cmbDYL.Visible = false;
                this.txtDYL.Visible = false;
                this.cmbJXDYL.Visible = false;
                this.txtJXDYL.Visible = false;
            }
        }

        private void lbSave_Click(object sender, EventArgs e)
        {

            if (!AddToDeepGrid()) {
                return;
            }

            ProDefine.g_SMExpermentParam.YLType = YLReturnValue;
            ProDefine.g_SMExpermentParam.JSMode = JSModReturnValue;
            ProDefine.g_SMExpermentParam.YLSetType = cbTLSetType.SelectedIndex;
            ProDefine.g_SMExpermentParam.CGTemperature = this.txtCG.Text;
            ProDefine.g_SMExpermentParam.CGXDSD = this.txtCGSD.Text;
            ProDefine.g_SMExpermentParam.CPJXTemperature = this.txtJX.Text;
            ProDefine.g_SMExpermentParam.CPJXXDSD = this.txtJXSD.Text;
            ProDefine.g_SMExpermentParam.JWType = this.cmbJW.SelectedIndex;
            ProDefine.g_SMExpermentParam.YBNumber = this.txtYBNumber.Text;
            ProDefine.g_SMExpermentParam.YLNumber = this.txtYLNumber.Text;
            ProDefine.g_SMExpermentParam.GUID = ProDefine.g_MyProject.GUID;

            ProDefine.g_SMExpermentParam.CGZD = this.txtZD.Text;
            ProDefine.g_SMExpermentParam.CGDYL = this.txtDYL.Text;
            ProDefine.g_SMExpermentParam.JXZD = this.txtJXZD.Text;
            ProDefine.g_SMExpermentParam.JXDYL = this.txtJXDYL.Text;

            m_Pro.SaveExpermentInfo(ProDefine.g_SMExpermentParam);
            //ProDefine.g_SMExpermentParam.CGTemperature = 
        }

        private bool AddToDeepGrid() {
            int YLNumber = Convert.ToInt32(this.txtYLNumber.Text);
            int YBNumber = Convert.ToInt32(this.txtYBNumber.Text);

            if (YLNumber > YBNumber) {
                return false;
            }

            string WDNumber = this.txtCG.Text;
            string SDNumber = this.txtCGSD.Text;

            int PerNumnber = YBNumber / YLNumber;
            for (int i = 0; i < YLNumber; i++)
            {
                int Rindex = this.dataGridView1.Rows.Add();
                this.dataGridView1.Rows[Rindex].Cells[0].Value = WDNumber;
                this.dataGridView1.Rows[Rindex].Cells[1].Value = SDNumber;
                this.dataGridView1.Rows[Rindex].Cells[2].Value = PerNumnber;
                this.dataGridView1.Rows[Rindex].Cells[3].Value = 100;
               
            }
            return true;
            
        }

        private void InsertExpermentSample() { 
            
        }

        private void comboBox2_Click(object sender, EventArgs e)
        {
            int ValueParam = GetJSModeValue(this.cmbYLType.Text.Trim());
            frmJSMod frmJS = new frmJSMod(ValueParam);
            frmJS.ShowDialog();
            if (frmJS.DialogResult == System.Windows.Forms.DialogResult.OK)
            {
                int returnValue = frmJS.returnValue;
                JSModReturnValue = returnValue;
                SetYLModValue(returnValue);

            }
        }

        private int GetJSModeValue(string text) {
            return 0;
        }

        private void SetYLModValue(int ValueParam) {
            this.cbJsMode.Text = "待接入";
        }

        
    }
}
