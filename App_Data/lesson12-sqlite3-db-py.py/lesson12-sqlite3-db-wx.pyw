#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Python 2.7
# lesson12-sqlite3-db-wx.pyw

import wx, sqlite3
from wx import ImageFromStream, BitmapFromImage, EmptyIcon
import cStringIO, base64

conf__strCaptain = 'lesson12-sqlite3-db-wx.pyw'

bstrIconData = 'R0lGODlhEAAQAJEAAAAAAMDAwAAAgP///yH5BAUUAAAALAAAAAAQABAAAAIuhI+jyKYCR3MDWtlq1Dhd' \
	'K3QHB4pOVE6VJgTmGV4TsG4zHS437e5I76MEhcNhAQA7'

class _align():
	left = wx.LIST_FORMAT_LEFT
	center = wx.LIST_FORMAT_CENTER
	right = wx.LIST_FORMAT_RIGHT

conf_columns = {
	'keys':('id', 'strTitle', 'strDate', 'nTypeID', 'strTypeName', 'nCount', 'strMemo'),
	'title':('id', u'标题', u'时间', u'分类ID', u'分类', u'浏览数', u'备注'),
	'width':(25, 320, 130, 55, 85, 55, 115),
	'align':(_align.center, _align.left, _align.center, _align.center, _align.left, _align.center, _align.left)}

class lesson12_sqlite3_db_wx(wx.Frame):
	def __init__(self):
		wx.Frame.__init__(self, None, title=conf__strCaptain, size=(800, 450) )
		self.SetIcon( self.getIcon() )
		self.Center()

		self.listDisplay = wx.ListCtrl(self, size=(-1, -1), style=wx.LC_REPORT)

		self.listData()

	def listData(self):
		nColumnCount = len( conf_columns['keys'] )
		for i in xrange(nColumnCount):
			self.listDisplay.InsertColumn(i, conf_columns['title'][i], conf_columns['align'][i], conf_columns['width'][i])
		conn = sqlite3.connect('../lesson12.sqlite3')
		cursor1 = conn.execute('select %s from table_article' % ', '.join(conf_columns['keys']))
		n = 0
		for row in cursor1:
			nItemID = self.listDisplay.InsertStringItem(n, str(row[0]))
			for i in xrange(1, nColumnCount):
				self.listDisplay.SetStringItem(nItemID, i, self._Conv(row[i]))
			n += 1
		conn.close()

	def _Conv(self, s):
		if s==None:
			return ''
		elif isinstance(s, (int)):
			return str(s)
		else:
			return s

	def getIcon(self):
		icon = EmptyIcon()
		icon.CopyFromBitmap( BitmapFromImage( ImageFromStream( cStringIO.StringIO( base64.b64decode( bstrIconData ) ) ) ) )
		return icon

if __name__ == '__main__':
	app = wx.App()
	ex = lesson12_sqlite3_db_wx()
	ex.Show()
	app.MainLoop()
