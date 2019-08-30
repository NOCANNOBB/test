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
using DLLStruct;

namespace PRO190726
{
    public partial class frmDataAalrmSet : Form
    {
        public frmDataAalrmSet()
        {
            InitializeComponent();
            InitUI();
            m_Pro = new DoProjectInfo();
            m_Pro.GetYBSetSignel();
        }
        DoProjectInfo m_Pro;

        private void InitUI() {
            this.rabBZData.Text = "\uf0ad 标准数据";
            this.rabBZData.Font = new Font("FontAwesome", 13, FontStyle.Bold);
            this.rabBZData.ForeColor = Color.Lavender;

            this.rabAlarmData.Text = "\uf071 报警设置";
            this.rabAlarmData.Font = new Font("FontAwesome", 13, FontStyle.Bold);
            this.rabAlarmData.ForeColor = Color.Lavender;

            this.lbSave.Text = "\uf0c7  保存";
            this.lbSave.Font = new Font("FontAwesome", 12);
            this.lbSave.ForeColor = Color.White;


            this.lbSave2.Text = "\uf0c7  保存";
            this.lbSave2.Font = new Font("FontAwesome", 12);
            this.lbSave2.ForeColor = Color.White;


            this.lbYBSelect1.Text = "\uf2da  样本选择";
            this.lbYBSelect1.Font = new Font("FontAwesome", 12);
            this.lbYBSelect1.ForeColor = Color.White;

            this.lbYBSelect.Text = "\uf2da  样本选择";
            this.lbYBSelect.Font = new Font("FontAwesome", 12);
            this.lbYBSelect.ForeColor = Color.White;

            AddIndex = this.dataGridView1.Columns.Count - 1;
            InitData(this.dataGridView1);
            
        }
        private int AddIndex = 0;
        private void dataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if ((e.RowIndex % 2 != 0) && (e.ColumnIndex == AddIndex))
            {
                DataGridViewTextBoxColumn acCode = new DataGridViewTextBoxColumn();
                acCode.Name = "acCode";
                acCode.DataPropertyName = "acCode";
                acCode.HeaderText = "";
                this.dataGridView1.Columns.Insert(this.dataGridView1.Columns.Count - 1, acCode);
                AddIndex = this.dataGridView1.Columns.Count - 1;
                for (int i = 0; i < this.dataGridView1.Rows.Count - 1; i++)
                {
                    this.dataGridView1.Rows[i].Cells[this.dataGridView1.Columns.Count - 2].Value = -1;
                }
            }
        }

