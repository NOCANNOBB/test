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
using DLLAccess;
using DLLProjectInfo;
using XMLHelper;
namespace PRO190726
{
    public partial class Main : Form
    {
        public Main()
        {
            InitializeComponent();

            this.lb_Close.Text = "\uf00d";
            this.lb_Close.Font = new Font("FontAwesome", 12);
            this.lb_Close.ForeColor = Color.White;

            this.lb_Small.Text = "\uf068";
            this.lb_Small.Font = new Font("FontAwesome", 12);
            this.lb_Small.ForeColor = Color.White;

            this.lb_Max.Text = "\uf0b2";
            this.lb_Max.Font = new Font("FontAwesome", 12);
            this.lb_Max.ForeColor = Color.White;


            this.文件ToolStripMenuItem.Text = "\uf15b 文件";
            this.文件ToolStripMenuItem.Font = new Font("FontAwesome", 12);
            this.文件ToolStripMenuItem.ForeColor = Color.CadetBlue;


            this.新建项目ToolStripMenuItem.Text = "\uf0c5 新建项目";
            this.新建项目ToolStripMenuItem.Font = new Font("FontAwesome", 12);
            this.新建项目ToolStripMenuItem.ForeColor = Color.CadetBlue;

            this.打开项目ToolStripMenuItem.Text = "\uf07c 打开项目";
            this.打开项目ToolStripMenuItem.Font = new Font("FontAwesome", 12);
            this.打开项目ToolStripMenuItem.ForeColor = Color.CadetBlue;

            this.删除项目ToolStripMenuItem.Text = "\uf1f8 删除项目";
            this.删除项目ToolStripMenuItem.Font = new Font("FontAwesome", 12);
            this.删除项目ToolStripMenuItem.ForeColor = Color.CadetBlue;

            this.保存ToolStripMenuItem.Text = "\uf0c7 保存";
            this.保存ToolStripMenuItem.Font = new Font("FontAwesome", 12);
            this.保存ToolStripMenuItem.ForeColor = Color.CadetBlue;


            this.退出ToolStripMenuItem.Text = "\uf057 退出";
            this.退出ToolStripMenuItem.Font = new Font("FontAwesome", 12);
            this.退出ToolStripMenuItem.ForeColor = Color.CadetBlue;


            this.方案设计及优化ToolStripMenuItem.Text = "\uf013 方案设计及优化";
            this.方案设计及优化ToolStripMenuItem.Font = new Font("FontAwesome", 12);
            this.方案设计及优化ToolStripMenuItem.ForeColor = Color.CadetBlue;

            this.实验检测ToolStripMenuItem.Text = "\uf0c3 实验检测";
            this.实验检测ToolStripMenuItem.Font = new Font("FontAwesome", 12);
            this.实验检测ToolStripMenuItem.ForeColor = Color.CadetBlue;

            this.数据处理ToolStripMenuItem.Text = "\uf201 数据处理";
            this.数据处理ToolStripMenuItem.Font = new Font("FontAwesome", 12);
            this.数据处理ToolStripMenuItem.ForeColor = Color.CadetBlue;

            this.可靠性评估ToolStripMenuItem.Text = "\uf066 可靠性评估";
            this.可靠性评估ToolStripMenuItem.Font = new Font("FontAwesome", 12);
            this.可靠性评估ToolStripMenuItem.ForeColor = Color.CadetBlue;

            this.可靠性验证ToolStripMenuItem.Text = "\uf295 可靠性验证";
            this.可靠性验证ToolStripMenuItem.Font = new Font("FontAwesome", 12);
            this.可靠性验证ToolStripMenuItem.ForeColor = Color.CadetBlue;

            this.帮助ToolStripMenuItem.Text = "\uf059 帮助";
            this.帮助ToolStripMenuItem.Font = new Font("FontAwesome", 12);
            this.帮助ToolStripMenuItem.ForeColor = Color.CadetBlue;




            this.tabControl1.TabPages[0].Text = "\uf00b 项目列表";
            this.tabControl1.Font = new Font("FontAwesome", 12);
            this.tabControl1.ForeColor = Color.BurlyWood;

            this.lbDataTitle.Text = "\uf1c0 数据存储区";
            this.lbDataTitle.Font = new Font("FontAwesome", 12);
            this.lbDataTitle.ForeColor = Color.Black ;



            this.lbTypeShow.Text = "\uf06e";
            this.lbTypeShow.Font = new Font("FontAwesome", 14,FontStyle.Bold);
            this.lbTypeShow.ForeColor = Color.LightSkyBlue;



            this.打开项目ToolStripMenuItem1.Text = "\uf07c 打开项目";
            this.打开项目ToolStripMenuItem1.Font = new Font("FontAwesome", 12);
            this.打开项目ToolStripMenuItem1.ForeColor = Color.CadetBlue;

            this.删除项目ToolStripMenuItem1.Text = "\uf1f8 删除项目";
            this.删除项目ToolStripMenuItem1.Font = new Font("FontAwesome", 12);
            this.删除项目ToolStripMenuItem1.ForeColor = Color.CadetBlue;

            this.保存项目ToolStripMenuItem.Text = "\uf0c7 保存";
            this.保存项目ToolStripMenuItem.Font = new Font("FontAwesome", 12);
            this.保存项目ToolStripMenuItem.ForeColor = Color.CadetBlue;

           // this.设置为分析项目ToolStripMenuItem.Text = "\uf085 设置为分析项目";
           // this.设置为分析项目ToolStripMenuItem.Font = new Font("FontAwesome", 12);
            //this.设置为分析项目ToolStripMenuItem.ForeColor = Color.CadetBlue;



            this.寿命实验方案ToolStripMenuItem.Text = "\uf11d 寿命实验方案";
            this.寿命实验方案ToolStripMenuItem.Font = new Font("FontAwesome", 12);
            this.寿命实验方案ToolStripMenuItem.ForeColor = Color.CadetBlue;


            this.实验方案设计ToolStripMenuItem.Text = "\uf044 实验方案设计";
            this.实验方案设计ToolStripMenuItem.Font = new Font("FontAwesome", 12);
            this.实验方案设计ToolStripMenuItem.ForeColor = Color.CadetBlue;


            this.优化实验方案ToolStripMenuItem.Text = "\uf19b 优化实验方案";
            this.优化实验方案ToolStripMenuItem.Font = new Font("FontAwesome", 12);
            this.优化实验方案ToolStripMenuItem.ForeColor = Color.CadetBlue;


            this.退化实验方案ToolStripMenuItem.Text = "\uf11d 退化实验方案";
            this.退化实验方案ToolStripMenuItem.Font = new Font("FontAwesome", 12);
            this.退化实验方案ToolStripMenuItem.ForeColor = Color.CadetBlue;


            this.实验方案设计ToolStripMenuItem1.Text = "\uf044 实验方案设计";
            this.实验方案设计ToolStripMenuItem1.Font = new Font("FontAwesome", 12);
            this.实验方案设计ToolStripMenuItem1.ForeColor = Color.CadetBlue;


            this.优化实验方案ToolStripMenuItem1.Text = "\uf19b 优化实验方案";
            this.优化实验方案ToolStripMenuItem1.Font = new Font("FontAwesome", 12);
            this.优化实验方案ToolStripMenuItem1.ForeColor = Color.CadetBlue;



            this.通道设置ToolStripMenuItem.Text = "\uf013 通道设置";
            this.通道设置ToolStripMenuItem.Font = new Font("FontAwesome", 12);
            this.通道设置ToolStripMenuItem.ForeColor = Color.CadetBlue;

            this.输出信号配置ToolStripMenuItem.Text = "\uf012 输出信号配置";
            this.输出信号配置ToolStripMenuItem.Font = new Font("FontAwesome", 12);
            this.输出信号配置ToolStripMenuItem.ForeColor = Color.CadetBlue;

            this.实验ToolStripMenuItem.Text = "\uf0c3 实验";
            this.实验ToolStripMenuItem.Font = new Font("FontAwesome", 12);
            this.实验ToolStripMenuItem.ForeColor = Color.CadetBlue;

            this.标准数据与故障报警设置ToolStripMenuItem.Text = "\uf06a 标准数据与故障报警设置";
            this.标准数据与故障报警设置ToolStripMenuItem.Font = new Font("FontAwesome", 12);
            this.标准数据与故障报警设置ToolStripMenuItem.ForeColor = Color.CadetBlue;


            this.寿命实验数据处理ToolStripMenuItem.Text = "\uf085 寿命实验数据处理";
            this.寿命实验数据处理ToolStripMenuItem.Font = new Font("FontAwesome", 12);
            this.寿命实验数据处理ToolStripMenuItem.ForeColor = Color.CadetBlue;

            this.退化实验数据处理ToolStripMenuItem.Text = "\uf085 退化实验数据处理";
            this.退化实验数据处理ToolStripMenuItem.Font = new Font("FontAwesome", 12);
            this.退化实验数据处理ToolStripMenuItem.ForeColor = Color.CadetBlue;

        }


