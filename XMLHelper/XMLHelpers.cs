using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using XmlDAL;

namespace XMLHelper
{
    public class XMLHelpers
    {
        public static XmlHelper m_xml = new XmlHelper();

        public  static string ProXMLFileName = "ProjectConfig.xml";

        public static Hashtable GetHashTable(ProjectInfo pro)
        {
            Hashtable ht = new Hashtable();
            ht.Add("ProjectName", pro.ProjectName);
            ht.Add("GUID",pro.GUID.ToString());
            ht.Add("ProjectPath", pro.ProjectPath);
            return ht;
        }
        
        public static int InsertaNode(string ConfigName,ProjectInfo pro) {

            try
            {

                if (m_xml.isNodeValueExist(ProXMLFileName, "ProjectName", pro.ProjectName, "Projects")) {
                    return -1;//存在
                }
                XmlDocument xmlDoc = new XmlDocument();

                xmlDoc.Load(ConfigName);

                XmlNode xn = xmlDoc.SelectSingleNode("Projects");

                XmlElement xmlelem = xmlDoc.CreateElement("Project");

                // 得到根节点的所有子节点
                XmlElement subNode = xmlDoc.CreateElement("ProjectName");
                subNode.InnerText = pro.ProjectName;
                xmlelem.AppendChild(subNode);

                XmlElement subNode1 = xmlDoc.CreateElement("ProjectPath");
                subNode1.InnerText = pro.ProjectPath;
                xmlelem.AppendChild(subNode1);

                XmlElement subNode2 = xmlDoc.CreateElement("GUID");
                subNode2.InnerText = pro.GUID.ToString();
                xmlelem.AppendChild(subNode2);

                xn.AppendChild(xmlelem);
                xmlDoc.Save(ConfigName);
                return 0;
            }
            catch
            {
                return -2;
            }
        }

        public static List<string> ReadNode(string ConfigName, string RootName, string NodeName)
        {

            try
            {
                XmlDocument xmlDoc = new XmlDocument();
                XmlReaderSettings settings = new XmlReaderSettings();
                settings.IgnoreComments = true;//忽略文档里面的注释
                XmlReader reader = XmlReader.Create(ConfigName, settings);
                xmlDoc.Load(reader);

                XmlNode xn = xmlDoc.SelectSingleNode(RootName);
                // 得到根节点的所有子节点
                XmlNodeList xnl = xn.ChildNodes;
                List<string> returnList = new List<string>();
                foreach (XmlNode xn1 in xnl)
                {
                    XmlElement xe = (XmlElement)xn1;
                    returnList.Add(xe.InnerText);
                }
                return returnList;
            }
            catch
            {
                return null;
            }
        }

        public static string ReadProNodeValue(string ConfigName, string RootName, string NodeName)
        {
            try
            {
                XmlDocument xmlDoc = new XmlDocument();
                XmlReaderSettings settings = new XmlReaderSettings();
                settings.IgnoreComments = true;//忽略文档里面的注释
                XmlReader reader = XmlReader.Create(ConfigName, settings);
                xmlDoc.Load(reader);

                XmlNode xn = xmlDoc.SelectSingleNode(RootName);
                // 得到根节点的所有子节点
                XmlNodeList xnl = xn.ChildNodes;
                // List<string> returnList = new List<string>();
                foreach (XmlNode xn1 in xnl)
                {
                    XmlNodeList xnl1 = xn1.ChildNodes;

                    foreach (XmlNode xnl2 in xnl1)
                    {
                        if (xnl2.Name == NodeName)
                        {
                            return xnl2.InnerText;
                        }
                    }
                }
                return "";
            }
            catch
            {
                return "";
            }
        }

         public static List<ProjectInfo> ReadProListNodeValue(string ConfigName, string RootName)
        {
            try
            {
                XmlDocument xmlDoc = new XmlDocument();
                XmlReaderSettings settings = new XmlReaderSettings();
                settings.IgnoreComments = true;//忽略文档里面的注释
                XmlReader reader = XmlReader.Create(ConfigName, settings);
                xmlDoc.Load(reader);

                XmlNode xn = xmlDoc.SelectSingleNode(RootName);
                // 得到根节点的所有子节点
                XmlNodeList xnl = xn.ChildNodes;
                List<ProjectInfo> returnList = new List<ProjectInfo>();
                foreach (XmlNode xn1 in xnl)
                {
                    XmlNodeList xnl1 = xn1.ChildNodes;
                    ProjectInfo pro = new ProjectInfo();
                    foreach (XmlNode xnl2 in xnl1) {
                        if (xnl2.Name == "ProjectName")
                        {
                            pro.ProjectName = xnl2.InnerText;
                        }
                        else if (xnl2.Name == "ProjectPath")
                        {
                            pro.ProjectPath = xnl2.InnerText;
                        }
                        else if (xnl2.Name == "GUID")
                        {
                            pro.GUID = Guid.Parse(xnl2.InnerText);
                        }
                    }
                    returnList.Add(pro);
                }
                //xmlDoc.
                return returnList;
            }
            catch
            {
                return null;
            }
        }

