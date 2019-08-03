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
    }
}
