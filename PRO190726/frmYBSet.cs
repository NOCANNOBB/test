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
using DLLProjectInfo;
using DLLStruct;

namespace PRO190726
{



    public partial class frmYBSet : Form
    {
        public frmYBSet()
        {
            InitializeComponent();
            initUI();
            m_pro = new DoProjectInfo();
            m_pro.GetYBChannelInfo();
            ShowFirst();
        }

        private void dataGridView1_CurrentCellChanged(object sender, EventArgs e)
        {
            if (dataGridView1.CurrentCell == null) { return; }
            DataGridViewColumn column = dataGridView1.CurrentCell.OwningColumn;
            //如果是要显示下拉列表的列的话
            if (column.Name.Equals("Column3"))
            {
                int columnIndex = dataGridView1.CurrentCell.ColumnIndex;
                int rowIndex = dataGridView1.CurrentCell.RowIndex;

                

                Rectangle rect = dataGridView1.GetCellDisplayRectangle(columnIndex, rowIndex, false);
                comboBox2.Left = this.dataGridView1.Left + rect.Left;
                comboBox2.Top = this.dataGridView1.Top + rect.Top;
                comboBox2.Width = rect.Width;
                comboBox2.Height = rect.Height;
                //将单元格的内容显示为下拉列表的当前项

                if (dataGridView1.Rows[rowIndex].Cells[columnIndex].Value == null)
                {
                    comboBox2.Visible = true;
                }
                else
                {
                    string consultingRoom = dataGridView1.Rows[rowIndex].Cells[columnIndex].Value.ToString();

                    OutAndInQueen(consultingRoom);
                  
                    //int index = comboBox2.Items.IndexOf(consultingRoom);
                   // comboBox2.Text = consultingRoom;
                    //comboBox2.SelectedIndex = index;
                    comboBox2.Visible = true;
                }

            }
            else
            {
                comboBox2.Visible = false;
            }
        }

        private void OutAndInQueen(string CombText)
        {
            if (CombText == "") { return; }
            int _index =  CombText.IndexOf('-');
            if(_index == -1){return;}
            string TypeStr = CombText.Substring(0, CombText.IndexOf('-'));
            int channelNumber = Convert.ToInt32(CombText.Substring(_index + 1, CombText.Length - _index - 1));

            int TIndex = UsedChannel.FindIndex(m => (m.ChannelID == channelNumber) & (m.ChannelType == TypeStr));
            if (TIndex == -1) { return; }

            noUserChannel.Add(UsedChannel[TIndex]);
            UsedChannel.RemoveAt(TIndex);
            AddComb();
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBox2.SelectedIndex < 0) { return; }
            if (dataGridView1.CurrentCell != null)
            {
                dataGridView1.CurrentCell.Value = comboBox2.Items[comboBox2.SelectedIndex];
                dataGridView1.Rows[dataGridView1.CurrentCell.RowIndex].Cells[dataGridView1.CurrentCell.ColumnIndex + 1].Value = this.noUserChannel[comboBox2.SelectedIndex].ChannelType;
                OutFromNoUseQueen(comboBox2.Items[comboBox2.SelectedIndex].ToString());
                
            }
            this.comboBox2.Visible = false;
            //this.UsedChannel.Add(Convert.ToInt32(comboBox2.Items[comboBox2.SelectedIndex].ToString()));
        }


        private void OutFromNoUseQueen(string combText)
        {
            if (combText == "") { return; }
            int _index = combText.IndexOf('-');
            if (_index == -1) { return; }
            string TypeStr = combText.Substring(0, combText.IndexOf('-'));
            int channelNumber = Convert.ToInt32(combText.Substring(_index + 1, combText.Length - _index - 1));

            int TIndex = noUserChannel.FindIndex(m => (m.ChannelID == channelNumber) & (m.ChannelType == TypeStr));
            if (TIndex == -1) { return; }

            UsedChannel.Add(noUserChannel[TIndex]);
            noUserChannel.RemoveAt(TIndex);
            AddComb();

        }

        private void comboBox3_SelectedIndexChanged(object sender, EventArgs e)
        {
        }

        List<YBSetuse> noUserChannel = new List<YBSetuse>();
        List<YBSetuse> UsedChannel = new List<YBSetuse>();

