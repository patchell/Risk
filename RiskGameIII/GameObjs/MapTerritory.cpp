// MapTerritory.cpp: implementation of the CMapTerritory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapTerritory.h"
#include "ListTerritory.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMapTerritory::CMapTerritory():CMapDataItem(MAPTYPE_TERRITORY)
{
	/****************************
	** CMapTerritory
	**
	** This is the constructor
	** for a territory object
	****************************/
	m_x = 0;	//initial location
	m_y = 0;
	m_pAdj = 0;
	m_pOwner = 0;
	m_Value = 0;
}

CMapTerritory::~CMapTerritory()
{
	/****************************
	** ~CMapTerritory
	**
	** This is the destructor
	** for a territory object
	****************************/

}

void CMapTerritory::Print(FILE *pO)
{
	/*************************
	** Print
	**
	** This function prints out
	** just this object to a
	** file
	*************************/
	fprintf(pO,"TERRITORY::\"%s\"\n",CMapDataItem::m_Name);
	fprintf(pO," LOCATION(%d,%d)\n",m_x,m_y);
	fprintf(pO," VALUE(%d)\n",m_Value);
	//------------------------------------------------
	// check to see if we need to save an adjacent
	// neighbor list.
	//-----------------------------------------------
	if(m_pAdj)
	{
		CListTerritory *pTL = (CListTerritory *)m_pAdj->GetHead();
		fprintf(pO,"ADJ [\n");
		while(pTL)
		{
			fprintf(pO,"\"%s\"",pTL->GetTerr()->GetName());
			pTL = (CListTerritory *)pTL->GetNext();
			if(pTL)
				fprintf(pO,",\n");
			else
				fprintf(pO,"\n");
		}
		fprintf(pO,"]\n");
	}
}

void CMapTerritory::SetLocation(int x, int y)
{
	/***************************
	** SetLocation
	**
	** This function is used to
	** set the location of the
	** object.
	**
	** parameters;
	**	x.....The x location
	**	y.....The y location
	***************************/
	m_x = x;
	m_y= y;
}

void CMapTerritory::GetLocation(int *x, int *y)
{
	/**************************
	** GetLocation
	**
	** This function is used to
	** retrieve the location of
	** The object.
	**
	** parameters:
	**	x.....pointer to the location
	**       to put the X location
	**	y.....Pointer to the location
	**        to put the Y location
	**************************/
	*x = m_x;
	*y = m_y;
}

void CMapTerritory::AddNeighbor(CMapTerritory *pN)
{
	/******************************************
	** AddNiegbor
	**
	** Yes,I misspelled neightbor.  This function
	** takes a territory pointer as a parameter
	** and adds it to the Adjacent territory
	** list.
	**
	** parameter:
	**	pN....pointer to the new neighbor
	******************************************/
	CListTerritory *pLT;

	pLT= new CListTerritory;
	pLT->SetTerr(pN);
	if(!m_pAdj)
		m_pAdj = new CList;
	m_pAdj->ADD(pLT);
}

void CMapTerritory::AddNeighbor(CList *pN)
{
	/******************************************
	** AddNiegbor
	**
	** This function
	** adds the name of an adjacent territory to
	** the adjacent territory list.  This is so
	** we can add territories before we know they
	** exist.  Right now, this is only used while
	** loading in a saved file.
	**
	** parameter:
	**	pN....pointer to the name of the new neighbor
	******************************************/
	CListTerritory *pLT = (CListTerritory *)pN->GetHead();

	while(pLT)
	{
		m_pAdj->ADD(pLT);
		pLT = (CListTerritory *)pN->Del(pLT);
	}
}

CArmies * CMapTerritory::FindArmies()
{
	CMapDataItem *pDM = GetChild();
	int loop;
	CArmies *pA = 0;

	loop = 1;
	while(pDM && loop)
	{
		if(pDM->GetType() == MAPTYPE_ARMY)
		{
			loop = 0;
			pA = (CArmies *)pDM;
		}
	}
	return pA;
}

int CMapTerritory::CountHostile(CPlayer *pP)
{
	CListTerritory *pL = (CListTerritory *)GetNieghborList()->GetHead();
	int count = 0;
	while(pL)
	{
		if(pL->GetTerr()->GetPlayer() != pP)
			++count;
		pL = (CListTerritory *)pL->GetNext();
	}
	return count;
}

int CMapTerritory::CountHostileArmies(CPlayer *pP)
{
	CListTerritory *pL = (CListTerritory *)GetNieghborList()->GetHead();
	int count = 0;
	while(pL)
	{
		if(pL->GetTerr()->GetPlayer() != pP)
		{
			count += pL->GetTerr()->FindArmies()->GetNumber();
		}
		pL = (CListTerritory *)pL->GetNext();
	}
	return count;
}

int CMapTerritory::CountFriendly(CPlayer *pP)
{
	CListTerritory *pL = (CListTerritory *)GetNieghborList()->GetHead();
	int count = 0;
	while(pL)
	{
		if(pL->GetTerr()->GetPlayer() == pP)
			++count;
		pL = (CListTerritory *)pL->GetNext();
	}
	return count;
}

void CMapTerritory::AddNeighbor(CListTerritory *pN)
{
	if(!m_pAdj)
		m_pAdj = new CList;
	m_pAdj->ADD(pN);

}
