// MapContinent.cpp: implementation of the CMapContinent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapContinent.h"
#include "MapTerritory.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMapContinent::CMapContinent():CMapDataItem(MAPTYPE_CONTINENT)
{
	/****************************
	** CMapContinent
	**
	** This is the constructor for a
	** continent data object
	****************************/
	//ctor
}

CMapContinent::~CMapContinent()
{
	/****************************
	** ~CMapContinent
	** This is the destructor for
	** a Continent data object
	****************************/
	//dtor
}

void CMapContinent::Print(FILE *pO)
{
	/***************************
	** Print
	**
	** this function prints out
	** just this object.
	**
	** parameter:
	**	pO....pointer to output file
	***************************/
	fprintf(pO,"CONTINENT::\"%s\"\n",m_Name);
	fprintf(pO," VALUE(%d)\n",m_Value);
}


int CMapContinent::IsOccupiedByPlayer(CPlayer *pP)
{
	int rV = 0;
	CMapTerritory *pMT;
	int a,b;

	pMT = (CMapTerritory *)this->GetChild();
	a = 0;
	b = 0;
	while(pMT)
	{
		++a;
		if(pMT->GetPlayer() == pP)
			++b;
		pMT = (CMapTerritory *)pMT->GetNext();
	}
	if(a == b)
		rV = this->GetValue();
	return rV;
}
