// AiParamEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "riskgame.h"
#include "AiParamEditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAiParamEditDlg dialog


CAiParamEditDlg::CAiParamEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAiParamEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAiParamEditDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAiParamEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAiParamEditDlg)
	DDX_Control(pDX, IDC_EDIT_AIPARM_PLACE_ATTR_WT, m_Edit_AttackValWt);
	DDX_Control(pDX, IDC_EDIT_AIPARM_PLACE_ENME_WT, m_Edit_EnemyValueWt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAiParamEditDlg, CDialog)
	//{{AFX_MSG_MAP(CAiParamEditDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAiParamEditDlg message handlers

void CAiParamEditDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CWnd *wC;
	char *s = new char[256];

	///locate control that has gocus
	wC = GetFocus();
	/// Get the ID of that control
	int id = wC->GetDlgCtrlID();
	switch(id)							///parse the id
	{
		case IDOK:
			m_Edit_AttackValWt.GetWindowText(s,255);
			m_pParams->PlaceAttackTerrWeight = atoi(s);
			m_Edit_EnemyValueWt.GetWindowText(s,255);
			m_pParams->PlaceEnemyTerrWeight = atoi(s);
			CDialog::OnOK();
			break;
	}
	delete[] s;
}

BOOL CAiParamEditDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char *s = new char[256];
	sprintf(s,"%d",m_pParams->PlaceAttackTerrWeight);
	m_Edit_AttackValWt.SetWindowText(s);
	sprintf(s,"%d",m_pParams->PlaceEnemyTerrWeight);
	m_Edit_EnemyValueWt.SetWindowText(s);
	delete[] s;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
