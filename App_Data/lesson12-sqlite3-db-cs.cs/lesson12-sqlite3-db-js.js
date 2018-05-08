import System;
import System.Drawing;
import System.Windows.Forms;
import System.Data.SQLite;
import Accessibility;

class lesson12_sqlite3_db_js extends Form{
	var _this = this;
	var lv = new ListView();

	protected override function get_DefaultSize(){
		return new System.Drawing.Size(800, 450);
	}

	function lesson12_sqlite3_db_js(){
		_this.set_Text("lesson12_sqlite3_db_js.js");
		_this.StartPosition = FormStartPosition.CenterScreen;

		lv.Dock = DockStyle.Fill;
		lv.View = View.Details;
		lv.GridLines = true;
		lv.FullRowSelect = true;

		initListData();

		_this.Controls.Add(lv);
	}

	function initListData(){
		lv.Clear();
		lv.Columns.Add("id", 25, HorizontalAlignment.Center);
		lv.Columns.Add("标题", 325, HorizontalAlignment.Left);
		lv.Columns.Add("时间", 130, HorizontalAlignment.Left);
		lv.Columns.Add("分类ID", 50, HorizontalAlignment.Center);
		lv.Columns.Add("分类", 85, HorizontalAlignment.Left);
		lv.Columns.Add("浏览数", 50, HorizontalAlignment.Center);
		lv.Columns.Add("备注", 115, HorizontalAlignment.Left);

		var dbPath = "Data Source=..\\lesson12.sqlite3";
		var strQuery = "select id, strTitle, strDate, nTypeID, strTypeName, nCount, strMemo from table_article";
		var strKeys = ["id", "strTitle", "strDate", "nTypeID", "strTypeName", "nCount", "strMemo"];
		try{
			var conn = new SQLiteConnection(dbPath);
			conn.Open();
			var cmd = new SQLiteCommand(strQuery, conn);
			var dr = cmd.ExecuteReader();
			var n = 0;
			while(dr.Read()){
				var lvi = new ListViewItem(dr[strKeys[0]].ToString(), n);
				for(var i=1; i<strKeys.length; i++){
					var _str = dr[strKeys[i]];
					_str = (_str==undefined ? '' : _str.ToString());
					lvi.SubItems.Add(_str);
				}
				lv.Items.Add(lvi);
				n++;
			}
			dr.Close();
			//cmd.Close();
			conn.Close();
			dr = null;
			conn = null;
		}catch(e){
			//MessageBox.Show('Exception:' + e);
		}
	}
}

Application.Run(new lesson12_sqlite3_db_js());