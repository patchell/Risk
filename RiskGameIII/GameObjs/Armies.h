// Armies.h: interface for the CArmies class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARMIES_H__DC89980F_B572_41E9_919D_82A0C7FDBBBF__INCLUDED_)
#define AFX_ARMIES_H__DC89980F_B572_41E9_919D_82A0C7FDBBBF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MapDataItem.h"

#ifndef DLLexport
#define DLLexport	__declspec(dllexport)
#endif

class DLLexport CArmies : public CMapDataItem  
{
	int m_Number;
public:
	void AddAnArmy(int a);
	int GetAnArmy(void);
	virtual void Print(FILE *pFO);
	CArmies();
	virtual ~CArmies();
	void SetNumber(int t){m_Number = t;}
	int GetNumber(void){return m_Number;}
};

#endif // !defined(AFX_ARMIES_H__DC89980F_B572_41E9_919D_82A0C7FDBBBF__INCLUDED_)