        DoProjectInfo m_Pro = null;

        int xPos, yPos;// 记录listView鼠标位置，解决点击空白处无法触发事件

        private void Form1_Load(object sender, EventArgs e)
        {
            if (m_Pro == null) {
                m_Pro = new DoProjectInfo();
            }

            ProDefine.g_SMExpermentDesin.ExpParamList = new List<DLLStruct.SMExpeDesignParam>();
            DoConfigInit();
            ShowlistPro();
        }
        private string dBPath = System.IO.Directory.GetCurrentDirectory() + "\\Experment.mdb";
        private void DoConfigInit() {
            try {
                AccessHelper.CreateAccessDb(dBPath);
                AccessHelper.CreateAccessTable(dBPath, "ProjectConfig");
                AccessHelper.CreateAccessTable(dBPath, "ExpermentParam");
                AccessHelper.CreateAccessTable(dBPath, "ExpermentDesign");
                AccessHelper.CreateAccessTable(dBPath, "ChannelInfo");
                AccessHelper.CreateAccessTable(dBPath, "YBChannelInfo");
            }
            catch { }
        }



        List<ProjectInfo> m_ProList = new List<ProjectInfo>();

        private void ShowlistPro() {

            this.lsProject.Items.Clear();
            m_ProList.Clear();
            m_ProList = m_Pro.GetProjectInfos();
            if (m_ProList == null) { return; }
            foreach (var info in m_ProList)
            {
                InsertListView(this.lsProject, info.ProjectName);
            }
        }

