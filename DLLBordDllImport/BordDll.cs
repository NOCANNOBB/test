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
        public static extern void GetDataFromBord(int Bordi,ref double BordBuffer);

        [DllImport("BordDLL.dll")]
        public static extern void Release();
    }
}
