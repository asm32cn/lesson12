// lesson12_sqlite3_db_mfc.h : main header file for the LESSON12_SQLITE3_DB_MFC application
//

#if !defined(AFX_LESSON12_SQLITE3_DB_MFC_H__8D11FEB2_BB69_47CA_99C0_F60D4746BE88__INCLUDED_)
#define AFX_LESSON12_SQLITE3_DB_MFC_H__8D11FEB2_BB69_47CA_99C0_F60D4746BE88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLesson12_sqlite3_db_mfcApp:
// See lesson12_sqlite3_db_mfc.cpp for the implementation of this class
//

class CLesson12_sqlite3_db_mfcApp : public CWinApp
{
public:
	CLesson12_sqlite3_db_mfcApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLesson12_sqlite3_db_mfcApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CLesson12_sqlite3_db_mfcApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LESSON12_SQLITE3_DB_MFC_H__8D11FEB2_BB69_47CA_99C0_F60D4746BE88__INCLUDED_)
