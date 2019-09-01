using Define;
using DevExpress.Utils.Menu;
using DevExpress.XtraEditors;
using DLLStruct;
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
    public partial class frmExperment : Form
    {
        public frmExperment()
        {
            InitializeComponent();
            InitUI();
        }

        private void InitUI() {
            this.lbStart.Text = "\uf04b 开始实验";
            this.lbStart.Font = new Font("FontAwesome", 15, FontStyle.Bold);
            this.lbStart.ForeColor = Color.White;


            this.lbEnd.Text = "\uf04d 停止实验";
            this.lbEnd.Font = new Font("FontAwesome", 15, FontStyle.Bold);
            this.lbEnd.ForeColor = Color.White;
        }

        private void lbStart_Click(object sender, EventArgs e)
        {
            this.lbStart.Enabled = false;
            this.lbEnd.Enabled = true;
        }

        private void lbStart_MouseEnter(object sender, EventArgs e)
        {
            this.lbStart.ForeColor = Color.Blue;
        }

        private void lbStart_MouseLeave(object sender, EventArgs e)
        {
            this.lbStart.ForeColor = Color.White;
        }

        private void lbEnd_Click(object sender, EventArgs e)
        {
            this.lbEnd.Enabled = false ;
            this.lbStart.Enabled = true;
        }

        private void lbEnd_MouseEnter(object sender, EventArgs e)
        {
            this.lbEnd.ForeColor = Color.Blue;
        }

        private void lbEnd_MouseLeave(object sender, EventArgs e)
        {
            this.lbEnd.ForeColor = Color.White;
        }

        private void GetDisntTimeList() {
            try {
                //方案1
                //1.  获取读取的数据频率，多久读取一次
                //2.  根据获取的个数启动多个线程，读取数据

                //方案2. 
                //分别用两线程表示读取和写入，根据起始时间计时来确定应该何时读取数据
                //
                //ProDefine.g_YBSetSignle.Distinct()
            }
            catch { 
            }
        }
        private List<SimpleButton> m_ButtonList = new List<SimpleButton>();
        private void DoUIInit() {
            try {
                this.ddbYBSelect.DropDownControl = CreateDXPopupMenu();
                m_ButtonList.Add(this.simpleButton01); m_ButtonList.Add(this.simpleButton02);
                m_ButtonList.Add(this.simpleButton03); m_ButtonList.Add(this.simpleButton04);
                m_ButtonList.Add(this.simpleButton05); m_ButtonList.Add(this.simpleButton06);
                m_ButtonList.Add(this.simpleButton07); m_ButtonList.Add(this.simpleButton08);
                m_ButtonList.Add(this.simpleButton09); m_ButtonList.Add(this.simpleButton10);
                foreach (var info in m_ButtonList) {
                    info.Visible = false;
                }
            }
            catch { }
        }

        private DXPopupMenu CreateDXPopupMenu()
        {
            DXPopupMenu menu = new DXPopupMenu();
            for (int info = 1; info <= Convert.ToInt32(ProDefine.g_SMExpermentParam.YBNumber);info++ )
            {
                menu.Items.Add(new DXMenuItem("样本" + info.ToString(), OnItemClick));
            }
            return menu;
        }

        private void OnItemClick(object sender, EventArgs e)
        {
            DXMenuItem item = sender as DXMenuItem;
            string YBName = item.Caption;

            YBChannelInfo ybc = ProDefine.g_YBsetting.Where(m => m.YBName == YBName).SingleOrDefault();

            int tCount = ybc.YBList.Count;
            int iindex = 1;
            foreach (var info in this.m_ButtonList) {
                if (iindex <= tCount)
                {
                    this.m_ButtonList[iindex - 1].Visible = true;
                    this.m_ButtonList[iindex - 1].Text = ybc.YBList[iindex - 1].GNFunction;
                }
                else {
                    this.m_ButtonList[iindex - 1].Visible = false;
                }
                iindex++;
            }
            
        }
    }
}
