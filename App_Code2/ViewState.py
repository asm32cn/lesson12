#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Python 2.7
#

import urllib, re, base64

strData = urllib.urlopen('http://localhost/lesson12/RArticleM.aspx').read()

strViewState = base64.b64decode(re.findall(r'<input type="hidden" name="__VIEWSTATE" id="__VIEWSTATE" value="(.*?)" />', strData)[0])

print [strViewState]
#print strViewState