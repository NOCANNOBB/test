using Define;
using DevExpress.Utils.Menu;
using DevExpress.XtraEditors;
using DLLStruct;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using DLLBordDllImport;
using DLLMemeryFile;
using System.Runtime.InteropServices;

namespace PRO190726
{
    public partial class frmExperment : Form
    {
        public frmExperment()
        {
            InitializeComponent();
            InitUI();
            DoUIInit();
            m_MemeryFile = new MemeryFile();
        }

        private void GetTotalExpTime()
        {
            int Totla = 0;
            foreach (var info in ProDefine.g_SMExpermentDesin.ExpParamList)
            {
                Totla += info.ExpermentTime;
            }
            m_TotalTime = Totla;
        }

        private MemeryFile m_MemeryFile = null;
        private Thread m_ReadThread = null;
        private Thread m_WriteThread = null;
        private bool m_IsExpermentEnd = false;
        private DateTime m_StartTime;
        private int m_TotalTime = 0;
        private int GetEcliptsTime()
        {
            return (int)(DateTime.Now - m_StartTime).Milliseconds;
        }

        private void InitUI() {
            this.lbStart.Text = "\uf04b 开始实验";
            this.lbStart.Font = new Font("FontAwesome", 15, FontStyle.Bold);
            this.lbStart.ForeColor = Color.White;


            this.lbEnd.Text = "\uf04d 停止实验";
            this.lbEnd.Font = new Font("FontAwesome", 15, FontStyle.Bold);
            this.lbEnd.ForeColor = Color.White;


            this.line1.Add(DateTime.Now.ToOADate(), 10);

            this.line1.GetVertAxis.SetMinMax(-10, 10);
            this.line1.GetVertAxis.Increment = 1;
            this.line1.GetHorizAxis.SetMinMax(DateTime.Now, DateTime.Now.AddSeconds(120));
            this.line1.XValues.DateTime = true;
            //this.line1.GetHorizAxis.Increment = 
            //this.line1.GetHorizAxis.Increment = 1;
            tChart2.Axes.Bottom.Labels.DateTimeFormat = "yyyy-MM-dd hh:mm:ss";
            if (!InitBords())
            {
               MessageBox.Show("设备初始化失败");
               return;
            }
            try
            {
                if (m_ReadThread == null)
                {
                    m_ReadThread = new Thread(DoReadData);
                }
                if (m_WriteThread == null)
                {
                    m_WriteThread = new Thread(DoWriteData);
                }
            }
            catch (System.Exception ex)
            {

            }

           
        }

        private int m_ExpermentStep = 0;
        private int m_lastExpermentStep = 0;

        private int GetNowStepExpermentTime()//获取当前步骤实验总时间
        {
            int NowTotalTime = 0;
            for (int i = 0; i <= m_ExpermentStep; i++ )
            {
                NowTotalTime += ProDefine.g_SMExpermentDesin.ExpParamList[i].ExpermentTime * 60 * 60 * 1000;
            }
            return NowTotalTime;
        }

        private List<FucntionChannelInfo> GetStepChannelList()//获取当前步骤通道
        {
            List<FucntionChannelInfo> returnList = new List<FucntionChannelInfo>();

            int YBStart = GetNowStepYBStart();
            int YBEnd = GetNowStepYBEnd();

            for (int i = YBStart; i <= YBEnd; i++)
            {

                returnList.AddRange(ProDefine.g_FunctionChannel.Where(m => m.ChannelNumber == i).ToList());
            }
            return returnList;
            
        }

        private bool InitBords()
        {
            if (!BordDll.DoInit())
            {
                return false;
            }
            foreach (var info in ProDefine.g_ChannelInfo)
            {
                BordDll.StartChannel((uint)info.channelNumber);
            }
            return true;
        }


