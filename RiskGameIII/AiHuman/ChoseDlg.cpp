// ChoseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AiHuman.h"
#include "ChoseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChoseDlg dialog


CChoseDlg::CChoseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChoseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChoseDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CChoseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChoseDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChoseDlg, CDialog)
	//{{AFX_MSG_MAP(CChoseDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChoseDlg message handlers

BOOL CChoseDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChoseDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
