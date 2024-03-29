﻿using System;
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

    public class ChannelSetInfo
    {
        public Guid m_ProGuid { get; set; }

        public string FunctionName { get; set; }

        public string Duanzi { get; set; }

        public string Xianhao { get; set; }

        public int hzZQ { get; set; }//数据类型 0 开关量 1 模拟量

        public int PerReadNumber { get; set; }//输入输入 0 输入 1 输出

        public string ChannelType { get; set; }//通道功能描述

        public int channelNumber { get; set; }
    }

    public class YBSetuse
    {
        public string GNFunction { get; set; }
        public int ChannelID { get; set; }
        public string ChannelType { get; set; }

    }

    public class YBChannelInfo
    {
        public string YBName { get; set; }

        public List<YBSetuse> YBList { get; set; }
    }

    public class YBSingleSetInput
    {
        public List<string> m_YBList { get; set; }

        public string GNFunction { get; set; }

        public int SetType { get; set; }// 0 恒定 1 循环信号 2 不循环变化信号

        public List<double> m_ValueList { get; set; }

        public List<int> m_TimeList { get; set; }
    }


    public class YBInputFunctionValueSet
    {
        public string GNFunctionName { get; set; }

        public int SignleType { get; set; }
    }

    public class YBAlarmSet
    {
        public List<string> m_YBList { get; set; }
        public string GNFcontion { get; set; }
        public string AlarmH { get; set; }
        public string AlarmL { get; set; }
        public string AlarmDataAbs { get; set; }
        public string AlarmTimeAbs { get; set; }
    }

    public struct YBData
    {
        public string YBName { get; set; }

        public int ChannID { get; set; }

        public string ChannType { get; set; }

        public int DTTime { get; set; }

        public Object flVot { get; set; }

        public string GNFunction { get; set; }

        public int DataInfo { get; set; }//数据信息 0 正常信息 1 上限报警信息 2下限报警信息 4 错误数据
    }

    public class ChannelSet
    {
        public string ChanleType{get;set;}
        public int ChannelID{get;set;}
    }


    public class ChannelInfos
    {
        public string IndexStr { get; set; }

        public string FucntionName { get; set; }

        public string FunctionType { get; set; }

        public string XianHao { get; set; }

        public string Duanzi { get; set; }

        public int Hz { get; set; }

        public int PerCount { get; set; }

        public bool IsFunctionSelect { get; set; }
    }

    public class FucntionChannelInfo
    {
        public string IndexStr { get; set; }

        public string FunctionName { get; set; }

        public int ChannelNumber { get; set; }

        public int YBNumber { get; set; }

        public byte InfoType { get; set; }//0 DA 1 AD
    }

}
