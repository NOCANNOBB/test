using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using Define;
using DLLAccess;
using DLLStruct;
using XMLHelper;

namespace DLLProjectInfo
{
    public class DoProjectInfo
    {
        public static string ProjectInfoDBName = "ProjectConfig";
        public static string ExperParmaDBName = "ExpermentParam";
        public static string ExperDesignDBName = "ExpermentDesign";
        public static string ChannelSetDBName = "ChannelInfo";
        public static string YBChannelInfo = "YBChannelInfo";
        public static string YBSetSignle = "YBSetSignle";
        public static string YBSetOutSignle = "YBSetOutSignle";
        public static string YBSetAlarm = "YBSetAlarm";
        public int SaveProjectInfo(ProjectInfo pro) {

            try {

                if (IsProjectExist(pro.ProjectName)) {
                    return -1;//表存在
                }
                CreateProjectInfoFile(pro);
                Dictionary<string, Object> mydata = new Dictionary<string, object>();
                mydata.Add("ProjectName", pro.ProjectName);
                mydata.Add("GUIDSTR", pro.GUID.ToString());
                mydata.Add("ProductName", pro.ProductName);
                mydata.Add("ProductGN", pro.ProductGN);

                mydata.Add("ProductUse", pro.ProductUse);
                mydata.Add("ExperTime", pro.ExperTime);
                mydata.Add("ExperAddress", pro.ExperAddress);
                mydata.Add("ProjectPath", pro.ProjectPath);

                if (AccessHelper.AppendData2Access(mydata, ProjectInfoDBName))
                {
                    return 0;
                }
                else {
                    return -2;
                }
                return 0;

            }
            catch {
                return -2;
            }
            //return XMLHelpers.InsertaNode("ProjectConfig.xml", "ProjectInfo", "ProjectName", ProjectName, "GUID", guid.ToString());
            
        }


        public bool ChangeProjectInfo(ProjectInfo pro) {
            try {
                string SQL = "update " + ProjectInfoDBName + " set ProjectName='" + pro.ProjectName + "',ProductName='" + pro.ProductName + "',ProductGN='" + pro.ProductGN + "',ProductUse='"
                    + pro.ProductUse + "',ExperTime='" + pro.ExperTime + "',ExperAddress='" + pro.ExperAddress + "' where GUIDSTR='" + pro.GUID.ToString() + "'";
                if (AccessHelper.ExcuteSql(SQL) > 0) {
                    return true;
                }
                return false;
            }
            catch {
                return true;
            }
        }

        public void CreateProjectInfoFile(ProjectInfo pro)
        {
            try {
                XMLHelpers.CreateProjectInfo(pro);
            }
            catch { }
        }


        private bool IsProjectExist(string ProName) {
            try {
                string SQL = "select * from " + ProjectInfoDBName + " where ProjectName='" + ProName + "'";
                DataTable dt = AccessHelper.GetDataTableFromDB(SQL);
                if (dt != null)
                {
                    if (dt.Rows.Count > 0)
                    {
                        return true;
                    }
                    else {
                        return false;
                    }
                }
                else {
                    return false;
                }

                return true;
            }
            catch {
                return false;
            }
        }

        public int AddProjectInfo(ProjectInfo pro)
        {
            try
            {

                if (IsProjectExist(pro.ProjectName))
                {
                    return -1;//表存在
                }
                //CreateProjectInfoFile(pro);
                Dictionary<string, Object> mydata = new Dictionary<string, object>();
                mydata.Add("ProjectName", pro.ProjectName);
                mydata.Add("GUIDSTR", pro.GUID.ToString());
                mydata.Add("ProductName", pro.ProductName);
                mydata.Add("ProductGN", pro.ProductGN);

                mydata.Add("ProductUse", pro.ProductUse);
                mydata.Add("ExperTime", pro.ExperTime);
                mydata.Add("ExperAddress", pro.ExperAddress);
                mydata.Add("ProjectPath", pro.ProjectPath);

                if (AccessHelper.AppendData2Access(mydata, ProjectInfoDBName))
                {
                    return 0;
                }
                else
                {
                    return -2;
                }
                return 0;

            }
            catch
            {
                return -2;
            }
        }


