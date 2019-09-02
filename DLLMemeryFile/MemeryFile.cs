using System;
using System.Collections.Generic;
using System.IO;
using System.IO.MemoryMappedFiles;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using DLLStruct;

namespace DLLMemeryFile
{
    public class MemeryFile
    {
        public  void CreateFile(string FileName) {
            if (!File.Exists(FileName)) {
                FileStream fs = File.Create(FileName);
                fs.Close();
            }
        }


        public long GetFileSize(string FileName) {
            try
            {
                FileInfo fi = new FileInfo(FileName);
                return fi.Length;
            }
            catch {
                return 0;
            }
        }


        //private const long
        //FILE_SIZE = 1024 * 1024 * 1024 * 100;
        /// <summary>
        /// 引用内存映射文件
        /// </summary>
        private MemoryMappedFile memoryFile = null;
        /// <summary>
        /// 用于访问内存映射文件的存取对象
        /// </summary>
        private MemoryMappedViewAccessor  accessor;
        /// <summary>
        /// 创建内存映射文件,循环调用，解决映射文件增长问题
        /// </summary>
        public void CreateWriteMemoryMapFile(string FileName,long NewSize)
        {
            try
            {
                CreateFile(FileName);
                long LastFileSize = GetFileSize(FileName);
                long NowNewSize =LastFileSize  + NewSize;

                memoryFile = MemoryMappedFile.CreateFromFile(FileName, FileMode.Open, "MyFile", NowNewSize);
                
           
                //访问上次结束，到本次添加的文件文件部分
                accessor = memoryFile.CreateViewAccessor(LastFileSize,NewSize);
                //InitFileContent();
            }
            catch (Exception ex)
            {
                
            }
        }
        /// <summary>
        /// 关闭并释放资源
        /// </summary>
        public void DisposeMemoryMapFile()
        {
            if (accessor != null)
                accessor.Dispose();
        
            if (memoryFile != null)
                memoryFile.Dispose();
        }
        long position = 0;

        public void WriteToMemFile(List<YBData> WriteList) {
            try {
                if (accessor != null) {
                    position = 0;
                    //accessor.CanWrite = true;
                    for (int i = 0; i < WriteList.Count; i++ )
                    {
                        YBData fd = WriteList[i];

                        accessor.Write<YBData>(position, ref fd);
                        //accessor.Write(position,12);
                        position += Marshal.SizeOf(fd);
                    }

                    accessor.Flush();
                   
                    
                }
            }
            catch { }
        }


        public long AlreadyReadSize = 0;
        /// <summary>
        /// 
        /// </summary>
        /// <param name="FileName">文件名</param>
        /// <param name="ReadSize">读取大小</param>
        /// <param name="Index"></param>
        /// <returns></returns>
        public bool CreateReadMemoryMapFile(string FileName, long ReadSize)
        {
            try
            {
                //CreateFile(FileName);

                if (!File.Exists(FileName)) {
                    return false;
                }

                long FileSize = GetFileSize(FileName);


                memoryFile = MemoryMappedFile.CreateFromFile(FileName, FileMode.Open, "MyFile", FileSize);


                //访问全部文件
                accessor = memoryFile.CreateViewAccessor(AlreadyReadSize, ReadSize);
                AlreadyReadSize += ReadSize;
                return true;
                //InitFileContent();
            }
            catch (Exception ex)
            {
                return false;
            }
        }

        public int PerSize = 0;

        public List<YBData> ReadFromMemFile()
        {
            List<YBData> returnList = new List<YBData>();
            try {
                if (accessor != null) {
                    YBData fd = new YBData();
                    PerSize = Marshal.SizeOf(fd);
                    long TCount = accessor.Capacity / PerSize;

                    for (long i = 0; i < TCount; i++) {
                        YBData fdk = new YBData();
                        accessor.Read<YBData>(i * PerSize, out fdk);
                        returnList.Add(fdk);


                    }
                   // double rValue = 0;
                   // accessor.Read(4, out rValue);
                }
            }
            catch { }
            return returnList;
        }
    }
}
