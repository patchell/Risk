#if !defined(AFX_DEFENDDLG_H__BD952F88_74FA_4260_A57D_B23D40352760__INCLUDED_)
#define AFX_DEFENDDLG_H__BD952F88_74FA_4260_A57D_B23D40352760__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DefendDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDefendDlg dialog

class CDefendDlg : public CDialog
{
// Construction
public:
	CDefendDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDefendDlg)
	enum { IDD = IDD_DIALOG_DEFEND };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDefendDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDefendDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEFENDDLG_H__BD952F88_74FA_4260_A57D_B23D40352760__INCLUDED_)
