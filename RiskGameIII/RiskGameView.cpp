// RiskGameView.cpp : implementation of the CRiskGameView class
//
#include "stdafx.h"
#include "RiskGame.h"

#include "RiskGameDoc.h"
#include "RiskGameView.h"
#include "MainFrm.h"
#include "RiskUtils.h"
#include "PlayerSetupDlg.h"
#include "AiList.h"
#include "WinMsg.h"
#include "TheRules.h"
#include "AiFuncs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define KEY_SHIFT	16


/*************************************
** Game States
*************************************/

#define STATE_START						0
#define STATE_SELECT_TERRITORIES		1
#define STATE_PLACE_ARMIES				2
#define STATE_GAME_TURNS				3
#define STATE_GAMEOVER					4
#define TURNSTATE_GET_BONUS				5
#define TURNSTATE_DISTRUBUTE_BONUS		6
#define TURNSTATE_ATTACK				7
#define TURNSTATE_ATTACKFROM			8
#define TURNSTATE_WAR_ATTACKER			9
#define TURNSTATE_WAR_DEFENDER			10
#define TURNSTATE_WAR_BATTLE			11
#define TURNSTATE_OCCUPY				12
#define TURNSTATE_MOVE_ARMIES			13
#define TURNSTATE_MOVE_ARMIESTO			14

char *GameStateNames[] =
{
	{"Start"},
	{"Select Territories"},
	{"Place Armies"},
	{"Turns"},
	{"Game Over"},
	{"Get Bonus"},
	{"Distribute Bonus"},
	{"Choose Terr To Attack"},
	{"Choose Terr to Attack From"},
	{"Its WAR Attacker"},
	{"Its WAR Defender"},
	{"Its WAR Battle"},
	{"Occupy"},
	{"Free Move From"},
	{"Free Move To"}
};

//--------------------------------
// internal states
//--------------------------------

#define INTERNAL_CHOOSE_TERRITORY	1
#define INTERNAL_PLACE_TERRITORY	2
#define INTERNAL_DISTRIBUTE_BONUS	3
#define INTERNAL_CHOOSE_ATTACK		4
#define INTERNAL_CHOOSE_FROM		5

//--------------------
// Timer Constants
//--------------------

#define TIMER_SCROLL	100

/////////////////////////////////////////////////////////////////////////////
// CRiskGameView

IMPLEMENT_DYNCREATE(CRiskGameView, CView)

BEGIN_MESSAGE_MAP(CRiskGameView, CView)
	//{{AFX_MSG_MAP(CRiskGameView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CONTEXTMENU()
	ON_WM_CHAR()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_TIMER()
	ON_COMMAND(ID_MENU_EDIT_SETUPPLAYER, OnMenuEditSetupplayer)
	ON_COMMAND(ID_MENU_PLAY_START, OnMenuPlayStart)
	ON_COMMAND(ID_MENU_VIEW_OCCUPIED, OnMenuViewOccupied)
	ON_COMMAND(ID_MENU_PLAY_TEST, OnMenuPlayTest)
	ON_COMMAND(ID_MENU_EDIT_ADDAI, OnMenuEditAddai)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MSGFROMAI,OnMsgFromAi)
END_MESSAGE_MAP()

CRiskGameView *pTHIS;
CMapTerritory *pChosen;


/////////////////////////////////////////////////////////////////////////////
// CRiskGameView construction/destruction

CRiskGameView::CRiskGameView()
{
	// TODO: add construction code here
	m_ScrollPosX = 0;
	m_ScrollPosY = 0;
	m_MaxX = 3600;
	m_MaxY = 2250;
	Block = 0;
	m_Timer_Scroll = 1;
	m_Scroll_Rate = 5;
	pTHIS = this;
	m_pCurrPlayer = 0;
	m_InternalState = 0;
	m_GameStarted = 0;
}

CRiskGameView::~CRiskGameView()
{
//	fclose(m_pFO);
}

BOOL CRiskGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CRiskGameView drawing

void CRiskGameView::OnDraw(CDC* pDC)
{
	CRect cR;
	CRiskGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CDC m_MemDC;
	CDC ScreenDC;	//where we construct the display
	CBitmap MemBM;	//where we draw the display
	CRect ScreenRect;
	GetClientRect(&cR);

	MemBM.CreateBitmap(cR.Width(),cR.Height(),1,32,0);
	m_MemDC.CreateCompatibleDC(pDC);
	ScreenDC.CreateCompatibleDC(pDC);
	ScreenDC.SelectObject(&MemBM);

	m_MemDC.SelectObject(pDoc->m_pMapBM);
	if(m_ScrollPosX >= (3600 - cR.right))
	{
		ScreenDC.BitBlt(0,0,3600-m_ScrollPosX,2250,&m_MemDC,m_ScrollPosX,m_ScrollPosY,SRCCOPY);
		ScreenDC.BitBlt(3600-m_ScrollPosX,0,3600-m_ScrollPosX+cR.Width(),2250,&m_MemDC,0,m_ScrollPosY,SRCCOPY);
	}
	else
	{
		ScreenDC.BitBlt(0,0,3600,2250,&m_MemDC,m_ScrollPosX,m_ScrollPosY,SRCCOPY);
	}
	if(pDoc->m_pMapData)
		DisplayTerritoryStatus(&ScreenDC,pDoc->m_pMapData,&cR);
	if(m_GameStarted)
	{
		CAiThread *pAiT = pDoc->m_PlayerAiThreads[m_CurrentPlayer];

		DisplayGameStatus(&ScreenDC,pAiT->GetPlayer(),0);
	}
	pDC->BitBlt(0,0,cR.Width(),cR.Height(),&ScreenDC,0,0,SRCCOPY);

}