        public ProjectInfo GetProjectInfo(string ProjectPath) {
            try {
                ProjectInfo pro = new ProjectInfo();
                string ProductName = XMLHelpers.ReadProNodeValue(ProjectPath, "Project", "ProductName");
                string Guidstr = XMLHelpers.ReadProNodeValue(ProjectPath, "Project", "GUID");
                string ProductGN = XMLHelpers.ReadProNodeValue(ProjectPath, "Project", "ProductGN");
                string ProjectName = XMLHelpers.ReadProNodeValue(ProjectPath, "Project", "ProjectName");
                string ProductUse = XMLHelpers.ReadProNodeValue(ProjectPath, "Project", "ProductUse");
                string ExperAddress = XMLHelpers.ReadProNodeValue(ProjectPath, "Project", "ExperAddress");
                string ExperTime = XMLHelpers.ReadProNodeValue(ProjectPath, "Project", "ExperTime");

                pro.ProductName = ProductName;
                pro.ProductGN = ProductGN;
                pro.GUID = Guid.Parse(Guidstr);
                pro.ProductUse = ProductUse;
                pro.ProjectName = ProjectName;
                pro.ProjectPath = ProjectPath;
                pro.ExperAddress = ExperAddress;
                pro.ExperTime = ExperTime;

                return pro;
            }
            catch {
                return null;
            }
        }



        public List<ProjectInfo> GetProjectInfos() {

            try {

                List<ProjectInfo> ProList = new List<ProjectInfo>();

                string SQL = "select * from " + ProjectInfoDBName + "";

                DataTable dt = AccessHelper.GetDataTableFromDB(SQL);

                if (dt != null) {
                    for (int i = 0; i < dt.Rows.Count; i++) {
                        ProjectInfo pro = new ProjectInfo();
                        pro.ProjectName = dt.Rows[i][0].ToString();
                        pro.GUID = Guid.Parse(dt.Rows[i][1].ToString());
                        pro.ProductName = dt.Rows[i][2].ToString();
                        pro.ProductGN = dt.Rows[i][3].ToString();
                        pro.ProductUse = dt.Rows[i][4].ToString();
                        pro.ExperTime = dt.Rows[i][5].ToString();
                        pro.ExperAddress = dt.Rows[i][6].ToString();
                        pro.ProjectPath = dt.Rows[i][7].ToString();
                        ProList.Add(pro);
                    }
                }
               
                return ProList;
            
            }
            catch {
                return null;
            }
        
            
        }

        public void DelProFromList(ProjectInfo pro) {
            try {
                string SQL = "delete from " + ProjectInfoDBName + " where ProjectName='" + pro.ProjectName + "'";

                AccessHelper.ExcuteSql(SQL);
                
            }
            catch { 
            
            }
        }

        public void SaveExpermentInfo(SMExpermentParam experParam) {
            try {
                string SQL = "select * from " + ExperParmaDBName + " where GUIDSTR = '" + experParam.GUID.ToString() + "'";
                DataTable dt = AccessHelper.GetDataTableFromDB(SQL);

                if (dt != null) {
                    if (dt.Rows.Count > 0)
                    {
                        SQL = "delete from " + ExperParmaDBName + " where GUIDSTR='" + ProDefine.g_SMExpermentParam.GUID.ToString() + "'";
                        AccessHelper.ExcuteSql(SQL);

                        //SQL = "update " + ExperParmaDBName + " set GUIDSTR='" + experParam.GUID.ToString() + "',ExpermentType='" + experParam.ExpermentType + "',YLType='" + experParam.YLType.ToString() + "',JSMode='"
                        //    + experParam.JSMode.ToString() + "',YLSetType='" + experParam.YLSetType.ToString() + "',CGTemperature='"+ experParam.CGTemperature + "',CGXDSD='" + experParam.CGXDSD + "',CPJXTemperature='" + experParam.CPJXTemperature + "',CPJXXDSD='" + experParam.CPJXXDSD
                        //    + "',YLNumber='" + experParam.YLNumber + "',YBNumber='" + experParam.YBNumber + "',JWType='" + experParam.JWType + "',CGZD='" + experParam.CGZD + "',CGDYL='" + experParam.CGDYL + "',JXZD='" + experParam.JXZD + "',JXDYL='" + experParam.JXDYL + "' where GUIDSTR='" + experParam.GUID.ToString() + "'";
                    }
                    
                        SQL = "insert into " + ExperParmaDBName + " values('" + experParam.GUID.ToString() + "','" + experParam.ExpermentType + "','" + experParam.YLType.ToString() + "','"
                            + experParam.JSMode.ToString() + "','" + experParam.YLSetType.ToString() + "','" + experParam.CGTemperature + "','" + experParam.CGXDSD + "','" + experParam.CPJXTemperature + "','" + experParam.CPJXXDSD
                            + "','" + experParam.YLNumber + "','" + experParam.YBNumber + "','" + experParam.JWType + "','" + experParam.CGZD + "','" + experParam.CGDYL + "','" + experParam.JXZD + "','" + experParam.JXDYL + "')";
                    

                    AccessHelper.ExcuteSql(SQL);
                }
            }
            catch { }
        }


