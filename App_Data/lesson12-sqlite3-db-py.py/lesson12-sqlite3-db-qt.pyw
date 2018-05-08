#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Python 2.7
# lesson12-sqlite3-db-qt.pyw

from PyQt4 import QtGui, QtCore
import sys, sqlite3

conf__strCaptain ='lesson12-sqlite3-db-qt.pyw'

class _align():
	left = QtCore.Qt.AlignLeft
	center = QtCore.Qt.AlignCenter
	right = QtCore.Qt.AlignRight

conf_columns = {
	'keys':('id', 'strTitle', 'strDate', 'nTypeID', 'strTypeName', 'nCount', 'strMemo'),
	'title':('id', u'标题', u'时间', u'分类ID', u'分类', u'浏览数', u'备注'),
	'width':(20, 325, 125, 45, 85, 35, 115),
	'align':(_align.center, _align.left, _align.center, _align.center, _align.left, _align.center, _align.left)}


class lesson12_sqlite3_db_qt(QtGui.QMainWindow):
	def __init__(self):
		QtGui.QMainWindow.__init__(self)
		self.setWindowTitle(conf__strCaptain)
		self.resize(780, 450)

		self.objDisplay = QtGui.QTreeView()
		self.objDisplay.setRootIsDecorated(False)
		self.objDisplay.setAlternatingRowColors(True)
		self.objDisplay.setEditTriggers(QtGui.QAbstractItemView.NoEditTriggers)
		self.setCentralWidget(self.objDisplay)

		self.listData()

	def listData(self):
		nColumnCount = len( conf_columns['keys'] )
		model = QtGui.QStandardItemModel(0, nColumnCount, self)
		for i in xrange(nColumnCount):
			model.setHeaderData(i, QtCore.Qt.Horizontal, conf_columns['title'][i])
			model.horizontalHeaderItem(i).setTextAlignment(conf_columns['align'][i])
		conn = sqlite3.connect('../lesson12.sqlite3')
		cursor1 = conn.execute('select %s from table_article' % ', '.join(conf_columns['keys']) )
		n = 0
		for row in cursor1:
			model.insertRow(n)
			oItem = QtGui.QStandardItem( str(row[0]) )
			model.setItem(n, oItem)
			for i in xrange(1, nColumnCount):
				model.setData( model.index(n, i), row[i] )
				model.item(n, i).setTextAlignment(conf_columns['align'][i])
			n += 1
		conn.close()
		self.objDisplay.setModel( model )
		for i in xrange(nColumnCount):
			self.objDisplay.setColumnWidth(i, conf_columns['width'][i])
	

if __name__ == '__main__':
	app = QtGui.QApplication(sys.argv)
	ex = lesson12_sqlite3_db_qt()
	ex.show()
	app.exec_()