/////////////////////////////////////////////////////////////////////////////
// CRiskGameView diagnostics

#ifdef _DEBUG
void CRiskGameView::AssertValid() const
{
	CView::AssertValid();
}

void CRiskGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRiskGameDoc* CRiskGameView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRiskGameDoc)));
	return (CRiskGameDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRiskGameView message handlers

void CRiskGameView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CPolygon *pPol;
	CRiskGameDoc *pDoc = GetDocument();
	CAiThread *pThrd = pDoc->m_PlayerAiThreads[m_CurrentPlayer]; ;
	CPoint pos = TranslatePosition(point);
	pPol = PointInWhichPolygon(pDoc->m_pPolyList,pos);
	if(pPol)
	{
		if(m_InternalState)
		{
			switch(m_InternalState)
			{
				case INTERNAL_CHOOSE_TERRITORY:
					if(pPol->GetTerritory()->GetPlayer() == 0)
					{
						//----------------------------
						// Make sure nobody occupies
						// the territory
						//----------------------------
						pThrd->Choose(pPol->GetTerritory(),sizeof(CMapTerritory *));
						m_InternalState = 0;
					}
					break;
				case INTERNAL_PLACE_TERRITORY:
					//-------------------------------
					// Make sure territory belongs to
					// player selecting it
					//-------------------------------
					if(pPol->GetTerritory()->GetPlayer() == pThrd->GetPlayer())
					{
						pThrd->Place(0,pPol->GetTerritory(),sizeof(CMapTerritory *));
						m_InternalState = 0;
					}
					break;
				case INTERNAL_DISTRIBUTE_BONUS:
					if(pPol->GetTerritory()->GetPlayer() == pThrd->GetPlayer())
					{
						pThrd->Place(0,pPol->GetTerritory(),sizeof(CMapTerritory *));
						m_InternalState = 0;
					}
					break;
				case INTERNAL_CHOOSE_ATTACK:	//choose where to attack
					if(pPol->GetTerritory()->GetPlayer() != pThrd->GetPlayer())
					{
						pThrd->Attack(0,pPol->GetTerritory(),sizeof(CMapTerritory *));
						m_InternalState = 0;
					}
					break;
				case INTERNAL_CHOOSE_FROM:		//choose where to attack from
					if(pPol->GetTerritory()->GetPlayer() == pThrd->GetPlayer())
					{
						pThrd->AttackFrom(1,(void *)pPol->GetTerritory(),sizeof(CMapTerritory *));
						m_InternalState = 0;
					}
					break;
			}
		}
	}
	CView::OnLButtonDown(nFlags, point);
}

void CRiskGameView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnLButtonUp(nFlags, point);
}

void CRiskGameView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	char *s = new char[256];
	int l = sprintf(s,"X=%5d Y=%5d",point.x,point.y);
	CMainFrame *pMF = (CMainFrame *)this->GetParentFrame();
	CRect ClientRect,DFRect;
	this->GetClientRect(&ClientRect);
	DFRect.CopyRect(&ClientRect);
	DFRect.DeflateRect(50,50);
	//---------------------------
	// find out where mouse is
	// in scrolling region so
	// we can scroll bitmap
	//---------------------------
	l += sprintf(&s[l]," OS");
	//
	if(point.x > DFRect.left && point.x < DFRect.right)
	{
		if(point.y > 0 && point.y < DFRect.top)
		{
			l += sprintf(&s[l]," Upper");
			if(m_KeyCode == KEY_SHIFT)
			{
				AutoScroll(0,-1);
			}
		}
		else if (point.y > DFRect.bottom && point.y < ClientRect.bottom)
		{
			l += sprintf(&s[l]," Lower");
			if(m_KeyCode == KEY_SHIFT)
			{
				AutoScroll(0,1);
			}
		}
		else
		{
			//process mouse movent when inside operating area
			sprintf(&s[l]," Inside");
		}
	}
	else if (point.x > 0 && point.x < DFRect.left)
	{
		if(point.y >  0 && point.y < DFRect.top)
		{
			l += sprintf(&s[l],"UL Corner");
			if(m_KeyCode == KEY_SHIFT)
			{
				AutoScroll(-1,-1);
			}
		}
		else if (point.y > DFRect.bottom && point.y < ClientRect.bottom)
		{
			l += sprintf(&s[l],"LL Corner");
			if(m_KeyCode == KEY_SHIFT)
			{
				AutoScroll(-1,1);
			}
		}
		else if (point.y > DFRect.top && point.y < DFRect.bottom)
		{
			l += sprintf(&s[l]," Left");
			if(m_KeyCode == KEY_SHIFT)
			{
				AutoScroll(-1,0);
			}
		}
	}
	else if (point.x > DFRect.right && point.x < ClientRect.right)
	{
		if(point.y > 0 && point.y < DFRect.top)
		{
			l += sprintf(&s[l]," UR Corner");
			if(m_KeyCode == KEY_SHIFT)
			{
				AutoScroll(1,-1);
			}
		}
		else if(point.y > DFRect.top && point.y < DFRect.bottom)
		{
			l += sprintf(&s[l]," Right");
			if(m_KeyCode == KEY_SHIFT)
			{
				AutoScroll(1,0);
			}
		}
		else if(point.y > DFRect.bottom && point.y < ClientRect.bottom)
		{
			l += sprintf(&s[l]," LR Corner");
			if(m_KeyCode == KEY_SHIFT)
			{
				AutoScroll(1,1);
			}
		}

	}
