#if !defined(AFX_PLACEDLG_H__BC6ECACD_BE93_4766_96CD_AC784E5EE5CE__INCLUDED_)
#define AFX_PLACEDLG_H__BC6ECACD_BE93_4766_96CD_AC784E5EE5CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlaceDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPlaceDlg dialog

class CPlaceDlg : public CDialog
{
// Construction
public:
	CPlayer * m_pPlayer;
	CPlaceDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPlaceDlg)
	enum { IDD = IDD_DIALOG_PLACE };
	CEdit	m_Edit_Armies;
	CStatic	m_Static_Armies;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlaceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPlaceDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLACEDLG_H__BC6ECACD_BE93_4766_96CD_AC784E5EE5CE__INCLUDED_)
