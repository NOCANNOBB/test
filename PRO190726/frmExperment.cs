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
            if (!InitBords())
            {
                MessageBox.Show("设备初始化失败");
            }
        }

        private int m_ExpermentStep = 0;

        private int GetNowStepExpermentTime()//获取当前步骤实验总时间
        {
            int NowTotalTime = 0;
            for (int i = 0; i <= m_ExpermentStep; i++ )
            {
                NowTotalTime += ProDefine.g_SMExpermentDesin.ExpParamList[i].ExpermentTime * 60 * 60 * 1000;
            }
            return NowTotalTime;
        }

        private List<YBChannelInfo> GetStepChannelList()//获取当前步骤通道
        {
            List<YBChannelInfo> returnList = new List<YBChannelInfo>();

            int YBStart = GetNowStepYBStart();
            int YBEnd = GetNowStepYBEnd();

            for (int i = YBStart; i <= YBEnd; i++)
            {
                returnList.Add(ProDefine.g_YBsetting.Where(m => m.YBName == ("样本" + i.ToString())).SingleOrDefault());
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
                BordDll.StartChannel((ulong)info.channelNumber);
            }
            return true;
        }


        private int GetChannelHz(int ChannelID,string ChannelType)
        {
            int Hz = 0;
            ChannelSetInfo cs = ProDefine.g_ChannelInfo.Where(m => m.channelNumber == ChannelID && m.ChannelType == ChannelType).SingleOrDefault();
            if (cs != null)
            {
                Hz = cs.hzZQ / cs.PerReadNumber;
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
            if (m_DataList.Count == 1024)
            {
                m_DataList.RemoveAt(0);
            }
            lock (m_lock)
            {
                m_DataList.Add(ydata);
            }
            
        }

        private void ReadData(int EclipsTime)
        {
            try
            {
                List<YBChannelInfo> chList = GetStepChannelList();

                foreach (var info in chList)
                {
                    foreach (var info_i in info.YBList)
                    {
                        int Hz = GetChannelHz(info_i.ChannelID,info_i.ChannelType);
                        double flVolt = 0;
                        double dfFreq =0;
                        double dfDuty = 0;
                        if ((EclipsTime % Hz) == 0)
                        {
                            switch (info_i.ChannelType)
                            {
                                case "AI":
                                    BordDll.GetAIDataFromBord((ulong)info_i.ChannelID, ref flVolt);
                                    break;
                                case "CNT":
                                    BordDll.GetCNTData((ulong)info_i.ChannelID, ref flVolt, ref dfDuty);
                                    break;
                            }
                        }

                        YBData ydata = new YBData();
                        ydata.ChannID = info_i.ChannelID;
                        ydata.ChannType = info_i.ChannelType;
                        ydata.DTTime = EclipsTime;
                        ydata.flVot = flVolt;
                        ydata.YBName = info.YBName;
                        ydata.GNFunction = info_i.GNFunction;
                        
                        int returnValue = JudageAlarmData(EclipsTime,info.YBName,info_i.GNFunction,flVolt);
                        ydata.DataInfo = returnValue;
                        InsertDataToList(ydata);
                        if ( returnValue == 0)
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
                            
                        }
                        
                    }
                }

            }
            catch (System.Exception ex)
            {
            	
            }
        }
        private List<YBData> m_AlarmList = new List<YBData>();
        private int JudageAlarmData(int EclipsTime,string YBName,string GNFucntion,double flVolt)
        {
            try
            {
                //获取当前时间段对应的数据，如果数据在范围内，为正常数据，范围外，判断是否在上下限值如果超出判定为报警值，如果报警时间，在报警时间误差范围内，不做报警
                YBAlarmSet ybAlarm = ProDefine.g_YBAlarm.Where(m => m.m_YBList.Contains(YBName) == true && m.GNFcontion == GNFucntion).SingleOrDefault();
                YBSingleSetInput YBs = ProDefine.g_YBSetSignle.Where(m => m.m_YBList.Contains(YBName) == true && m.GNFunction == GNFucntion).SingleOrDefault();

                if ((YBs != null) &&(ybAlarm != null))
                {
                    double lowValue = 0;
                    double HightValue = 0;
                    //if (YBs.SetType == 0)
                    {
                        lowValue = HightValue = YBs.m_ValueList[0];
                        if (flVolt > (Convert.ToDouble(ybAlarm.AlarmH) + Convert.ToDouble(ybAlarm.AlarmAbs)))
                        {
                            return 1;
                        }
                        else if (flVolt < (Convert.ToDouble(ybAlarm.AlarmL) - Convert.ToDouble(ybAlarm.AlarmAbs)))
                        {
                            return 2;
                        }
                        else{
                            return 0;
                        }
                    }
                    
                }
                if (ybAlarm == null)
                {
                    if (YBs.SetType == 0)
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
                    else if ((YBs.SetType == 1) ||(YBs.SetType == 2))
                    {
                        int SumTimeValue = 0;
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
                 List<YBChannelInfo> chList = GetStepChannelList();

                foreach (var info in chList)
                {
                    foreach (var info_i in info.YBList)
                    {
                        if (info_i.ChannelType == "AO")
                        {
                            double WriteValue = GetWriteValue(eclipstime, info.YBName, info_i.GNFunction,info_i.ChannelID, info_i.ChannelType);
                            BordDll.WriteAOData((ulong)info_i.ChannelID,ref WriteValue);
                        }
                        else if (info_i.ChannelType == "DO")
                        {

                            //BordDll.WriteDOData_1();
                        }
                        
                    }
                }

            }
            catch (System.Exception ex)
            {
            	
            
            }
           
        }

        private double GetWriteValue(int EclipsTime, string YbName,string GNFunction,int ChannelID,string channelType)
        {
            try
            {
                YBSingleSetInput YBs = ProDefine.g_YBSetSignleOut.Where(m => m.m_YBList.Contains(YbName) == true && m.GNFunction == GNFunction).SingleOrDefault();
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
            GetTotalExpTime();
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

        private void OnItemClick(object sender, EventArgs e)
        {
            DXMenuItem item = sender as DXMenuItem;
            string YBName = item.Caption;

            YBChannelInfo ybc = ProDefine.g_YBsetting.Where(m => m.YBName == YBName).SingleOrDefault();

            int tCount = ybc.YBList.Count;
            int iindex = 1;
            foreach (var info in this.m_ButtonList) {
                if (iindex <= tCount)
                {
                    this.m_ButtonList[iindex - 1].Visible = true;
                    this.m_ButtonList[iindex - 1].Text = ybc.YBList[iindex - 1].GNFunction;
                }
                else {
                    this.m_ButtonList[iindex - 1].Visible = false;
                }
                iindex++;
            }
            
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
                    lbStart.Enabled = true;
                    lbEnd.Enabled = false;
                    
                }
                
            }
        }
    }
}
