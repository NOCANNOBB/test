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
    public partial class frmInputSet : Form
    {
        public frmInputSet()
        {
            InitializeComponent();

            initUI();
            m_Pro = new DoProjectInfo();
            m_Pro.GetYBSetSignel();
        }
        private int AddIndex = 0;

        DoProjectInfo m_Pro;
        private void initUI (){
            //f156

            this.lbTitle.Text = "\uf00d 标况输入";
            this.lbTitle.Font = new Font("FontAwesome", 12);
            this.lbTitle.ForeColor = Color.White;

            this.lbSave.Text = "\uf0c7  保存";
            this.lbSave.Font = new Font("FontAwesome", 12);
            this.lbSave.ForeColor = Color.White;
            AddIndex = this.dataGridView1.Columns.Count - 1;
        }


        private void SetValueAndTime(int rindex,List<int> TimeList,List<double> ValueList)
        {
            try
            {
                for (int i = 0; i < TimeList.Count;i++)
                {
                    if (rindex == 1)
                    {
                        DataGridViewTextBoxColumn acCode = new DataGridViewTextBoxColumn();
                        acCode.Name = "acCode";
                        acCode.DataPropertyName = "acCode";
                        acCode.HeaderText = "";
                        this.dataGridView1.Columns.Insert(this.dataGridView1.Columns.Count - 1, acCode);
                    }
                    this.dataGridView1.Rows[rindex - 1].Cells[i + 2].Value = TimeList[i].ToString();
                    this.dataGridView1.Rows[rindex].Cells[i + 2].Value = ValueList[i].ToString();
                }
                
            }
            catch (System.Exception ex)
            {
            	
            }
        }

        private void InitData()
        {
            this.dataGridView1.Rows.Clear();

            if (ProDefine.g_YBSetSignle.Count > 0)
            {
                int kinde = 0;
                foreach (var info in ProDefine.g_YBSetSignle)
                {

                    int Rindex = this.dataGridView1.Rows.Add();
                    Rindex = this.dataGridView1.Rows.Add();

                    this.dataGridView1.Rows[Rindex].Cells[0].Value = info.GNFunction;
                    this.dataGridView1.Rows[Rindex].Cells[1].Value = this.comboBox1.Items[info.SetType].ToString();
                    SetValueAndTime(Rindex,info.m_TimeList,info.m_ValueList);

                }
            }
            else
            {
                List<string> aList = new List<string>();

                foreach (var info in ProDefine.g_ChannelInfos)
                {
                    if ((info.FunctionType == "AI") || (info.FunctionType == "CNT"))
                    {
                        aList.Add(info.FucntionName);
                    }
                }
                foreach (var info in aList)
                {
                    int Rindex = this.dataGridView1.Rows.Add();
                    Rindex = this.dataGridView1.Rows.Add();

                    this.dataGridView1.Rows[Rindex].Cells[0].Value = info;
                }
            }
        }



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

        private void comboBox1_DrawItem(object sender, DrawItemEventArgs e)
        {
            e.DrawBackground();
            e.Graphics.DrawString(comboBox1.Items[e.Index].ToString(), e.Font, Brushes.Black,
            e.Bounds, StringFormat.GenericDefault);
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (dataGridView1.CurrentCell != null)
                dataGridView1.CurrentCell.Value = comboBox1.Items[comboBox1.SelectedIndex];
        }

        List<int> m_YB = new List<int>();
        private void textBox1_Click(object sender, EventArgs e)
        {
           
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void lbSave_Click(object sender, EventArgs e)
        {
           
        }

        private List<double> GetValuesList(int k,out List<int> TimeList)
        {
            try
            {
                List<double> returnList = new List<double>();
                TimeList = new List<int>();

                for (int _index = 2; _index < this.dataGridView1.Columns.Count - 1; _index++ )
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


        
        private bool IsYBIsSet(string YBName)
        {
            try
            {
                foreach (var info in ProDefine.g_YBSetSignle)
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

        private void label1_Click(object sender, EventArgs e)
        {

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
                YBSS.SetType = SetType;

                ProDefine.g_YBSetSignle.Add(YBSS);
            }
            m_Pro.SaveYBSetSignel();
            MessageBox.Show("保存成功");
        }

        private void frmOutputSet_Load(object sender, EventArgs e)
        {
            InitData();
        }
    }
}
