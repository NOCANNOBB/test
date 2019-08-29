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
                int RowCount = ProDefine.g_ChannelInfo.Count;
                int ColNum = 7;
                for (int i = 0; i < RowCount; i++)
                {
                    ChannelSetInfo csi = ProDefine.g_ChannelInfo[i];
                    int kindex = this.dataGridView1.Rows.Add();
                    this.dataGridView1.Rows[kindex].Cells[0].Value = csi.FunctionName;
                    this.dataGridView1.Rows[kindex].Cells[1].Value = csi.Duanzi;
                    this.dataGridView1.Rows[kindex].Cells[2].Value = csi.Xianhao;
                    this.dataGridView1.Rows[kindex].Cells[3].Value = csi.hzZQ;
                    this.dataGridView1.Rows[kindex].Cells[4].Value = csi.PerReadNumber;
                    this.dataGridView1.Rows[kindex].Cells[5].Value = csi.ChannelType;
                    this.dataGridView1.Rows[kindex].Cells[6].Value = csi.channelNumber;

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

                    List<string> GetContentStr = ExcelHelper.ReadFromExcelFile(FileName);

                    if (GetContentStr.Count == 0)
                    {
                        MessageBox.Show("获取到数据内容为空");
                        return;
                    }

                    int RowCount = GetContentStr.Count;
                    int ColNum = GetContentStr[0].Split(',').Count();

                    this.dataGridView1.Rows.Clear();
                    for (int i = 1; i < RowCount; i++)
                    {
                        int kindex = this.dataGridView1.Rows.Add();
                        for (int k = 0; k < ColNum; k++)
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

                    for (int i = 0; i < this.dataGridView1.Columns.Count; i++)
                    {

                        CaptionString += this.dataGridView1.Columns[i].HeaderText + ",";
                    }
                    CaptionString = CaptionString.Substring(0, CaptionString.Length - 1);
                    StrArr[0] = CaptionString;

                    for (int k = 0; k < this.dataGridView1.Rows.Count -1; k++)
                    {
                        string RowsString = "";
                        for (int i = 0; i < this.dataGridView1.Columns.Count; i++)
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
                    ExcelHelper.WriteToExcel(SaveFileName, StrArr);
                    MessageBox.Show("导出文件成功！", "导出文件");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void lbSave_Click(object sender, EventArgs e)
        {
            try
            {
                ProDefine.g_ChannelInfo.Clear();
                int YBNumber = Convert.ToInt32(ProDefine.g_SMExpermentParam.YBNumber);
                int iCount = this.dataGridView1.Rows.Count - 1;

                if ((iCount % YBNumber) != 0)
                {
                    MessageBox.Show("通道数需为样本数的整数倍");
                    return;
                }

                int cloCount = this.dataGridView1.Columns.Count;
                bool IsFindNull = false;
                for (int i = 0; i < iCount; i++)
                {
                    string FunctionName = "";
                    string CardNumber = "";
                    string channelNumber = "";
                    string sValueType = "";
                    string ChannelType = "";
                    string sCardindex = "";
                    string sHz = "";
                    string PerGetNumber = "";
                    string StrDUANzi = "";
                    string XHStr = "";
                    for (int k = 0; k < cloCount; k++)
                    {
                        object CellValue = this.dataGridView1.Rows[i].Cells[k].Value;
                        if (CellValue == null)
                        {
                            IsFindNull = true;
                            continue;
                        }

                        if (k == 0)
                        {
                            FunctionName = CellValue.ToString();
                        }
                        else if (k == 1)
                        {
                            StrDUANzi = CellValue.ToString();
                        }
                        else if (k == 2)
                        {
                            XHStr = CellValue.ToString();
                        }
                        else if (k == 3)
                        {
                            sHz = CellValue.ToString();
                        }
                        else if (k == 4)
                        {
                            PerGetNumber = CellValue.ToString();
                        }
                        else if (k == 5)
                        {
                            ChannelType = CellValue.ToString();
                        }
                        else if (k == 6)
                        {
                            channelNumber = CellValue.ToString();
                        }

                    }

                    ChannelSetInfo csInfo = new ChannelSetInfo();
                    
                    csInfo.channelNumber = Convert.ToInt32(channelNumber);
                    csInfo.ChannelType = ChannelType;
                    csInfo.FunctionName = FunctionName;
                    csInfo.Duanzi = StrDUANzi;
                    csInfo.m_ProGuid = ProDefine.g_MyProject.GUID;
                    csInfo.hzZQ = Convert.ToInt32(sHz);
                    csInfo.PerReadNumber = Convert.ToInt32(PerGetNumber);
                    csInfo.Xianhao = XHStr;
                    ProDefine.g_ChannelInfo.Add(csInfo);
                    SaveConfigInfo();
                }
                if (IsFindNull)
                {

                    MessageBox.Show("存在内容为空的项，请检查");
                }
                MessageBox.Show("保存完成");
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            
        }

       

        private void SaveConfigInfo()
        {
            try
            {
                m_Pro.SaveChannelSetInfo();
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
