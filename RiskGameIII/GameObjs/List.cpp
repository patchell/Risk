// List.cpp: implementation of the CList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "List.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#include "List.h"

CList::CList()
{
	//ctor
	m_pList = 0;
	m_pListEnd = 0;
	m_Count = 0;
}

CList::~CList()
{
	//dtor
	CBucket *pL;
	while(m_pList)
	{
		pL = m_pList->GetNext();
		delete m_pList;
		m_pList = pL;
	}
}

void CList::ADD(CBucket *pB)
{
	++m_Count;
	if(m_pList)	//list started
	{
		m_pListEnd->SetNext(pB);
		pB->SetPrev(m_pListEnd);
		m_pListEnd = pB;
	}
	else//start list
	{
		m_pList = pB;
		m_pListEnd = pB;
	}
}

CBucket *CList::Del(CBucket *pB)
{
	///-----------------------
	/// Find the object first
	///-----------------------
	CBucket *pBL = m_pList;
	CBucket *pBr = m_pList->GetNext();
	int loop = 1;
	if(pB == m_pList)
	{
		m_pList = m_pList->GetNext();
		if(m_pList)
			m_pList->SetPrev(0);
	}
	else if(pB == m_pListEnd)
	{
		m_pListEnd = m_pListEnd->GetPrev();
		m_pListEnd->SetNext(0);

	}
	else
	{
		while(pBL && loop)
		{
			if(pBL == pB)
			{
				loop = 0;
			}
			else
				pBL = pBL->GetNext();
		}
		if(pBL)
		{
			pBL->GetPrev()->SetNext(pBL->GetNext());
			pBL->GetNext()->SetPrev(pBL->GetPrev());
		}
	}
	return pBr;
}
