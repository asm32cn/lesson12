// Lesson12SQLite3DBDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Lesson12SQLite3DB.h"
#include "Lesson12SQLite3DBDlg.h"
#include "DbSQLite.h"

#define VK_ENTER 0x0D

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLesson12SQLite3DBDlg dialog

CLesson12SQLite3DBDlg::CLesson12SQLite3DBDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLesson12SQLite3DBDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLesson12SQLite3DBDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLesson12SQLite3DBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLesson12SQLite3DBDlg)
	DDX_Control(pDX, IDC_DISPLAY, m_listDisplay);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLesson12SQLite3DBDlg, CDialog)
	//{{AFX_MSG_MAP(CLesson12SQLite3DBDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLesson12SQLite3DBDlg message handlers

BOOL CLesson12SQLite3DBDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_listDisplay.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

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

void CLesson12SQLite3DBDlg::OnPaint() 
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
HCURSOR CLesson12SQLite3DBDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CLesson12SQLite3DBDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CRect rect;
	GetClientRect(&rect);
	CWnd* pWnd = GetDlgItem(IDC_DISPLAY);
	if(pWnd){
		pWnd->MoveWindow(rect, TRUE);
	}
	
}

void CLesson12SQLite3DBDlg::PA_DoReloadData()
{
	CString dbPath = "..\\lesson12.sqlite3";
	CDbSQLite sqlite;
	BOOL rc;
	rc = sqlite.Open(dbPath);
	if(!rc){
		AfxMessageBox("打开数据库错误.");
	}
	CSqlStatement* stmt = sqlite.Statement("select  id, strTitle, strDate, nTypeID, strTypeName, nCount, strMemo from table_article");
	if(stmt != NULL){
		m_listDisplay.DeleteAllItems();
		int nFields = stmt->Fields(); // 获得数据表列数
		int nCol = 0;
		int nRow = 0;
		CString szText;
		while(stmt->NextRow()){
			szText = stmt->ValueString(0);
			m_listDisplay.InsertItem(nRow, szText);
			for(nCol=1; nCol<nFields; nCol++){
				UTF8_GBK(szText, (char *)stmt->ValueString(nCol));
				m_listDisplay.SetItemText(nRow, nCol, szText);
			}
			nRow++;
		}
	}else{
		//AfxMessageBox("empty");
	}
	delete stmt;
}

BOOL CLesson12SQLite3DBDlg::UTF8_GBK(CString &strText, char *szUtf8)
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

BOOL CLesson12SQLite3DBDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN && (pMsg->wParam==VK_ESCAPE || pMsg->wParam==VK_ENTER)){
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
