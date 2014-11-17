#if !defined(AFX_AIPARAMEDITDLG_H__180010DD_7C28_479A_B520_C08B9F6A3CC7__INCLUDED_)
#define AFX_AIPARAMEDITDLG_H__180010DD_7C28_479A_B520_C08B9F6A3CC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AiParamEditDlg.h : header file
//
#include "AIFuncs.h"
/////////////////////////////////////////////////////////////////////////////
// CAiParamEditDlg dialog

class CAiParamEditDlg : public CDialog
{
// Construction
public:
	AIPARAMS * m_pParams;
	CAiParamEditDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAiParamEditDlg)
	enum { IDD = IDD_DIALOG_AIPARAMS };
	CEdit	m_Edit_AttackValWt;
	CEdit	m_Edit_EnemyValueWt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAiParamEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAiParamEditDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AIPARAMEDITDLG_H__180010DD_7C28_479A_B520_C08B9F6A3CC7__INCLUDED_)
