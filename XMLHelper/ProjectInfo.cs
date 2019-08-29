using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XMLHelper
{
    public class ProjectInfo
    {
        public string ProjectName { get; set; }

        public Guid GUID { get; set; }

        public string ProductName { get; set; }

        public string ProductGN { get; set; }

        public string ProductUse { get; set; }

        public string ExperTime { get; set; }

        public string ExperAddress { get; set; }

        public string ProjectPath { get; set; }

        public int ProjectType { get; set; }// 项目实验类型
    }


    public class ExpermentInfo {

        public ProjectInfo Pro { get; set; }

        public int Expertype { get; set; }//0 jiasu 1 jiansu


    }
}