//	pMF->SetMessageText(s);
	delete[] s;
	CView::OnMouseMove(nFlags, point);
}

void CRiskGameView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	
}

void CRiskGameView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
//	m_pFO = fopen("log.txt","w");
//	CRiskGameDoc *pDoc = GetDocument();
}

void CRiskGameView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnChar(nChar, nRepCnt, nFlags);
}

BOOL CRiskGameView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
//	return CView::OnEraseBkgnd(pDC);
	return TRUE;
}

void CRiskGameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	m_KeyCode = nChar;	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CRiskGameView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	m_KeyCode = -1;
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CRiskGameView::AutoScroll(int x, int y)
{
	MSG msg;
	int loop;
	CPoint CurPos;
	CRect ClientRect;
	CRect DFRect;

	if(Block == 0)
	{
		++Block;

		msg.message = 0;   // forces at least one loop.
		loop = 1;
		while(loop)
		{
			if(m_Timer_Scroll)
			{
				GetCursorPos(&CurPos);
				ScreenToClient(&CurPos);
				GetClientRect(&ClientRect);
				int sx,sy;
				sx = ClientRect.right;
				sy = ClientRect.bottom;
				if(x > 0 && m_ScrollPosX  < m_MaxX) m_ScrollPosX += x * m_Scroll_Rate;
				else if (x < 0 && m_ScrollPosX >= 0) m_ScrollPosX += x * m_Scroll_Rate;
				if(y > 0 && m_ScrollPosY + sy  < m_MaxY) m_ScrollPosY += y * m_Scroll_Rate;
				else if (y < 0 && m_ScrollPosY > 0)m_ScrollPosY += y * m_Scroll_Rate;
				if(m_ScrollPosX >= m_MaxX) m_ScrollPosX = 0;	//wrap map
				else if (m_ScrollPosX < 0) m_ScrollPosX = 3599;
				if(m_ScrollPosY > m_MaxY) m_ScrollPosY = m_MaxY;
				else if (m_ScrollPosY < 0) m_ScrollPosY = 0;
				Invalidate();
				SetTimer(TIMER_SCROLL,1,0);
				m_Timer_Scroll = 0;
			}
			//----------------------------------------
			// Pump Messages
			//----------------------------------------
			while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))	//message pump
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				//------------------------------------
				// Check to see if this was a keyup
				// message.  We really need to check
				// to make sure it was really the
				// Shift Key that went up, but
				// what the heck
				//------------------------------------
				if (msg.message == WM_KEYUP)
				{
					loop = 0;
					m_KeyCode = -1;
				}

			}	//end of message pump
		}
		--Block;
	}
}

void CRiskGameView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
		case TIMER_SCROLL:
			m_Timer_Scroll = 1;
			break;
	}
	CView::OnTimer(nIDEvent);
}

CPoint CRiskGameView::TranslatePosition(CPoint nP)
{
	/************************************************
	** TranslatePosition
	**
	** this function translates the screen position
	** into our scroll window (map) coordinates
	**
	*************************************************/

	CPoint rV;
	CRect cR;

	GetClientRect(&cR);

	if((this->m_MaxX - m_ScrollPosX) < cR.Width() )
	{
		if(nP.x > m_MaxX - m_ScrollPosX)
			rV.x = nP.x - (m_MaxX - m_ScrollPosX);
		else
			rV.x = nP.x + this->m_ScrollPosX;
	}
	else
		rV.x = nP.x + this->m_ScrollPosX;
	rV.y = nP.y + m_ScrollPosY;
	return rV;
}