        public void initUI()
        {
            foreach (var info in ProDefine.g_ChannelInfo)
            {
                YBSetuse ybs = new YBSetuse();
                ybs.ChannelID = info.channelNumber;
                ybs.ChannelType = info.ChannelType;
                noUserChannel.Add(ybs);
                comboBox2.Items.Add(ybs.ChannelType.ToString() + "-" + ybs.ChannelID.ToString());
            }
            int YBNumber = Convert.ToInt32(ProDefine.g_SMExpermentParam.YBNumber);
            for (int i = 0; i < YBNumber; i++ )
            {
                this.comboBox1.Items.Add("样本" + (i + 1).ToString());
            }
            
        }

        private void AddComb()
        {
            comboBox2.Items.Clear();
            foreach (var info in noUserChannel)
            {
                comboBox2.Items.Add(info.ChannelType.ToString() + "-" + info.ChannelID.ToString());
            }

        }

        private void label3_Click(object sender, EventArgs e)
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

                    for (int k = 0; k < this.dataGridView1.Rows.Count - 1; k++)
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

        private void label4_Click(object sender, EventArgs e)
        {
            try
            {
                OpenFileDialog file = new OpenFileDialog();
                file.Filter = "xls files(*.xls)|*.xls|xlsx files(*.xlsx)|*.xlsx";
                if (file.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    this.dataGridView1.Rows.Clear();
                    string FileName = file.FileName;

                    List<string> GetContentStr = ExcelHelper.ReadFromExcelFile(FileName,"sheet0");

                    if (GetContentStr.Count == 0)
                    {
                        MessageBox.Show("获取到数据内容为空");
                        return;
                    }

                    int RowCount = GetContentStr.Count;
                    int ColNum = GetContentStr[0].Split(',').Count();

                    if (ColNum != this.dataGridView1.Columns.Count)
                    {
                        MessageBox.Show("模板格式不正确");
                        return;
                    }

                    this.dataGridView1.Rows.Clear();
                    for (int i = 1; i < RowCount; i++)
                    {
                        int kindex = this.dataGridView1.Rows.Add();
                        for (int k = 0; k < 1; k++)
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


        private string LastSelcetYBName = "";
        private string NoSelcetYBName = "";

        private void ShowFirst()
        {
            this.dataGridView1.Rows.Clear();
            if (ProDefine.g_YBsetting.Count > 0)
            {
                comboBox1.Text = ProDefine.g_YBsetting[0].YBName;
                foreach (var info in ProDefine.g_YBsetting[0].YBList)
                {
                    //foreach (var info in ybc.YBList)
                    {
                        int RowIndex = this.dataGridView1.Rows.Add();
                        this.dataGridView1.Rows[RowIndex].Cells[0].Value = info.GNFunction;
                        this.dataGridView1.Rows[RowIndex].Cells[1].Value = info.ChannelType + "-" + info.ChannelID.ToString();
                        this.dataGridView1.Rows[RowIndex].Cells[2].Value = info.ChannelType;
                    }
                }
            }
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            NoSelcetYBName = this.comboBox1.Items[comboBox1.SelectedIndex].ToString();
            if (NoSelcetYBName != LastSelcetYBName)
            {
                if (LastSelcetYBName == "")
                {
                    LastSelcetYBName = this.comboBox1.Items[comboBox1.SelectedIndex].ToString();
                }
                else if ((this.dataGridView1.Rows.Count - 1) > 0)
                {

                    if (ProDefine.g_YBsetting.Count == 0)
                    {
                        insertANewYBSet();
                        ClearSettingColumn();
                    }
                    else
                    {
                        int PreCount = ProDefine.g_YBsetting[0].YBList.Count;
                        if (PreCount != (this.dataGridView1.Rows.Count - 1))
                        {
                            MessageBox.Show("本次配置样本通道数目和上次不符");
                            return;
                        }

                        YBChannelInfo ybc = ProDefine.g_YBsetting.Where(m => m.YBName == NoSelcetYBName).SingleOrDefault();
                        if (ybc == null)
                        {
                            insertANewYBSet();
                            ClearSettingColumn();
                        }
                        else
                        {
                            insertANewYBSet();
                            this.dataGridView1.Rows.Clear();
                            int RowCount = ybc.YBList.Count;
                            foreach (var info in ybc.YBList)
                            {
                                int RowIndex = this.dataGridView1.Rows.Add();
                                this.dataGridView1.Rows[RowIndex].Cells[0].Value = info.GNFunction;
                                this.dataGridView1.Rows[RowIndex].Cells[1].Value = info.ChannelType + "-"+ info.ChannelID.ToString();
                                this.dataGridView1.Rows[RowIndex].Cells[2].Value = info.ChannelType;
                            }
                            
                        }

                    }
                    LastSelcetYBName = NoSelcetYBName;
                    //ClearSettingColumn();
                }
            }
        }

        private void insertANewYBSet()
        {
            try
            {
                bool isInsert = false;
                YBChannelInfo ybc = ProDefine.g_YBsetting.Where(m => m.YBName == LastSelcetYBName).SingleOrDefault();
                if (ybc == null)
                {
                    ybc = new YBChannelInfo();
                    isInsert = true;
                    ybc.YBList = new List<YBSetuse>();
                    ybc.YBName = LastSelcetYBName;
                }
                

                int settingCount = this.dataGridView1.Rows.Count - 1;

                for (int i = 0; i < settingCount; i++)
                {
                    YBSetuse ybs;
                    if (isInsert)
                    {
                        ybs = new YBSetuse();
                    }
                    else
                    {
                        ybs = ybc.YBList[i];
                    }
                    
                    ybs.GNFunction = this.dataGridView1.Rows[i].Cells[0].Value.ToString();
                    string ChannelInfo = this.dataGridView1.Rows[i].Cells[1].Value.ToString();
                    string TypeStr = this.dataGridView1.Rows[i].Cells[2].Value.ToString();
                    int _index = ChannelInfo.IndexOf('-');
                    int ChannleID = Convert.ToInt32(ChannelInfo.Substring(_index + 1,ChannelInfo.Length - _index -1));
                    ybs.ChannelID = ChannleID;
                    ybs.ChannelType = TypeStr;
                    if (isInsert)
                    {
                        ybc.YBList.Add(ybs);
                    }
                }
                if (isInsert)
                {
                    ProDefine.g_YBsetting.Add(ybc);
                }
                
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void ClearSettingColumn()
        {
            try
            {
                int RowsCount = this.dataGridView1.Rows.Count -1;
                for (int i = 0; i < RowsCount; i++ )
                {
                    this.dataGridView1.Rows[i].Cells[1].Value = null;
                    this.dataGridView1.Rows[i].Cells[2].Value = null;
                }
            }
            catch (System.Exception ex)
            {
            	
            }

        }
        private DoProjectInfo m_pro;
        private bool IsYBSetiingOK()
        {
            try
            {
                if (ProDefine.g_YBsetting.Count == 0)
                {
                    return false;
                }

                foreach (var info in ProDefine.g_YBsetting)
                {
                    if (info.YBName == "")
                    {
                        return false;
                    }
                    if (info.YBList.Count == 0)
                    {
                        return false;
                    }
                    foreach (var info_i in info.YBList)
                    {
                        if ((info_i.ChannelType == "")||(info_i.GNFunction == ""))
                        {

                            return false;
                        }
                    }
                }

                return true;
            }
            catch (System.Exception ex)
            {
                return false;
            }
        }

        private void label2_Click(object sender, EventArgs e)
        {
            try
            {
                insertLastSetting();
                if (!IsYBSetiingOK())
                {
                    MessageBox.Show("样本参数配置不完全，无法进行保存");
                    return;
                }
                m_pro.SaveYBChannelInfo();
                MessageBox.Show("保存成功");
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            
        }

        private void insertLastSetting()
        {
            try
            {
                bool isInsert = false;
                YBChannelInfo ybc = ProDefine.g_YBsetting.Where(m => m.YBName == comboBox1.Text).SingleOrDefault();
                if (ybc == null)
                {
                    ybc = new YBChannelInfo();
                    isInsert = true;
                    ybc.YBList = new List<YBSetuse>();
                    ybc.YBName = comboBox1.Text;
                }


                int settingCount = this.dataGridView1.Rows.Count - 1;

                for (int i = 0; i < settingCount; i++)
                {
                    YBSetuse ybs;
                    if (isInsert)
                    {
                        ybs = new YBSetuse();
                    }
                    else
                    {
                        ybs = ybc.YBList[i];
                    }

                    ybs.GNFunction = this.dataGridView1.Rows[i].Cells[0].Value.ToString();
                    string ChannelInfo = this.dataGridView1.Rows[i].Cells[1].Value.ToString();
                    string TypeStr = this.dataGridView1.Rows[i].Cells[2].Value.ToString();
                    int _index = ChannelInfo.IndexOf('-');
                    int ChannleID = Convert.ToInt32(ChannelInfo.Substring(_index + 1, ChannelInfo.Length - _index - 1));
                    ybs.ChannelID = ChannleID;
                    ybs.ChannelType = TypeStr;
                    if (isInsert)
                    {
                        ybc.YBList.Add(ybs);
                    }
                }
                if (isInsert)
                {
                    ProDefine.g_YBsetting.Add(ybc);
                }

            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }
}
