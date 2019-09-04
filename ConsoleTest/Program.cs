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
            int[] arrayarr = { 11,3,998,5455,1,152,900};
            int min = arrayarr[0];
            for (int i = 0; i < arrayarr.Length - 1; i++ )
            {
                for (int j = 0; j < arrayarr.Length -1 - i;  j++)
                {
                    if (arrayarr[j] > arrayarr[j + 1])
                    {
                        min = arrayarr[j];
                        arrayarr[j] = arrayarr[j + 1];
                        arrayarr[j + 1] = min;
                    }
                }
                
            }
            Console.ReadKey();
        }

    }
}
