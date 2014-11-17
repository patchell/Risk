// Score.cpp: implementation of the CScore class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Score.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CScore::CScore()
{
	//ctor
	m_Score = 0;
}

CScore::~CScore()
{
	//dtor
}

void CScore::Copy(CScore *pS)
{
	m_pT = pS->GetTerr();
	m_Score = pS->GetScore();
}
