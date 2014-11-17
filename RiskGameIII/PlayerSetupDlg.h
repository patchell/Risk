#if !defined(AFX_PLAYERSETUPDLG_H__311A6DD7_F891_4B09_907B_AB7824DADD4D__INCLUDED_)
#define AFX_PLAYERSETUPDLG_H__311A6DD7_F891_4B09_907B_AB7824DADD4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlayerSetupDlg.h : header file
//

#include "HorzScrollBar.h"
#include "Player.h"
#include "StaticBitmap.h"
#include "AiList.h"
#include "AiThread.h"
#include "RiskGameDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CPlayerSetupDlg dialog

class CPlayerSetupDlg : public CDialog
{
// Construction
public:
	CRiskGameDoc * m_pDoc;
	int m_InitArmies;
	void NewPlayer(int index);
	CAiList * pAiList;
	int m_TotalPlayers;
	int m_CurrentPlayerIndex;
	int m_CurrentPlayer;
	CPlayerSetupDlg(CWnd* pParent = NULL);   // standard constructor
	CAiThread **m_ppAiPlayers;
// Dialog Data
	//{{AFX_DATA(CPlayerSetupDlg)
	enum { IDD = IDD_SETUP_PLAYERS_DLG };
	CEdit	m_Edit_InitArmies;
	CListBox	m_List_Player_Type;
	CStaticBitmap	m_Static_Color;
	CHorzScrollBar	m_SB_CurPlayer;
	CStatic	m_Static_CurPlayer;
	CEdit	m_Edit_TotalPlayers;
	CEdit	m_Edit_PlayerName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayerSetupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	LRESULT OnSBTotPlayer(WPARAM wparam, LPARAM lparam);

	// Generated message map functions
	//{{AFX_MSG(CPlayerSetupDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeListPlayerType();
	afx_msg void OnStaticPlayerColor();
	afx_msg void OnButtonSetupplayersEditAiParams();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYERSETUPDLG_H__311A6DD7_F891_4B09_907B_AB7824DADD4D__INCLUDED_)
