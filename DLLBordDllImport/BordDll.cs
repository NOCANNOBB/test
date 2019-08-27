using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace DLLBordDllImport
{
    public class BordDll
    {
        [DllImport("BordDLL.dll")]
        public static extern bool DoInit();

        [DllImport("BordDLL.dll")]
        public static extern bool StartChannel(ulong ulChan);

        [DllImport("BordDLL.dll")]
        public static extern void GetAIDataFromBord(ulong ulChan, ref double AIData);

        [DllImport("BordDLL.dll")]
        public static extern void WriteDOData(ulong ulChan, Boolean wDoData);

        [DllImport("BordDLL.dll")]
        public static extern void WriteDOData_1(ulong ulChan, byte[] wData);

        [DllImport("BordDLL.dll")]
        public static extern void ReadDOData(ulong ulChan, ref Boolean rDoData);

        [DllImport("BordDLL.dll")]
        public static extern void ReadDOData_1(ulong ulChan, byte[] RData);


        [DllImport("BordDLL.dll")]
        public static extern void GetCNTData(ulong ulChan, ref double dfFreq, ref double dfDutyCycle);

        [DllImport("BordDLL.dll")]
        public static extern void WriteAOData(ulong ulChan, ref double wAOData);


        [DllImport("BordDLL.dll")]
        public static extern void GetDataFromBord(int Bordi,ref double BordBuffer);

        [DllImport("BordDLL.dll")]
        public static extern void Release();
    }
}
