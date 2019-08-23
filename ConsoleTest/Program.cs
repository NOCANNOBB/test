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
    class Program
    {


        public static double GetExlipseTime() {
            return (double)(DateTime.Now - TStartTime).TotalSeconds;
        }
        public static DateTime TStartTime;

        static void Main(string[] args)
        {
            MemeryFile mf = new MemeryFile();
            //mf.CreateFile("FileData.data");
            string dataPath = @"F:\" + DateTime.Now.ToString("yyyymmddhhmmss") + ".data";

            BordDll.DoInit();
            List<int> nChannelList = new List<int>{
                0,1,2,3,4,5,6,7,8,9,10,11,12,13
            };
            double expermentTime = 500 * 60 * 60;


            TStartTime = DateTime.Now;
            while (true) {

                if (expermentTime <= GetExlipseTime()) {
                    break;
                }

                //每次写入list中的数据
                List<FileData> fdList = new List<FileData>();
                long newSize = 0;
                foreach (var info in nChannelList) {
                    FileData fd = new FileData();
                    fd.ChannleID = info;
                    double dvalue = 0;
                    BordDll.GetDataFromBord(info, ref dvalue);
                    fd.dVflot = dvalue;

                    fd.DataType = 0;
                    newSize += Marshal.SizeOf(fd);
                    fdList.Add(fd);
                }

                mf.CreateWriteMemoryMapFile(dataPath, newSize);
                mf.WriteToMemFile(fdList);
                mf.DisposeMemoryMapFile();
                Thread.Sleep(1);
            }

            BordDll.Release();
            
            Console.ReadKey();
        }
    }
}
