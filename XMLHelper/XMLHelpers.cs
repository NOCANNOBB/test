using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace XMLHelper
{
    public class XMLHelpers
    {

        public static bool InsertaNode(string ConfigName,string RootName,string NodeName,string NodeValue,string AttributeName,string AttributeValue) {

            try
            {
                XmlDocument doc = new XmlDocument();
                doc.Load(ConfigName);
                XmlNode root = doc.SelectSingleNode(RootName);
                XmlElement xelKey = doc.CreateElement(NodeName);
                XmlAttribute xelType = doc.CreateAttribute(AttributeName);
                xelType.InnerText = AttributeValue;
                xelKey.SetAttributeNode(xelType);
                xelKey.InnerText = NodeValue;
                root.AppendChild(xelKey);
                doc.Save(@"ProjectConfig.xml");
                return true;
            }
            catch
            {
                return false;
            }
        }

        public static List<string> ReadNode(string ConfigName, string RootName, string NodeName)
        {

            try
            {
                XmlDocument xmlDoc = new XmlDocument();
                XmlReaderSettings settings = new XmlReaderSettings();
                settings.IgnoreComments = true;//忽略文档里面的注释
                XmlReader reader1 = XmlReader.Create(ConfigName, settings);
                xmlDoc.Load(reader1);

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




        public string XMLPathName = "";

        public bool WriteNodeInfo(string NodeStr, string NodeValue) {
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
