#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Python 2.7
# sqlite3-db-01-insert-lesson12.py

import sqlite3

A_strQuery = (
	"insert into table_article(id, strTitle, strContent, strDate, nTypeID, strTypeName, nCount, strMemo) values(7, '这个村子 两千年来出了59个宰相 59个将军！', '这个村子 两千年来出了59个宰相 59个将军！...正蒙学堂古典书城古典君2016-10-21 13:01我要分享 3...[摘要]裴氏家族没有为子孙后代留下深宅大院和万贯家财，而是留下了自强不息的精神力量和修身自重的道德典范，这才是真正的、弥足珍贵的财富...', '2016-09-22 16:51:27', 6, 'HISTORY 历史', 0, 'Python写入')",
	"insert into table_article(id, strTitle, strContent, strDate, nTypeID, strTypeName, nCount, strMemo) values(8, 'HTTP访问的两种方式（HttpClient和HttpURLConnection）', 'HTTP访问的两种方式（HttpClient和HttpURLConnection）...(2013-01-25 09:52:17)...转载 标签： 杂谈 分类： android开发...使用HttpClient...使用HttpURLConnection...', '2016-10-16 05:47:02', 4, 'Java', 0, 'Python写入')",
)

conn = sqlite3.connect('../lesson12.sqlite3')
print 'sqlite3-db-01-insert-lesson12.py'

nCount = conn.execute('select count(1) from table_article where id in(7, 8)').fetchone()[0]
if nCount>0:
	print 'Exists ', nCount
else:
	for strQuery in A_strQuery:
		print strQuery.decode('utf-8')
		conn.execute(strQuery)

conn.commit()
conn.close()
