#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Python 2.7
# sqlite3-db-01-select-lesson12.py

import sqlite3

def print_row(row):
	print '\t'.join([i if isinstance(i, unicode) else str(i) for i in row])
	#print [i if isinstance(i, str) else str(i) for i in row]
	#print [type(i) for i in row]

conn = sqlite3.connect('../lesson12.sqlite3')
print 'sqlite3-db-01-select-lesson12.py'

#cursor1 = conn.execute('select id, strTitle, strDate, nTypeID, strTypeName, nCount from table_article')
cursor1 = conn.execute('select id, strDate, nTypeID, nCount, strTypeName, strTitle from table_article;')
for row in cursor1:
	print_row( row )

conn.close()
