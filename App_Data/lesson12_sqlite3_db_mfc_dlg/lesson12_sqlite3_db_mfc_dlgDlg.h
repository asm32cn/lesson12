// lesson12_sqlite3_db_mfc_dlgDlg.h : header file
//

#if !defined(AFX_LESSON12_SQLITE3_DB_MFC_DLGDLG_H__67D27ABF_8C4B_426A_959F_FD0188ECE852__INCLUDED_)
#define AFX_LESSON12_SQLITE3_DB_MFC_DLGDLG_H__67D27ABF_8C4B_426A_959F_FD0188ECE852__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CLesson12_sqlite3_db_mfc_dlgDlg dialog

class CLesson12_sqlite3_db_mfc_dlgDlg : public CDialog
{
// Construction
public:
	CLesson12_sqlite3_db_mfc_dlgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLesson12_sqlite3_db_mfc_dlgDlg)
	enum { IDD = IDD_LESSON12_SQLITE3_DB_MFC_DLG_DIALOG };
	CListCtrl	m_listDisplay;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLesson12_sqlite3_db_mfc_dlgDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL UTF8_GBK(CString& strText, char *szUtf8);
	void PA_DoReloadData();
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLesson12_sqlite3_db_mfc_dlgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LESSON12_SQLITE3_DB_MFC_DLGDLG_H__67D27ABF_8C4B_426A_959F_FD0188ECE852__INCLUDED_)