        public void InsertListView(ListView lv,string ProName)
        {
            this.lsProject.BeginUpdate();
            //获取文本框中的值
            string name = ProName;
            
            ListViewItem li = new ListViewItem();
            //添加同一行的数据
            li.Text = "\uf02e  " + name;
            li.Font = new Font("FontAwesome", 14, FontStyle.Bold);
            li.ForeColor = Color.DarkMagenta;
            //将行对象绑定在listview对象中
            lv.Items.Add(li);
            this.lsProject.EndUpdate();
            //return lv;
        }

        private void lb_Close_MouseEnter(object sender, EventArgs e)
        {
            this.lb_Close.ForeColor = Color.Red;
        }

        private void lb_Small_MouseEnter(object sender, EventArgs e)
        {
            this.lb_Small.ForeColor = Color.Red;
        }

        private void lb_Small_MouseLeave(object sender, EventArgs e)
        {
            this.lb_Small.ForeColor = Color.White;
        }

        private void lb_Close_MouseLeave(object sender, EventArgs e)
        {
            this.lb_Close.ForeColor = Color.White;
        }

        private void lb_Max_MouseEnter(object sender, EventArgs e)
        {
            this.lb_Max.ForeColor = Color.Red;
        }

        private void lb_Max_MouseLeave(object sender, EventArgs e)
        {
            this.lb_Max.ForeColor = Color.White;
        }

