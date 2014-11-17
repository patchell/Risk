// RiskGameDoc.h : interface of the CRiskGameDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RISKGAMEDOC_H__D1BBF63A_AD6D_4513_BA29_7C542CB4A9DE__INCLUDED_)
#define AFX_RISKGAMEDOC_H__D1BBF63A_AD6D_4513_BA29_7C542CB4A9DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyBitmap.h"
#include "Polygon.h"
#include "Map.h"
#include "MapDataItem.h"
#include "Polygon.h"
#include "MapContinent.h"
#include "MapTerritory.h"
#include "AiList.h"
#include "Card.h"
#include "AiThread.h"

class CRiskGameDoc : public CDocument
{
	//parser variables
	int m_LookAHead;
	int m_TokenValue;
	int m_Unget_Buffer;
	char *m_pLexBuff;
	int m_Line;
	//parser functions
	int Lookup(char *s);
	int Lexer(FILE *pI);
	CMap *Parser(FILE *pI);
	CPolygon * ParsePolygon(FILE *pI,CMap *pM);
	CMapContinent * ParseContinent(FILE *pI);
	CMapTerritory * ParseTerritory(FILE *pI);
	CMapDataItem * ParseObjects(FILE *pI);
	int Expect(int Tv,int LookAHead);
	int match(FILE *pI, int token);
	int GetChar(FILE *pI);
	void Error(char *em);
protected: // create from serialization only
	CRiskGameDoc();
	DECLARE_DYNCREATE(CRiskGameDoc)

// Attributes
public:
	CAiThread ** m_PlayerAiThreads;
	CPolygon *m_pPolyList,*m_pPolyEnd;
	CList * m_ListCards;
	int m_TotalPlayers;
	CAiList * m_pAiListEnd;
	CAiList * m_pAiList;
	CMap * m_pMapData;
	CMyBitmap * m_pMapBM;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRiskGameDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	void CreateNewPlayer(int i, int Armies);
	int TurnInCardSet(CCard *pC1, CCard *pC2, CCard *pC3);
	CCard * DrawCard(void);
	void CreateCards(CMap *pMap);
	int CountPlayers(void);
	void RemovePlayer(int Index);
	void CheckForLoosers(void);
	int Compile(CMap *pMap);
	void AddAi(CAiList *pA);
	void AddPolygon(CPolygon *pP);
	virtual ~CRiskGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRiskGameDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RISKGAMEDOC_H__D1BBF63A_AD6D_4513_BA29_7C542CB4A9DE__INCLUDED_)
