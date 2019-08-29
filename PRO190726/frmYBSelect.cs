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
    public partial class frmYBSelect : Form
    {
        public frmYBSelect()
        {
            InitializeComponent();
            initUI();
        }
        public int YBNumber = 0;
        public List<int> returnList = new List<int>();
        List<CheckBox> m_CheckList = new List<CheckBox>();
        public void initUI()
        {
            int YBNumber = Convert.ToInt32(ProDefine.g_SMExpermentParam.YBNumber);
            m_CheckList.Add(this.checkBox1); m_CheckList.Add(this.checkBox2); m_CheckList.Add(this.checkBox3); m_CheckList.Add(this.checkBox4); m_CheckList.Add(this.checkBox5);

            m_CheckList.Add(this.checkBox6); m_CheckList.Add(this.checkBox7); m_CheckList.Add(this.checkBox8); m_CheckList.Add(this.checkBox9); m_CheckList.Add(this.checkBox10);

            m_CheckList.Add(this.checkBox11); m_CheckList.Add(this.checkBox12); m_CheckList.Add(this.checkBox13); m_CheckList.Add(this.checkBox14); m_CheckList.Add(this.checkBox15);

            m_CheckList.Add(this.checkBox16); m_CheckList.Add(this.checkBox17); m_CheckList.Add(this.checkBox18); m_CheckList.Add(this.checkBox19); m_CheckList.Add(this.checkBox20);

            m_CheckList.Add(this.checkBox21); m_CheckList.Add(this.checkBox22); m_CheckList.Add(this.checkBox23); m_CheckList.Add(this.checkBox24); m_CheckList.Add(this.checkBox25);

            m_CheckList.Add(this.checkBox26); m_CheckList.Add(this.checkBox27); m_CheckList.Add(this.checkBox28); m_CheckList.Add(this.checkBox29); m_CheckList.Add(this.checkBox30);

            m_CheckList.Add(this.checkBox31); m_CheckList.Add(this.checkBox32); m_CheckList.Add(this.checkBox33); m_CheckList.Add(this.checkBox34); m_CheckList.Add(this.checkBox35);


            int CCount = m_CheckList.Count;
            for (int i = 0; i < CCount; i++ )
            {
                if (i <= YBNumber)
                {
                    m_CheckList[i].Visible = true;
                } 
                else
                {
                    m_CheckList[i].Visible = false;
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int CCount = m_CheckList.Count;
            for (int i = 0; i < CCount; i++)
            {
                if (m_CheckList[i].Visible && m_CheckList[i].Checked)
                {
                    returnList.Add(i);
                }
            }
            DialogResult = DialogResult.OK;
            this.Close();
        }
    }
}