        public void GetExpermentInfo(string GUIDSTR) {
            try
            {

                string SQL = "select * from " + ExperParmaDBName + " where GUIDSTR = '" + GUIDSTR + "'";

                DataTable dt = AccessHelper.GetDataTableFromDB(SQL);
                if (dt != null) {
                    if (dt.Rows.Count > 0) {
                        ProDefine.g_SMExpermentParam.GUID = Guid.Parse(dt.Rows[0][0].ToString());
                        ProDefine.g_SMExpermentParam.ExpermentType = Convert.ToInt32(dt.Rows[0][1].ToString());
                        ProDefine.g_SMExpermentParam.YLType = Convert.ToInt32(dt.Rows[0][2].ToString()); ;
                        ProDefine.g_SMExpermentParam.JSMode = Convert.ToInt32(dt.Rows[0][3].ToString()); ;
                        ProDefine.g_SMExpermentParam.YLSetType = Convert.ToInt32(dt.Rows[0][4].ToString());
                        ProDefine.g_SMExpermentParam.CGTemperature = dt.Rows[0][5].ToString();
                        ProDefine.g_SMExpermentParam.CGXDSD = dt.Rows[0][6].ToString();
                        ProDefine.g_SMExpermentParam.CPJXTemperature = dt.Rows[0][7].ToString();
                        ProDefine.g_SMExpermentParam.CPJXXDSD = dt.Rows[0][8].ToString();
                        ProDefine.g_SMExpermentParam.JWType = Convert.ToInt32(dt.Rows[0][11].ToString());
                        ProDefine.g_SMExpermentParam.YBNumber = dt.Rows[0][10].ToString();
                        ProDefine.g_SMExpermentParam.YLNumber = dt.Rows[0][9].ToString();

                        ProDefine.g_SMExpermentParam.CGZD = dt.Rows[0][12].ToString();
                        ProDefine.g_SMExpermentParam.CGDYL = dt.Rows[0][13].ToString();
                        ProDefine.g_SMExpermentParam.JXZD = dt.Rows[0][14].ToString();
                        ProDefine.g_SMExpermentParam.JXDYL = dt.Rows[0][15].ToString();
                        //ProDefine.g_SMExpermentParam.GUID = ProDefine.g_MyProject.GUID;
                    }
                }
                SQL = "select * from " + ExperDesignDBName + " where GUIDSTR ='" + GUIDSTR + "'";
                DataTable dt1 = AccessHelper.GetDataTableFromDB(SQL);
                ProDefine.g_SMExpermentDesin.ExpParamList.Clear();
                if (dt1 != null)
                {
                    if (dt1.Rows.Count > 0)
                    {
                        int RowsCount = dt1.Rows.Count;
                        for (int i = 0; i < RowsCount; i++)
                        {
                            SMExpeDesignParam ExperDesign = new SMExpeDesignParam();
                            ExperDesign.ExpermentTime = Convert.ToInt32(dt1.Rows[i][4].ToString());
                            ExperDesign.SD = Convert.ToDouble(dt1.Rows[i][2].ToString());
                            ExperDesign.Temperature = Convert.ToDouble(dt1.Rows[i][1].ToString());
                            ExperDesign.YBNumber = Convert.ToInt32(dt1.Rows[i][3].ToString());
                            ProDefine.g_SMExpermentDesin.ExpParamList.Add(ExperDesign);
                        }

                    }
                }
            }
            catch { }
        }


