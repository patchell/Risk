// Bucket.cpp: implementation of the CBucket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Bucket.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBucket::CBucket()
{
	//ctor
	m_pNext = 0;
	m_pPrev = 0;
}

CBucket::~CBucket()
{
	//dtor
}
