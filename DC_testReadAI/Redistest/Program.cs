using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using NewLife.Caching;
using NewLife.Log;

namespace Redistest
{

    class Program
    {
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>

        static void Main(string[] args)
        {
           // XTrace.UseConsole();
            
            var ic = Redis.Create("127.0.0.1:6379", 7);
            //var ic = Redis.Create("server=127.0.0.1:6379;password=pass", 7);
            ic.Log = XTrace.Log; // 调试日志。正式使用时注释\\\

            var Dic = new Dictionary<String,Object>();
            Stopwatch sw = new Stopwatch();
            //sw.Start();
            for (int i = 0; i < 50000; i++) {
                Dic["name" + i.ToString()] = "NewLife";
                Dic["time" + i.ToString()] =  DateTime.Now;
            }
            sw.Start();
            //ic.SetAll(Dic, -1);
            var vs = ic.Get<String>("name49999");
            sw.Stop();

            Console.WriteLine(vs);
            //var user2 = ic.Get<User>("user");
           // XTrace.WriteLine("Json: {0}", ic.Get<String>("user"));
            //if (ic.ContainsKey("user")) XTrace.WriteLine("存在！");
            Console.WriteLine("done!");
            Console.ReadKey();
        }
    }
}