        private int GetChannelHz(int ChannelID,string FunctionName,ref int PerRead)
        {
            int Hz = 0;
            ChannelInfos cs = ProDefine.g_ChannelInfos.Where(m => m.FucntionName == FunctionName).SingleOrDefault();
            if (cs != null)
            {
                Hz = cs.Hz;
                PerRead = cs.PerCount;
            }
            return Hz;
        }

        private int GetNowStepYBStart()//获取当前步骤，样本起始
        {
            int StepStart = 0;
            for (int i = 0; i < m_ExpermentStep; i++)
            {
                StepStart += ProDefine.g_SMExpermentDesin.ExpParamList[i].YBNumber;
            }
            return (StepStart + 1);
        }
        private int GetNowStepYBEnd()//获取当前步骤，样本结束
        {
            int StepEnd = 0;
            for (int i = 0; i <= m_ExpermentStep; i++)
            {
                StepEnd += ProDefine.g_SMExpermentDesin.ExpParamList[i].YBNumber;
            }
            return StepEnd;
        }

        private List<YBData> m_DataList = new List<YBData>();
        private object m_lock = new object();
        private object m_diskLock = new object();
        private void InsertDataToList(YBData ydata)
        {
            List<YBData> ChannelListData = m_DataList.Where(m => m.ChannID == ydata.ChannID && m.ChannType == ydata.ChannType).ToList();
            if (ChannelListData.Count >= 1)
            {
                m_DataList.Remove(ChannelListData.ElementAt(0));
            }
            lock (m_lock)
            {
                m_DataList.Add(ydata);
            }
            
        }

        private string GetNowChannelType(string GNFunction)
        {
            try
            {
                ChannelInfos ci = ProDefine.g_ChannelInfos.Where(m => m.FucntionName == GNFunction).SingleOrDefault();
                if (ci != null)
                {
                    return ci.FunctionType;
                }
            }
            catch (System.Exception ex)
            {
            	
            }
            return "";
        }