        public void SaveExpermentDesign() {
            try {
                string SQL = "select * from " + ExperDesignDBName + " where GUIDSTR='" + ProDefine.g_SMExpermentParam.GUID.ToString() + "'" ;

                DataTable dt = AccessHelper.GetDataTableFromDB(SQL);

                if (dt != null) {
                    if (dt.Rows.Count > 0)
                    {
                        SQL = "delete from " + ExperDesignDBName + " where GUIDSTR='" + ProDefine.g_SMExpermentParam.GUID.ToString() + "'";
                        AccessHelper.ExcuteSql(SQL);
                        
                    }
                    foreach (var info in ProDefine.g_SMExpermentDesin.ExpParamList) {
                        SQL = "insert into " + ExperDesignDBName + " Values('" + ProDefine.g_SMExpermentParam.GUID.ToString() + "','" + info.Temperature + "','" + info.SD + "','"
                            + info.YBNumber + "','" + info.ExpermentTime + "')";
                        AccessHelper.ExcuteSql(SQL);

                    }
                }
            }
            catch { }
        }


        public void SaveChannelSetInfo()
        {
            try
            {
                string SQL = "select * from " + ChannelSetDBName + " where GUIDSTR='" + ProDefine.g_SMExpermentParam.GUID.ToString() + "'";

                DataTable dt = AccessHelper.GetDataTableFromDB(SQL);

                if (dt != null)
                {
                    if (dt.Rows.Count > 0)
                    {
                        SQL = "delete from " + ChannelSetDBName + " where GUIDSTR='" + ProDefine.g_SMExpermentParam.GUID.ToString() + "'";
                        AccessHelper.ExcuteSql(SQL);

                    }
                    foreach (var info in ProDefine.g_ChannelInfos)
                    {
                        SQL = "insert into " + ChannelSetDBName + " Values('" + ProDefine.g_SMExpermentParam.GUID.ToString() + "','" + info.IndexStr + "','" + info.FucntionName + "','"
                            + info.FunctionType + "','" + info.XianHao + "','" + info.Duanzi + "','" + info.Hz.ToString() + "','" + info.PerCount.ToString() + "','" + info.IsFunctionSelect.ToString() + "')";
                        AccessHelper.ExcuteSql(SQL);

                    }
                }
            }
            catch (System.Exception ex)
            {
            	
            }
            
        }

        public void GetChannelSetInfo()
        {
            try
            {
                string SQL = "select * from " + ChannelSetDBName + " where GUIDSTR='" + ProDefine.g_SMExpermentParam.GUID.ToString() + "'";
                DataTable dt = AccessHelper.GetDataTableFromDB(SQL);

                if (dt != null)
                {
                    if (dt.Rows.Count > 0)
                    {
                        ProDefine.g_ChannelInfos.Clear();
                        for (int i = 0; i < dt.Rows.Count; i++ )
                        {
                            ChannelInfos csi = new ChannelInfos();
                            csi.IndexStr = dt.Rows[i][1].ToString();
                            csi.FucntionName =  dt.Rows[i][2].ToString();
                            csi.FunctionType =  dt.Rows[i][3].ToString();
                            csi.XianHao = dt.Rows[i][4].ToString();
                            csi.Duanzi =  dt.Rows[i][5].ToString();
                            csi.Hz =  Convert.ToInt32(dt.Rows[i][6].ToString());
                            csi.PerCount = Convert.ToInt32(dt.Rows[i][7].ToString());
                            csi.IsFunctionSelect = Convert.ToBoolean(dt.Rows[i][8].ToString());
                            ProDefine.g_ChannelInfos.Add(csi);
                        }
                    }

                }
            }
            catch (System.Exception ex)
            {
            	
            }

        }

