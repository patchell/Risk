// RiskGameView.h : interface of the CRiskGameView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RISKGAMEVIEW_H__095CE458_AF61_45BE_8BC7_10D92364321D__INCLUDED_)
#define AFX_RISKGAMEVIEW_H__095CE458_AF61_45BE_8BC7_10D92364321D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Map.h"
#include "MapDataItem.h"
#include "Polygon.h"
#include "MapContinent.h"
#include "MapTerritory.h"
#include "Player.h"
#include "AiThread.h"

enum {BATTLERES_ATKR_WON_BAT,
	BATTLERES_DEF_WON_BAT,
	BATTLERES_ATKR_WON_WAR,
	BATTLERES_DEF_WON_WAR,
	BATTLERES__TIE,
	BATTLERES_TIE_WAR
};

class CRiskGameView : public CView
{
protected: // create from serialization only
	CRiskGameView();
	DECLARE_DYNCREATE(CRiskGameView)

// Attributes
public:
	CRiskGameDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRiskGameView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual BOOL DestroyWindow();
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_BattleResult;
	int GetPlayerIndex(CPlayer *pP);
	int m_Attacker_Strat;
	int m_Defender_Strat;
	CMapTerritory * m_pAttackFrom;
	CMapTerritory * m_pAttack;
	int NextToPlaceArmies(int player);
	int m_GameStarted;
	int m_InternalState;
	void GameMachine(void);
	int GetNextState(void);
	int m_GameState;
	int m_CurrentPlayer;
	int m_Turn;
	CPlayer * m_pCurrPlayer;
	void DisplayGameStatus(CDC *pDC,CPlayer *pP,char *pS);
	CPoint ReverseTranslatePosition(CPoint nP,CRect pCr);
	void DisplayTerritoryStatus(CDC *pDC,CMap *pM, CRect *pCr);
	HINSTANCE m_Dll;
	int PumpMessages(unsigned Msg);
	void PumpMessages(void);
	int BonusArmies(CPlayer *pP);
	int PlayerTurn(CPlayer *pP);
	int m_TotalPlayers;
	int GameStateMachine(void);
	CPoint TranslatePosition(CPoint nP);
	int m_Scroll_Rate;
	int m_Timer_Scroll;
	int Block;
	int m_MaxY;
	int m_MaxX;
	int m_ScrollPosY;
	int m_ScrollPosX;
	void AutoScroll(int x, int y);
	int m_KeyCode;
	virtual ~CRiskGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	LRESULT OnMsgFromAi(WPARAM wP, LPARAM lP);
	//{{AFX_MSG(CRiskGameView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMenuEditSetupplayer();
	afx_msg void OnMenuPlayStart();
	afx_msg void OnMenuViewOccupied();
	afx_msg void OnMenuPlayTest();
	afx_msg void OnMenuEditAddai();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in RiskGameView.cpp
inline CRiskGameDoc* CRiskGameView::GetDocument()
   { return (CRiskGameDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RISKGAMEVIEW_H__095CE458_AF61_45BE_8BC7_10D92364321D__INCLUDED_)
