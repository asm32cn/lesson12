<%@ Page Language="C#" AutoEventWireup="true" CodeFile="RArticleM.aspx.cs" Inherits="lesson12.RArticleM" EnableViewState="false" %>

<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<meta http-equiv="Content-Type" content="text/html;charset=utf-8"/>
	<title>RArticleM.aspx</title>
	<style type="text/css">#GridView1{font-size:12px;}</style>
</head>
<body>

	<h1>RArticleM.aspx</h1>

	<form id="form1" runat="server">
	<asp:GridView ID="GridView1" runat="server" AutoGenerateColumns="false" CellPadding="3">
		<Columns>
			<asp:BoundField DataField="id" HeaderText="id" />
			<asp:BoundField DataField="strTitle" HeaderText="标题" />
			<asp:BoundField DataField="strDate" HeaderText="时间" />
			<asp:BoundField DataField="nTypeID" HeaderText="分类ID" ItemStyle-HorizontalAlign="Center" />
			<asp:BoundField DataField="strTypeName" HeaderText="分类" />
			<asp:BoundField DataField="nCount" HeaderText="浏览数" ItemStyle-HorizontalAlign="Center" />
			<asp:BoundField DataField="strMemo" HeaderText="备注" />
		</Columns>
	</asp:GridView>

	<asp:Literal id="LT_Display" runat="server" />

	<p><font color="red"><em style="font-size:16px;">总结 sqlite3 写入的时候不管什么情况下都必须 2016-01-01 00:00:00 的格式写，否则会出现非标准数据。至于显示规则，有些情况下系统会缩略输出，例如 2016-1-1 0:00:00 月、日、时 三部分显示可能会省去前缀0</em></font></p>

	</form>
</body>
</html>
