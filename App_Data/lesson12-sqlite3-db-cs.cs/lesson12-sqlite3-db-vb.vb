Imports System
Imports System.Drawing
Imports System.Windows.Forms
Imports System.Data
Imports System.Data.SQLite

Class lesson12_sqlite3_db_vb : Inherits Form
	Private Const strCaptain As String = "lesson12-sqlite3-db-vb.vb"
	Private lv As New ListView()

	Protected Overrides ReadOnly Property DefaultSize As Size
		Get
			Return New Size(800, 450)
		End Get
	End Property

	Sub New()
		Me.Text = strCaptain
		Me.StartPosition = FormStartPosition.CenterScreen

		lv.Dock = DockStyle.Fill
		lv.View = View.Details
		lv.GridLines = True
		lv.FullRowSelect = True

		initListData()

		Me.Controls.Add(lv)
	End Sub

	Private Sub initListData()
		lv.Clear()
		lv.Columns.Add("id", 25, HorizontalAlignment.Center)
		lv.Columns.Add("标题", 325, HorizontalAlignment.Left)
		lv.Columns.Add("时间", 130, HorizontalAlignment.Left)
		lv.Columns.Add("分类ID", 50, HorizontalAlignment.Center)
		lv.Columns.Add("分类", 85, HorizontalAlignment.Left)
		lv.Columns.Add("浏览数", 50, HorizontalAlignment.Center)
		lv.Columns.Add("备注", 115, HorizontalAlignment.Left)
		
		Dim dbPath As String = "Data Source=..\lesson12.sqlite3"
		Dim strQuery As String = "select id, strTitle, strDate, nTypeID, strTypeName, nCount, strMemo from table_article"
		Dim strKeys() As String = {"id", "strTitle", "strDate", "nTypeID", "strTypeName", "nCount", "strMemo"}
		Try
			Using conn As New SQLiteConnection(dbPath)
				conn.Open()
				Using cmd As New SQLiteCommand(strQuery, conn)
					Using dr As SQLiteDataReader = cmd.ExecuteReader()
						Dim n As Integer = 0
						While dr.Read()
							Dim lvi As New ListViewItem(dr(strKeys(0)).ToString(), 0)
							Dim i As Integer
							For i = 1 To strKeys.Length - 1
								lvi.SubItems.Add(  dr(strKeys(i)).ToString())
							Next
							lv.Items.Add(lvi)
							n += 1
						End While
					End Using
				End Using
			End Using
		Catch ex As Exception
			MsgBox(ex.Message)
		End Try
	End Sub

	Shared Sub Main()
		Application.Run(New lesson12_sqlite3_db_vb())
	End Sub
End Class