        public void SaveYBChannelInfo()
        {
            try
            {
                string SQL = "select * from " + YBChannelInfo + " where GUIDSTR='" + ProDefine.g_SMExpermentParam.GUID.ToString() + "'";
                DataTable dt = AccessHelper.GetDataTableFromDB(SQL);
                if (dt != null)
                {
                    if (dt.Rows.Count > 0)
                    {
                        SQL = "delete from " + YBChannelInfo + " where GUIDSTR='" + ProDefine.g_SMExpermentParam.GUID.ToString() + "'";
                        AccessHelper.ExcuteSql(SQL);
                    }
                    foreach (var info in ProDefine.g_FunctionChannel)
                    {
                        /*SQL = "insert into " + ChannelSetDBName + " Values('" + ProDefine.g_SMExpermentParam.GUID.ToString() + "','" + info.FunctionName + "','" + info.Duanzi + "','"
                            + info.Xianhao + "','" + info.hzZQ + "','" + info.PerReadNumber + "','" + info.ChannelType + "','" + info.channelNumber + "')";
                        AccessHelper.ExcuteSql(SQL);*/
                        {
                            SQL = "insert into " + YBChannelInfo + " Values('" + ProDefine.g_SMExpermentParam.GUID.ToString() + "','" + info.IndexStr + "','" + info.FunctionName + "','"
                            + info.ChannelNumber.ToString() + "','" + info.YBNumber.ToString() + "','" + info.InfoType + "')";
                            AccessHelper.ExcuteSql(SQL);
                        }

                    }
                }
            }
            catch (System.Exception ex)
            {
            	
            }
        }

        public void GetYBChannelInfo()
        {
            try
            {
                ProDefine.g_YBsetting.Clear();
                string SQL = "select * from " + YBChannelInfo + " where GUIDSTR='" + ProDefine.g_SMExpermentParam.GUID.ToString() + "'";
                DataTable dt = AccessHelper.GetDataTableFromDB(SQL);
                if (dt != null)
                {
                    if (dt.Rows.Count > 0)
                    {
                       
                        for (int i = 0; i < dt.Rows.Count; i++ )
                        {
                            FucntionChannelInfo fc = new FucntionChannelInfo();
                            fc.IndexStr = dt.Rows[i][1].ToString();
                            fc.FunctionName = dt.Rows[i][2].ToString();
                            fc.ChannelNumber = Convert.ToInt32(dt.Rows[i][3].ToString());
                            fc.YBNumber = Convert.ToInt32(dt.Rows[i][4].ToString());
                            fc.InfoType = Convert.ToByte(dt.Rows[i][5].ToString());
                            ProDefine.g_FunctionChannel.Add(fc);

                        }

                    }
                }
            }
            catch (System.Exception ex)
            {
            	
            }
        }

        public void SaveYBSetSignel()
        {
            try
            {
                string SQL = "select * from " + YBSetSignle + " where GUIDSTR='" + ProDefine.g_SMExpermentParam.GUID.ToString() + "'";
                DataTable dt = AccessHelper.GetDataTableFromDB(SQL);
                if (dt != null)
                {
                    if (dt.Rows.Count > 0)
                    {
                        SQL = "delete from " + YBSetSignle + " where GUIDSTR='" + ProDefine.g_SMExpermentParam.GUID.ToString() + "'";
                        AccessHelper.ExcuteSql(SQL);
                    }
                    foreach (var info in ProDefine.g_YBSetSignle)
                    {
                        string Timestr = "";
                        string ValueStr = "";
                        string YbStr = "";
                        foreach (var kkk in info.m_TimeList)
                        {
                            Timestr = Timestr + kkk.ToString() + ",";
                        }
                        foreach (var kkk in info.m_ValueList)
                        {
                            ValueStr = ValueStr + kkk.ToString() + ",";
                        }
                        
                        Timestr = Timestr.Substring(0, Timestr.Length - 1);
                        ValueStr = ValueStr.Substring(0, ValueStr.Length - 1);
                        

                        SQL = "insert into " + YBSetSignle + " Values('" + ProDefine.g_SMExpermentParam.GUID.ToString() + "','" + info.GNFunction + "','" + Timestr + "','"
                            + ValueStr + "','','" + info.SetType.ToString() + "')";
                        AccessHelper.ExcuteSql(SQL);
                    }
                }
            }
            catch (System.Exception ex)
            {
            	
            }
        }

    

