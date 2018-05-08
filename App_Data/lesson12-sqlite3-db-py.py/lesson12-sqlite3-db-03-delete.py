#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Python 2.7
# sqlite3-db-01-delete-lesson12.py

import sqlite3

conn = sqlite3.connect('../lesson12.sqlite3')
print 'sqlite3-db-01-delete-lesson12.py'

nCount = conn.execute('delete from table_article where id in(7, 8)')
conn.commit()
conn.close()

print 'Done.'