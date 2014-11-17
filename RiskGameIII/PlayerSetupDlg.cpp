// PlayerSetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RiskGame.h"
#include "PlayerSetupDlg.h"
#include "WinMsg.h"
#include "RiskUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlayerSetupDlg dialog


CPlayerSetupDlg::CPlayerSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlayerSetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPlayerSetupDlg)
	//}}AFX_DATA_INIT
	m_InitArmies = 100;
	m_CurrentPlayer = 0;
}


void CPlayerSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlayerSetupDlg)
	DDX_Control(pDX, IDC_EDIT_PLAYER_INITARMIES, m_Edit_InitArmies);
	DDX_Control(pDX, IDC_LIST_PLAYER_TYPE, m_List_Player_Type);
	DDX_Control(pDX, IDC_STATIC_PLAYER_COLOR, m_Static_Color);
	DDX_Control(pDX, IDC_SCROLLBAR_PLAYER_CUR, m_SB_CurPlayer);
	DDX_Control(pDX, IDC_STATIC_PLAYER_CUR, m_Static_CurPlayer);
	DDX_Control(pDX, IDC_EDIT_PLAYER_TOTAL, m_Edit_TotalPlayers);
	DDX_Control(pDX, IDC_EDIT_PLAYER_NAME, m_Edit_PlayerName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlayerSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CPlayerSetupDlg)
	ON_LBN_SELCHANGE(IDC_LIST_PLAYER_TYPE, OnSelchangeListPlayerType)
	ON_BN_CLICKED(IDC_STATIC_PLAYER_COLOR, OnStaticPlayerColor)
	ON_BN_CLICKED(IDC_BUTTON_SETUPPLAYERS_EDIT_AI_PARAMS, OnButtonSetupplayersEditAiParams)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_SBTOTAL,OnSBTotPlayer)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayerSetupDlg message handlers

BOOL CPlayerSetupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char *s = new char[256];
	sprintf(s,"%d",m_InitArmies);
	m_Edit_InitArmies.SetWindowText(s);
	m_Static_Color.Init();
	this->m_Edit_TotalPlayers.SetWindowText("4");
	this->m_SB_CurPlayer.SetScrollRange(0,3);
	this->m_SB_CurPlayer.SetDisplayText(&this->m_Static_CurPlayer);
	m_SB_CurPlayer.SetScrollPos(0);
	m_SB_CurPlayer.SetActionMessage(this->m_hWnd,WM_SBTOTAL);
	//------------------------------------
	// init dialog with player info, if any
	//------------------------------------
	CPlayer *pL;
	pL = this->m_ppAiPlayers[0]->GetPlayer();
	m_Edit_PlayerName.SetWindowText(pL->GetName() );
	m_Static_Color.SetColor(pL->m_Color);
	sprintf(s,"%d",m_TotalPlayers);
	m_Edit_TotalPlayers.SetWindowText(s);
	GetWindowText(s,256);
	sprintf(&s[strlen(s)],":%s",pL->GetName());
	SetWindowText(s);

	CAiList *pAL = pAiList;
	while(pAL)
	{
		this->m_List_Player_Type.AddString((*(char *(*)(void))pAL->GetFuncs(AIFUNC_NAME))());
		pAL = pAL->GetNext();
	}
	int sel = m_List_Player_Type.FindString(0,(*pL->GetAiFuncs()->Name)());
	m_List_Player_Type.SetCurSel(sel);
	delete[] s;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPlayerSetupDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CWnd *wC;
	char *s = new char[256];
	int n,i;
	CPlayer *pP,*pCur;

	pCur = m_ppAiPlayers[m_CurrentPlayer]->GetPlayer();
	///locate control that has gocus
	wC = GetFocus();
	/// Get the ID of that control
	int id = wC->GetDlgCtrlID();
	switch(id)							///parse the id
	{
		case IDOK:
			CDialog::OnOK();
			break;
		case IDC_EDIT_PLAYER_TOTAL:
			this->m_Edit_TotalPlayers.GetWindowText(s,256);
			n = atoi(s);
			for(i=m_TotalPlayers;i<n;++i)
			{
				NewPlayer(i);
			}
			this->m_TotalPlayers = n;
			//update player select scroll bar
			m_SB_CurPlayer.SetScrollRange(0,m_TotalPlayers-1);
			break;
		case IDC_EDIT_PLAYER_NAME:
			m_Edit_PlayerName.GetWindowText(s,256);
			pCur->SetName(s);
			sprintf(s,"SETUP PLAYER:%s",pCur->GetName());
			SetWindowText(s);
			break;
		case IDC_EDIT_PLAYER_INITARMIES:
			m_Edit_TotalPlayers.GetWindowText(s,256);
			n = atoi(s);
			if(n != m_TotalPlayers)
			{
				for(i=m_TotalPlayers;i<n;++i)
				{
					NewPlayer(i);
				}
				this->m_TotalPlayers = n;
				//update player select scroll bar
				m_SB_CurPlayer.SetScrollRange(0,m_TotalPlayers-1);
			}
			m_Edit_InitArmies.GetWindowText(s,256);
			n = atoi(s);
			for(i=0;i<m_TotalPlayers;++i)
			{
				pP = this->m_ppAiPlayers[i]->GetPlayer();
				pP->GetArmies()->SetNumber(n);
			}
			m_InitArmies = n;
			break;
		default:
			wC = GetNextDlgTabItem(wC);	//reset the focus
			wC->SetFocus();
			break;
	}
	delete[] s;
}