        private void ReadData(int EclipsTime)
        {
            try
            {
                List<FucntionChannelInfo> chList = GetStepChannelList();

                foreach (var info in chList)
                {
                    int PerRread1 = 5;
                    //foreach (var info_i in info.YBList)
                    {
                        int Hz = GetChannelHz(info.ChannelNumber, info.FunctionName, ref PerRread1);
                        string ChannelType = GetNowChannelType(info.FunctionName);
                        double flVolt = 0;
                        double dfFreq =0;
                        double dfDuty = 0;
                        
                        if ((EclipsTime % Hz) == 0)
                        {
                            switch (ChannelType)
                            {
                                case "AI":
                                    int retRead = 0;
                                    double[] bBuffer = new double[PerRread1];
                                    BordDll.GetDataFromBord(info.ChannelNumber, bBuffer,PerRread1,ref retRead);

                                    for (int i = 0; i < retRead; i++ )
                                    {
                                        YBData ydata = new YBData();
                                        ydata.ChannID = info.ChannelNumber;
                                        ydata.ChannType = ChannelType;
                                        ydata.DTTime = EclipsTime;
                                        ydata.flVot = bBuffer[i];
                                        ydata.YBName = info.YBNumber.ToString();
                                        ydata.GNFunction = info.FunctionName;

                                        int returnValue = JudageAlarmData(EclipsTime, info.YBNumber, info.FunctionName, flVolt);
                                        ydata.DataInfo = returnValue;
                                        InsertDataToList(ydata);
                                        if (returnValue == 0)
                                        {
                                            lock (m_diskLock)
                                            {
                                                m_YBDataList.Add(ydata);
                                            }
                                        }
                                        else
                                        {
                                            lock (m_AlarmDiskLock)
                                            {
                                                m_AlarmList.Add(ydata);
                                            }
                                            lock (m_AlarmShowLock)
                                            {
                                                m_AlarmListShow.Add(ydata);
                                            }

                                        }
                                    }

                                    break;
                                case "CNT":
                                    BordDll.GetCNTData((uint)info.ChannelNumber, ref flVolt, ref dfDuty);
                                        YBData ydataCNT = new YBData();
                                        ydataCNT.ChannID = info.ChannelNumber;
                                        ydataCNT.ChannType = ChannelType;
                                        ydataCNT.DTTime = EclipsTime;
                                        ydataCNT.flVot = flVolt;
                                        ydataCNT.YBName = info.YBNumber.ToString();
                                        ydataCNT.GNFunction = info.FunctionName;

                                        int returnValueCNT = JudageAlarmData(EclipsTime, info.YBNumber, info.FunctionName, flVolt);
                                        ydataCNT.DataInfo = returnValueCNT;
                                        InsertDataToList(ydataCNT);
                                        if (returnValueCNT == 0)
                                        {
                                            lock (m_diskLock)
                                            {
                                                m_YBDataList.Add(ydataCNT);
                                            }
                                        }
                                        else
                                        {
                                            lock (m_AlarmDiskLock)
                                            {
                                                m_AlarmList.Add(ydataCNT);
                                            }
                                            lock (m_AlarmShowLock)
                                            {
                                                m_AlarmListShow.Add(ydataCNT);
                                            }

                                        }
                                    break;
                            }
                            
                        }

                        
                        
                    }
                }

            }
            catch (System.Exception ex)
            {
            	
            }
        }
        private List<YBData> m_AlarmList = new List<YBData>();
        private List<YBData> m_AlarmListShow = new List<YBData>();
        private int JudageAlarmData(int EclipsTime,int YBNumber,string GNFucntion,double flVolt)
        {
            try
            {
                //获取当前时间段对应的数据，如果数据在范围内，为正常数据，范围外，判断是否在上下限值如果超出判定为报警值，如果报警时间，在报警时间误差范围内，不做报警
                YBAlarmSet ybAlarm = ProDefine.g_YBAlarm.Where(m =>m.GNFcontion == GNFucntion).SingleOrDefault();
                YBSingleSetInput YBs = ProDefine.g_YBSetSignle.Where(m => m.GNFunction == GNFucntion).SingleOrDefault();

                if ((YBs != null) &&(ybAlarm != null))
                {
                    double lowValue = 0;
                    double HightValue = 0;
                    //if (YBs.SetType == 0)
                    {
                        lowValue = HightValue = YBs.m_ValueList[0];
                        if (flVolt > (Convert.ToDouble(ybAlarm.AlarmH) + Convert.ToDouble(ybAlarm.AlarmDataAbs)))
                        {
                            return 1;//超高报警
                        }
                        else if (flVolt < (Convert.ToDouble(ybAlarm.AlarmL) - Convert.ToDouble(ybAlarm.AlarmDataAbs)))
                        {
                            return 2;//超低报警
                        }
                        else{
                            return 0;
                        }
                    }
                    
                }
                //if (ybAlarm == null)
                {
                    if (YBs.SetType == 0)//恒定信号
                    {
                        if (flVolt != YBs.m_ValueList[0])
                        {
                            return 4;
                        }
                        else
                        {
                            return 0;
                        }
                    }
                    else if ((YBs.SetType == 1) ||(YBs.SetType == 2))//循环信号 变化信号
                    {
                        int SumTimeValue = 0;
                        /*取得对应时间对应的值范围*/
                        for (int i = 0; i < YBs.m_TimeList.Count; i++ )
                        {
                            if (YBs.m_TimeList[i] == -1)
                            {
                                break;
                            }
                            SumTimeValue = YBs.m_TimeList[i];
                        }
                        int Posi = EclipsTime % SumTimeValue;
                        SumTimeValue = 0;
                        int Kindex = 0;
                        for (Kindex= 0; Kindex < YBs.m_TimeList.Count; Kindex++)
                        {
                            SumTimeValue = YBs.m_TimeList[Kindex];
                            if (Posi <= SumTimeValue)
                            {
                                break;
                            }
                        }
                        double dValue1 = YBs.m_ValueList[Kindex - 1];
                        double dValue2 = YBs.m_ValueList[Kindex];

                        if ((flVolt >= Math.Min(dValue1,dValue2)) &&(flVolt <= Math.Max(dValue1,dValue2)))
                        {
                            return 0;
                        }
                        else
                        {
                            return 4;
                        }
                    }
                }

                return 0;
            }
            catch (System.Exception ex)
            {
                return -1;
            }
        }