        private void lb_Close_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void lb_Small_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
        }

        private void lb_Max_Click(object sender, EventArgs e)
        {
            if (this.WindowState == FormWindowState.Normal) {
                this.WindowState = FormWindowState.Maximized;
            }
            else if (this.WindowState == FormWindowState.Maximized) {
                this.WindowState = FormWindowState.Normal;
            }
            
        }


        private frmExpermentSM frmSM = null;
        private frmExpermentTH frmTH = null;
        private frmProjectInfo frmPro = null;
        private frmYHExperienceSM frmYHSM = null;
        private frmYHExperienceTH frmYHTH = null;
        private frmChannelSet frmCHS = null;

        private frmOutputSet frmOutputs = null;
        private frmDataAalrmSet frmDataAlarmSet = null;
        private frmExperment frmExp = null;

        private frmTHData frmth = null;
        private frmSMData frmsm = null;

        private frmKKXPG frmKK = null;

        private frmKKXYANZHENG frmKKYZ = null;

        private frmYBSet frmYBS = null;
     

        private bool IsRightClick = false;
        private void 新建项目ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (frmPro != null) {
                frmPro.Dispose();
                frmPro = null;
            }
            if (frmPro == null)
            {
                frmPro = new frmProjectInfo(this.toolStripStatusLabel1,this.lsProject);
            }