LRESULT CPlayerSetupDlg::OnSBTotPlayer(WPARAM v, LPARAM lparam)
{
	int sel;
	CPlayer *pL;

	m_CurrentPlayer = v;
	pL = m_ppAiPlayers[v]->GetPlayer();
	char *s = new char[256];
	GetWindowText(s,256);
	sprintf(s,"SETUP PLAYER:%s",pL->GetName());
	SetWindowText(s);
	delete[] s;
	m_Edit_PlayerName.SetWindowText(pL->GetName());
	m_Static_Color.SetColor(pL->m_Color);
	if(pL->GetAiFuncs())
	{
		sel = this->m_List_Player_Type.FindString(0,(*pL->GetAiFuncs()->Name)());
		m_List_Player_Type.SetCurSel(sel);
	}
	else
	{
		m_List_Player_Type.SetCurSel(0);
	}
	return 0;
}

void CPlayerSetupDlg::NewPlayer(int i)
{
	m_pDoc->CreateNewPlayer(i,m_InitArmies);
}

void CPlayerSetupDlg::OnSelchangeListPlayerType() 
{
	// TODO: Add your control notification handler code here
	int sel = this->m_List_Player_Type.GetCurSel();
	char *s = new char[256];
	CPlayer *pL = m_ppAiPlayers[m_CurrentPlayer]->GetPlayer();
	m_List_Player_Type.GetText(sel,s);
	CAiList *pP = FindAI(s,pAiList);
	pL->SetAiFuncs(pP->GetFuncs());
	pL->SetParams((*pL->GetAiFuncs()->GetParams)());
	delete[] s;
}

void CPlayerSetupDlg::OnStaticPlayerColor() 
{
	// TODO: Add your control notification handler code here
	CPlayer *pL = m_ppAiPlayers[m_CurrentPlayer]->GetPlayer();
	CColorDialog Dlg(pL->m_Color,CC_FULLOPEN);


	Dlg.DoModal();
	pL->m_Color = Dlg.GetColor();
	m_Static_Color.SetColor(pL->m_Color);
}

void CPlayerSetupDlg::OnButtonSetupplayersEditAiParams() 
{
	// TODO: Add your control notification handler code here
	CPlayer *pL = m_ppAiPlayers[m_CurrentPlayer]->GetPlayer();

	(*pL->GetAiFuncs()->EditParamDLG)(pL->GetParams());
}

