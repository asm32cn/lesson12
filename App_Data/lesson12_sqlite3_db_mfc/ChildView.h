// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__C37F9D88_647B_4531_ACD2_C013FA8512CD__INCLUDED_)
#define AFX_CHILDVIEW_H__C37F9D88_647B_4531_ACD2_C013FA8512CD__INCLUDED_

#include "sqlite3.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChildView window

class CChildView : public CListView/*CWnd*/
{
// Construction
public:
	CChildView();
	DECLARE_DYNCREATE(CChildView)

// Attributes
public:


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildView)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL UTF8_GBK(CString& str, char * szUtf8);
	BOOL NextRow(sqlite3_stmt* stmt);
	virtual ~CChildView();

	// Generated message map functions
protected:
	void PA_DoReloadData();
	void PA_DoViewInitialize();
	//{{AFX_MSG(CChildView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__C37F9D88_647B_4531_ACD2_C013FA8512CD__INCLUDED_)
