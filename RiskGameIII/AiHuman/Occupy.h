#if !defined(AFX_OCCUPY_H__AFB4B075_E87B_4A80_9E4A_E242D82F0C20__INCLUDED_)
#define AFX_OCCUPY_H__AFB4B075_E87B_4A80_9E4A_E242D82F0C20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Occupy.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COccupy dialog

class COccupy : public CDialog
{
// Construction
public:
	char * m_pPrompt;
	int m_Armies;
	COccupy(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COccupy)
	enum { IDD = IDD_DIALOG_OCCUPY };
	CStatic	m_Static_Prompt;
	CEdit	m_Edit_NArmies;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COccupy)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COccupy)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OCCUPY_H__AFB4B075_E87B_4A80_9E4A_E242D82F0C20__INCLUDED_)