        private List<YBData> m_YBDataList = new List<YBData>();
        private object m_AlarmDiskLock = new object();
        private object m_AlarmShowLock = new object();
        private int WriteSizeCount = 2000;
        private void WriteDataToDisk()
        {
            try
            {
                lock (m_diskLock)
                {
                    if (m_YBDataList.Count >= WriteSizeCount)
                    {
                        int newSize = Marshal.SizeOf(m_YBDataList[0]) * m_YBDataList.Count;
                        m_MemeryFile.CreateWriteMemoryMapFile(m_dataPath, newSize);
                        m_MemeryFile.WriteToMemFile(m_YBDataList);
                        m_MemeryFile.DisposeMemoryMapFile();
                        m_YBDataList.Clear();
                    }

                }
                lock (m_AlarmDiskLock)
                {
                    if (m_AlarmList.Count >= WriteSizeCount)
                    {
                        int newSize = Marshal.SizeOf(m_AlarmList[0]) * m_AlarmList.Count;
                        m_MemeryFile.CreateWriteMemoryMapFile(m_AlarmDataPath, newSize);
                        m_MemeryFile.WriteToMemFile(m_AlarmList);
                        m_MemeryFile.DisposeMemoryMapFile();
                        m_AlarmList.Clear();
                    }
                }
                 
            }
            catch (System.Exception ex)
            {
            	
            }
        }

        

        private void DoReadData()
        {
            while (!m_IsExpermentEnd)
            {
                int EclipsTime = GetEcliptsTime();
                int NowTotalTime = GetNowStepExpermentTime();
                if (EclipsTime <= NowTotalTime)
                {
                }
                else
                {
                    m_lastExpermentStep = m_ExpermentStep;
                    m_ExpermentStep++;
                }
                ReadData(EclipsTime);

                Thread.Sleep(1);
            }
        }

        private void DoWriteData()
        {
            while (!m_IsExpermentEnd)
            {
                int EclipsTime = GetEcliptsTime();
                WriteData(EclipsTime);

                Thread.Sleep(1);
            }
        }

        private void WriteData(int eclipstime)
        {
            try
            {
                List<FucntionChannelInfo> chList = GetStepChannelList();
                
                foreach (var info in chList)
                {
                    string ChannelType = GetNowChannelType(info.FunctionName);
                    //foreach (var info_i in info)
                    {
                        if (ChannelType == "AO")
                        {
                            double WriteValue = GetWriteValue(eclipstime, info.YBNumber, info.FunctionName, info.ChannelNumber, ChannelType);
                            BordDll.WriteAOData((uint)info.ChannelNumber,WriteValue);
                        }
                        else if (ChannelType == "DO")
                        {
                            double WriteValue = GetWriteValue(eclipstime, info.YBNumber, info.FunctionName, info.ChannelNumber, ChannelType);


                            if ((WriteValue != 0) || (WriteValue != 1))
                            {
                                WriteValue = 0;
                            }

                            byte tpByte = 0;
                            tpByte = (byte)WriteValue;
                            BordDll.WriteDOData((uint)info.ChannelNumber, tpByte);
                            //BordDll.WriteDOData_1();
                        }
                        
                    }
                }

            }
            catch (System.Exception ex)
            {
            	
            
            }
           
        }

