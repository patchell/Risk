#ifndef CPLAYER_H
#define CPLAYER_H

#include "..\AIfuncs.h"
#include <stdio.h>
#include "Armies.h"
#include "List.h"

#ifndef DLLexport
#define DLLexport	__declspec(dllexport)
#endif


class DLLexport CPlayer
{
public:
		char * m_pPrompt;
		int m_Prompt;
private:
		AIFUNCS *m_pAifunc;
		CList *m_pOccupiedTerritory;
		char *m_pName;
		CArmies * m_BonusArmies;
		CPlayer *m_pNext;	//next player
		void *m_pAI;	//weights for descisions
	public:
		CList * m_pCards;
		COLORREF m_Color;
		/** Default constructor */
		CPlayer();
		/** Default destructor */
		virtual ~CPlayer();
		/** Operations	**/
		int CountTerritories(void);
		CList *GetOccupiedTerritories(void) {return m_pOccupiedTerritory;}
		CMapTerritory * RemoveTerritory(CMapTerritory *pT);
		void AddTerritory(CMapTerritory *pT);
		void GetTotalAssets(ASSETS *pASS);
		void SetName(char *pName);
		char *GetName(void) {return m_pName;};
		void SetNext(CPlayer *pN){m_pNext = pN;}
		CPlayer *GetNext(void){return m_pNext;}
		void Print(FILE *pO);
		CArmies *GetArmies(void){return m_BonusArmies;}
		void SetArmies(CArmies *pA){m_BonusArmies = pA;}
		void SetAiFuncs(AIFUNCS *pF);
		AIFUNCS *GetAiFuncs(void){return m_pAifunc;}
		void SetParams(void *pV){m_pAI = pV;}
		void *GetParams(void){return m_pAI;}
};

#endif // CPLAYER_H
