// Lesson12SQLite3DBDlg.h : header file
//

#if !defined(AFX_LESSON12SQLITE3DBDLG_H__52A13B28_5218_4331_90C4_417A69F7541F__INCLUDED_)
#define AFX_LESSON12SQLITE3DBDLG_H__52A13B28_5218_4331_90C4_417A69F7541F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CLesson12SQLite3DBDlg dialog

class CLesson12SQLite3DBDlg : public CDialog
{
// Construction
public:
	CLesson12SQLite3DBDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLesson12SQLite3DBDlg)
	enum { IDD = IDD_LESSON12SQLITE3DB_DIALOG };
	CListCtrl	m_listDisplay;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLesson12SQLite3DBDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL UTF8_GBK(CString &strText, char *szUtf8);
	void PA_DoReloadData();
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLesson12SQLite3DBDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LESSON12SQLITE3DBDLG_H__52A13B28_5218_4331_90C4_417A69F7541F__INCLUDED_)