void CRiskGameView::OnMenuEditSetupplayer() 
{
	// TODO: Add your command handler code here
	CPlayerSetupDlg Dlg;
	CRiskGameDoc *pDoc;
	pDoc = GetDocument();
	Dlg.pAiList = pDoc->m_pAiList;
	Dlg.m_TotalPlayers = pDoc->m_TotalPlayers;
	Dlg.m_ppAiPlayers = pDoc->m_PlayerAiThreads;
	if(Dlg.DoModal() == IDOK)
	{
		pDoc->m_TotalPlayers = Dlg.m_TotalPlayers;
	}
}

//-------------------------------------
// State Machine Messages
//--------------------------------------

#define GSMSG_NEXTSTATE		0

int CRiskGameView::PlayerTurn(CPlayer *pP)
{
	return 0;
}

int CRiskGameView::GameStateMachine()
{
	extern void Stats(CPlayer *pL);
	extern FILE *GetFile(void);

	int loop = 1;
	int state = STATE_START;
	CRiskGameDoc *pDoc = GetDocument();
	CPlayer *pPlayer;
	FILE *pLog;
extern void SetLog(FILE *pL);
extern void CloseLog(void);

	char *s = new char[256];
	m_Turn = 0;
	pLog = GetFile();

	while(loop)
	{
		switch(state)
		{
			case STATE_START:
				break;
			case STATE_SELECT_TERRITORIES:
				break;
			case STATE_PLACE_ARMIES:
				break;
			case STATE_GAME_TURNS:
//				pPlayer = pDoc->m_pPlayerList;
				++m_Turn;
				if(m_Turn > 100)
					state = STATE_GAMEOVER;
				else
				{
					int loop = 1;
					if(pLog) fprintf(pLog,"###################### Turn %d ################\n",m_Turn);
					while(pPlayer && loop)
					{
						m_pCurrPlayer = pPlayer;
						PlayerTurn(pPlayer);
						pDoc->CheckForLoosers();
						if(pDoc->CountPlayers() == 1)
						{
							loop = 0;
							state = STATE_GAMEOVER;
						}
						pPlayer = pPlayer->GetNext();
						Invalidate();
						PumpMessages();
					}
//					Stats(pDoc->m_pPlayerList);
//					OnMenuViewOccupied();
				}
				break;
			case STATE_GAMEOVER:
				MessageBox("Game Over","Hey");
				loop = 0;
				break;
		}
		PumpMessages();
	}
	delete[] s;
	return 0;
}

void CRiskGameView::OnMenuPlayStart() 
{
	// TODO: Add your command handler code here
	srand( (unsigned)time( NULL ) );	//radomize random number generator
	CRiskGameDoc *pDoc = GetDocument();

	int i;
	for(i=0;i<pDoc->m_TotalPlayers ;++i)
	{
		pDoc->m_PlayerAiThreads[i]->m_hWnd = this->m_hWnd;
	}
	m_GameState = STATE_START;
	m_CurrentPlayer = 0;	//start at the first player
	m_Turn = 0;
	m_TotalPlayers = pDoc->m_TotalPlayers;
	m_GameStarted = 1;
	GameMachine();
}

void CRiskGameView::OnMenuViewOccupied() 
{
	// TODO: Add your command handler code here
	CRiskGameDoc *pDoc = GetDocument();
	CBitmap *pBMold;
	CMapContinent *pC;
	CMapTerritory *pT;
	CBrush *pB,*OldBrush;;

	int x,y;
	
	CDC *dc = GetDC();
	CDC MemDC;
	MemDC.CreateCompatibleDC(dc);

	pBMold = MemDC.SelectObject(pDoc->m_pMapBM);
	pC = (CMapContinent *)pDoc->m_pMapData->GetChild();
	while(pC)
	{
		pT = (CMapTerritory *)pC->GetChild();
		while(pT)
		{
			pB = new CBrush;
			pB->CreateSolidBrush(pT->GetPlayer()->m_Color);
			OldBrush = MemDC.SelectObject(pB);
			pT->GetLocation(&x,&y);
			MemDC.FloodFill(x,y,RGB(0,0,0));
			MemDC.SelectObject(OldBrush);
			delete pB;
			pT = (CMapTerritory *)pT->GetNext();
		}
		pC = (CMapContinent *)pC->GetNext();
	}
	MemDC.SelectObject(pBMold);
	Invalidate();
}


int CRiskGameView::BonusArmies(CPlayer *pP)
{
	int rV = pP->CountTerritories();
	rV /= 3;
	if(rV < 3) rV = 3;
	return rV;
}

int CRiskGameView::PumpMessages(unsigned Msg)
{
	MSG msg;
	int rV = 0;

	while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))	//message pump
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		//------------------------------------
		// Check to see if this was a watched
		// message.  
		//------------------------------------
		if (msg.message == Msg)
		{
			rV = 1;
		}
	}	//end of message pump
	return rV;
}

void CRiskGameView::PumpMessages()
{
	MSG msg;

	while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))	//message pump
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}	//end of message pump
}

