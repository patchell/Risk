// PlaceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AiHuman.h"
#include "Player.h"
#include "PlaceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlaceDlg dialog


CPlaceDlg::CPlaceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlaceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPlaceDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPlaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlaceDlg)
	DDX_Control(pDX, IDC_EDIT_PLACE_ARMIES, m_Edit_Armies);
	DDX_Control(pDX, IDC_STATIC_PLACE_ARMIES, m_Static_Armies);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlaceDlg, CDialog)
	//{{AFX_MSG_MAP(CPlaceDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlaceDlg message handlers

BOOL CPlaceDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char *s = new char[256];
	m_Edit_Armies.SetWindowText("1");
	sprintf(s,"%d",m_pPlayer->GetArmies()->GetNumber());
	m_Static_Armies.SetWindowText(s);
	delete[] s;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPlaceDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
