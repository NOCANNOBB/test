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
using DLLNOPI;
using DLLStruct;
using DLLProjectInfo;

namespace PRO190726
{
    public partial class frmChannelSet : Form
    {
        public frmChannelSet()
        {
            InitializeComponent();
            InitUI();
            m_Pro = new DoProjectInfo();
            GetExternalChannelInfo();
        }
        DoProjectInfo m_Pro;
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


        private void GetExternalChannelInfo()
        {
            try
            {
                m_Pro.GetChannelSetInfo();
                m_Pro.GetYBChannelInfo();
                int RowCount = ProDefine.g_ChannelInfos.Count;
                int ColNum = 7;
                for (int i = 0; i < RowCount; i++)
                {
                    ChannelInfos csi = ProDefine.g_ChannelInfos[i];
                    int kindex = this.dataGridView1.Rows.Add();
                    this.dataGridView1.Rows[kindex].Cells[0].Value = csi.IsFunctionSelect;
                    this.dataGridView1.Rows[kindex].Cells[1].Value = csi.FucntionName;
                    this.dataGridView1.Rows[kindex].Cells[2].Value = csi.FunctionType;
                    this.dataGridView1.Rows[kindex].Cells[3].Value = csi.XianHao;
                    this.dataGridView1.Rows[kindex].Cells[4].Value = csi.Duanzi;
                    this.dataGridView1.Rows[kindex].Cells[5].Value = csi.Hz;
                    this.dataGridView1.Rows[kindex].Cells[6].Value = csi.PerCount;

                }
            }
            catch (System.Exception ex)
            {
            	
            }

        }

