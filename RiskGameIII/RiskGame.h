// RiskGame.h : main header file for the RISKGAME application
//

#if !defined(AFX_RISKGAME_H__7AB96602_1563_498E_B363_4C0F37A981DF__INCLUDED_)
#define AFX_RISKGAME_H__7AB96602_1563_498E_B363_4C0F37A981DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRiskGameApp:
// See RiskGame.cpp for the implementation of this class
//

class CRiskGameApp : public CWinApp
{
public:
	CRiskGameApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRiskGameApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CRiskGameApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RISKGAME_H__7AB96602_1563_498E_B363_4C0F37A981DF__INCLUDED_)
