// Map.cpp: implementation of the CMap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Map.h"
#include "MapTerritory.h"
#include "MapContinent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CMap::CMap():CMapDataItem(MAPTYPE_MAP)
{
	m_Width = 0;
	m_Hieght = 0;
	m_MerSpacing=0;
	m_MerStart=0;
	m_MerEnd=0;
	m_MerLineWidth=1;
	m_LogSpacing=0;
	m_LogStart=0;
	m_LogEnd=0;
	m_LogLineWidth=1;
	m_pPolyList = 0;
	m_pPolyEnd = 0;
}

CMap::~CMap()
{

}

void CMap::AddPolygon(CPolygon *pP)
{
	/***************************************
	** AddPolygon
	**
	**	This function adds a polygon to
	** a map.  These polygons are eventually
	** attatched to items in the map so that
	** when clicked, Windows can tell us
	** what we have clicked on.
	**
	** Paraameters:
	** pP......Polygon to add to map.
	***************************************/
	CPolygon *pNew = new CPolygon();
	pNew->Copy(pP);
	if(m_pPolyList)
	{
		m_pPolyEnd->SetNext(pNew);
		m_pPolyEnd = pNew;
	}
	else
	{
		m_pPolyList = pNew;
		m_pPolyEnd = pNew;
	}
}

void CMap::Print(FILE *pO)
{
	/*******************************************
	** Print
	**	This function prints out in
	** text format the values that
	** make of a CMap object.
	** this is primarily used to
	** save the map to the disk
	*******************************************/
	fprintf(pO,"MAP::\"%s\"\n",GetName());
	fprintf(pO," WIDTH(%d)\n",m_Width);
	fprintf(pO," HEIGHT(%d)\n",m_Hieght);
	fprintf(pO," MERIDIAN SPACING(%d)\n",m_MerSpacing);
	fprintf(pO," MERIDIAN START(%d)\n",m_MerStart);
	fprintf(pO," MERIDIAN END(%d)\n",m_MerEnd);
	fprintf(pO," MERIDIAN WIDTH(%d)\n",m_MerLineWidth);
	fprintf(pO," LONGITUDE SPACING(%d)\n",m_LogSpacing);
	fprintf(pO," LONGITUDE START(%d)\n",m_LogStart);
	fprintf(pO," LONGITUDE END(%d)\n",m_LogEnd);
	fprintf(pO," LONGITUDE WIDTH(%d)\n",m_LogLineWidth);
	fprintf(pO," BORDER COLOR(RGB(%d,%d,%d) )\n",(m_BorderColor & 0x00ff0000) >> 16,(m_BorderColor & 0x0000ff00) >> 8, (m_BorderColor & 0x00ff));

}

CMapContinent * CMap::FindContinent(CMapTerritory *pT)
{
	CMapContinent *pMC = 0;
	CMapTerritory *pMTlist;
	int loop;
	//------------------------------
	// Get list of continents
	//------------------------------
	loop = 1;
	CMapContinent *pMClist = (CMapContinent *)GetChild();
	while(pMClist && loop)
	{
		pMTlist = (CMapTerritory *)pMClist->GetChild();
		while(pMTlist && loop)
		{
			if(pMTlist == pT)	//is this the territory?
			{
				loop = 0;
				pMC = pMClist;
			}
			else
				pMTlist = (CMapTerritory *)pMTlist->GetNext();
		}
		if(loop)
			pMClist = (CMapContinent *)pMClist->GetNext();
	}
	return pMC;
}

int CMap::CountContinents()
{
	int i=0;
	CMapContinent *pC = (CMapContinent *)this->GetChild();
	while(pC)
	{
		++i;
		pC = (CMapContinent *)pC->GetNext();
	}
	return i;
}

int CMap::TotalTerritorries()
{
	int i=0;
	CMapContinent *pC = (CMapContinent *)this->GetChild();
	CMapTerritory *pT;

	while(pC)
	{
		pT = (CMapTerritory *)pC->GetChild();
		while(pT)
		{
			++i;
			pT = (CMapTerritory *)pT->GetNext();
		}
		pC = (CMapContinent *)pC->GetNext();
	}
	return i;
}

int CMap::BonusForOccupiedContinents(CPlayer *pP)
{
	int rV = 0;
	CMapContinent *pMC;

	pMC = (CMapContinent *)this->GetChild();
	while(pMC)
	{
		rV += pMC->IsOccupiedByPlayer(pP);
		pMC = (CMapContinent *)pMC->GetNext();
	}
	return rV;
}

int CMap::TotalUnoccupied()
{
	int i=0;
	CMapContinent *pC = (CMapContinent *)this->GetChild();
	CMapTerritory *pT;

	while(pC)
	{
		pT = (CMapTerritory *)pC->GetChild();
		while(pT)
		{
			//count just the unocupied Territorys
			if(pT->GetPlayer() == NULL)	++i;
			pT = (CMapTerritory *)pT->GetNext();
		}
		pC = (CMapContinent *)pC->GetNext();
	}
	return i;
}
