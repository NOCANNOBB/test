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
    public partial class frmChannelSet : Form
    {
        public frmChannelSet()
        {
            InitializeComponent();
            InitUI();
        }

        private void InitUI()
        {

            this.lbIn.Text = "\uf149 导入通道设置";
            this.lbIn.Font = new Font("FontAwesome", 14,FontStyle.Bold);
            this.lbIn.ForeColor = Color.LightCyan;

            this.lbOut.Text = "\uf148 导出通道设置";
            this.lbOut.Font = new Font("FontAwesome", 14,FontStyle.Bold);
            this.lbOut.ForeColor = Color.LightCyan;

            this.lbSave.Text = "\uf0c7 保存配置";
            this.lbSave.Font = new Font("FontAwesome", 14, FontStyle.Bold);
            this.lbSave.ForeColor = Color.LightCyan;

        }
    }
}
