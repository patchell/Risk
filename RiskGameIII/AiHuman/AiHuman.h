// AiHuman.h : main header file for the AIHUMAN DLL
//

#if !defined(AFX_AIHUMAN_H__8CA06953_3AD0_4D44_8A13_05013398F365__INCLUDED_)
#define AFX_AIHUMAN_H__8CA06953_3AD0_4D44_8A13_05013398F365__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAiHumanApp
// See AiHuman.cpp for the implementation of this class
//

class CAiHumanApp : public CWinApp
{
public:
	CAiHumanApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAiHumanApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CAiHumanApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AIHUMAN_H__8CA06953_3AD0_4D44_8A13_05013398F365__INCLUDED_)