        public void GetYBSetSignel()
        {
            try
            {
                ProDefine.g_YBSetSignle.Clear();
                string SQL = "select * from " + YBSetSignle + " where GUIDSTR='" + ProDefine.g_SMExpermentParam.GUID.ToString() + "'";
                DataTable dt = AccessHelper.GetDataTableFromDB(SQL);
                if (dt != null)
                {
                    if (dt.Rows.Count > 0)
                    {
                        for (int i = 0; i < dt.Rows.Count; i++ )
                        {
                            string GN = dt.Rows[i][1].ToString();
                            string TimeList = dt.Rows[i][2].ToString();
                            string ValueList = dt.Rows[i][3].ToString();
                            string YBList = dt.Rows[i][4].ToString();
                            string Settype = dt.Rows[i][5].ToString();
                            List<int> lTimeList = new List<int>();
                            List<double> lValueList = new List<double>();
                            string[] TimeArr = TimeList.Split(',');
                            foreach (var info in TimeArr)
                            {
                                lTimeList.Add(Convert.ToInt32(info));
                            }
                            string[] ValueArr = ValueList.Split(',');
                            foreach (var info in ValueArr)
                            {
                                lValueList.Add(Convert.ToDouble(info));
                            }
                            YBSingleSetInput ybs = new YBSingleSetInput();
                            ybs.GNFunction = GN;
                            ybs.m_TimeList = lTimeList;
                            ybs.m_ValueList = lValueList;
                            ybs.m_YBList = new List<string>();
                            ybs.m_YBList.AddRange(YBList.Split(','));
                            ybs.SetType = Convert.ToInt32(Settype);
                            ProDefine.g_YBSetSignle.Add(ybs);
                        }
                    }
                }
            }
            catch (System.Exception ex)
            {
            	
            }
        }

        public void SaveYBSetSignelOut()
        {
            try
            {
                string SQL = "select * from " + YBSetOutSignle + " where GUIDSTR='" + ProDefine.g_SMExpermentParam.GUID.ToString() + "'";
                DataTable dt = AccessHelper.GetDataTableFromDB(SQL);
                if (dt != null)
                {
                    if (dt.Rows.Count > 0)
                    {
                        SQL = "delete from " + YBSetOutSignle + " where GUIDSTR='" + ProDefine.g_SMExpermentParam.GUID.ToString() + "'";
                        AccessHelper.ExcuteSql(SQL);
                    }
                    foreach (var info in ProDefine.g_YBSetSignleOut)
                    {
                        string Timestr = "";
                        string ValueStr = "";
                        string YbStr = "";
                        foreach (var kkk in info.m_TimeList)
                        {
                            Timestr = Timestr + kkk.ToString() + ",";
                        }
                        foreach (var kkk in info.m_ValueList)
                        {
                            ValueStr = ValueStr + kkk.ToString() + ",";
                        }
                        
                        Timestr = Timestr.Substring(0, Timestr.Length - 1);
                        ValueStr = ValueStr.Substring(0, ValueStr.Length - 1);
                        

                        SQL = "insert into " + YBSetOutSignle + " Values('" + ProDefine.g_SMExpermentParam.GUID.ToString() + "','" + info.GNFunction + "','" + Timestr + "','"
                            + ValueStr + "','','" + info.SetType.ToString() + "')";
                        AccessHelper.ExcuteSql(SQL);
                    }
                }
            }
            catch (System.Exception ex)
            {

            }
        }



