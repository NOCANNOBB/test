using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using XMLHelper;

namespace DLLProjectInfo
{
    public class DoProjectInfo
    {

        public bool SaveProjectInfo(string ProjectName,Guid guid) {
            return XMLHelpers.InsertaNode("ProjectConfig.XML", "ProjectInfo", "ProjectName", ProjectName, "GUID", guid.ToString());
            
        }

        public List<ProjectInfo> GetProjectInfos() {

            try {
                List<string> ProNameList = XMLHelpers.ReadNode("ProjectConfig.XML", "ProjectInfo", "ProjectName");

                List<string> GUIDNameList = XMLHelpers.ReadNodeAttribute("ProjectConfig.XML", "ProjectInfo", "GUID");

                List<ProjectInfo> ProList = new List<ProjectInfo>();
                for (int i = 0; i < ProNameList.Count; i++) {
                    ProjectInfo pro = new ProjectInfo();

                    pro.GUID = new Guid(GUIDNameList[i]);
                    pro.ProjectName = ProNameList[i];
                    ProList.Add(pro);
                }
                return ProList;
            
            }
            catch {
                return null;
            }
        
            
        }
    }
}
