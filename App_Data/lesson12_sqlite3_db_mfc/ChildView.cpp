// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "lesson12_sqlite3_db_mfc.h"
#include "ChildView.h"
#include "sqlite3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildView

CChildView::CChildView()
{

}

CChildView::~CChildView()
{
}

IMPLEMENT_DYNCREATE(CChildView, CListView)

BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
//	if (!CWnd::PreCreateWindow(cs))
//		return FALSE;
	return CListView::PreCreateWindow(cs);

	/*
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;*/
}




int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd ::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	PA_DoViewInitialize();
	
	return 0;
}

void CChildView::PA_DoViewInitialize()
{
	CListCtrl& m_listDisplay = GetListCtrl();
	m_listDisplay.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listDisplay.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	m_listDisplay.InsertColumn(0, "ID", LVCFMT_LEFT, 25);
	m_listDisplay.InsertColumn(1, "标题", LVCFMT_LEFT, 325);
	m_listDisplay.InsertColumn(2, "时间", LVCFMT_LEFT, 130);
	m_listDisplay.InsertColumn(3, "分类ID", LVCFMT_CENTER, 55);
	m_listDisplay.InsertColumn(4, "分类", LVCFMT_LEFT, 85);
	m_listDisplay.InsertColumn(5, "浏览数", LVCFMT_CENTER, 55);
	m_listDisplay.InsertColumn(6, "备注", LVCFMT_LEFT, 115);

	PA_DoReloadData();
}

void CChildView::PA_DoReloadData()
{
	CListCtrl& m_listDisplay = GetListCtrl();
	/**/
	sqlite3 *db = NULL;
	char *errMsg = NULL;
	sqlite3_stmt* stmt = NULL;
	int rc = 0;
	CString s;

	rc = sqlite3_open("..\\lesson12.sqlite3", &db);
	if(rc != SQLITE_OK){
		s.Format("Can't open database: %s", sqlite3_errmsg(db));
		AfxMessageBox(s);
		return;
	}
	char szQuery[] = "select id, strTitle, strDate, nTypeID, strTypeName, nCount, strMemo from table_article";
	INT nRow = 0;
	CString strText;
	rc = sqlite3_prepare(db, szQuery, -1, &stmt, 0);
	if(rc == SQLITE_OK){
		INT nFields = sqlite3_column_count(stmt);
		while( NextRow(stmt) ){
			strText.Format("%s", sqlite3_column_text(stmt, 0));
			INT nItemID = m_listDisplay.InsertItem(nRow, strText);
			for(INT i=1; i<nFields; i++){
				const unsigned char* pszText = sqlite3_column_text(stmt, i);
				if( UTF8_GBK(strText, (char *)pszText) == FALSE ) strText = "";
				m_listDisplay.SetItemText(nItemID, i, strText);
			}
			nRow++;
		}
	}else{
		stmt = NULL;
	}
	sqlite3_close(db);
}

BOOL CChildView::NextRow(sqlite3_stmt* stmt)
{
   CString szError;
   int rc = sqlite3_step(stmt);

   if ( rc == SQLITE_ROW )
   {
      return true;
   }

   if ( rc == SQLITE_DONE )
   {
      sqlite3_reset(stmt);
      return false;
   }
   else if ( rc == SQLITE_MISUSE )
   {
      szError = _T("CSqlStatement::NextRow SQLITE_MISUSE");
   }
   else if ( rc == SQLITE_BUSY )
   {
      szError = _T("CSqlStatement::NextRow SQLITE_BUSY");
   }
   else if ( rc == SQLITE_ERROR )
   {
      szError = _T("CSqlStatement::NextRow SQLITE_ERROR");
   }

   AfxMessageBox(szError);
   return false;
}

BOOL CChildView::UTF8_GBK(CString& strText, char *szUtf8)
{
	if(NULL==szUtf8) return FALSE;
	int nLen = MultiByteToWideChar( CP_UTF8, 0,	szUtf8, -1, NULL,0 );
	wchar_t* pUnicode = new wchar_t[nLen+1];
	if(NULL==pUnicode) return FALSE;
	MultiByteToWideChar( CP_UTF8, 0, szUtf8, -1, (LPWSTR)pUnicode, nLen );
	strText = pUnicode;
	strText.Format("%s", strText);
	return TRUE;
}