        private double GetWriteValue(int EclipsTime, int YBNumber,string GNFunction,int ChannelID,string channelType)
        {
            try
            {
                YBSingleSetInput YBs = ProDefine.g_YBSetSignleOut.Where(m => m.GNFunction == GNFunction).SingleOrDefault();
                if (YBs != null)
                {
                    if (YBs.SetType == 0)
                    {
                        double flVolt = YBs.m_ValueList[0];
                        return flVolt;
                    }
                    else if ((YBs.SetType == 1) || (YBs.SetType == 2))
                    {
                        int SumTimeValue = 0;
                        for (int i = 0; i < YBs.m_TimeList.Count; i++)
                        {
                            if (YBs.m_TimeList[i] == -1)
                            {
                                break;
                            }
                            SumTimeValue = YBs.m_TimeList[i];
                        }
                        int Posi = EclipsTime % SumTimeValue;
                        SumTimeValue = 0;
                        int Kindex = 0;
                        for (Kindex = 0; Kindex < YBs.m_TimeList.Count; Kindex++)
                        {
                            SumTimeValue = YBs.m_TimeList[Kindex];
                            if (Posi <= SumTimeValue)
                            {
                                break;
                            }
                        }
                        double dValue1 = YBs.m_ValueList[Kindex - 1];
                        double dValue2 = YBs.m_ValueList[Kindex];
                        return dValue1;
                    }
                }
                return -1;
            }
            catch (System.Exception ex)
            {
                return -1;
            }
        } 


        private string m_dataPath = "";
        private string m_AlarmDataPath = "";
        private void lbStart_Click(object sender, EventArgs e)
        {
            this.lbStart.Enabled = false;
            this.lbEnd.Enabled = true;
            m_IsExpermentEnd = false;
            m_StartTime = DateTime.Now;
            this.line1.Clear();
            GetTotalExpTime();
            this.line1.GetHorizAxis.SetMinMax(DateTime.Now, DateTime.Now.AddSeconds(120));
            m_dataPath = ProDefine.g_MyProject.ProjectName + "_" + DateTime.Now.ToString("yyyymmddhhmmss") + ".data";
            m_AlarmDataPath = ProDefine.g_MyProject.ProjectName + "_" + DateTime.Now.ToString("yyyymmddhhmmss") + ".Alarmdata";
            if (m_WriteThread != null)
            {
                m_WriteThread.Start();
            }
            if (m_ReadThread != null)
            {
                m_ReadThread.Start();
            }
            timer1.Enabled = true;
            timer2.Enabled = true;
            timer3.Enabled = true;
            timer4.Enabled = true;
            
        }

        private void lbStart_MouseEnter(object sender, EventArgs e)
        {
            this.lbStart.ForeColor = Color.Blue;
        }

        private void lbStart_MouseLeave(object sender, EventArgs e)
        {
            this.lbStart.ForeColor = Color.White;
        }

        private void lbEnd_Click(object sender, EventArgs e)
        {
            this.lbEnd.Enabled = false ;
            this.lbStart.Enabled = true;
            m_IsExpermentEnd = true;
            try
            {
                if (m_WriteThread != null)
                {
                    m_WriteThread.Abort();
                }
                
            }
            catch (System.Exception ex)
            {
            	
            }
            try
            {
                if (m_ReadThread != null)
                {
                    m_ReadThread.Abort();
                }
            }
            catch (System.Exception ex)
            {
            	
            }
            timer3.Enabled = false;
            timer4.Enabled = false;
            timer1.Enabled = false;
            timer2.Enabled = false;
            
        }

        private void lbEnd_MouseEnter(object sender, EventArgs e)
        {
            this.lbEnd.ForeColor = Color.Blue;
        }

        private void lbEnd_MouseLeave(object sender, EventArgs e)
        {
            this.lbEnd.ForeColor = Color.White;
        }

