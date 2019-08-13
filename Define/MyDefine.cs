using DLLStruct;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using XMLHelper;

namespace Define
{
    public class frmSetInfo
    {
        public static int ExpermentType = 0;

        
    }

    public class ProDefine {
        public static string NowProjectName = "";
        public static ProjectInfo g_MyProject = null;

        public static SMExpermentParam g_SMExpermentParam = new SMExpermentParam();

        public static uint ClearBit(uint value, int BitInDWORD)
        {
            value = (uint)(value & (~(0x1 << BitInDWORD)));
            return value;
        }

        public static ushort ClearBit(ushort value, int BitInDWORD)
        {
            value = (ushort)(value & (~(0x1 << BitInDWORD)));
            return value;
        }
        public static int ClearBit(int value, int BitInDWORD)
        {
            value = value & (~(0x1 << BitInDWORD));
            return value;
        }

        public static uint SetBit(uint value, int BitInDWORD)
        {
            value |= (uint)(0x1 << BitInDWORD);
            return value;
        }

        public static int SetBit(int value, int BitInDWORD)
        {
            value |= (0x1 << BitInDWORD);
            return value;
        }

        public static ushort SetBit(ushort value, int BitInDWORD)
        {
            value |= (ushort)(0x1 << BitInDWORD);
            return value;
        }

        public static bool GetBit(uint value, int BitInDWORD)
        {
            if (((value >> BitInDWORD) & 0x1) == 0)
            {
                return false;
            }
            return true;
        }

        public static bool GetBit(ushort value, int BitInDWORD)
        {
            if (((value >> BitInDWORD) & 0x1) == 0)
            {
                return false;
            }
            return true;
        }
        public static bool GetBit(int value, int BitInDWORD)
        {
            if (((value >> BitInDWORD) & 0x1) == 0)
            {
                return false;
            }
            return true;
        }
    }
    
}
