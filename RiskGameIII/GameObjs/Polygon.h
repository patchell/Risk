// Polygon.h: interface for the CPolygon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLYGON_H__6B41D47F_05BB_4035_A037_9D6862C9C946__INCLUDED_)
#define AFX_POLYGON_H__6B41D47F_05BB_4035_A037_9D6862C9C946__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MapTerritory.h"

#ifndef DLLexport
#define DLLexport	__declspec(dllexport)
#endif

class DLLexport CPolygon  
{
	CPoint * m_pVertex;
	int m_size;
	int m_Count;
	CPolygon *m_pNext;
	CMapTerritory *m_pT;
	int m_Selected;
public:
	int m_MaxY;
	int m_MinY;
	int m_MaxX;
	int m_MinX;
	int m_PolyID;
	void Print(FILE *pO);
	void Reset(void);
	inline void SetCount(int cnt){m_Count = cnt;}
	inline void SetSize(int sz){m_size = sz;}
	inline int GetSize(void){return m_size;}
	void Copy(CPolygon *pP);
	CPoint * GetPoints(void);
	int CompareToLast(CPoint nP);
	int DeleteLastPoint(void);
	int GetCount(void);
	void AddPoint(CPoint nP);
	BOOL PointEnclosed(CPoint);
	void Create(CPoint *);
	CPolygon();
	CPolygon(int size);
	virtual ~CPolygon();
	inline void SetNext(CPolygon *pNxt){m_pNext = pNxt;}
	inline CPolygon *GetNext(void){return m_pNext;}
	inline CMapTerritory *GetTerritory(void){return m_pT;}
	inline void SetTerritory(CMapTerritory *pT){m_pT = pT;}
	inline void SetSelected(int sel){m_Selected = sel;}
	inline int GetSelected(void){return m_Selected;}
};

#endif // !defined(AFX_POLYGON_H__6B41D47F_05BB_4035_A037_9D6862C9C946__INCLUDED_)