            ShowForm(frmPro);
            this.lbTypeShow.Text = "\uf06e 新建项目";
        }

        public void ShowForm(Form form)
        {

            this.panel2.Controls.Clear();

            form.TopLevel = false;

            form.FormBorderStyle = FormBorderStyle.None;

            form.Dock = DockStyle.Fill;

            form.Parent = this.panel2;

            this.panel2.Controls.Add(form);

            form.Show();

        }

        private void 方案设计及优化ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            
            
        }

        private void lsProject_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Right)
            {

                string ProName = this.lsProject.SelectedItems[0].Text;
                ProName = ProName.Substring(ProName.LastIndexOf(" ") + 1, ProName.Length - ProName.LastIndexOf(" ") - 1);
                SetNowListSelected(ProName);
                if (this.lsProject.SelectedItems.Count > 0)
                {
                    contextMenuStrip1.Show(MousePosition.X, MousePosition.Y);
                }
            }
            
        }

        private void SetListSelected() {
            foreach (ListViewItem info in this.lsProject.Items) {
                string ProName = info.Text;
                ProName = ProName.Substring(ProName.LastIndexOf(" ") + 1, ProName.Length - ProName.LastIndexOf(" ") - 1);

                if (ProName == ProDefine.NowProjectName)
                {
                    info.Selected = true;
                    break;
                }
                //else {
                //    info.Selected = false;
                //}
            }
        }


        private void SetNowListSelected()
        {
            foreach (ListViewItem info in this.lsProject.Items)
            {
                string ProName = info.Text;
                ProName = ProName.Substring(ProName.LastIndexOf(" ") + 1, ProName.Length - ProName.LastIndexOf(" ") - 1);

                if (ProName == ProDefine.NowProjectName)
                {
                    info.Selected = true;
                    
                }
                else {
                    info.Selected = false;
                }
            }
        }

        private void SetNowListSelected(string NameParam)
        {
            foreach (ListViewItem info in this.lsProject.Items)
            {
                string ProName = info.Text;
                ProName = ProName.Substring(ProName.LastIndexOf(" ") + 1, ProName.Length - ProName.LastIndexOf(" ") - 1);

                if (ProName == NameParam)
                {
                    info.Selected = true;

                }
                else
                {
                    info.Selected = false;
                }
            }
        }

        private void SetNoListSelected()
        {
            foreach (ListViewItem info in this.lsProject.Items)
            {
                    info.Selected = false;
            }
        }

        private void 打开项目ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog file = new OpenFileDialog();
            file.Filter = "csproj files(*.csproj)|*.csproj|All files(*.*)|*.*";
            if (file.ShowDialog() == System.Windows.Forms.DialogResult.OK) {
                string FileName = file.SafeFileName;

                if (m_Pro == null)
                {
                    m_Pro = new DoProjectInfo();
                }

                string ProjectName = FileName;
                string ProjectPathName = file.FileName;

                ProjectInfo pro = m_Pro.GetProjectInfo(ProjectPathName);


                int returnvalue = m_Pro.AddProjectInfo(pro);

                if (returnvalue == -1) {
                    MessageBox.Show("项目列表中存在当前名称的项目，添加失败");
                    return;
                }

               // Guid guid = Guid.NewGuid();
               // if (m_Pro.SaveProjectInfo(ProjectName, guid))
                {
                   //// MessageBox.Show("保存成功");
                }
               // else
                {
                   // MessageBox.Show("保存失败");
                }
                ShowlistPro();
            }
            
            
        }

        private void 删除项目ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (this.lsProject.SelectedItems.Count <= 0) {
                MessageBox.Show("请选择要删除的项目");
                return;
            }

            if (MessageBox.Show("确定删除 项目" + this.lsProject.SelectedItems[0].Text, "提示", MessageBoxButtons.YesNo) == DialogResult.Yes) {
                int SelIndex = this.lsProject.SelectedItems[0].Index;
                DoDlePro(SelIndex);
            }
        }

        private void DoDlePro(int SelIndex) {
            m_Pro.DelProFromList(m_ProList[SelIndex]);
            ShowlistPro();
        }


        private void 设置为分析项目ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (this.lsProject.SelectedItems.Count > 0) {

                string ProName = this.lsProject.SelectedItems[0].Text;
                ProName = ProName.Substring(ProName.LastIndexOf(" ") + 1, ProName.Length - ProName.LastIndexOf(" ") - 1);
                if (ProDefine.NowProjectName != "")
                {
                    if (MessageBox.Show("当前默认项目为" + ProDefine.NowProjectName + "  确定切换为 项目" + this.lsProject.SelectedItems[0].Text, "提示", MessageBoxButtons.YesNo) == DialogResult.Yes)
                    {
                        ProDefine.NowProjectName = ProName;
                    }
                }
                else {
                    ProDefine.NowProjectName = ProName;
                }
                SetNowListSelected();
                this.toolStripStatusLabel1.Text = "当前选择项目为：" + ProDefine.NowProjectName;
            }
        }

        

        private void lsProject_MouseLeave(object sender, EventArgs e)
        {

            if (ProDefine.NowProjectName == "") {
                
                return;
            }

          //  SetListSelected();
        }

        private void 实验方案设计ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (frmSM != null) {
                frmSM.Dispose();
                frmSM = null;
            }
            frmSM = new frmExpermentSM();
            ShowForm(frmSM);
            this.lbTypeShow.Text = "\uf06e 寿命实验--实验方案设计";
        }

        private void 优化实验方案ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (frmYHSM != null) {
                frmYHSM.Dispose();
                frmYHSM = null;
            }
            frmYHSM = new frmYHExperienceSM();
            ShowForm(frmYHSM);
            this.lbTypeShow.Text = "\uf06e 寿命实验--优化实验方案";
        }

        private void 实验方案设计ToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if (frmTH != null)
            {
                frmTH.Dispose();
                frmTH = null;
            }
            frmTH = new frmExpermentTH();
            ShowForm(frmTH);
            this.lbTypeShow.Text = "\uf06e 退化实验--实验方案设计";
        }

        private void 优化实验方案ToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if (frmYHTH != null)
            {
                frmYHTH.Dispose();
                frmYHTH = null;
            }
            frmYHTH = new frmYHExperienceTH();
            ShowForm(frmYHTH);
            this.lbTypeShow.Text = "\uf06e 退化实验--优化实验方案";
        }

        private void 通道设置ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if(frmCHS != null)
            {
                frmCHS.Dispose();
                frmCHS = null;
            }
            frmCHS = new  frmChannelSet();
            ShowForm(frmCHS);
            this.lbTypeShow.Text = "\uf06e 实验检测--通道设置";
        }

        private void 输出信号配置ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (frmOutputs != null) {
                frmOutputs.Dispose();
                frmOutputs = null;
            }
            frmOutputs = new frmOutputSet();
            ShowForm(frmOutputs);
            this.lbTypeShow.Text = "\uf06e 实验检测--输出信号配置";
        }

        private void 标准数据与故障报警设置ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (frmDataAlarmSet != null)
            {
                frmDataAlarmSet.Dispose();
                frmDataAlarmSet = null;
            }
            frmDataAlarmSet = new frmDataAalrmSet();
            ShowForm(frmDataAlarmSet);
            this.lbTypeShow.Text = "\uf06e 实验检测--标准数据与故障报警设置";
        }

        private void 实验ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (frmExp != null)
            {
                frmExp.Dispose();
                frmExp = null;
            }
            frmExp = new frmExperment();
            ShowForm(frmExp);
            this.lbTypeShow.Text = "\uf06e 实验检测--实验";
        }

        private void 寿命实验数据处理ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (frmsm != null)
            {
                frmsm.Dispose();
                frmsm = null;
            }
            frmsm = new frmSMData();
            ShowForm(frmsm);
            this.lbTypeShow.Text = "\uf06e 数据处理--寿命实验数据处理";
        }

        private void 退化实验数据处理ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (frmth != null)
            {
                frmth.Dispose();
                frmth = null;
            }
            frmth = new frmTHData();
            ShowForm(frmth);
            this.lbTypeShow.Text = "\uf06e 数据处理--退化实验数据处理";
        }

        private void 可靠性评估ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (frmKK != null)
            {
                frmKK.Dispose();
                frmKK = null;
            }
            frmKK = new frmKKXPG();
            ShowForm(frmKK);
            this.lbTypeShow.Text = "\uf06e 可靠性评估";
        }

        private void 可靠性验证ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (frmKKYZ != null)
            {
                frmKKYZ.Dispose();
                frmKKYZ = null;
            }
            frmKKYZ = new frmKKXYANZHENG();
            ShowForm(frmKKYZ);
            this.lbTypeShow.Text = "\uf06e 可靠性验证";
        }

        private void 打开项目ToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if (this.lsProject.SelectedItems.Count <= 0) {
                MessageBox.Show("请选择项目");
                return;
            }
            int SelIndex = this.lsProject.SelectedItems[0].Index;
            ShowlistPro();
            

            
            ProjectInfo pro = m_ProList[SelIndex];

            ProDefine.g_MyProject = pro;
            frmProjectInfo frmpro = new frmProjectInfo(this.toolStripStatusLabel1,this.lsProject,pro);
            ShowForm(frmpro);
            this.toolStripStatusLabel1.Text = "当前项目：" + pro.ProjectName;
            this.lbTypeShow.Text = "\uf06e  项目信息";
        }

        private void 删除项目ToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if (this.lsProject.SelectedItems.Count <= 0)
            {
                MessageBox.Show("请选择要删除的项目");
                return;
            }

            if (MessageBox.Show("确定删除 项目" + this.lsProject.SelectedItems[0].Text, "提示", MessageBoxButtons.YesNo) == DialogResult.Yes)
            {
                int SelIndex = this.lsProject.SelectedItems[0].Index;
                DoDlePro(SelIndex);
            }
        }

        private void 样本通道配置ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (frmYBS != null)
            {
                frmYBS.Dispose();
                frmYBS = null;
            }
            frmYBS = new frmYBSet();
            ShowForm(frmYBS);
        }


       
    }
}
