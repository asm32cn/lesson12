// lesson12_sqlite3_db_mfc_dlg.h : main header file for the LESSON12_SQLITE3_DB_MFC_DLG application
//

#if !defined(AFX_LESSON12_SQLITE3_DB_MFC_DLG_H__9964BDF7_54C3_4A90_B161_A4C35F299330__INCLUDED_)
#define AFX_LESSON12_SQLITE3_DB_MFC_DLG_H__9964BDF7_54C3_4A90_B161_A4C35F299330__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLesson12_sqlite3_db_mfc_dlgApp:
// See lesson12_sqlite3_db_mfc_dlg.cpp for the implementation of this class
//

class CLesson12_sqlite3_db_mfc_dlgApp : public CWinApp
{
public:
	CLesson12_sqlite3_db_mfc_dlgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLesson12_sqlite3_db_mfc_dlgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLesson12_sqlite3_db_mfc_dlgApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LESSON12_SQLITE3_DB_MFC_DLG_H__9964BDF7_54C3_4A90_B161_A4C35F299330__INCLUDED_)
