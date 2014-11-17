/********************************************
	AiFuncs.h
	Created January 6, 2014

	Author: Jim Patchell
	patchell@cox.net

	This is for the HUMAN interface to the game
********************************************/

#ifndef AIFUNCSDLL_H
#define AIFUNCSDLL_H

#include "MapTerritory.h"
#include "Map.h"

#define AIM_NEXTSTATE		0
#define AIM_SELECTTERRITORY	1
#define AIM_PLACETERRITORY	2
#define AIM_DISTRIBUTEBONUS	3
#define AIM_SELECT_ATTACK	4
#define AIM_SELECT_FROM		5
#define AIM_WAR				6
#define AIM_BATTLE			7
#define AIM_OCCUPY			8

#define STRATTAGY_ROCK		1
#define STRATTAGY_PAPER		2
#define STRATTAGY_SCISSORS	3

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************************
** These functions get called from inside a thread.  To Communicate
** with them, we use a message.
**********************************************************************/

__declspec(dllexport)  void Attack(void *pParam, CMap *pM, CPlayer *pPlayer,AMSG *pMsg);
__declspec(dllexport)  void AttackFrom(void *pParam, CMap *pM, CPlayer *pPlayer,AMSG *pMsg);
__declspec(dllexport)  void Cards(void *pParam, CMap *pM, CPlayer *pPlayer,AMSG *pMsg);
__declspec(dllexport)  void Choose(void *pParam, CMap *pM, CPlayer *pPlayer,AMSG *pMsg);
__declspec(dllexport)  void Defend(void *pParam, CMap *pM,CPlayer *pP,AMSG *pMsg);
__declspec(dllexport)  void FreeMove(void *pParam, CMap *pM,CPlayer *pPlayer,AMSG *pMsg);
__declspec(dllexport)  void Occupy(void *pParam, CMap *pM,CPlayer *pP,AMSG *pMsg);
__declspec(dllexport)  void Place(void *pParam, CMap *pM, CPlayer *pPlayer,AMSG *pMsg);
__declspec(dllexport)  void War(void *pParam, CMap *pM,CPlayer *pP,AMSG *pMsg);

/*************************************************************
** these functions are called direct.  They are for managing
** The AI
*************************************************************/
__declspec(dllexport)  char *Name(void);
__declspec(dllexport)  void *GetParams(void);
__declspec(dllexport)  int GetParamSize(void);
__declspec(dllexport)  int GetParamIndex(int ParamNumber);
__declspec(dllexport)  int GetTotalParams(void);
__declspec(dllexport)  int SetParameter(void *pParams, int ParamNumber, long value);
__declspec(dllexport)  int GetParameter(void *pParams, int ParamNumber);
__declspec(dllexport)  void EditParamDLG(void *pParams);

#ifdef __cplusplus
}
#endif

#endif	//AIFUNCSDLL_H
