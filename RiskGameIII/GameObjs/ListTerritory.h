// ListTerritory.h: interface for the CListTerritory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTTERRITORY_H__3194AB9B_3F51_495B_B2C8_93A1C10862D7__INCLUDED_)
#define AFX_LISTTERRITORY_H__3194AB9B_3F51_495B_B2C8_93A1C10862D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Bucket.h"
#include "MapTerritory.h"

#ifndef DLLexport
#define DLLexport	__declspec(dllexport)
#endif

class DLLexport CListTerritory : public CBucket  
{
	char *m_pName;
	CMapTerritory *m_pMT;
public:
	void SetName(char *s);
	CListTerritory();
	virtual ~CListTerritory();
	CMapTerritory *GetTerr(void){return m_pMT;}
	void SetTerr(CMapTerritory *pT){m_pMT = pT;}
	char *GetName(void){return m_pName;}
};

#endif // !defined(AFX_LISTTERRITORY_H__3194AB9B_3F51_495B_B2C8_93A1C10862D7__INCLUDED_)
