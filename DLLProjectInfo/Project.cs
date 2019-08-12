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

        public int SaveProjectInfo(ProjectInfo pro) {

            int returnvalue = XMLHelpers.InsertaNode("ProjectConfig.XML", pro);

            XMLHelpers.CreateProjectInfo(pro);
            return returnvalue;
            //return XMLHelpers.InsertaNode("ProjectConfig.xml", "ProjectInfo", "ProjectName", ProjectName, "GUID", guid.ToString());
            
        }

        public int AddProjectInfo(ProjectInfo pro)
        {
            int returnvalue = XMLHelpers.InsertaNode("ProjectConfig.XML", pro);
            return returnvalue;
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

                List<ProjectInfo> ProList = XMLHelpers.ReadProListNodeValue("ProjectConfig.XML", "Projects");
               
                return ProList;
            
            }
            catch {
                return null;
            }
        
            
        }

        public void DelProFromList(ProjectInfo pro) {
            XMLHelpers.DelFromProList("ProjectConfig.XML", "Projects", pro.ProjectName);
        }

    }
}