         public static void DelFromProList(string ConfigName, string RootName,string NodeValue)
         {
             try
             {
                 XmlDocument xmlDoc = new XmlDocument();
                 XmlReaderSettings settings = new XmlReaderSettings();
                 settings.IgnoreComments = true;//忽略文档里面的注释
                 XmlReader reader = XmlReader.Create(ConfigName, settings);
                 xmlDoc.Load(reader);

                 XmlNode xn = xmlDoc.SelectSingleNode(RootName);
                 // 得到根节点的所有子节点
                 XmlNodeList xnl = xn.ChildNodes;
                // List<ProjectInfo> returnList = new List<ProjectInfo>();
                 foreach (XmlNode xn1 in xnl)
                 {
                     XmlNodeList xnl1 = xn1.ChildNodes;
                     //ProjectInfo pro = new ProjectInfo();
                     foreach (XmlNode xnl2 in xnl1)
                     {
                         if((xnl2.Name == "ProjectName") &&(xnl2.InnerText == NodeValue))
                         {
                             xnl2.ParentNode.RemoveChild(xnl2);
                             break;
                         }
                     }
                     //returnList.Add(pro);
                 }
                 xmlDoc.Save(ConfigName);

                // return returnList;
             }
             catch
             {
                // return null;
             }
         }

        public static List<string> ReadNodeAttribute(string ConfigName, string RootName, string AttributeName)
        {

            try
            {
                XmlDocument xmlDoc = new XmlDocument();
                XmlReaderSettings settings = new XmlReaderSettings();
                settings.IgnoreComments = true;//忽略文档里面的注释
                XmlReader reader = XmlReader.Create(ConfigName, settings);
                xmlDoc.Load(reader);

                XmlNode xn = xmlDoc.SelectSingleNode(RootName);
                // 得到根节点的所有子节点
                XmlNodeList xnl = xn.ChildNodes;
                List<string> returnList = new List<string>();
                foreach (XmlNode xn1 in xnl)
                {
                    XmlElement xe = (XmlElement)xn1;
                    returnList.Add(xe.Attributes[AttributeName].Value.ToString());
                }
                return returnList;
                
            }
            catch
            {
                return null;
            }
        }

        private static string ProPath =  System.IO.Directory.GetCurrentDirectory() + "\\Pro\\";
        public static void CreateProFile(ProjectInfo pro)
        { 

            
            string FileProPath = ProPath + pro.ProjectName;
            if (Directory.Exists(ProPath)) {
                Directory.CreateDirectory(ProPath);
            }

            if (!File.Exists(FileProPath))
            {
                //File.Create(FileProPath);
            }
        }

        public static Hashtable CreateInsertHash(ProjectInfo Pro)
        {

            try {
                Hashtable ht = new Hashtable();

                ht.Add("ProjectName", Pro.ProjectName);
                ht.Add("GUID", Pro.GUID);
                ht.Add("ProductGN", Pro.ProductGN);
                ht.Add("ProductUse", Pro.ProductUse);
                ht.Add("ProductName", Pro.ProductName);
                ht.Add("ExperTime", Pro.ExperTime);
                ht.Add("ExperAddress", Pro.ExperAddress);
                return ht;

            }
            catch {
                return null;
            }
        }




        public static int CreateProjectInfo(ProjectInfo pro)
        {
            try {

                if (File.Exists(ProPath + pro.ProjectName + ".csproj")) {
                    return -1; //表示路径下存在当前名称的项目
                }
                string FileName = ProPath + pro.ProjectName + ".csproj";
                //File.Create(ProPath + pro.ProjectName + ".csproj");
                m_xml.CreateXmlDocument(FileName, "Project", "UTF-8");

                Hashtable ht = CreateInsertHash(pro);


                m_xml.InsertNode(FileName,"ProjectInfo",false,"Project",null,ht);



                return 0;
            }
            catch {
                return 0;
            }
        }




        public string XMLPathName = "";

        public static bool WriteNodeInfo(string NodeStr, string NodeValue)
        {
            try {


                return true;
            }
            catch{
                return false;
            }
        }

        public bool ReadNodeValue(string NodeStr, string NodeValue)
        {
            try
            {


                return true;
            }
            catch
            {
                return false;
            }
        }

    }
}
