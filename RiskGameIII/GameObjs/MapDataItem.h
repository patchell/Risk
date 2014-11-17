// MapDataItem.h: interface for the CMapDataItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPDATAITEM_H__E9D1B32D_3A50_4AB8_A381_030220DAA312__INCLUDED_)
#define AFX_MAPDATAITEM_H__E9D1B32D_3A50_4AB8_A381_030220DAA312__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>

#define MAPTYPE_MAP	1
#define MAPTYPE_CONTINENT	2
#define MAPTYPE_TERRITORY	3
#define MAPTYPE_ARMY	4
#define MAPTYPE_GENERAL	5
#define MAPTYPE_SHIP	6
#define MAPTYPE_CAPITOL	7
#define MAPTYPE_FORT	8
#define MAPTYPE_FACTORY	9
#define MAPTYPE_FARM	10

#ifndef DLLexport
#define DLLexport	__declspec(dllexport)
#endif

//friend classes
class CMapTerritory;
class CMapContinent;
class CArmies;

class DLLexport CMapDataItem
{
	friend CMapTerritory;
	friend CMapContinent;
	friend CArmies;
	char *m_Name;	//name of object
	int m_Type;
	CMapDataItem *m_Child;	//next item down in hierarchy
	CMapDataItem *m_ChildEnd;	//next item down in hierarchy list end
	CMapDataItem *m_Next;	//next item at this level
public:
	CMapDataItem();
	CMapDataItem(int T);
	virtual ~CMapDataItem();
	virtual int IsType(int t);
	virtual void SetName(char *s);
	virtual char *GetName(void);
	virtual void SetType(int t);
	virtual int GetType(void);
	void SetChild(CMapDataItem *pChild) {m_Child = pChild;}
	void AddChild(CMapDataItem *pChild);
	CMapDataItem *GetChild(void) {return m_Child;}
	void SetNext(CMapDataItem *pNext){m_Next = pNext;}
	CMapDataItem *GetNext(void) {return m_Next;}
	virtual void Print(FILE *pO);
	void PrintAll(FILE *pO);
};

#endif // !defined(AFX_MAPDATAITEM_H__E9D1B32D_3A50_4AB8_A381_030220DAA312__INCLUDED_)