        private void GetDisntTimeList() {
            try {
                //方案1
                //1.  获取读取的数据频率，多久读取一次
                //2.  根据获取的个数启动多个线程，读取数据

                //方案2. 
                //分别用两线程表示读取和写入，根据起始时间计时来确定应该何时读取数据
                //
                //ProDefine.g_YBSetSignle.Distinct()
            }
            catch { 
            }
        }
        private List<SimpleButton> m_ButtonList = new List<SimpleButton>();
        private void DoUIInit() {
            try {
                this.ddbYBSelect.DropDownControl = CreateDXPopupMenu();
                m_ButtonList.Add(this.simpleButton01); m_ButtonList.Add(this.simpleButton02);
                m_ButtonList.Add(this.simpleButton03); m_ButtonList.Add(this.simpleButton04);
                m_ButtonList.Add(this.simpleButton05); m_ButtonList.Add(this.simpleButton06);
                m_ButtonList.Add(this.simpleButton07); m_ButtonList.Add(this.simpleButton08);
                m_ButtonList.Add(this.simpleButton09); m_ButtonList.Add(this.simpleButton10);
                foreach (var info in m_ButtonList) {
                    info.Visible = false;
                }
                int Rindex = 0;
                foreach (var info in ProDefine.g_ChannelInfos)
                {
                    if ((info.FunctionType == "AI") || (info.FunctionType == "CNT"))
                    {
                        m_ButtonList[Rindex].Text = info.FucntionName;
                        m_ButtonList[Rindex].Visible = true;
                    }
                }
            }
            catch { }
        }

        private DXPopupMenu CreateDXPopupMenu()
        {
            DXPopupMenu menu = new DXPopupMenu();
            for (int info = 1; info <= Convert.ToInt32(ProDefine.g_SMExpermentParam.YBNumber);info++ )
            {
                menu.Items.Add(new DXMenuItem("样本" + info.ToString(), OnItemClick));
            }
            return menu;
        }
        private List<YBSetuse> m_NowSelecedChannelList = new List<YBSetuse>();
        private void OnItemClick(object sender, EventArgs e)
        {
            DXMenuItem item = sender as DXMenuItem;
            string YBName = item.Caption;

         
            
            int iindex = 1;
            
            m_NowYB = item.Caption;
            m_NowGNFunction = this.m_ButtonList[0].Text;
            this.tChart2.Header.Text = m_NowYB + "--" + m_NowGNFunction;
            ChannelInfos yb = ProDefine.g_ChannelInfos.Where(m => m.FucntionName == m_NowGNFunction).SingleOrDefault();

            FucntionChannelInfo fc = ProDefine.g_FunctionChannel.Where(m => m.FunctionName == m_NowGNFunction && m.YBNumber == Convert.ToInt32(m_NowYB.Substring(2,m_NowYB.Length - 2))).SingleOrDefault();

            m_NowChannel = fc.ChannelNumber;
            m_NowChannleType = yb.FunctionType;
            this.line1.Clear();
            
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            WriteDataToDisk();
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            SetData();
        }

        private delegate void SetDataDelegate();
        private void SetData()
        {
            if (this.InvokeRequired)
            {
                this.Invoke(new SetDataDelegate(SetData));
            }
            else
            {
                int Hour = (DateTime.Now - m_StartTime).Hours;
                int min = (DateTime.Now - m_StartTime).Minutes;
                int Sec = (DateTime.Now - m_StartTime).Seconds;
                lbHour.Text = Hour.ToString();
                lbMin.Text = min.ToString();
                lbSec.Text = Sec.ToString();
                if (Hour == m_TotalTime)
                {
                    m_IsExpermentEnd = true;
                    timer1.Enabled = false;
                    timer2.Enabled = false;
                    timer3.Enabled = false;
                    timer4.Enabled = false;
                    lbStart.Enabled = true;
                    lbEnd.Enabled = false;
                    
                }
                
            }
        }
        private string m_NowGNFunction = "";
        private string m_NowYB = "";
        private void AnimateSeries(Steema.TeeChart.TChart chart,YBData ydata)
        {
           
            double newX, newY;

            chart.AutoRepaint = false;

            /// <summary>
            /// 绘画坐标点超过100个时将实时更新X时间坐标
            /// </summary>
            while (this.line1.Count > 100)
            {
                this.line1.Delete(0);
                line1.GetHorizAxis.SetMinMax(DateTime.Now.AddSeconds(-50), DateTime.Now.AddSeconds(60));
            }

            newX = DateTime.Now.ToOADate();
            if (ydata.flVot == null)
            {
                newY = 0;
            }
            else
            {
                newY = (double)ydata.flVot;
            }
            
            line1.Add(newX, newY);

            chart.AutoRepaint = true;
            chart.Refresh();
        }

