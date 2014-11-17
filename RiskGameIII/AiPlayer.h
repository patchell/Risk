// AiPlayer.h: interface for the CAiPlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPLAYER_H__FB5DC159_2EB1_45C2_B000_8C9ECB36544F__INCLUDED_)
#define AFX_AIPLAYER_H__FB5DC159_2EB1_45C2_B000_8C9ECB36544F__INCLUDED_

#include "Map.h"
#include "Player.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAiPlayer  
{
	CAiPlayer *m_pNext;
	char m_Name[32];	//name of AI
public:
	CAiPlayer();
	virtual ~CAiPlayer();
	void SetNext(CAiPlayer *pN){m_pNext = pN;}
	CAiPlayer *GetNext(void){return m_pNext;}
	void SetName(char *n){strcpy(m_Name,n);}
	char *GetName(void) {return m_Name;}
	//-----------------------------
	//AiPlayer plugin interface
	//-----------------------------
	int (*War)(CMapTerritory *,CMapTerritory *);
	CMapTerritory *(*Attack)(CMap *pMap, CPlayer *);	//attack a territory
	CMapTerritory *(*AttackFrom)(CMap *pMap, CPlayer *,CMapTerritory *);
	CMapTerritory *(*Choose)(CMap *pMap);	//choose a territory
	int (*Place)(CMap *pMap, CPlayer *pPlayer);	//place assets on territory
	int (*Cards)(CMap *pMap);	//turn in cards
	char *(*Name)(void);			//Get the name of the AI
	int (*FreeMove)(CMap *pMap, CPlayer *pPlayer);	//Move your troops around
	//------------------------------
	//
};

#endif // !defined(AFX_AIPLAYER_H__FB5DC159_2EB1_45C2_B000_8C9ECB36544F__INCLUDED_)
