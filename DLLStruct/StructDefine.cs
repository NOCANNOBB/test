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

    public class SMExpermentParam //寿命实验参数
    {
        public int YLType { get; set; }//应力类型

        public int JSMode { get; set; }//加速模型

        public int YLSetType { get; set; }//应力施加方式

        public float CGTemperature { get; set; }//常规使用温度

        public float CGXDSD { get; set; }//相对湿度

        public float CPJXTemperature { get; set; }//极限温度

        public float CPJXXDSD { get; set; }

        public int YLNumber { get; set; }

        public int YBNumber { get; set; }

        public int JWType { get; set; }
    }
}