void CRiskGameView::OnMenuPlayTest() 
{
	// TODO: Add your command handler code here
}

static const char * const NamesList[] = {
	"Attack",
	"Choose",
	"Place",
	"Cards",
	"Name",
	"AttackFrom",
	"War",
	"FreeMove",
	"Defend",
	"GetParams",
	"GetParamSize",
	"GetParamIndex",
	"GetTotalParams",
	"SetParameter",
	"GetParameter",
	"EditParamDLG",
	"Occupy",
	NULL
};

void CRiskGameView::OnMenuEditAddai() 
{
	// TODO: Add your command handler code here
	/***********************************
	** First, open up a DLL
	***********************************/
	int i;
	void *pProc;
	CAiList *pAi;
	CRiskGameDoc *pDoc = GetDocument();

	CFileDialog Dlg(TRUE,"AI plugin","*.dll",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,NULL,this);
	Dlg.DoModal();
	CString nm = Dlg.GetPathName();
	char *name = nm.GetBuffer(256);
	MessageBox(name,"DEBUG");
	m_Dll = LoadLibrary(name);
	if(m_Dll)
	{
		pAi = new CAiList;

		for(i=0;NamesList[i];++i)
		{
			pProc = GetProcAddress(m_Dll,NamesList[i]);
			if(pProc == NULL)
				MessageBox(NamesList[i],"Error:Can't Find");
			else
				pAi->SetFuncs(i,pProc);
		}
		pDoc->AddAi(pAi);
	}
	else
	{
		MessageBox(name,"ERROR:Could not LOAD");
	}
}

BOOL CRiskGameView::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	FreeLibrary(m_Dll);
	return CView::DestroyWindow();
}

void CRiskGameView::DisplayTerritoryStatus(CDC *pDC, CMap *pM, CRect *pCr)
{
	/**********************************************
	** DisplayTerritoryStatus
	**
	** This function is used to display the status
	** of the territory on the map.  The info includes
	**
	**	1. Occupier
	**	2. Number of armies
	**********************************************/
	CMapContinent *pMC = (CMapContinent *)pM->GetChild();
	CMapTerritory *pMT;
	CRect R1,R2,R;
	int X,Y;
	CBrush *pB;
	CPoint P;
	char *s;
	CArmies *pA;

	s = new char[256];
	CFont mfont;
	mfont.CreatePointFont(100,"ARIAL",pDC);
//	mfont.CreateFont(10,7,0,0,400,0,0,0,0,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"ARIAL");
	pDC->SelectObject(&mfont);

	if(m_ScrollPosX >= (3600 - pCr->right))
	{
		
		R1.bottom = pCr->bottom + m_ScrollPosY;
		R1.top = m_ScrollPosY;
		R1.left = m_ScrollPosX;;
		R1.right = m_MaxX;

		R2.bottom = pCr->bottom + m_ScrollPosY;
		R2.top = m_ScrollPosY;
		R2.left = 0;
		R2.right = pCr->Width() - R1.Width();
		while(pMC)
		{
			pMT = (CMapTerritory *)pMC->GetChild();
			while(pMT)
			{
				if(pMT->GetPlayer())
				{
					pMT->GetLocation(&X,&Y);
					if(R1.PtInRect(CPoint(X,Y)) || R2.PtInRect(CPoint(X,Y)) )
					{
						//------------------------------
						// Vissable, Draw info on screen
						//------------------------------
						if(pMT->GetPlayer())
						{
							P = ReverseTranslatePosition(CPoint(X,Y),pCr);
							R.top = P.y;
							R.left = P.x;
							R.right = P.x + 20;
							R.bottom = P.y + 20;
							pB = new CBrush(pMT->GetPlayer()->m_Color);
							pDC->FillRect(&R,pB);
							pA = pMT->FindArmies();
							if(pA)
							{
								sprintf(s,"%d",pA->GetNumber());
								pDC->TextOut(P.x+3,P.y+3,CString(s));
							}
							delete pB;
						}
					}
				}
				pMT = (CMapTerritory *)pMT->GetNext();
			}
			pMC = (CMapContinent *)pMC->GetNext();
		}
	}
	else
	{
		R1.bottom = pCr->bottom + m_ScrollPosY;
		R1.top = m_ScrollPosY;
		R1.left = m_ScrollPosX;
		R1.right = pCr->right + m_ScrollPosX;

		while(pMC)
		{
			pMT = (CMapTerritory *)pMC->GetChild();
			while(pMT)
			{
				pMT->GetLocation(&X,&Y);
				if(R1.PtInRect(CPoint(X,Y)))
				{
					//------------------------------
					// Vissable, Draw info on screen
					//------------------------------
					if(pMT->GetPlayer())
					{
						P = ReverseTranslatePosition(CPoint(X,Y),pCr);
						R.top = P.y;
						R.left = P.x;
						R.right = P.x + 20;
						R.bottom = P.y + 20;
						pB = new CBrush(pMT->GetPlayer()->m_Color);
						pDC->FillRect(&R,pB);
						pA = pMT->FindArmies();
						if(pA)
						{
							sprintf(s,"%d",pA->GetNumber());
							pDC->TextOut(P.x+3,P.y+3,CString(s));
						}
						delete pB;
					}
				}
				pMT = (CMapTerritory *)pMT->GetNext();
			}
			pMC = (CMapContinent *)pMC->GetNext();
		}
	}
	delete[] s;
}

