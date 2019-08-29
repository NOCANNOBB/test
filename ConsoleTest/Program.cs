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

        static List<aaa> mylist= new List<aaa>();
        public static double GetExlipseTime() {
            return (double)(DateTime.Now - TStartTime).TotalSeconds;
        }
        public static DateTime TStartTime;
        
        static void Main(string[] args)
        {
            aaa a = new aaa();
            a.k = 12;
            a.kk = "aaaa";
            mylist.Add(a);

            aaa k = mylist[0];
            k.k = 2;
            k.kk = "123123";
            Console.WriteLine(mylist[0].kk);
            Console.ReadKey();
        }
    }
}
