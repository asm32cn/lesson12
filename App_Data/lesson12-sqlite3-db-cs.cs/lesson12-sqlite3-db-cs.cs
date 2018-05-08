using System;
using System.Drawing;
using System.Windows.Forms;
using System.Data;
using System.Data.SQLite;

class lesson12_sqlite3_db_cs : Form{
	private const string strCaption = "lesson12-sqlite3-db-cs.cs";
	private ListView lv = new ListView();

	protected override Size DefaultSize{
		get{
			return new Size(800, 450);
		}
	}

	public lesson12_sqlite3_db_cs(){
		this.Text = strCaption;
		this.StartPosition = FormStartPosition.CenterScreen;

		lv.Dock = DockStyle.Fill;
		lv.View = View.Details;
		lv.GridLines = true;
		lv.FullRowSelect = true;

		initListData();

		this.Controls.Add(lv);
	}

	public void initListData(){
		lv.Clear();
		lv.Columns.Add("id", 25, HorizontalAlignment.Center);
		lv.Columns.Add("标题", 325, HorizontalAlignment.Left);
		lv.Columns.Add("时间", 130, HorizontalAlignment.Left);
		lv.Columns.Add("分类ID", 50, HorizontalAlignment.Center);
		lv.Columns.Add("分类", 85, HorizontalAlignment.Left);
		lv.Columns.Add("浏览数", 50, HorizontalAlignment.Center);
		lv.Columns.Add("备注", 115, HorizontalAlignment.Left);

		string dbPath = "Data Source=..\\lesson12.sqlite3";
		string strQuery = "select id, strTitle, strDate, nTypeID, strTypeName, nCount, strMemo from table_article";
		string[] strKeys = {"id", "strTitle", "strDate", "nTypeID", "strTypeName", "nCount", "strMemo"};
		try{
			using(SQLiteConnection conn = new SQLiteConnection(dbPath)){
				conn.Open();
				using(SQLiteCommand cmd = new SQLiteCommand(strQuery, conn)){
					/**/
					using(SQLiteDataReader dr = cmd.ExecuteReader()){
						int n = 0;
						while(dr.Read()){
							ListViewItem lvi = new ListViewItem(dr[strKeys[0]].ToString(), n);
							for(int i=1; i<strKeys.Length; i++){
								lvi.SubItems.Add(dr[strKeys[i]].ToString());
							}
							lv.Items.Add(lvi);
							n++;
						}
					}
				}
			}
		}catch(Exception ex){
			MessageBox.Show(ex.Message);
		}
	}

	public static void Main(string[] args){
		Application.Run(new lesson12_sqlite3_db_cs());
	}

}