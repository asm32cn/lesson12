#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Python 2.7
# sqlite3-db-lesson12-tk.pyw

from Tkinter import *
import sqlite3, ttk

bstrIconData = 'R0lGODlhEAAQAJEAAAAAAMDAwAAAgP///yH5BAUUAAAALAAAAAAQABAAAAIuhI+jyKYCR3MDWtlq1Dhd' \
	'K3QHB4pOVE6VJgTmGV4TsG4zHS437e5I76MEhcNhAQA7'

conf_columns = {
	'keys':('id', 'strTitle', 'strDate', 'nTypeID', 'strTypeName', 'nCount', 'strMemo'),
	'title':('id', u'标题', u'时间', u'分类ID', u'分类', u'浏览数', u'备注'),
	'width':(20, 325, 125, 45, 85, 35, 115),
	'anchor':('center', 'w', 'center', 'center', 'w', 'center', 'w')}

def _Conv(_s):
	return '' if _s==None else _s

class sqlite3_db_lesson12_tk(Tk):
	def __init__(self):
		Tk.__init__(self)
		self.title('sqlite3-db--lesson12-tk.py')
		self.geometry('800x450+%s+%s' % (self.winfo_screenwidth()/2-400, self.winfo_screenheight()/2-225))

		self.tk.call('wm', 'iconphoto', self._w, PhotoImage(data=bstrIconData))

		objListview = ttk.Treeview(self, columns=conf_columns['keys'], show='headings')
		objListview.pack(expand=YES, fill=BOTH)
		for i in xrange(7):
			strColumnName = '#%s' % (i+1)
			objListview.column(strColumnName, width=conf_columns['width'][i], anchor=conf_columns['anchor'][i])
			objListview.heading(strColumnName, text=conf_columns['title'][i], anchor=conf_columns['anchor'][i])
		conn = sqlite3.connect('../lesson12.sqlite3')
		cursor1 = conn.execute('select %s from table_article' % ', '.join(conf_columns['keys']))
		n = 0
		for row in cursor1:
			objListview.insert('', n, values=[_Conv(row[i]) for i in xrange(7)])
			n += 1
		conn.close()

if __name__ == '__main__':
	sqlite3_db_lesson12_tk()
	mainloop()
