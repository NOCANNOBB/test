using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using DevExpress.XtraCharts;

namespace ExperienceDemo
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        /// <summary>
    /// 根据数据创建一个图形展现
    /// </summary>
    /// <param name="caption">图形标题</param>
    /// <param name="viewType">图形类型</param>
    /// <param name="rowIndex">图形数据的行序号</param>
    /// <returns></returns>
        public Series CreateSeries(string caption, ViewType viewType, Color _color)
        {
            Series series = new Series(caption, viewType);
            series.CrosshairEnabled = DevExpress.Utils.DefaultBoolean.True;
            series.View.Color = _color;
            //必须设置ArgumentScaleType的类型，否则显示会转换为日期格式，导致不是希望的格式显示
            //也就是说，显示字符串的参数，必须设置类型为ScaleType.Qualitative
            series.ArgumentScaleType = ScaleType.Qualitative;
            //series.LabelsVisibility = DevExpress.Utils.DefaultBoolean.True;//显示标注标签
            return series;
        }


        private void button1_Click(object sender, EventArgs e)
        {
            string Caption = "通道：" + this.comboBox1.Text;
            Series series1 = CreateSeries("变量1", ViewType.Line, Color.Brown);
        }


        /// <summary>
/// 创建图表的第二坐标系
/// </summary>
/// <param name="series">Series对象</param>
/// <returns></returns>
        public SecondaryAxisY CreateAxisY(DevExpress.XtraCharts.ChartControl _chartCtrl, Series series)
        {
            SecondaryAxisY myAxis = new SecondaryAxisY(series.Name);
            ((XYDiagram)_chartCtrl.Diagram).SecondaryAxesY.Add(myAxis);
            ((LineSeriesView)series.View).AxisY = myAxis;
            myAxis.Title.Text = series.Name;
            myAxis.Title.Alignment = StringAlignment.Far; //顶部对齐
            myAxis.Title.Visible = true; //显示标题
            myAxis.Title.Font = new Font("宋体", 9.0f);

            Color color = series.View.Color;//设置坐标的颜色和图表线条颜色一致

            myAxis.Title.TextColor = color;
            myAxis.Label.TextColor = color;
            myAxis.Color = color;

            return myAxis;
        }

        int DataRowIndex;
        private void UpdateChart(double Values)
        {
            DataRowIndex = DataRowIndex + 1;
            //曲线点数超过10后水平左移
            if (chart.Series[0].Points.Count >= 10)
            {
                for (int i = 0; i < chart.Series.Count; i++)
                {
                    if (chart.Series[i].Points.Count > 0)
                        chart.Series[i].Points.RemoveAt(0);
                }
            }
            for (int i = 0; i < 1; i++)
            {
                chart.Series[i].Points.Add(new SeriesPoint(DataRowIndex, Values[i]));
            }
            //第二坐标系归一化
            for (int i = 0; i < chart.Series.Count; i++)
            {
                if (chart.Series[i].Points.Count > 0)
                {
                    double Min = chart.Series[i].Points[0].Values[0];
                    double Max = chart.Series[i].Points[0].Values[0];
                    for (int j = 1; j < chart.Series[i].Points.Count; j++)
                    {
                        double Value = chart.Series[i].Points[j].Values[0];
                        if (Value < Min)
                            Min = Value;
                        if (Value > Max)
                            Max = Value;
                    }
                    XYDiagram RealDiag = (XYDiagram)chart.Diagram;
                    if (RealDiag != null)
                    {
                        RealDiag.SecondaryAxesY[i].WholeRange.MinValue = Min - 1;
                        RealDiag.SecondaryAxesY[i].WholeRange.MaxValue = Max + 1;
                    }
                }
            }
        }
    }
}
