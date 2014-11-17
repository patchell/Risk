// Card.h: interface for the CCard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CARD_H__68DD3B36_83E3_44E8_8920_31E14DDC5B01__INCLUDED_)
#define AFX_CARD_H__68DD3B36_83E3_44E8_8920_31E14DDC5B01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Bucket.h"
#include "MapTerritory.h"

#define CARD_TYPE_INFANTRY	1
#define CARD_TYPE_CALVALRY	2
#define CARD_TYPE_ARTTIERY	3

#ifndef DLLexport
#define DLLexport	__declspec(dllexport)
#endif

class DLLexport CCard : public CBucket  
{
	CMapTerritory *m_pTer;	//territory associated with this card
	int m_Type;
public:
	CCard();
	virtual ~CCard();
	CMapTerritory *GetTerr(void){return m_pTer;}
	void SetTerr(CMapTerritory *pT){m_pTer = pT;}
	int GetCardType(void){return m_Type;}
	void SetCardType(int c){m_Type = c;}
};

#endif // !defined(AFX_CARD_H__68DD3B36_83E3_44E8_8920_31E14DDC5B01__INCLUDED_)