        public void GetYBSetSignelOut()
        {
            try
            {
                ProDefine.g_YBSetSignle.Clear();
                string SQL = "select * from " + YBSetOutSignle + " where GUIDSTR='" + ProDefine.g_SMExpermentParam.GUID.ToString() + "'";
                DataTable dt = AccessHelper.GetDataTableFromDB(SQL);
                if (dt != null)
                {
                    if (dt.Rows.Count > 0)
                    {
                        for (int i = 0; i < dt.Rows.Count; i++)
                        {
                            string GN = dt.Rows[i][1].ToString();
                            string TimeList = dt.Rows[i][2].ToString();
                            string ValueList = dt.Rows[i][3].ToString();
                            string YBList = dt.Rows[i][4].ToString();
                            string Settype = dt.Rows[i][5].ToString();
                            List<int> lTimeList = new List<int>();
                            List<double> lValueList = new List<double>();
                            string[] TimeArr = TimeList.Split(',');
                            foreach (var info in TimeArr)
                            {
                                lTimeList.Add(Convert.ToInt32(info));
                            }
                            string[] ValueArr = ValueList.Split(',');
                            foreach (var info in ValueArr)
                            {
                                lValueList.Add(Convert.ToDouble(info));
                            }
                            YBSingleSetInput ybs = new YBSingleSetInput();
                            ybs.GNFunction = GN;
                            ybs.m_TimeList = lTimeList;
                            ybs.m_ValueList = lValueList;
                          
                            ybs.SetType = Convert.ToInt32(Settype);
                            ProDefine.g_YBSetSignleOut.Add(ybs);
                        }
                    }
                }
            }
            catch (System.Exception ex)
            {

            }
        }

        public void SaveAlarm()
        {
            try
            {
                string SQL = "select * from " + YBSetAlarm + " where GUIDSTR='" + ProDefine.g_SMExpermentParam.GUID.ToString() + "'";
                DataTable dt = AccessHelper.GetDataTableFromDB(SQL);
                if (dt != null)
                {
                    if (dt.Rows.Count > 0)
                    {
                        SQL = "delete from " + YBSetAlarm + " where GUIDSTR='" + ProDefine.g_SMExpermentParam.GUID.ToString() + "'";
                        AccessHelper.ExcuteSql(SQL);
                    }
                    foreach (var info in ProDefine.g_YBAlarm)
                    {
                        string Timestr = "";
                        string ValueStr = "";
                        string YbStr = "";
                        
                        

                       

                        SQL = "insert into " + YBSetAlarm + " Values('" + ProDefine.g_SMExpermentParam.GUID.ToString() + "','" + info.GNFcontion + "','" + info.AlarmH + "','"
                            + info.AlarmL + "','" + info.AlarmDataAbs + "','" + info.AlarmTimeAbs + "','')";
                        AccessHelper.ExcuteSql(SQL);
                    }
                }
            }
            catch (System.Exception ex)
            {

            }
        }



        public void GetAlarm()
        {
            try
            {
                ProDefine.g_YBSetSignle.Clear();
                string SQL = "select * from " + YBSetOutSignle + " where GUIDSTR='" + ProDefine.g_SMExpermentParam.GUID.ToString() + "'";
                DataTable dt = AccessHelper.GetDataTableFromDB(SQL);
                if (dt != null)
                {
                    if (dt.Rows.Count > 0)
                    {
                        for (int i = 0; i < dt.Rows.Count; i++)
                        {
                            string GN = dt.Rows[i][1].ToString();
                            string AlarmH = dt.Rows[i][2].ToString();
                            string AlarmL = dt.Rows[i][3].ToString();
                            string AlarmData = dt.Rows[i][4].ToString();
                            string AlarmAbs = dt.Rows[i][5].ToString();
                            string YBList = dt.Rows[i][6].ToString();
                            YBAlarmSet ybs = new YBAlarmSet();
                            ybs.GNFcontion = GN;
                            ybs.AlarmTimeAbs = AlarmAbs;
                            ybs.AlarmDataAbs = AlarmData;
                            ybs.AlarmH = AlarmH;
                            ybs.AlarmL = AlarmL;
                            

                            ybs.m_YBList = new List<string>();
                            ybs.m_YBList.AddRange(YBList.Split(','));
                            
                            ProDefine.g_YBAlarm.Add(ybs);
                        }
                    }
                }
            }
            catch (System.Exception ex)
            {

            }
        }
    }
}
