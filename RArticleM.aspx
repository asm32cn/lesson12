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
			<asp:BoundField DataField="strTitle" HeaderText="����" />
			<asp:BoundField DataField="strDate" HeaderText="ʱ��" />
			<asp:BoundField DataField="nTypeID" HeaderText="����ID" ItemStyle-HorizontalAlign="Center" />
			<asp:BoundField DataField="strTypeName" HeaderText="����" />
			<asp:BoundField DataField="nCount" HeaderText="�����" ItemStyle-HorizontalAlign="Center" />
			<asp:BoundField DataField="strMemo" HeaderText="��ע" />
		</Columns>
	</asp:GridView>

	<asp:Literal id="LT_Display" runat="server" />

	<p><font color="red"><em style="font-size:16px;">�ܽ� sqlite3 д���ʱ�򲻹�ʲô����¶����� 2016-01-01 00:00:00 �ĸ�ʽд���������ַǱ�׼���ݡ�������ʾ������Щ�����ϵͳ��������������� 2016-1-1 0:00:00 �¡��ա�ʱ ��������ʾ���ܻ�ʡȥǰ׺0</em></font></p>

	</form>
</body>
</html>
