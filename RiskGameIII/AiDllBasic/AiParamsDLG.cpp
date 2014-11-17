// AiParamsDLG.cpp : implementation file
//

#include "stdafx.h"
#include "AiDllBasic.h"
#include "AiParamsDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAiParamsDLG dialog


CAiParamsDLG::CAiParamsDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CAiParamsDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAiParamsDLG)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAiParamsDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAiParamsDLG)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAiParamsDLG, CDialog)
	//{{AFX_MSG_MAP(CAiParamsDLG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAiParamsDLG message handlers

BOOL CAiParamsDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

extern "C" void RunParamDLG(void)
{
	CAiParamsDLG Dlg;

	Dlg.DoModal();
}