        private void timer3_Tick(object sender, EventArgs e)
        {
            lock (m_lock)
            {
                YBData ydata = m_DataList.Where(m => m.ChannType == m_NowChannleType && m.ChannID == m_NowChannel).SingleOrDefault();
                AnimateSeries(tChart2, ydata);
            }
            
        }
        private string m_LastYB = "";
        private string m_LastGnFunction = "";
        private int m_NowChannel = -1;
        private string m_NowChannleType = "";
        private void GNFunctionSelect(Object o, EventArgs e)
        {
            SimpleButton spb = (SimpleButton)o;
            this.line1.GetHorizAxis.SetMinMax(DateTime.Now, DateTime.Now.AddSeconds(120));
            m_NowGNFunction = spb.Text;
            this.line1.Clear();
            this.tChart2.Header.Text = m_NowYB + "---" + m_NowGNFunction;
            GetNowSelectYBInfo();
        }

        private void GetNowSelectYBInfo()
        {
            try
            {
                ChannelInfos yb = ProDefine.g_ChannelInfos.Where(m => m.FucntionName == m_NowGNFunction).SingleOrDefault();

                FucntionChannelInfo fc = ProDefine.g_FunctionChannel.Where(m => m.FunctionName == m_NowGNFunction && m.YBNumber == Convert.ToInt32(m_NowYB.Substring(2, m_NowYB.Length - 2))).SingleOrDefault();

                m_NowChannel = fc.ChannelNumber;
                m_NowChannleType = yb.FunctionType;
            }
            catch (System.Exception ex)
            {
            	
            }
        }

        private void timer4_Tick(object sender, EventArgs e)
        {
            SetDataAlarm();
        }

        private delegate void SetDataAlarmDelegate();
        private void SetDataAlarm()
        {
            if (this.InvokeRequired)
            {
                this.Invoke(new SetDataAlarmDelegate(SetDataAlarm));
            }
            else
            {
                lock (m_AlarmShowLock)
                {
                    if (m_AlarmList.Count > 0)
                    {
                        foreach (var info in m_AlarmListShow)
                        {
                            listBox1.Items.Add(info.YBName + "--" + info.GNFunction + "--报警值：" + info.flVot + "--报警信息：" + info.DataInfo + "--报警时间：" + info.DTTime);
                        }
                    }
                }
               
            }
        }

        private void frmExperment_FormClosed(object sender, FormClosedEventArgs e)
        {
            try
            {
                if (this.m_ReadThread != null)
                {
                    m_ReadThread.Abort();
                }
            }
            catch (System.Exception ex)
            {
                m_ReadThread = null;
            }
            try
            {
                if (this.m_WriteThread != null)
                {
                    m_WriteThread.Abort();
                }
            }
            catch (System.Exception ex)
            {
                m_WriteThread = null;
            }
            if (m_MemeryFile!= null)
            {
                m_MemeryFile.DisposeMemoryMapFile();
                m_MemeryFile = null;
            }
             

            if (m_AlarmList != null)
            {
                m_AlarmList.Clear();
                m_AlarmList = null;
            }
            if (m_DataList != null)
            {
                m_DataList.Clear();
                m_DataList = null;
            }

        }
    }
}
