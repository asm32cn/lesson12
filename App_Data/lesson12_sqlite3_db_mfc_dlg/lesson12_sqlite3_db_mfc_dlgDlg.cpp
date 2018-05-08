// lesson12_sqlite3_db_mfc_dlgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "lesson12_sqlite3_db_mfc_dlg.h"
#include "lesson12_sqlite3_db_mfc_dlgDlg.h"
#include "sqlite3.h"

#define VK_ENTER 0x0D

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLesson12_sqlite3_db_mfc_dlgDlg dialog

CLesson12_sqlite3_db_mfc_dlgDlg::CLesson12_sqlite3_db_mfc_dlgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLesson12_sqlite3_db_mfc_dlgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLesson12_sqlite3_db_mfc_dlgDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLesson12_sqlite3_db_mfc_dlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLesson12_sqlite3_db_mfc_dlgDlg)
	DDX_Control(pDX, IDC_DISPLAY, m_listDisplay);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLesson12_sqlite3_db_mfc_dlgDlg, CDialog)
	//{{AFX_MSG_MAP(CLesson12_sqlite3_db_mfc_dlgDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLesson12_sqlite3_db_mfc_dlgDlg message handlers

BOOL CLesson12_sqlite3_db_mfc_dlgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_listDisplay.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listDisplay.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	m_listDisplay.InsertColumn(0, "ID", LVCFMT_LEFT, 30);
	m_listDisplay.InsertColumn(1, "标题", LVCFMT_LEFT, 325);
	m_listDisplay.InsertColumn(2, "时间", LVCFMT_LEFT, 130);
	m_listDisplay.InsertColumn(3, "分类ID", LVCFMT_CENTER, 55);
	m_listDisplay.InsertColumn(4, "分类", LVCFMT_LEFT, 85);
	m_listDisplay.InsertColumn(5, "浏览数", LVCFMT_CENTER, 55);
	m_listDisplay.InsertColumn(6, "备注", LVCFMT_LEFT, 115);

	PA_DoReloadData();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLesson12_sqlite3_db_mfc_dlgDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLesson12_sqlite3_db_mfc_dlgDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CLesson12_sqlite3_db_mfc_dlgDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CRect rect;
	GetClientRect(&rect);
	//CString s;
	//s.Format("%d %d %d %d", rect.top, rect.left, rect.right, rect.bottom);
	//AfxMessageBox(s);
	CWnd* hWnd = GetDlgItem(IDC_DISPLAY);
	if(hWnd){
		hWnd->MoveWindow(rect, TRUE);
	}else{
		//AfxMessageBox("bin");
	}
}

void CLesson12_sqlite3_db_mfc_dlgDlg::PA_DoReloadData()
{
	sqlite3* db = NULL;
	sqlite3_stmt* stmt = NULL;
	char* pErrMsg = NULL;
	int rc = 0;
	CString s;
	
	rc = sqlite3_open("..\\lesson12.sqlite3", &db);
	if(rc != SQLITE_OK){
		s.Format("不能代开数据库: %s", sqlite3_errmsg(db));
		return;
	}
	char szQuery[] = "select id, strTitle, strDate, nTypeID, strTypeName, nCount, strMemo from table_article";
	int nRow = 0;
	CString strText;
	rc = sqlite3_prepare(db, szQuery, -1, &stmt, 0);
	if(rc == SQLITE_OK){
		int nFields = sqlite3_column_count(stmt);
		while( (rc = sqlite3_step(stmt)) == SQLITE_ROW ){
			strText.Format("%s", sqlite3_column_text(stmt, 0));
			int nItemID = m_listDisplay.InsertItem(nRow, strText);
			for(INT i=1; i<nFields; i++){
				const unsigned char* pszText = sqlite3_column_text(stmt, i);
				if( UTF8_GBK(strText, (char *)pszText) == FALSE) strText = "";
				m_listDisplay.SetItemText(nItemID, i, strText);
			}
			nRow++;
		}
	}else{
		stmt = NULL;
	}
	sqlite3_close(db);
}

BOOL CLesson12_sqlite3_db_mfc_dlgDlg::UTF8_GBK(CString &strText, char *szUtf8)
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

BOOL CLesson12_sqlite3_db_mfc_dlgDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN && (pMsg->wParam==VK_ESCAPE || pMsg->wParam==VK_ENTER)){
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
