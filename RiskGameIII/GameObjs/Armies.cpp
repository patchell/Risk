// Armies.cpp: implementation of the CArmies class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Armies.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CArmies::CArmies():CMapDataItem(MAPTYPE_ARMY)
{
	m_Number = 0;
}

CArmies::~CArmies()
{

}

void CArmies::Print(FILE *pFO)
{
	fprintf(pFO,"ARMIES(%d)\n",m_Number);
}

int CArmies::GetAnArmy()
{
	int rV = 0;

	if(m_Number)
	{
		--m_Number;
		rV = 1;
	}
	return rV;
}

void CArmies::AddAnArmy(int a)
{
	if(a)
		++m_Number;
}
