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
            this.line1.Add(DateTime.Now.ToOADate(), 1000);

            this.line1.GetVertAxis.SetMinMax(0, 1500);
            this.line1.GetVertAxis.Increment = 100;
            this.line1.GetHorizAxis.SetMinMax(DateTime.Now, DateTime.Now.AddSeconds(120));
            this.line1.XValues.DateTime = true;
            //this.line1.GetHorizAxis.Increment = 
            //this.line1.GetHorizAxis.Increment = 1;
            tChart1.Axes.Bottom.Labels.DateTimeFormat = "yyyy-MM-dd hh:mm:ss";
            
            //this.line1.DateTimeFormat = string.Format("yyyy-mm-dd hh:mm:ss");
        }

       

        private void button1_Click_1(object sender, EventArgs e)
        {
            tChart1.Header.Text = "实时曲线";
            
           
            timer1.Enabled = true;
        }

        Random rnd = new Random();
        private void AnimateSeries(Steema.TeeChart.TChart chart)
        {
          
            double newX, newY;
          
            chart.AutoRepaint = false;
            
            /// <summary>
            /// 绘画坐标点超过50个时将实时更新X时间坐标
            /// </summary>
            while (this.line1.Count > 150)
            {
                this.line1.Delete(0);
                line1.GetHorizAxis.SetMinMax(DateTime.Now.AddSeconds(-50), DateTime.Now.AddSeconds(60));
            }
                           
            newX = DateTime.Now.ToOADate();
            newY =  rnd.Next(1500);
            line1.Add(newX,newY);
 
            chart.AutoRepaint = true;
            chart.Refresh();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            AnimateSeries(tChart1);
        }
    }
}