CPoint CRiskGameView::ReverseTranslatePosition(CPoint nP,CRect Cr)
{
	/************************************************
	** ReverseTranslatePosition
	**
	** This function translates a Map Corrinate into
	** our Scroll Window corridinate
	************************************************/
	CPoint rV;

	if (nP.x > m_ScrollPosX)
		rV.x =  nP.x - m_ScrollPosX;
	else if(nP.x + m_ScrollPosX > (m_MaxX - Cr.Width()) )
	{
		rV.x = m_MaxX - m_ScrollPosX + nP.x;
	}
	else
	{
		rV.x = nP.x - m_ScrollPosX;
	}
	rV.y = nP.y - m_ScrollPosY;
	return rV;
}

void CRiskGameView::DisplayGameStatus(CDC *pDC, CPlayer *pP, char *pS)
{
	int spacing = 20;
	CRect dRect;
	CBrush br(RGB(255,255,0));
	CBrush *pOldBr;
	CPen *pOldPen;
	CPen pen(PS_SOLID,3,pP->m_Color);
	CFont font,*oldfont;
//	font.CreateFont(10,6,0,0,400,0,0,0,0,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"ARIAL");
	font.CreatePointFont(160,"ARIAL");
	char *s = new char[256];
	int X,Y;

	dRect.top = 0;
	dRect.left = 0;
	dRect.bottom = 150;
	dRect.right = 300;
	
	pOldBr = pDC->SelectObject(&br);
	pOldPen = pDC->SelectObject(&pen);
	pDC->Rectangle(&dRect);
	//---------------------------
	// Display stuff in rectangle
	//---------------------------
	oldfont = pDC->SelectObject(&font);
	X = 10;
	Y = 10;
	sprintf(s,"%s",GameStateNames[m_GameState]);
	pDC->TextOut(X,Y,CString(s));
	Y += spacing;
	sprintf(s,"TURN %3d",m_Turn);
	pDC->TextOut(X,Y,CString(s));
	Y += spacing;
	sprintf(s,"%s",pP->GetName());
	pDC->TextOut(X,Y,CString(s));
	Y += spacing;
	sprintf(s,"Terr Tot=%3d Troops: %d",pP->CountTerritories(),pP->GetArmies()->GetNumber());
	pDC->TextOut(X,Y,CString(s));
	if(pP->m_Prompt)
	{
		Y += spacing;
		pDC->TextOut(X,Y,CString(pP->m_pPrompt));
	}
	//---------------------------
	// Cleanup stuff
	//---------------------------
	pDC->SelectObject(pOldBr);
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(oldfont);
	delete[] s;
}

LRESULT CRiskGameView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CView::WindowProc(message, wParam, lParam);
}

