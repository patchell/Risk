/********************************************************
** RiskUtils.cpp
**
** Thuis is a collection misc functions that are no
** part of any of the classes.
********************************************************/

#include "stdafx.h"
#include "Map.h"
#include "RiskUtils.h"
#include "Card.h"

/********************************************************
** PoinInWhichPolygon
**
** This function is used to figure out which polygon
** a specfice point is enclosed by.
**
** parameters:
**	pList......pointer to a list of polygons
** pos........the point to check
**
** Returns:
**	NULL, if no polygon is found
**	otherwise, a pointer to the polygon containing the point
********************************************************/
CPolygon *PointInWhichPolygon(CPolygon *pList,CPoint pos)
{
	CPolygon *pP = 0;
	int loop = 1;

	while(pList && loop)
	{
		if(pList->PointEnclosed(pos))		{
			loop = 0;	//on finding the polygon, quit
			pP = pList;	//assign the returned value
		}
		else
			pList = pList->GetNext();	//get next polygon
	}
	return pP;
}

CMapContinent *PointInWhichContinent(CMap *pMap,CPolygon *pList,CPoint pos)
{
	CMapContinent *pMC;
	CMapTerritory *pMT;
	CPolygon *pP;
	pP = PointInWhichPolygon(pList,pos);
	if(pP)
	{
		pMT = pP->GetTerritory();
		pMC = FindContinent(pMap,pMT);
	}
	return pMC;
}

CMapTerritory *PointInWhichTerritory(CMap *pMap,CPolygon *pList,CPoint pos)
{
	CMapTerritory *pMT=0;
	CPolygon *pP;
	pP = PointInWhichPolygon(pList,pos);
	if(pP)
		pMT = pP->GetTerritory();
	return pMT;
}

CMapTerritory *FindTerritory(CMap *pMap,char *name)
{
	CMapTerritory *pT;
	CMapContinent *pC;
	int loop = 1;
	pC = (CMapContinent *)pMap->GetChild();
	while(pC && loop)
	{
		pT = (CMapTerritory *)pC->GetChild();
		while(pT && loop)
		{
			if(strcmp(pT->GetName(),name) == 0)
			{
				loop = 0;
			}
			else
				pT = (CMapTerritory *)pT->GetNext();
		}
		pC = (CMapContinent *)pC->GetNext();
	}
	return pT;
}

CMapContinent *FindContinent(CMap *pMap,CMapTerritory *pMT)
{
	CMapContinent *pC;
	CMapTerritory *pT;
	int loop = 1;
	pC = (CMapContinent *)pMap->GetChild();
	while(pC && loop)
	{
		pT = (CMapTerritory *)pC->GetChild();
		while(pT && loop)
		{
			if(pT == pMT)
			{
				loop = 0;
			}
			else
				pT = (CMapTerritory *)pT->GetNext();
		}
		if(loop)
			pC = (CMapContinent *)pC->GetNext();
	}
	return pC;
}

CAiList *FindAI(char *s,CAiList *pL)
{
	CAiList *r_pAi;
	int loop = 1;

	while(pL && loop)
	{
		if(strcmp(s,(*(char *(*)(void))pL->GetFuncs(AIFUNC_NAME))()) == 0)
		{
			r_pAi = pL;
			loop = 0;
		}
		else
			pL = pL->GetNext();
	}
	return r_pAi;
}

int IsCardSet(int a, int b, int c)
{
	int rV = 0;

	switch(a)
	{
		case CARD_TYPE_INFANTRY:
			switch(b)
			{
				case CARD_TYPE_INFANTRY:
					switch(c)
					{
						case CARD_TYPE_INFANTRY:
							rV = 1;
							break;
						case CARD_TYPE_CALVALRY:
						case CARD_TYPE_ARTTIERY:
							break;
					}
					break;
				case CARD_TYPE_CALVALRY:
					switch(c)
					{
						case CARD_TYPE_INFANTRY:
						case CARD_TYPE_CALVALRY:
							break;
						case CARD_TYPE_ARTTIERY:
							rV = 4;
							break;
					}
					break;
				case CARD_TYPE_ARTTIERY:
					switch(c)
					{
						case CARD_TYPE_INFANTRY:
							break;
						case CARD_TYPE_CALVALRY:
							rV = 4;
							break;
						case CARD_TYPE_ARTTIERY:
							break;
					}
					break;
			}
			break;
		case CARD_TYPE_CALVALRY:
			switch(b)
			{
				case CARD_TYPE_INFANTRY:
					switch(c)
					{
						case CARD_TYPE_INFANTRY:
						case CARD_TYPE_CALVALRY:
							break;
						case CARD_TYPE_ARTTIERY:
							rV = 4;
							break;
					}
					break;
				case CARD_TYPE_CALVALRY:
					switch(c)
					{
						case CARD_TYPE_INFANTRY:
							break;
						case CARD_TYPE_CALVALRY:
							rV = 2;
							break;
						case CARD_TYPE_ARTTIERY:
							break;
					}
					break;
				case CARD_TYPE_ARTTIERY:
					switch(c)
					{
						case CARD_TYPE_INFANTRY:
							rV = 4;
							break;
						case CARD_TYPE_CALVALRY:
						case CARD_TYPE_ARTTIERY:
							break;
					}
					break;
			}
			break;
		case CARD_TYPE_ARTTIERY:
			switch(b)
			{
				case CARD_TYPE_INFANTRY:
					switch(c)
					{
						case CARD_TYPE_INFANTRY:
							break;
						case CARD_TYPE_CALVALRY:
							rV = 4;
							break;
						case CARD_TYPE_ARTTIERY:
							break;
					}
					break;
				case CARD_TYPE_CALVALRY:
					switch(c)
					{
						case CARD_TYPE_INFANTRY:
							rV = 4;
							break;
						case CARD_TYPE_CALVALRY:
							break;
						case CARD_TYPE_ARTTIERY:
							break;
					}
					break;
				case CARD_TYPE_ARTTIERY:
					switch(c)
					{
						case CARD_TYPE_INFANTRY:
							break;
						case CARD_TYPE_CALVALRY:
							break;
						case CARD_TYPE_ARTTIERY:
							rV = 3;
							break;
					}
					break;
			}
			break;
	}
	return rV;
}
