#if !defined(AFX_AIPARAMSDLG_H__83661FEB_3646_4F52_83CF_B2F3282272CE__INCLUDED_)
#define AFX_AIPARAMSDLG_H__83661FEB_3646_4F52_83CF_B2F3282272CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AiParamsDLG.h : header file
//
#include "AiDllBasicRSC.h"

/////////////////////////////////////////////////////////////////////////////
// CAiParamsDLG dialog

class CAiParamsDLG : public CDialog
{
// Construction
public:
	CAiParamsDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAiParamsDLG)
	enum { IDD = IDD_DIALOG_AIPARAMS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAiParamsDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAiParamsDLG)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern "C" void RunParamDLG(void);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined(AFX_AIPARAMSDLG_H__83661FEB_3646_4F52_83CF_B2F3282272CE__INCLUDED_)