        private void dataGridView1_CurrentCellChanged(object sender, EventArgs e)
        {
            if (dataGridView1.CurrentCell == null) { return; }
            DataGridViewColumn column = dataGridView1.CurrentCell.OwningColumn;
            //如果是要显示下拉列表的列的话
            if (column.Name.Equals("Column2"))
            {
                int columnIndex = dataGridView1.CurrentCell.ColumnIndex;
                int rowIndex = dataGridView1.CurrentCell.RowIndex;

                if ((rowIndex % 2) == 0) { return; }

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
            if (dataGridView1.CurrentCell != null)
                dataGridView1.CurrentCell.Value = comboBox1.Items[comboBox1.SelectedIndex];
        }

        private void comboBox1_DrawItem(object sender, DrawItemEventArgs e)
        {
            e.DrawBackground();
            e.Graphics.DrawString(comboBox1.Items[e.Index].ToString(), e.Font, Brushes.Black,
            e.Bounds, StringFormat.GenericDefault);
        }

        private void rabBZData_Click(object sender, EventArgs e)
        {
            if (this.rabBZData.Checked) {
                this.panel1.Visible = true;
                this.panel2.Visible = false;
                //this.panel1.BringToFront();
            }

        }

        private void rabBZData_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void rabAlarmData_Click(object sender, EventArgs e)
        {
            if (this.rabAlarmData.Checked) {
                this.panel1.Visible = false;
                this.panel2.Visible = true ;
                //this.panel2.BringToFront();
            }
        }

        private void lbYBSelect1_MouseEnter(object sender, EventArgs e)
        {
            this.lbYBSelect1.ForeColor = Color.Violet;
        }

        private void lbYBSelect1_MouseLeave(object sender, EventArgs e)
        {
            this.lbYBSelect1.ForeColor = Color.White;
        }

        private void lbSave2_MouseEnter(object sender, EventArgs e)
        {
            this.lbSave2.ForeColor = Color.Violet;
        }

        private void lbSave2_MouseLeave(object sender, EventArgs e)
        {
            this.lbSave2.ForeColor = Color.White;
        }

        private void lbYBSelect_Click(object sender, EventArgs e)
        {
            this.lbYBSelect.ForeColor = Color.White;
        }

        private void lbYBSelect_MouseEnter(object sender, EventArgs e)
        {
            this.lbYBSelect.ForeColor = Color.Violet;
        }

        private void lbYBSelect_MouseLeave(object sender, EventArgs e)
        {
            this.lbYBSelect.ForeColor = Color.White;
        }

        private void lbSave_Click(object sender, EventArgs e)
        {
            m_Pro.SaveYBSetSignelOut();
        }

        private void lbSave_MouseEnter(object sender, EventArgs e)
        {
            this.lbSave.ForeColor = Color.Violet;
        }

        private void lbSave_MouseLeave(object sender, EventArgs e)
        {
            this.lbSave.ForeColor = Color.White;
        }
        List<int> m_YB = new List<int>();
        private void textBox1_Click(object sender, EventArgs e)
        {
            this.textBox1.Text = "";
            int ybNumber = Convert.ToInt32(ProDefine.g_SMExpermentParam.YBNumber);


            frmYBSelect frmyb = new frmYBSelect();
            frmyb.YBNumber = ybNumber;
            frmyb.ShowDialog();
            if (frmyb.DialogResult == System.Windows.Forms.DialogResult.OK)
            {
                m_YB = frmyb.returnList;
                foreach (var info in m_YB)
                {
                    this.textBox1.Text += "样本" + (info + 1).ToString() + ",";
                }
                InitData(this.dataGridView1);

            }
            else
            {
                this.textBox1.Text = "样本选择";
            }
        }

        private void InitData(DataGridView dgv)
        {
           dgv.Rows.Clear();

           if (dgv.Columns.Count > 3)
            {
                for (int i = 2; i <= dgv.Columns.Count - 1; )
                {
                    if (dgv.Columns.Count <= 3)
                    {
                        break;
                    }
                    dgv.Columns.RemoveAt(i);

                }
            }

           AddIndex = dgv.Columns.Count - 1;
            if (ProDefine.g_YBSetSignleOut.Count == 0)
            {
                foreach (var info in ProDefine.g_YBsetting)
                {
                    if (this.textBox1.Text.Contains(info.YBName))
                    {
                        foreach (var info_i in info.YBList)
                        {
                            if (!info_i.ChannelType.Contains("O"))
                            {
                                int kAddIndex = dgv.Rows.Add();
                                kAddIndex = dgv.Rows.Add();
                                dgv.Rows[kAddIndex].Cells[0].Value = info_i.GNFunction;
                            }
                        }
                        break;
                    }

                }
            }
            else
            {
                foreach (var info in ProDefine.g_YBsetting)
                {
                    if (this.textBox1.Text.Contains(info.YBName))
                    {
                        foreach (var info_i in info.YBList)
                        {
                            if (!info_i.ChannelType.Contains("O"))
                            {
                                int kAddIndex = dgv.Rows.Add();
                                kAddIndex = dgv.Rows.Add();
                                dgv.Rows[kAddIndex].Cells[0].Value = info_i.GNFunction;
                            }
                        }
                        break;
                    }

                }
            }


        }

        private List<string> GetYBList()
        {
            try
            {
                List<string> returnList = new List<string>();

                string Txt = this.textBox1.Text.Trim();
                if ((Txt == "") || (Txt == "样本选择"))
                {
                    return null;
                }
                string[] YBArr = Txt.Split(',');


                foreach (var info in YBArr)
                {
                    IsYBIsSet(info);
                    returnList.Add(info);
                }
                return returnList;
            }
            catch (System.Exception ex)
            {
                return null;
            }
        }

        private bool IsYBIsSet(string YBName)
        {
            try
            {
                foreach (var info in ProDefine.g_YBSetSignleOut)
                {
                    if (info.m_YBList.Contains(YBName))
                    {
                        info.m_YBList.Remove(YBName);
                        return true;
                    }
                }
                return false;
            }
            catch (System.Exception ex)
            {
                return false;
            }
        }


        private void label2_Click(object sender, EventArgs e)
        {
            List<string> YBList = GetYBList();

            int tCount = this.dataGridView1.Rows.Count - 1;

            int GNCount = tCount / 2;

            for (int i = 0; i < GNCount; i++)
            {
                string GNFunction = GetGNFunctionList(i);
                int SetType = GetTypeOfSignle(i);

                List<int> TimeList;
                List<double> VaLueList = GetValuesList(i, out TimeList);

                YBSingleSetInput YBSS = new YBSingleSetInput();

                YBSS.GNFunction = GNFunction;
                YBSS.m_TimeList = TimeList;
                YBSS.m_ValueList = VaLueList;
                YBSS.m_YBList = YBList;
                YBSS.SetType = SetType;

                ProDefine.g_YBSetSignleOut.Add(YBSS);
            }
        }

        private string GetGNFunctionList(int k)
        {
            try
            {
                string returnStr = "";
                int tCount = this.dataGridView1.Rows.Count - 1;
                if (this.dataGridView1.Rows[2 * k + 1].Cells[0].Value != null)
                {
                    returnStr = this.dataGridView1.Rows[2 * k + 1].Cells[0].Value.ToString();
                    return returnStr;
                }
                return returnStr;
            }
            catch (System.Exception ex)
            {
                return "";
            }


        }

        private int GetTypeOfSignle(int k)
        {
            try
            {
                int returnStr = -1;
                int tCount = this.dataGridView1.Rows.Count - 1;
                if (this.dataGridView1.Rows[2 * k + 1].Cells[1].Value != null)
                {
                    string Str = (this.dataGridView1.Rows[2 * k + 1].Cells[1].Value.ToString());

                    if (Str == "恒定值")
                    {
                        return 0;
                    }
                    else if (Str == "循环信号")
                    {
                        return 1;
                    }
                    else if (Str == "不循环变化信号")
                    {
                        return 2;
                    }
                    return returnStr;
                }
                return returnStr;
            }
            catch (System.Exception ex)
            {
                return -1;
            }

        }

        private List<double> GetValuesList(int k, out List<int> TimeList)
        {
            try
            {
                List<double> returnList = new List<double>();
                TimeList = new List<int>();

                for (int _index = 2; _index < this.dataGridView1.Columns.Count - 1; _index++)
                {
                    int iCellValue = -1;
                    object OValue = this.dataGridView1.Rows[2 * k].Cells[_index].Value;
                    if (OValue != null)
                    {
                        TimeList.Add(Convert.ToInt32(OValue));
                    }

                    OValue = this.dataGridView1.Rows[2 * k + 1].Cells[_index].Value;
                    if (OValue != null)
                    {
                        returnList.Add(Convert.ToDouble(OValue));
                    }

                }

                return returnList;
            }
            catch (System.Exception ex)
            {
                TimeList = null;
                return null;
            }
        }
        private void InitData2()
        {
            try
            {
                foreach (var info in ProDefine.g_YBsetting)
                {
                    if (this.textBox1.Text.Contains(info.YBName))
                    {
                        foreach (var info_i in info.YBList)
                        {
                            if (!info_i.ChannelType.Contains("O"))
                            {
                                int kAddIndex = this.dataGridView2.Rows.Add();
                                this.dataGridView2.Rows[kAddIndex].Cells[0].Value = info_i.GNFunction;
                            }
                        }
                        break;
                    }

                }
            }
            catch (System.Exception ex)
            {
            	
            }
        }
        private void textBox2_Click(object sender, EventArgs e)
        {
            this.textBox1.Text = "";
            int ybNumber = Convert.ToInt32(ProDefine.g_SMExpermentParam.YBNumber);


            frmYBSelect frmyb = new frmYBSelect();
            frmyb.YBNumber = ybNumber;
            frmyb.ShowDialog();
            if (frmyb.DialogResult == System.Windows.Forms.DialogResult.OK)
            {
                m_YB = frmyb.returnList;
                foreach (var info in m_YB)
                {
                    this.textBox1.Text += "样本" + (info + 1).ToString() + ",";
                }
                InitData2();

            }
            else
            {
                this.textBox1.Text = "样本选择";
            }
        }

        private void label1_Click(object sender, EventArgs e)
        {
            List<string> YBList = GetYBList();

            int tCount = this.dataGridView2.Rows.Count - 1;



            for (int i = 0; i < tCount; i++)
            {
                string GNFunction = this.dataGridView2.Rows[i].Cells[0].Value.ToString();
                string AlarmH = this.dataGridView2.Rows[i].Cells[1].Value.ToString();

                string AlarmL = this.dataGridView2.Rows[i].Cells[2].Value.ToString();

                string AlarmData = this.dataGridView2.Rows[i].Cells[3].Value.ToString();
                string AlarmAbs = this.dataGridView2.Rows[i].Cells[4].Value.ToString();

                YBAlarmSet ybs = new YBAlarmSet();
                ybs.AlarmAbs = AlarmAbs;
                ybs.AlarmData = AlarmData;
                ybs.AlarmH = AlarmH;
                ybs.AlarmL = AlarmL;
                ybs.GNFcontion = GNFunction;
                ybs.m_YBList = YBList;

                ProDefine.g_YBAlarm.Add(ybs);
            }
        }

        private void lbSave2_Click(object sender, EventArgs e)
        {

        }

    }
}
