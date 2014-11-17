// DefendDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AiHuman.h"
#include "DefendDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDefendDlg dialog


CDefendDlg::CDefendDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDefendDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDefendDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDefendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDefendDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDefendDlg, CDialog)
	//{{AFX_MSG_MAP(CDefendDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDefendDlg message handlers

BOOL CDefendDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDefendDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
