using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using DLLMemeryFile;
using DLLStruct;
using DLLBordDllImport;

namespace ConsoleTest
{
    class aaa{
        public int k{get;set;}
        public string kk{get;set;}
    }

    class Program
    {

        static List<aaa> mylist = new List<aaa>();
        public static double GetExlipseTime()
        {
            return (double)(DateTime.Now - TStartTime).TotalSeconds;
        }
        public static DateTime TStartTime;

        static void Main(string[] args)
        {
            int k = 0;
            BordDll.DoInit();
            while (k <= 10)
            {
                double dfValue = 0;
                double dfValue2 = 12.1;
               // dfValue[0] = 0;
               // BordDll.WriteAOData(0, dfValue2);
                BordDll.WriteDOData(0, (byte)1);
                //double dValue = Marshal.PtrToStructure(dfValue,typeof(double));
                Console.WriteLine(dfValue.ToString());
                Thread.Sleep(1000);
                k++;
            }

            Console.ReadKey();
        }

    }
}