LRESULT CRiskGameView::OnMsgFromAi(WPARAM wP, LPARAM lP)
{
	/************************************************
	** OnMsgFromAi
	**	This is where we get a kick in the pants from
	** the AI so that we can keep the game play going
	**
	** parameters:
	**	wP......Command from AI
	**	lP......Depends on command
	************************************************/
	WAR_DATA_MSG wdm;

	switch(wP)
	{
		case AIM_NEXTSTATE:
//			MessageBox("Got Reply From AI","DEBUG");
			GetNextState();
			GameMachine();
			Invalidate();
			break;
		case AIM_SELECTTERRITORY:
			m_InternalState = INTERNAL_CHOOSE_TERRITORY;
			break;
		case AIM_PLACETERRITORY:
			m_InternalState = INTERNAL_PLACE_TERRITORY;
			break;
		case AIM_DISTRIBUTEBONUS:
			m_InternalState = INTERNAL_DISTRIBUTE_BONUS;
			break;
		case AIM_SELECT_ATTACK:
			if(lP == 0)	//indicates a human interaction
			{
				m_InternalState = INTERNAL_CHOOSE_ATTACK;
			}
			else
			{
				CMapTerritory *pMT = (CMapTerritory *)lP;
				m_pAttack = pMT;	//set the territory to attack
				MessageBox(pMT->GetName(),"Attack Territory");
				GetNextState();
				GameMachine();
				Invalidate();
			}
			break;
		case AIM_SELECT_FROM:
			if(lP == 0)	//indicates a human interaction
			{
				m_InternalState = INTERNAL_CHOOSE_FROM;
			}
			else
			{
				CMapTerritory *pMT = (CMapTerritory *)lP;
				m_pAttackFrom = pMT;	//set the territory to attack from
				MessageBox(pMT->GetName(),"Attack From Territory");
				GetNextState();
				GameMachine();
				Invalidate();
			}
			break;
		case AIM_WAR:
			wdm.v = lP;
			switch(wdm.wd.State)
			{
				case 0:
					m_Attacker_Strat = wdm.wd.Strat;
					break;
				case 1:
					m_Defender_Strat = wdm.wd.Strat;
					break;
				case 2:
					break;
			}
			GetNextState();
			GameMachine();
			Invalidate();
			break;
		case AIM_BATTLE:
			if(lP > 0)	//attacker won battle
			{
				if(m_pAttack->FindArmies()->GetNumber() == 0)
				{
					//-----------------------------------
					// Defender has lost war
					//-----------------------------------
					m_BattleResult = BATTLERES_ATKR_WON_WAR;
				}
				else
					m_BattleResult = BATTLERES_ATKR_WON_BAT;

			}
			else if (lP < 0)	//attacker lost battle
			{
				if(m_pAttackFrom->FindArmies()->GetNumber() < 2)
				{
					//-----------------------------------
					// Attacker has lost war
					//-----------------------------------
					m_BattleResult = BATTLERES_DEF_WON_WAR;
				}
				else
					m_BattleResult = BATTLERES_DEF_WON_BAT;
			}
			else	//it was a tie
			{
				if(m_pAttackFrom->FindArmies()->GetNumber() < 2)
				{
					//-----------------------------------
					// Attacker has lost war
					//-----------------------------------
					m_BattleResult = BATTLERES_DEF_WON_WAR;
				}
				else if(m_pAttack->FindArmies()->GetNumber() == 0)
				{
					//-----------------------------------
					// Defender has lost war
					//-----------------------------------
					m_BattleResult = BATTLERES_ATKR_WON_WAR;
				}
				else
					m_BattleResult = BATTLERES__TIE;

			}
			GetNextState();
			GameMachine();
			Invalidate();
			break;
		case AIM_OCCUPY:
			/**********************************
			** Here is where we let a player
			** take over another territory
			**********************************/
			{
				int i;
				CPlayer *pDef = m_pAttack->GetPlayer();	//get defender
				CPlayer *pAtkr = m_pAttackFrom->GetPlayer();	//get attacker
				//remove it from the players occupied list
				pDef->RemoveTerritory(m_pAttack);
				//add it to the attackers list
				m_pAttack->SetPlayer(pAtkr);	//change ownership
				pAtkr->AddTerritory(m_pAttack);
				//transfer armies to the new prize
				for(i=0;i<lP;++i)
				{
					m_pAttackFrom->FindArmies()->GetAnArmy();
					m_pAttack->FindArmies()->AddAnArmy(1);
				}
			}
			GetNextState();
			GameMachine();
			Invalidate();
			break;
	}
	return 0;
}

int CRiskGameView::GetNextState()
{
	CRiskGameDoc *pDoc = GetDocument();

	switch(m_GameState)
	{
		case STATE_START:
			m_GameState = STATE_SELECT_TERRITORIES;
			break;
		case STATE_SELECT_TERRITORIES:
			m_CurrentPlayer++;
			if(m_CurrentPlayer == m_TotalPlayers)
			{
				m_CurrentPlayer = 0;
			}
			if(pDoc->m_pMapData->TotalUnoccupied() == 0)
			{
				m_CurrentPlayer = 0;
				m_GameState = STATE_PLACE_ARMIES;
			}
			break;
		case STATE_PLACE_ARMIES:
			m_CurrentPlayer = NextToPlaceArmies(m_CurrentPlayer);
			if(m_CurrentPlayer < 0)
			{
				m_CurrentPlayer = 0;
				m_GameState = STATE_GAME_TURNS;
			}
			break;
		case STATE_GAME_TURNS:
			m_GameState = TURNSTATE_GET_BONUS;
			break;
		case STATE_GAMEOVER:
			break;
		case TURNSTATE_GET_BONUS:
			break;
		case TURNSTATE_DISTRUBUTE_BONUS:
			if(pDoc->m_PlayerAiThreads[m_CurrentPlayer]->GetPlayer()->GetArmies()->GetNumber() > 0)
			{
			}
			else
			{
				m_GameState = TURNSTATE_ATTACK;
			}
			break;
		case TURNSTATE_ATTACK:
			m_GameState = TURNSTATE_ATTACKFROM;
			break;
		case TURNSTATE_ATTACKFROM:
			m_GameState = TURNSTATE_WAR_ATTACKER;
			break;
		case TURNSTATE_WAR_ATTACKER:
			m_GameState = TURNSTATE_WAR_DEFENDER;
			break;
		case TURNSTATE_WAR_DEFENDER:
			m_GameState = TURNSTATE_WAR_BATTLE;
			break;
		case TURNSTATE_WAR_BATTLE:
			switch(m_BattleResult)
			{
				case BATTLERES_ATKR_WON_BAT:
				case BATTLERES_DEF_WON_BAT:
				case BATTLERES__TIE:
				case BATTLERES_TIE_WAR:
					m_GameState = TURNSTATE_WAR_ATTACKER;
					break;
				case BATTLERES_ATKR_WON_WAR:
		 			m_GameState = TURNSTATE_OCCUPY;
					break;
				case BATTLERES_DEF_WON_WAR:
		 			m_GameState = TURNSTATE_ATTACK;
					break;
			}
			break;
		case TURNSTATE_OCCUPY:
			m_GameState = TURNSTATE_GET_BONUS;
			m_CurrentPlayer += 1;
			if(m_CurrentPlayer == m_TotalPlayers) m_CurrentPlayer = 0;
			break;
		case TURNSTATE_MOVE_ARMIES:
			break;
		case TURNSTATE_MOVE_ARMIESTO:
			break;
	}
	return 0;
}

