using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using System.Data.SQLite;

namespace lesson12 {
	public partial class RArticleM:System.Web.UI.Page{
		protected void Page_Load(object sender, EventArgs e){
			string [] A_strQuery = {
				"create table if not exists table_article(id int, strTitle varchar(150), strContent text, strDate datetime, nTypeID int, strTypeName varchar(50), nCount int, strMemo varchar(100))",
				"select id, strTitle, strDate, nTypeID, strTypeName, nCount, strMemo from table_article",
				"select count(1) from table_article",
				"insert into table_article(id, strTitle, strContent, strDate, nTypeID, strTypeName, nCount, strMemo) values(1, 'VC++ 如何创建一个线程并传递参数', 'VC++ 如何创建一个线程并传递参数...标签： vc++attributessecurity.netnullthread...2009-11-26 11:04 3672人阅读...', '2016-10-21 20:58:24', 1, 'VC++', 0, 'C#写入')",
				"insert into table_article(id, strTitle, strContent, strDate, nTypeID, strTypeName, nCount, strMemo) values(2, 'C#使用System.Data.SQLite操作SQLite', 'C#使用System.Data.SQLite操作SQLite...博客分类： C#学习...使用System.Data.SQLite...', '2016-10-23 20:54:18', 2, 'C#', 0, 'C#写入')",
				"insert into table_article(id, strTitle, strContent, strDate, nTypeID, strTypeName, nCount, strMemo) values(3, 'Python 代码性能优化技巧', '选择了脚本语言就要忍受其速度，这句话在某种程度上说明了 python 作为脚本的一个不足之处...', '2014-09-18 10:14:17', 3, 'Python', 0, 'C#写入')",
				"insert into table_article(id, strTitle, strContent, strDate, nTypeID, strTypeName, nCount, strMemo) values(4, 'Java下载远程文件到本地', 'Java下载远程文件到本地.../**...* 下载远程文件并保存到本地...* @param remoteFilePath 远程文件路径...* @param localFilePath 本地文件路径...*/...', '2016-10-16 14:20:50', 4, 'Java', 0, 'C#写入')",
				"insert into table_article(id, strTitle, strContent, strDate, nTypeID, strTypeName, nCount, strMemo) values(5, 'VS SLN文件详解', 'VS SLN文件详解...SLN 文件格式...Visual Studio 开发套装进入 .net 时代后，使用解决方案文件（后缀为 sln 的文件）表示一个项目组，他通常包含一个项目中所有的工程文件信息...', '2016-10-23 04:55:25', 2, 'C#', 0, 'C#写入')",
				"insert into table_article(id, strTitle, strContent, strDate, nTypeID, strTypeName, nCount, strMemo) values(6, '[置顶] JavaScript全局变量var与不var的区别', '[置顶] JavaScript全局变量var与不var的区别...2013-06-09 20:11 3581人阅读...分类：Javascript（44）...版权声明：本文为博主原创文章，未经博主允许不得转载...', '2016-10-24 00:53:26', 5, 'JavaScript', 0, 'C#写入')"};
			//DataTable dt = SqlHelper.ExecuteDataSetText(strSql, null).Tables[0];
			string dbPath = "Data Source=" + Server.MapPath("App_Data") + @"\lesson12.sqlite3";

			/*
			LT_Display.Text = dbPath + "<br />\n" +
				A_strQuery[0] + "<br />\n" +
				A_strQuery[1] + "<br />\n" +
				A_strQuery[2] + "<br />\n" +
				A_strQuery[3];
			*/

			using(SQLiteConnection conn = new SQLiteConnection(dbPath)){
				conn.Open();
				using(SQLiteCommand cmd = new SQLiteCommand(A_strQuery[0], conn)){
					cmd.ExecuteNonQuery();
					cmd.CommandText = A_strQuery[2];
					int nCount = 0;
					using(SQLiteDataReader dr = cmd.ExecuteReader()){
						dr.Read();
						nCount = Convert.ToInt32(dr[0].ToString());
					}
					if (nCount>0){
						LT_Display.Text = "Exists " + nCount;
					}else{
						for(int i=0; i<6; i++){
							cmd.CommandText = A_strQuery[i+3];
							cmd.ExecuteNonQuery();
						}
					}
					cmd.CommandText = A_strQuery[1];
					using(SQLiteDataReader dr = cmd.ExecuteReader()){
						this.GridView1.DataSource = dr;
						this.GridView1.DataBind();
					}
				}
			}
		}
	}
}