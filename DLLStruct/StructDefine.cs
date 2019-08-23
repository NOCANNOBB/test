using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DLLStruct
{
    public class StructDefine
    {
    }


    public struct FileData {

        public int ChannleID { get; set; }

        public double dVflot { get; set; }
        /// <summary>
        /// 数据类型 0 为正常数据  1为报警数据
        /// </summary>
        public byte DataType { get; set; }
    }

    public class SMExpeDesignParam {
        public double Temperature { get; set; }

        public double SD { get; set; }
        public int YBNumber { get; set; }

        public int ExpermentTime { get; set; }
    }

    public class SMExpermentDesin {
        public List<SMExpeDesignParam> ExpParamList { get; set; }
    }

    public class SMExpermentParam //寿命实验参数
    {
        public Guid GUID { get; set; }

        public int YLType { get; set; }//应力类型

        public int JSMode { get; set; }//加速模型

        public int YLSetType { get; set; }//应力施加方式

        public string CGTemperature { get; set; }//常规使用温度

        public string CGXDSD { get; set; }//相对湿度

        public string CPJXTemperature { get; set; }//极限温度

        public string CPJXXDSD { get; set; }

        public string YLNumber { get; set; }

        public string YBNumber { get; set; }

        public int JWType { get; set; }

        public int ExpermentType { get; set; }

        public string CGZD { get; set; }

        public string CGDYL { get; set; }

        public string JXZD { get; set; }

        public string JXDYL { get; set; }



        public string XNTHCS { get; set; }// 性能退化参数
        public string THYZ { get; set; }//退化阈值

    }
}
