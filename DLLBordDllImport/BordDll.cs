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
        [DllImport("BordDLL.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool DoInit();

        [DllImport("BordDLL.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool StartChannel(uint ulChan);

        [DllImport("BordDLL.dll", EntryPoint = "GetAIDataFromBord", CallingConvention = CallingConvention.Cdecl)]
        public static extern void GetAIDataFromBord(int ulChan, ref double AIData);

        [DllImport("BordDLL.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void WriteDOData(uint ulChan, byte wDoData);



        [DllImport("BordDLL.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ReadDOData(uint ulChan, byte[] rDoData);



        [DllImport("BordDLL.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void GetCNTData(uint ulChan, ref double dfFreq, ref double dfDutyCycle);

        [DllImport("BordDLL.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void WriteAOData(uint ulChan, double wAOData);


        [DllImport("BordDLL.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void GetDataFromBord(int Bordi, double[] BordBuffer,int ReadSize, ref int retReadSize);

        [DllImport("BordDLL.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Release();
    }
}
