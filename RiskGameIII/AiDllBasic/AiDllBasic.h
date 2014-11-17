// AiDllBasic.h : main header file for the AIDLLBASIC DLL
//

#if !defined(AFX_AIDLLBASIC_H__12E073C3_68BA_4513_8587_4E336EDBBF09__INCLUDED_)
#define AFX_AIDLLBASIC_H__12E073C3_68BA_4513_8587_4E336EDBBF09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "AiDllBasicRSC.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAiDllBasicApp
// See AiDllBasic.cpp for the implementation of this class
//

class CAiDllBasicApp : public CWinApp
{
public:
	CAiDllBasicApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAiDllBasicApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CAiDllBasicApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AIDLLBASIC_H__12E073C3_68BA_4513_8587_4E336EDBBF09__INCLUDED_)
