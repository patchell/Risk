// Occupy.cpp : implementation file
//

#include "stdafx.h"
#include "aihuman.h"
#include "Occupy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COccupy dialog


COccupy::COccupy(CWnd* pParent /*=NULL*/)
	: CDialog(COccupy::IDD, pParent)
{
	//{{AFX_DATA_INIT(COccupy)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pPrompt = 0;
	m_Armies = 0;
}


void COccupy::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COccupy)
	DDX_Control(pDX, IDC_STATIC_OCCUPY, m_Static_Prompt);
	DDX_Control(pDX, IDC_EDIT1, m_Edit_NArmies);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COccupy, CDialog)
	//{{AFX_MSG_MAP(COccupy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COccupy message handlers

BOOL COccupy::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if(m_pPrompt)
		m_Static_Prompt.SetWindowText(m_pPrompt);
	char *s = new char[256];
	sprintf(s,"%d",m_Armies);
	m_Edit_NArmies.SetWindowText(s);
	delete[] s;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COccupy::OnOK() 
{
	// TODO: Add extra validation here
	char *s = new char[256];
	m_Edit_NArmies.GetWindowText(s,256);
	m_Armies = atoi(s);
	delete[] s;
	CDialog::OnOK();
}
