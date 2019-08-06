﻿using System;
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
    public partial class frmExpermentSM : Form
    {
        public frmExpermentSM()
        {
            InitializeComponent();
            initUI();
        }

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
            if (ProDefine.GetBit(ValueParam, 2))
            {
                YLText += "电应力+";
            }
            if (YLText != "") {
                YLText = YLText.Substring(0, YLText.Length - 1);
            }
            
            this.cmbYLType.Text = YLText;
        }

        private void lbSave_Click(object sender, EventArgs e)
        {
            ProDefine.g_SMExpermentParam.YLType = YLReturnValue;
            ProDefine.g_SMExpermentParam.JSMode = JSModReturnValue;
            ProDefine.g_SMExpermentParam.YLSetType = cbTLSetType.SelectedIndex;
            //ProDefine.g_SMExpermentParam.CGTemperature = 
        }

        private void comboBox2_Click(object sender, EventArgs e)
        {
            int ValueParam = GetJSModeValue(this.cmbYLType.Text.Trim());
            frmJSMod frmJS = new frmJSMod(ValueParam);
            frmJS.ShowDialog();
            if (frmJS.DialogResult == System.Windows.Forms.DialogResult.OK)
            {
                int returnValue = frmJS.returnValue;
                YLReturnValue = returnValue;
                SetYLValue(returnValue);

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