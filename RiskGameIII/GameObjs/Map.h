// Map.h: interface for the CMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAP_H__3B220061_C619_432B_903A_BB0C551C6E22__INCLUDED_)
#define AFX_MAP_H__3B220061_C619_432B_903A_BB0C551C6E22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MapDataItem.h"
#include "Polygon.h"

#ifndef DLLexport
#define DLLexport	__declspec(dllexport)
#endif

class DLLexport CMap : public CMapDataItem  
{
public:
	int TotalUnoccupied(void);
	int BonusForOccupiedContinents(CPlayer *pP);
	int TotalTerritorries(void);
	int CountContinents(void);
	CMapContinent * FindContinent(CMapTerritory *pT);
	CPolygon *m_pPolyList,*m_pPolyEnd;
	void AddPolygon(CPolygon *pP);
	CMap();
	virtual ~CMap();
	virtual void Print(FILE *pO);
	inline void SetMerSpacing(int Ms) {m_MerSpacing = Ms;}
	inline int GetMerSpacing(void) {return m_MerSpacing;}
	inline void SetMerStart(int Ms) {m_MerStart = Ms;}
	inline int GetMerStart(void) {return m_MerStart;}
	inline void SetMerEnd(int Me) {m_MerEnd = Me;}
	inline int GetMerEnd(void) {return m_MerEnd;}
	inline void SetMerLineWidth(int MLw) {m_MerLineWidth = MLw;}
	inline int GetMerLineWidth(void) {return m_MerLineWidth;}
	inline void SetLogSpacing(int Ls) {m_LogSpacing = Ls;}
	inline int GetLogSpacing(void) {return m_LogSpacing;}
	inline void SetLogStart(int Ls) {m_LogStart = Ls;}
	inline int GetLogStart(void) {return m_LogStart;}
	inline void SetLogEnd(int Le) {m_LogEnd = Le;}
	inline int GetLogEnd(void) {return m_LogEnd;}
	inline void SetLogLineWidth(int LLw) {m_LogLineWidth = LLw;}
	inline int GetLogLineWidth(void) {return m_LogLineWidth;}
	inline void SetMapWidth(int W){m_Width = W;}
	inline int GetMapWidth(void){return m_Width;}
	inline void SetMapHieght(int H){m_Hieght = H;};
	inline int GetMapHieght(void){return m_Hieght;}
	inline void SetBorderColor(unsigned c){m_BorderColor = c;}
	inline int GetBorderColor(void){return m_BorderColor;}
private:
	int m_MerSpacing;
	int m_MerStart;
	int m_MerEnd;
	int m_MerLineWidth;
	int m_LogSpacing;
	int m_LogStart;
	int m_LogEnd;
	int m_LogLineWidth;
	int m_Hieght;
	int m_Width;
	unsigned m_BorderColor;
};

#endif // !defined(AFX_MAP_H__3B220061_C619_432B_903A_BB0C551C6E22__INCLUDED_)