void CRiskGameView::GameMachine()
{
	CRiskGameDoc *pDoc = GetDocument();
	CAiThread *pPlT = pDoc->m_PlayerAiThreads[m_CurrentPlayer];
	int BArm,stratsize;
	STRATAGY *pSB;
	int v;

	switch(m_GameState)
	{
		case STATE_START:
			OnMenuEditSetupplayer();	//setup players
			PostMessage(WM_MSGFROMAI,AIM_NEXTSTATE,0);
			break;
		case STATE_SELECT_TERRITORIES:
			pPlT->Choose();	//send a message to the choose AI function;
			break;
		case STATE_PLACE_ARMIES:
			pPlT->Place(AIM_PLACETERRITORY);
			break;
		case STATE_GAME_TURNS:
			PostMessage(WM_MSGFROMAI,AIM_NEXTSTATE,0);
			break;
		case STATE_GAMEOVER:
			MessageBox("Who Won?","Game Over");
			break;
		case TURNSTATE_GET_BONUS:
			BArm = this->BonusArmies(pPlT->GetPlayer());
			BArm += pDoc->m_pMapData->BonusForOccupiedContinents(pPlT->GetPlayer());
			pPlT->GetPlayer()->GetArmies()->SetNumber(BArm);
			m_GameState = TURNSTATE_DISTRUBUTE_BONUS;
		case TURNSTATE_DISTRUBUTE_BONUS:
			pPlT->Place(AIM_DISTRIBUTEBONUS);
			break;
		case TURNSTATE_ATTACK:
			pPlT->Attack(AIM_SELECT_ATTACK);
			break;
		case TURNSTATE_ATTACKFROM:
			pPlT->AttackFrom(0,(void *)m_pAttack,sizeof(CMapTerritory *));
			break;
		case TURNSTATE_WAR_ATTACKER:
			GetAttackStratagies(m_pAttackFrom ,&pSB,&stratsize);
			pPlT->War(0,pSB,stratsize);
			break;
		case TURNSTATE_WAR_DEFENDER:
			GetDefenseStratagies(m_pAttack,&pSB,&stratsize);
			pDoc->m_PlayerAiThreads[GetPlayerIndex(m_pAttack->GetPlayer())]->War(1,pSB,stratsize);
			break;
		case TURNSTATE_WAR_BATTLE:
			v = ConductWar(m_pAttackFrom, m_pAttack,m_Attacker_Strat,m_Defender_Strat);
			PostMessage(WM_MSGFROMAI,AIM_BATTLE,v);
			break;
		case TURNSTATE_OCCUPY:
			{
				WAR_PAYLOAD *wpl = new WAR_PAYLOAD;
				wpl->pAttackFrom = m_pAttackFrom;
				wpl->pAttackTo = m_pAttack;
				pPlT->Occupy(0,wpl,sizeof(WAR_PAYLOAD));
			}
			break;
		case TURNSTATE_MOVE_ARMIES:
			break;
		case TURNSTATE_MOVE_ARMIESTO:
			break;
	}
}

int CRiskGameView::NextToPlaceArmies(int player)
{
	CRiskGameDoc *pDoc = GetDocument();
	int i = player+1;

	int loop = 1;
	if(i == m_TotalPlayers) i = 0;
	int c = 0;
	while(loop)
	{
		if(pDoc->m_PlayerAiThreads[i]->GetPlayer()->GetArmies()->GetNumber() == 0)
		{
			if(++c == m_TotalPlayers) loop = 0;
			i += 1;
			if(i == m_TotalPlayers) i = 0;	//wrap i
		}
		else
			loop = 0;
	}
	if(c == m_TotalPlayers) i = -1;	//no armies left
	return i;
}

int CRiskGameView::GetPlayerIndex(CPlayer *pP)
{
	CRiskGameDoc *pDoc = GetDocument();
	int i;
	int index=-1;

	for(i=0;i<m_TotalPlayers && (index < 0);++i)
	{
		if(pDoc->m_PlayerAiThreads[i]->GetPlayer() == pP)
		{
			index = i;
		}
	}
	if(index < 0)
		MessageBox("Can't find player","ERROR");
	return index;
}
