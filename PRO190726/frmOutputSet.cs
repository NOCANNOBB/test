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
    public partial class frmOutputSet : Form
    {
        public frmOutputSet()
        {
            InitializeComponent();

            initUI();
        }
        private int AddIndex = 0;
        private void initUI (){
            //f156

            this.lbTitle.Text = "\uf00d 标况输入";
            this.lbTitle.Font = new Font("FontAwesome", 12);
            this.lbTitle.ForeColor = Color.White;

            this.lbSave.Text = "\uf0c7  保存";
            this.lbSave.Font = new Font("FontAwesome", 12);
            this.lbSave.ForeColor = Color.White;


            AddIndex = this.dataGridView1.Columns.Count - 1;


            for(int i = 0; i < 7; i++){

                int kindex = this.dataGridView1.Rows.Add();
                if (kindex % 2 != 0)
                {

                    dataGridView1.Rows[kindex].Cells["Column3"].Value = this.pictureBox1.Image;
                    //DataGridViewImageColumn Imange = new DataGridViewImageColumn();
                    //Imange.HeaderText = "照片";
                    //Imange.Image = this.pictureBox1.Image;//把PictureBox上的图片赋值给图像列
                    // Imange.ImageLayout = DataGridViewImageCellLayout.Zoom;//设置“照片”列的图像制定布局设定为缩略图
                    //this.dataGridView1.Columns.Add(Imange);//最后添加这
                    //this.dataGridView1.Columns["照片"].Visible = false;
                }
                else
                {
                    dataGridView1.Rows[kindex].Cells["Column3"].Value = pictureBox2.Image;
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
    }
}
