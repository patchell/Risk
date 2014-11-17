// Rules.h : main header file for the RULES DLL
//

#if !defined(AFX_RULES_H__7D71AAC7_AD38_4EDB_B6BF_D75E6B526FB1__INCLUDED_)
#define AFX_RULES_H__7D71AAC7_AD38_4EDB_B6BF_D75E6B526FB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRulesApp
// See Rules.cpp for the implementation of this class
//

class CRulesApp : public CWinApp
{
public:
	CRulesApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRulesApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CRulesApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RULES_H__7D71AAC7_AD38_4EDB_B6BF_D75E6B526FB1__INCLUDED_)
