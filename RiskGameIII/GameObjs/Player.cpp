#include "stdafx.h"

#include <string.h>
#include "Player.h"
#include "ListTerritory.h"

CPlayer::CPlayer()
{
	//ctor
	m_pName = 0;
	m_pOccupiedTerritory = 0;
	m_pNext = 0;
	m_BonusArmies = 0;
	m_pAifunc = 0;
	m_Prompt = 0;
}

CPlayer::~CPlayer()
{
	//dtor
	if(m_pName) delete[] m_pName;
}

void CPlayer::GetTotalAssets(ASSETS *pASS)
{
	/*******************************************
	** GetTotalAssets
	**
	** This function gets a list of all the
	** assets that the player has.
	*******************************************/
}

void CPlayer::SetName(char *pName)
{
	/**************************************
	** SetName
	**	Set the name of the player
	**
	** parameter:
	**	pName....name to set player to
	**************************************/
	if(!m_pName) m_pName = new char[256];
	strcpy(m_pName,pName);
}

void CPlayer::Print(FILE *pO)
{
	fprintf(pO,"Player:%s\n",m_pName);
}


void CPlayer::AddTerritory(CMapTerritory *pT)
{
	CListTerritory *pTL = new CListTerritory;
	pTL->SetTerr(pT);
	if(!m_pOccupiedTerritory)
		m_pOccupiedTerritory = new CList;
	m_pOccupiedTerritory->ADD(pTL);
}

CMapTerritory * CPlayer::RemoveTerritory(CMapTerritory *pT)
{
	CListTerritory *pTL = (CListTerritory *)GetOccupiedTerritories()->GetHead();
	int loop=1;

	while(pTL && loop)
	{
		if(pTL->GetTerr() == pT)	//this the one?
		{
			loop = 0;
			GetOccupiedTerritories()->Del(pTL);
		}
		else
			pTL = (CListTerritory *)pTL->GetNext();
	}
	return pT;
}

int CPlayer::CountTerritories()
{
	CListTerritory *pL;
	int i=0;
	CList *pList = GetOccupiedTerritories();
	if(pList)
	{
		pL = (CListTerritory *)pList->GetHead();
		while(pL)
		{
			++i;
			pL = (CListTerritory *)pL->GetNext();
		}
	}
	return i;
}

void CPlayer::SetAiFuncs(AIFUNCS *pF)
{
	if(m_pAifunc == NULL)m_pAifunc = new AIFUNCS;
	memcpy(m_pAifunc,pF,sizeof(AIFUNCS));
}