        private void lbIn_Click(object sender, EventArgs e)
        {
            
            try
            {
                OpenFileDialog file = new OpenFileDialog();
                file.Filter = "xls files(*.xls)|*.xls|xlsx files(*.xlsx)|*.xlsx";
                if (file.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    this.dataGridView1.Rows.Clear();
                    string FileName = file.FileName;

                    List<string> GetContentStr = ExcelHelper.ReadFromExcelFile(FileName,"总表");
                    List<string> GetDAContent = ExcelHelper.ReadFromExcelFile(FileName, "DA表");
                    List<string> GetADContent = ExcelHelper.ReadFromExcelFile(FileName, "AD表");
                    if (GetContentStr.Count == 0)
                    {
                        MessageBox.Show("获取到数据格式不正确");
                        return;
                    }
                    if (GetDAContent.Count == 0)
                    {
                        MessageBox.Show("获取到数据格式不正确");
                        return;
                    }
                    if (GetADContent.Count == 0)
                    {
                        MessageBox.Show("获取到数据格式不正确");
                        return;
                    }
                    ProDefine.g_FunctionChannel.Clear();
                    InserFunctionChannel(GetContentStr);
                    InsertDAADInfo(GetDAContent,0);
                    InsertDAADInfo(GetADContent, 1);

                    int RowCount = GetContentStr.Count;
                    int ColNum = GetContentStr[0].Split(',').Count();

                    this.dataGridView1.Rows.Clear();
                    for (int i = 1; i < RowCount; i++)
                    {
                        int kindex = this.dataGridView1.Rows.Add();
                        this.dataGridView1.Rows[kindex].Cells[0].Value = true;
                        for (int k = 1; k < ColNum; k++)
                        {
                            this.dataGridView1.Rows[kindex].Cells[k].Value = GetContentStr[i].Split(',')[k];
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void InserFunctionChannel(List<string> ContentStr)
        {
            try
            {
                ProDefine.g_ChannelInfos.Clear();
                int RowCount = ContentStr.Count;
                int ColNum = ContentStr[0].Split(',').Count();

                for (int i = 1; i < RowCount; i++)
                {
                    ChannelInfos CI = new ChannelInfos();

                    CI.IndexStr = ContentStr[i].Split(',')[0];
                    CI.FucntionName = ContentStr[i].Split(',')[1];
                    CI.FunctionType = ContentStr[i].Split(',')[2];
                    CI.XianHao = ContentStr[i].Split(',')[3];
                    CI.Duanzi = ContentStr[i].Split(',')[4];
                    CI.Hz = Convert.ToInt32( ContentStr[i].Split(',')[5]);
                    CI.PerCount = Convert.ToInt32(ContentStr[i].Split(',')[6]);
                    CI.IsFunctionSelect = true;
                    ProDefine.g_ChannelInfos.Add(CI);
                }
            }
            catch (System.Exception ex)
            {
            	
            }
        }

        private void InsertDAADInfo(List<string> ContentStr,byte strType)
        {
            try
            {
                
                int RowCount = ContentStr.Count;
                int ColNum = ContentStr[0].Split(',').Count();

                for (int i = 1; i < RowCount; i++)
                {
                    FucntionChannelInfo FC = new FucntionChannelInfo();

                    FC.IndexStr = ContentStr[i].Split(',')[0];
                    FC.FunctionName = ContentStr[i].Split(',')[1];
                    FC.ChannelNumber = Convert.ToInt32(ContentStr[i].Split(',')[2]);
                    FC.YBNumber = Convert.ToInt32(ContentStr[i].Split(',')[3]);
                    FC.InfoType = strType;
                    ProDefine.g_FunctionChannel.Add(FC);
                }
            }
            catch (System.Exception ex)
            {
            	
            }
        }

        private void lbOut_Click(object sender, EventArgs e)
        {
            try
            {
                SaveFileDialog saveFileDialog1 = new SaveFileDialog();
                saveFileDialog1.InitialDirectory = "d:\\";
                saveFileDialog1.Filter = "xls files (*.xls)|*.xls|xlsx files(*.xlsx)|*.xlsx";
                saveFileDialog1.FilterIndex = 2;
                saveFileDialog1.RestoreDirectory = true;
                DialogResult dr = saveFileDialog1.ShowDialog();
                if (dr == DialogResult.OK && saveFileDialog1.FileName.Length > 0)
                {
                    string SaveFileName = saveFileDialog1.FileName;
                    string[] StrArr = new string[this.dataGridView1.Rows.Count];
                    string CaptionString = "";

                    for (int i = 1; i < this.dataGridView1.Columns.Count; i++)
                    {

                        CaptionString += this.dataGridView1.Columns[i].HeaderText + ",";
                    }
                    CaptionString = CaptionString.Substring(0, CaptionString.Length - 1);
                    StrArr[0] = CaptionString;

                    for (int k = 0; k < this.dataGridView1.Rows.Count -1; k++)
                    {
                        string RowsString = "";
                        for (int i = 1; i < this.dataGridView1.Columns.Count; i++)
                        {

                            if (this.dataGridView1.Rows[k].Cells[i].Value == null)
                            {
                                RowsString += ",";

                            }
                            else
                            {

                                RowsString += this.dataGridView1.Rows[k].Cells[i].Value.ToString() + ",";
                            }

                        }
                        RowsString = RowsString.Substring(0, RowsString.Length - 1);
                        StrArr[k + 1] = RowsString;
                    }
                    List<string> DAList = new List<string>();
                    List<string> ADList = new List<string>();
                    GetADContent(ref DAList,ref ADList);
                    ExcelHelper.WriteToExcel(SaveFileName, StrArr,ADList.ToArray(),DAList.ToArray());
                    MessageBox.Show("导出文件成功！", "导出文件");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }


        public void GetADContent(ref List<string> DAList,ref List<string> ADList)
        {
            string CaptiontStr = "索引,命名,通道,样本号";
            DAList.Add(CaptiontStr);
            ADList.Add(CaptiontStr);
            foreach (var info in ProDefine.g_FunctionChannel)
            {
                string ValueStre = "";
                if (info.InfoType == 0)
                {
                    ValueStre = info.IndexStr + "," + info.FunctionName + "," + info.ChannelNumber + "," + info.YBNumber;
                    DAList.Add(ValueStre);
                }
                else
                {
                    ValueStre = info.IndexStr + "," + info.FunctionName + "," + info.ChannelNumber + "," + info.YBNumber;
                    ADList.Add(ValueStre);
                }
            }
        }

        private void lbSave_Click(object sender, EventArgs e)
        {
            try
            {
                int Rowcount = this.dataGridView1.Rows.Count - 1;

                for (int i = 0; i < Rowcount; i++ )
                {
                    ProDefine.g_ChannelInfos[i].IsFunctionSelect = (bool)this.dataGridView1.Rows[i].Cells[0].Value;
                    ProDefine.g_ChannelInfos[i].FucntionName = this.dataGridView1.Rows[i].Cells[1].Value.ToString();
                    ChangeFunctionName(ProDefine.g_ChannelInfos[i].IndexStr,ProDefine.g_ChannelInfos[i].FucntionName);
                }

                SaveConfigInfo();
                MessageBox.Show("保存完成");
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            
        }

        private void ChangeFunctionName(string IndexStr, string NewFunctionName)
        {
            List<FucntionChannelInfo> func = ProDefine.g_FunctionChannel.Where(m => m.IndexStr == IndexStr).ToList();
            foreach (var info in func)
            {
                info.FunctionName = NewFunctionName;
            }
        }

        private void SaveConfigInfo()
        {
            try
            {
                m_Pro.SaveChannelSetInfo();
                m_Pro.SaveYBChannelInfo();
            }
            catch (System.Exception ex)
            {
            	
            }

        }

        private void dataGridView1_CurrentCellChanged(object sender, EventArgs e)
        {
            if (dataGridView1.CurrentCell == null) { return; }
            DataGridViewColumn column = dataGridView1.CurrentCell.OwningColumn;
            //如果是要显示下拉列表的列的话
            if (column.Name.Equals("Column6"))
            {
                int columnIndex = dataGridView1.CurrentCell.ColumnIndex;
                int rowIndex = dataGridView1.CurrentCell.RowIndex;



                Rectangle rect = dataGridView1.GetCellDisplayRectangle(columnIndex, rowIndex, false);
                comboBox1.Left = this.dataGridView1.Left + rect.Left;
                comboBox1.Top = this.dataGridView1.Top + rect.Top;
                comboBox1.Width = rect.Width;
                comboBox1.Height = rect.Height;
                //将单元格的内容显示为下拉列表的当前项

                if (dataGridView1.Rows[rowIndex].Cells[columnIndex].Value == null)
                {
                    comboBox1.Visible = true;
                }
                else
                {
                    string consultingRoom = dataGridView1.Rows[rowIndex].Cells[columnIndex].Value.ToString();
                    int index = comboBox1.Items.IndexOf(consultingRoom);

                    comboBox1.SelectedIndex = index;
                    comboBox1.Visible = true;
                }

            }
            else
            {
                comboBox1.Visible = false;
            }
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBox1.SelectedIndex < 0) { return; }
            if (dataGridView1.CurrentCell != null)
                dataGridView1.CurrentCell.Value = comboBox1.Items[comboBox1.SelectedIndex];
        }

        private void lbIn_MouseEnter(object sender, EventArgs e)
        {
            this.lbIn.ForeColor = Color.DeepSkyBlue;
        }

        private void lbIn_MouseLeave(object sender, EventArgs e)
        {
            this.lbIn.ForeColor = Color.LightCyan;
        }

        private void lbOut_MouseEnter(object sender, EventArgs e)
        {
            this.lbOut.ForeColor = Color.DeepSkyBlue;
        }

        private void lbOut_MouseLeave(object sender, EventArgs e)
        {
            this.lbOut.ForeColor = Color.LightCyan;
        }

        private void lbSave_MouseEnter(object sender, EventArgs e)
        {
            this.lbSave.ForeColor = Color.DeepSkyBlue;
        }

        private void lbSave_MouseLeave(object sender, EventArgs e)
        {
            this.lbSave.ForeColor = Color.LightCyan;
        }

        private void lbAdd_Click(object sender, EventArgs e)
        {
            int Rowindex = this.dataGridView1.Rows.Add();
        }

        private void lbAdd_MouseEnter(object sender, EventArgs e)
        {
           
        }

        private void lbAdd_MouseLeave(object sender, EventArgs e)
        {
            
        }

        private void frmChannelSet_Load(object sender, EventArgs e)
        {

        }
    }
}
