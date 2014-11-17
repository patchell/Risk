/***********************************
** This is the default AI for the
** Risk Game.
**
** Interface functions are declared
** as external C functions
**
** Created December 13, 2013
** by James Patchell
************************************/

#ifndef DEFAULTAI__H
#define DEFAULTAI__H

#include "Map.h"
#include "MSG.h"

/************************************************************
** These functions are called direct and are used to manage
** the AI
************************************************************/

extern "C" char *DefaultName(void);
extern "C" void *DefaultGetParams(void);
extern "C" int DefaultGetParamSize(void);
extern "C" int DefaultGetParamIndex(int ParamNumber);
extern "C" int DefaultGetTotalParams(void);
extern "C" int DefaultSetParameter(void *pParams, int ParamNumber, long value);
extern "C" int DefaultGetParameter(void *pParams, int ParamNumber);
extern "C" void DefaultEditParamDLG(void *pParams);

/***********************************************************
** These functions are called from a Thread, and are sent
** parameters through a message
***********************************************************/

extern "C" void DefaultAttackFrom(void *pParam,CMap *pM, CPlayer *pPlayer,AMSG *pMsg);
extern "C" void DefaultAttack(void *pParam,CMap *pM, CPlayer *pPlayer,AMSG *pMsg);
extern "C" void DefaultCards(void *pParam,CMap *pM, CPlayer *pPlayer,AMSG *pMsg);
extern "C" void DefaultChoose(void *pParam,CMap *pM,CPlayer *pP,AMSG *pMsg);
extern "C" void DefaultDefend(void *pParam, CMap *pM,CPlayer *pP, AMSG *pMsg);
extern "C" void DefaultFreeMove(CMap *pM, CPlayer *pPlayer,AMSG *pMsg);
extern "C" void DefaultOccupy(void *pParam, CMap *pM,CPlayer *pP, AMSG *pMsg);
extern "C" void DefaultPlace(void *pParam,CMap *pM, CPlayer *pPlayer,AMSG *pMsg);
extern "C" void DefaultWar(void *pParam,CMap *pM,CPlayer *pP,AMSG *pMsg);

#endif
