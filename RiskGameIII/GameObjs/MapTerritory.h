// MapTerritory.h: interface for the CMapTerritory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPTERRITORY_H__EDE6583A_16CF_4C18_9C8E_6608B06DFE4C__INCLUDED_)
#define AFX_MAPTERRITORY_H__EDE6583A_16CF_4C18_9C8E_6608B06DFE4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MapDataItem.h"
#include "Player.h"

class CListTerritory;

#ifndef DLLexport
#define DLLexport	__declspec(dllexport)
#endif

class DLLexport CMapTerritory : public CMapDataItem
{
	COLORREF m_Color;
	CList *m_pAdj;
	CPlayer *m_pOwner;
	int m_x,m_y;	//location on map
	int m_Value;
public:
	void AddNeighbor(CListTerritory *pN);
	int CountFriendly(CPlayer *pP);
	int CountHostileArmies(CPlayer *pP);
	int CountHostile(CPlayer *pP);
	CArmies * FindArmies(void);
	CMapTerritory();
	virtual ~CMapTerritory();
	void SetPlayer(CPlayer *pP){m_pOwner = pP;}
	CPlayer *GetPlayer(void){return m_pOwner;}
	void AddNeighbor(CMapTerritory *pN);
	void AddNeighbor(CList *pN);
	inline CList *GetNieghborList(void){return m_pAdj;}
	inline void SetNieghborList(CList *pL){m_pAdj = pL;}
	virtual void Print(FILE *pO);
	void SetValue(int v){m_Value = v;}
	int GetValue(void) {return m_Value;}
	void SetLocation(int x, int y);
	void GetLocation(int *x, int *y);
	void SetColor(COLORREF c){m_Color = c;}
	COLORREF GetColor(void){return m_Color;}
};

#endif // !defined(AFX_MAPTERRITORY_H__EDE6583A_16CF_4C18_9C8E_6608B06DFE4C__INCLUDED_)
