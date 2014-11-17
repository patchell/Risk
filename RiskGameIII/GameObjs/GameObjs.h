// GameObjs.h : main header file for the GAMEOBJS DLL
//

#if !defined(AFX_GAMEOBJS_H__AFFF4088_FA9A_45CB_9876_B0237E8C8F66__INCLUDED_)
#define AFX_GAMEOBJS_H__AFFF4088_FA9A_45CB_9876_B0237E8C8F66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGameObjsApp
// See GameObjs.cpp for the implementation of this class
//

class CGameObjsApp : public CWinApp
{
public:
	CGameObjsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGameObjsApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CGameObjsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GAMEOBJS_H__AFFF4088_FA9A_45CB_9876_B0237E8C8F66__INCLUDED_)
