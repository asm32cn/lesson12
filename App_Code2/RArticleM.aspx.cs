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
				"create table if not exists table_article(id int, strTitle varchar(150), strDate date, nTypeID int, strTypeName varchar(50), nCount int)",
				"select count(1) from table_article",
				"insert into table_article(id, strTitle, strDate, nTypeID, strTypeName, nCount) values(1, 'VC++ 如何创建一个线程并传递参数', '2016-10-23', 1, 'VC++', 0)",
				"select id, strTitle, strDate, nTypeID, strTypeName, nCount from table_article"};
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
					cmd.CommandText = A_strQuery[1];
					int nCount = 0;
					using(SQLiteDataReader dr = cmd.ExecuteReader()){
						dr.Read();
						nCount = Convert.ToInt32(dr[0].ToString());
					}
					if (nCount>0){
						//LT_Display.Text += "<br />\n" + "Exists " + nCount;
						LT_Display.Text = "Exists " + nCount;
					}else{
						cmd.CommandText = A_strQuery[2];
						cmd.ExecuteNonQuery();
					}
					cmd.CommandText = A_strQuery[3];
					using(SQLiteDataReader dr = cmd.ExecuteReader()){
						this.GridView1.DataSource = dr;
						this.GridView1.DataBind();
					}
				}
			}
		}
	}
}