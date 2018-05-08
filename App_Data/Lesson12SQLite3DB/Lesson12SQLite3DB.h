// Lesson12SQLite3DB.h : main header file for the LESSON12SQLITE3DB application
//

#if !defined(AFX_LESSON12SQLITE3DB_H__C25F545C_FC81_4299_8ABA_F6B90627F4AB__INCLUDED_)
#define AFX_LESSON12SQLITE3DB_H__C25F545C_FC81_4299_8ABA_F6B90627F4AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLesson12SQLite3DBApp:
// See Lesson12SQLite3DB.cpp for the implementation of this class
//

class CLesson12SQLite3DBApp : public CWinApp
{
public:
	CLesson12SQLite3DBApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLesson12SQLite3DBApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLesson12SQLite3DBApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LESSON12SQLITE3DB_H__C25F545C_FC81_4299_8ABA_F6B90627F4AB__INCLUDED_)
