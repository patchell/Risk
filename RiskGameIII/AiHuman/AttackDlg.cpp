// AttackDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AiHuman.h"
#include "AttackDlg.h"
#include "HumanAiFuncs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAttackDlg dialog


CAttackDlg::CAttackDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAttackDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAttackDlg)
	//}}AFX_DATA_INIT
}


void CAttackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAttackDlg)
	DDX_Control(pDX, IDC_COMBO_ATTACK_STRAT, m_Combo_Strat);
	DDX_Control(pDX, IDC_CHECK_ATTACK_SURRENDER, m_Checkbox_Surrender);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAttackDlg, CDialog)
	//{{AFX_MSG_MAP(CAttackDlg)
	ON_BN_CLICKED(IDC_CHECK_ATTACK_SURRENDER, OnCheckAttackSurrender)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAttackDlg message handlers

BOOL CAttackDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char *s = new char[256];
	int i,n;
	n = m_NStrat/sizeof(STRATAGY);
	for(i=0;i<n;++i)
	{
		m_Combo_Strat.AddString(m_pStrat[i].Name);
	}
	this->SetFocus();
	SetWindowText(m_pTitle);
	delete [] s;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAttackDlg::OnOK() 
{
	// TODO: Add extra validation here
	m_Strattegy = m_Combo_Strat.GetCurSel();
	CDialog::OnOK();
}

void CAttackDlg::OnCheckAttackSurrender(void)
{
	m_Checkbox_Surrender.SetCheck(m_Checkbox_Surrender.GetCheck() ^ 0xffff);
}