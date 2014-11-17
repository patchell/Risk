#include "stdafx.h"

#include "TerrList.h"

CTerrList::CTerrList()
{
	//ctor
	m_pNext = 0;
	m_pTerr = 0;
	m_pName = 0;
}

CTerrList::~CTerrList()
{
	//dtor
	if(m_pName) delete[] m_pName;
}

void CTerrList::SetName(char *s)
{
	/******************************
	** SetName
	**
	** This function is used to set
	** the name of this object to
	** the name of the territory
	** that we will eventually want
	** this object to point to.
	**
	** parameter:
	**	s.....pointer to name of desired
	**        territory.
	******************************/
	m_pName = new char[256];
	strcpy(m_pName,s);
}
