// ListTerritory.cpp: implementation of the CListTerritory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ListTerritory.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListTerritory::CListTerritory()
{
	m_pMT = 0;
	m_pName = 0;
}

CListTerritory::~CListTerritory()
{
	if(m_pName) delete[] m_pName;
}

void CListTerritory::SetName(char *s)
{
	if(!m_pName)
		m_pName = new char[256];
	strcpy(m_pName,s);
}
