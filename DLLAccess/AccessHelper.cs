using ADOX;
using System;
using System.Collections.Generic;
using System.Data.OleDb;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data;

namespace DLLAccess
{
    public class AccessHelper
    {
        private static OleDbConnection accessConnection;
        private static string TableName;
        private static List<string> dataShareFiled = new List<string>();
        private static string conn_str = "";
        private static OleDbCommand ole_command = new OleDbCommand();

        private static OleDbDataReader ole_reader;
        private static DataTable dt;

        public static bool CreateAccessDb(string filePath) {

            ADOX.Catalog catalog = new Catalog();
            if (!File.Exists(filePath)) {
                try {
                    conn_str = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + filePath + ";Jet OLEDB:Engine Type=5";
                    catalog.Create("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + filePath + ";Jet OLEDB:Engine Type=5");
                }
                catch {
                    Trace.TraceWarning("创建access数据库失败");
                    return false;
                }
            }
            return true;
        }


        public static bool CreateAccessTable(string FilePath, string tbName) {
            ADOX.Catalog catalog = new Catalog();

            List<string> colums = new List<string>();
            //数据库文件不存在则创建
            if (!File.Exists(FilePath))
            {
                try
                {
                    catalog.Create("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + FilePath + ";Jet OLEDB:Engine Type=5");
                }
                catch (System.Exception e)
                {
                    Trace.TraceWarning("创建Access表出错", e);
                    return false;
                }

               
             
            }

            ADODB.Connection cn = new ADODB.Connection();
            try
            {
                cn.Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + FilePath, null, null, -1);
                if(accessConnection == null){
                    accessConnection = new OleDbConnection(cn.ConnectionString);
                }
            }
            catch (System.Exception ex)
            {
                Trace.TraceWarning("Access连接打开失败", ex);
                return false;
            }
            try
            {
                catalog.ActiveConnection = cn;
                ADOX.Table table = new ADOX.Table();
                table.ParentCatalog = catalog;
                table.Name = tbName;


                if (tbName == "ProjectConfig")

                //公共字段
                {
                    colums.Insert(0, "ProjectName");
                    colums.Insert(1, "GUIDSTR");
                    colums.Insert(2, "ProductName");
                    colums.Insert(3, "ProductGN");
                    colums.Insert(4, "ProductUse");
                    colums.Insert(5, "ExperTime");
                    colums.Insert(6, "ExperAddress");
                    colums.Insert(7, "ProjectPath");
                }
                if (tbName == "ExpermentParam")
                {
                    colums.Insert(0, "GUIDSTR");// 1加速 0 寿命
                    colums.Insert(1, "ExpermentType");// 1加速 0 寿命
                    colums.Insert(2, "YLType");
                    colums.Insert(3, "JSMode");
                    colums.Insert(4, "YLSetType");
                    colums.Insert(5, "CGTemperature");
                    colums.Insert(6, "CGXDSD");
                    colums.Insert(7, "CPJXTemperature");
                    colums.Insert(8, "CPJXXDSD");
                    colums.Insert(9, "YLNumber");
                    colums.Insert(10, "YBNumber");
                    colums.Insert(11, "JWType");
                    colums.Insert(12, "CGZD");
                    colums.Insert(13, "CGDYL");
                    colums.Insert(14, "JXZD");
                    colums.Insert(15, "JXDYL");
                }
                if (tbName == "ExpermentDesign")
                {
                    colums.Insert(0, "GUIDSTR");// 1加速 0 寿命
                    colums.Insert(1, "Temperature");// 1加速 0 寿命
                    colums.Insert(2, "SD");
                    colums.Insert(3, "YBNumber");
                    colums.Insert(4, "ExpermentTime");
                }


                foreach (var column in colums)
                {
                    ADOX.ColumnClass col = new ADOX.ColumnClass
                    {
                        ParentCatalog = catalog,
                        Name = column,
                        Attributes = ColumnAttributesEnum.adColNullable //允许空值
                    };


                    table.Columns.Append(col, DataTypeEnum.adVarWChar, 50); //默认数据类型和字段大小
                }
                catalog.Tables.Append(table);

                accessConnection = new OleDbConnection(cn.ConnectionString);
                TableName = tbName;
                
                
                try
                {
                    accessConnection.Open();
                }
                catch (System.Exception ex)
                {
                    Trace.TraceWarning("Access连接打开失败", ex);
                    return false;
                }

                cn.Close();
            }
            catch { 
                
            }

            return true;



        }


        public static bool AppendData2Access(Dictionary<string, object> data,string TableNameParam)
        {
            if (data.Count > 0)
            {
                try
                {
                    string fields = null;
                    string values = null;
                    string sql = null;
                    foreach (var item in data)
                    {
                        fields += item.Key.ToString() + ',';
                        values += string.Format("'{0}'", item.Value.ToString()) + ',';
                    }
                    fields = fields.Remove(fields.Length - 1, 1);
                    values = values.Remove(values.Length - 1, 1);
                    sql = string.Format("insert into {0} ({1}) values ({2})", TableNameParam, fields, values);
                    OleDbCommand cmd = new OleDbCommand(sql, accessConnection);
                    accessConnection.Open();//打开连接
                    cmd.ExecuteNonQuery();
                }
                catch { }

                finally {
                    if (accessConnection.State != ConnectionState.Closed)
                    {
                        accessConnection.Close();
                    }
                }
                
            }
            return true;
        }

        private static DataTable BuildAndInitDataTable(int Field_Count)
        {
            DataTable dt_tmp = null;
            DataColumn dc = null;
            int i = 0;

            if (Field_Count <= 0)
            {
                return null;
            }

            dt_tmp = new DataTable();

            for (i = 0; i < Field_Count; ++i)
            {
                dc = new DataColumn(i.ToString());
                dt_tmp.Columns.Add(dc);
            }

            return dt_tmp;
        }

        private static DataTable ConvertOleDbReaderToDataTable(ref OleDbDataReader reader)
        {
            DataTable dt_tmp = null;
            DataRow dr = null;
            int data_column_count = 0;
            int i = 0;

            data_column_count = reader.FieldCount;
            dt_tmp = BuildAndInitDataTable(data_column_count);

            if (dt_tmp == null)
            {
                return null;
            }

            while (reader.Read())
            {
                dr = dt_tmp.NewRow();

                for (i = 0; i < data_column_count; ++i)
                {
                    dr[i] = reader[i];
                }

                dt_tmp.Rows.Add(dr);
            }

            return dt_tmp;
        }

        public static DataTable GetDataTableFromDB(string strSql)
        {
            if (conn_str == null)
            {
                return null;
            }

            try
            {

                {
                    accessConnection.Open();//打开连接

                    if (accessConnection.State == ConnectionState.Closed)
                    {
                        return null;
                    }

                    ole_command.CommandText = strSql;
                    ole_command.Connection = accessConnection;

                    ole_reader = ole_command.ExecuteReader(CommandBehavior.Default);

                    dt = ConvertOleDbReaderToDataTable(ref ole_reader);

                    ole_reader.Close();
                    ole_reader.Dispose();
                }
            }
            catch (System.Exception e)
            {

            }
            finally
            {

                {
                    if (accessConnection.State != ConnectionState.Closed)
                    {
                        accessConnection.Close();
                    }
                }
            }

            return dt;
        } 

        public static void ClosedbConnection()
        {
            accessConnection.Close();
        }

        public static int ExcuteSql(string strSql)
        {



            int nResult = 0;

            try
            {

                {
                    if (accessConnection.State == ConnectionState.Closed)
                    {
                        accessConnection.Open();//打开数据库连接
                    }
                    if (accessConnection.State == ConnectionState.Closed)
                    {
                        return nResult;
                    }

                    ole_command.Connection = accessConnection;
                    ole_command.CommandText = strSql;

                    nResult = ole_command.ExecuteNonQuery();
                }
            }
            catch (System.Exception e)
            {
                if (strSql == "")
                {

                    //Console.WriteLine(e.ToString());
                    return nResult;
                }


                //Console.WriteLine(e.ToString());
                return nResult;
            }
            finally
            {

                {
                    if (accessConnection.State != ConnectionState.Closed)
                    {
                        accessConnection.Close();
                    }
                }
            }

            return nResult;
        }
    }
}
