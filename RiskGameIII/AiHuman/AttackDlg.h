#if !defined(AFX_ATTACKDLG_H__5523D2F3_8FF5_4912_AD37_9A95EE923005__INCLUDED_)
#define AFX_ATTACKDLG_H__5523D2F3_8FF5_4912_AD37_9A95EE923005__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AttackDlg.h : header file
//
#include "TheRules.h"

/////////////////////////////////////////////////////////////////////////////
// CAttackDlg dialog

class CAttackDlg : public CDialog
{
// Construction
public:
	char * m_pTitle;
	int m_NStrat;			//number of stratagies
	STRATAGY * m_pStrat;	//pointer to array of strategys
	int m_Surrender;
	int m_Strattegy;
	CAttackDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAttackDlg)
	enum { IDD = IDD_DIALOG_ATTACK };
	CComboBox	m_Combo_Strat;
	CButton	m_Checkbox_Surrender;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAttackDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAttackDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnCheckAttackSurrender();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ATTACKDLG_H__5523D2F3_8FF5_4912_AD37_9A95EE923005__INCLUDED_)
