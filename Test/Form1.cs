using DevExpress.Utils;
using DevExpress.XtraEditors;
using DevExpress.XtraEditors.Repository;
using DevExpress.XtraGrid.Views.Base;
using DevExpress.XtraGrid.Views.Grid;
using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using DLLMemeryFile;
using DLLStruct;
using DLLNOPI;

namespace Test
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

            BindDataSource(InitDt());

            AddIndex = this.dataGridView1.Columns.Count - 1;
        }


        private DataTable InitDt()
        {
            DataTable dt = new DataTable("个人简历");
            dt.Columns.Add("ImageName", typeof(string));
            dt.Columns.Add("F1", typeof(string));
            dt.Columns.Add("F2", typeof(string));
            
            //dt.Rows.Add(new object[] { });
            return dt;
        }

        private void BindDataSource(DataTable dt)
        {
            //绑定DataTable  
            gridControl1.DataSource = dt;

           
        }  
        

        private void gridView1_InitNewRow(object sender, DevExpress.XtraGrid.Views.Grid.InitNewRowEventArgs e)
        {
            
        }

        private void gridView1_InitNewRow_1(object sender, DevExpress.XtraGrid.Views.Grid.InitNewRowEventArgs e)
        {
            ColumnView View = sender as ColumnView;
           // gridView1.SetRowCellValue(e.RowHandle, "gridColumn1", "1"); //复制最后一行的数据到新行
            RepositoryItemPictureEdit repositoryItemPictureEdit2 = new RepositoryItemPictureEdit();
            repositoryItemPictureEdit2.InitialImage= Image.FromFile(@"G:\test\PRO190726\Images\player-icons_40px_1137045_easyicon.net.png");
            View.SetRowCellValue(e.RowHandle, View.Columns[0], repositoryItemPictureEdit2);
            View.SetRowCellValue(e.RowHandle, View.Columns[1], "12312");
            
        }

        private void simpleButton1_Click(object sender, EventArgs e)
        {
            gridView1.AddNewRow();
          

           // gridView1.EndDataUpdate();
           // gridView2.EndDataUpdate();
           // gridView3.EndDataUpdate();
        }
        Hashtable Images = new Hashtable();
        private void gridView1_CustomUnboundColumnData(object sender, CustomColumnDataEventArgs e)
        {
            if (e.Column.FieldName == "Image" && e.IsGetData)
            {

                GridView view = sender as GridView;

                //string colorName = (string)((DataRowView)e.Row)["gridColumn1"];

                string fileName = "player-icons_40px_1137045_easyicon.net.png";

                if (!Images.ContainsKey(fileName))
                {

                    Image img = null;

                    try
                    {

                        string filePath = @"G:\test\PRO190726\Images\player-icons_40px_1137045_easyicon.net.png";//DevExpress.Utils.FilesHelper.FindingFileName(Application.StartupPath,, false);

                        img = Image.FromFile(filePath);

                    }

                    catch
                    {

                    }

                    Images.Add(fileName, img);

                }

                e.Value = Images[fileName];

            }
            else if (e.Column.FieldName == "F1") {
                e.Value = "11111";
            }
        }

        private void gridView2_InitNewRow(object sender, InitNewRowEventArgs e)
        {
            ColumnView View = sender as ColumnView;
            
            View.SetRowCellValue(e.RowHandle, View.Columns[0], "1231");
        }

        private void gridView3_InitNewRow(object sender, InitNewRowEventArgs e)
        {
            ColumnView View = sender as ColumnView;

            View.SetRowCellValue(e.RowHandle, View.Columns[0], "1231");

            View.SetRowCellValue(e.RowHandle, View.Columns[1], "1231");

            View.SetRowCellValue(e.RowHandle, View.Columns[2], "1231");

            //view.SetRowCellValue(e.RowHandle, view.Columns[0], 1);
            //view.SetRowCellValue(e.RowHandle, view.Columns[1], 2);
            //view.SetRowCellValue(e.RowHandle, view.Columns[2], 3);
        }

        private void simpleButton2_Click(object sender, EventArgs e)
        {
            if (gridView1.RowCount > 0) {
                //this.gridView1.GetRowCellValue(0, "F2");
                this.gridView1.Columns[1].AppearanceCell.BackColor = Color.Red;
                //this.gridView1.
            }
        }

        private void gridView1_RowCellStyle(object sender, RowCellStyleEventArgs e)
        {
            if ((e.RowHandle == 0)&&(e.Column.ColumnHandle == 1)) {
                
            }
        }

        private void simpleButton3_Click(object sender, EventArgs e)
        {
            dataGridView1.Controls.Add(comboBox1);

            int RowIndex = this.dataGridView1.Rows.Add();




            if (RowIndex % 2 != 0)
            {

                dataGridView1.Rows[RowIndex].Cells["Column3"].Value = this.pictureBox1.Image;
                //DataGridViewImageColumn Imange = new DataGridViewImageColumn();
                //Imange.HeaderText = "照片";
                //Imange.Image = this.pictureBox1.Image;//把PictureBox上的图片赋值给图像列
               // Imange.ImageLayout = DataGridViewImageCellLayout.Zoom;//设置“照片”列的图像制定布局设定为缩略图
                //this.dataGridView1.Columns.Add(Imange);//最后添加这
                //this.dataGridView1.Columns["照片"].Visible = false;
            }
            else {
                dataGridView1.Rows[RowIndex].Cells["Column3"].Value = pictureBox2.Image;
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

                if (rowIndex == 0) { return; }

                Rectangle rect = dataGridView1.GetCellDisplayRectangle(columnIndex, rowIndex, false);
                comboBox1.Left = rect.Left;
                comboBox1.Top = rect.Top;
                comboBox1.Width = rect.Width;
                comboBox1.Height = rect.Height;
                //将单元格的内容显示为下拉列表的当前项

                if (dataGridView1.Rows[rowIndex].Cells[columnIndex].Value == null)
                {
                    comboBox1.Visible = true;
                }
                else {
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

        private int AddIndex = 2;

        private void dataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if ((e.RowIndex % 2 != 0) && (e.ColumnIndex == AddIndex))
            {
                DataGridViewTextBoxColumn acCode = new DataGridViewTextBoxColumn();
                acCode.Name = "acCode";
                acCode.DataPropertyName = "acCode";
                acCode.HeaderText = "";
                this.dataGridView1.Columns.Insert(this.dataGridView1.Columns.Count - 1,acCode);
                AddIndex = this.dataGridView1.Columns.Count - 1;
            }
        }
        MemeryFile mf = null;
        private void simpleButton4_Click(object sender, EventArgs e)
        {

        }

        private void simpleButton5_Click(object sender, EventArgs e)
        { 
        }

        private void simpleButton6_Click(object sender, EventArgs e)
        {
            string[] StrArr = new string[this.dataGridView2.Rows.Count + 1];
            string CaptionString = "";

            for (int i = 0; i < this.dataGridView2.Columns.Count; i++)
            {

                CaptionString += this.dataGridView2.Columns[i].HeaderText + ",";
            }
            CaptionString = CaptionString.Substring(0, CaptionString.Length - 1);
            StrArr[0] = CaptionString;

            for (int k = 0; k < this.dataGridView2.Rows.Count; k++)
            {
                string RowsString = "";
                for (int i = 0; i < this.dataGridView2.Columns.Count; i++)
                {

                    if(this.dataGridView2.Rows[k].Cells[i].Value == null){
                        RowsString += ",";

                    }
                    else{

                        RowsString += this.dataGridView2.Rows[k].Cells[i].Value.ToString()+",";
                    }
                    
                }
                RowsString = RowsString.Substring(0, RowsString.Length - 1);
                StrArr[k+1] = RowsString;
            }
            ExcelHelper.WriteToExcel("kkk.xls", StrArr);

        }

        private void simpleButton7_Click(object sender, EventArgs e)
        {
            List<string> returnArr = ExcelHelper.ReadFromExcelFile("kkk.xls");

            int RowCount = returnArr.Count;
            int ColNum = returnArr[0].Split(',').Count();

            this.dataGridView2.Rows.Clear();
            for (int i = 1; i < RowCount; i++)
            {
                int kindex = this.dataGridView2.Rows.Add();
                for(int k= 0; k < ColNum; k++){
                    this.dataGridView2.Rows[kindex].Cells[k].Value = returnArr[i].Split(',')[k];
                }
            }
        }
    }
}
