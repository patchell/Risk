#if !defined(AFX_CHOSEDLG_H__01665E14_F160_47AE_B839_3EFF6742A58E__INCLUDED_)
#define AFX_CHOSEDLG_H__01665E14_F160_47AE_B839_3EFF6742A58E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChoseDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChoseDlg dialog

class CChoseDlg : public CDialog
{
// Construction
public:
	CChoseDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChoseDlg)
	enum { IDD = IDD_DIALOG_CHOOSE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChoseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChoseDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOSEDLG_H__01665E14_F160_47AE_B839_3EFF6742A58E__INCLUDED_)
