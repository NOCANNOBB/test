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
            for (int i = 0; i < 10; i++ )
            {
                aaa a = new aaa();
                a.k = i;
                if ((i < 8)&&(i > 3))
                {
                    a.kk = i.ToString() + "kkk";
                }
                else
                a.kk =  i.ToString();
                mylist.Add(a);
            }

            List<aaa> tp = mylist.Where(m => m.kk.Contains("kkk")).ToList();

            foreach (var info in tp)
            {
                info.kk = "asd";
            }
            Console.ReadKey();
        }

    }
}
