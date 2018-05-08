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
				"insert into table_article(id, strTitle, strContent, strDate, nTypeID, strTypeName, nCount, strMemo) values(1, 'VC++ ��δ���һ���̲߳����ݲ���', 'VC++ ��δ���һ���̲߳����ݲ���...��ǩ�� vc++attributessecurity.netnullthread...2009-11-26 11:04 3672���Ķ�...', '2016-10-21 20:58:24', 1, 'VC++', 0, 'C#д��')",
				"insert into table_article(id, strTitle, strContent, strDate, nTypeID, strTypeName, nCount, strMemo) values(2, 'C#ʹ��System.Data.SQLite����SQLite', 'C#ʹ��System.Data.SQLite����SQLite...���ͷ��ࣺ C#ѧϰ...ʹ��System.Data.SQLite...', '2016-10-23 20:54:18', 2, 'C#', 0, 'C#д��')",
				"insert into table_article(id, strTitle, strContent, strDate, nTypeID, strTypeName, nCount, strMemo) values(3, 'Python ���������Ż�����', 'ѡ���˽ű����Ծ�Ҫ�������ٶȣ���仰��ĳ�̶ֳ���˵���� python ��Ϊ�ű���һ������֮��...', '2014-09-18 10:14:17', 3, 'Python', 0, 'C#д��')",
				"insert into table_article(id, strTitle, strContent, strDate, nTypeID, strTypeName, nCount, strMemo) values(4, 'Java����Զ���ļ�������', 'Java����Զ���ļ�������.../**...* ����Զ���ļ������浽����...* @param remoteFilePath Զ���ļ�·��...* @param localFilePath �����ļ�·��...*/...', '2016-10-16 14:20:50', 4, 'Java', 0, 'C#д��')",
				"insert into table_article(id, strTitle, strContent, strDate, nTypeID, strTypeName, nCount, strMemo) values(5, 'VS SLN�ļ����', 'VS SLN�ļ����...SLN �ļ���ʽ...Visual Studio ������װ���� .net ʱ����ʹ�ý�������ļ�����׺Ϊ sln ���ļ�����ʾһ����Ŀ�飬��ͨ������һ����Ŀ�����еĹ����ļ���Ϣ...', '2016-10-23 04:55:25', 2, 'C#', 0, 'C#д��')",
				"insert into table_article(id, strTitle, strContent, strDate, nTypeID, strTypeName, nCount, strMemo) values(6, '[�ö�] JavaScriptȫ�ֱ���var�벻var������', '[�ö�] JavaScriptȫ�ֱ���var�벻var������...2013-06-09 20:11 3581���Ķ�...���ࣺJavascript��44��...��Ȩ����������Ϊ����ԭ�����£�δ������������ת��...', '2016-10-24 00:53:26', 5, 'JavaScript', 0, 'C#д��')"};
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