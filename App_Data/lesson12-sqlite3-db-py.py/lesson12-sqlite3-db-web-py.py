#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Python 2.7
# sqlite3-db--lesson12--web.py

import web, sqlite3

conf__strTitle = 'sqlite3-db--lesson12--web.py'

urls = (
	'/', 'Index',
)

conf__strTemplates = ('''<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	<meta http-equiv="Content-Type" content="text/html;charset=utf-8" />
	<title>%s</title>
	<style type="text/css">#GridView1{font-size:12px;}</style>
</head>
<body>
	<h1>%s</h1>
	<div>
	<table cellspacing="0" cellpadding="3" rules="all" border="1" id="GridView1" style="border-collapse:collapse;">
		<tr>
			<th scope="col">id</th><th scope="col">标题</th><th scope="col">时间</th><th scope="col">分类ID</th><th scope="col">分类</th><th scope="col">浏览数</th><th scope="col">备注</th>
		</tr>
%s
	</table>
	</div>

	Exists %s

	<p><font color="red"><em style="font-size:16px;">总结 sqlite3 写入的时候不管什么情况下都必须 2016-01-01 00:00:00 的格式写，否则会出现非标准数据。至于显示规则，有些情况下系统会缩略输出，例如 2016-1-1 0:00:00 月、日、时 三部分显示可能会省去前缀0</em></font></p>

</body>
</html>
''',
u'''
		<tr>
			<td>%s</td><td>%s</td><td>%s</td><td align="center">%s</td><td>%s</td><td align="center">%s</td><td>%s</td>
		</tr>
''')

db = web.database(dbn='sqlite', db='../lesson12.sqlite3')

A_strKeys = ('id', 'strTitle', 'strDate', 'nTypeID', 'strTypeName', 'nCount', 'strMemo')
def _Conv(_s):
	return '' if _s==None else _s

class Index():
	def GET(self):
		nCount = int(db.query("select count(1) as c from table_article;")[0]['c'])
		data = db.query("select id, strTitle, strDate, nTypeID, strTypeName, nCount, strMemo from table_article;")

		return conf__strTemplates[0] % (conf__strTitle,	conf__strTitle,
			''.join([conf__strTemplates[1] % tuple( [_Conv(row[A_strKeys[i]]) for i in xrange(len(A_strKeys)) ] ) for row in data]).encode('utf-8'), nCount)

if __name__ == '__main__':
	web.application(urls, globals()).run()
