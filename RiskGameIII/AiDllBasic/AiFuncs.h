/********************************************
	AiFuncs.h
	Created January 6, 2014

	Author: Jim Patchell
	patchell@cox.net

********************************************/

#ifndef AIFUNCSDLL_H
#define AIFUNCSDLL_H

#include "MapTerritory.h"
#include "Map.h"

#ifdef __cplusplus
extern "C" {
#endif

__declspec(dllexport) void *GetParams(void);
__declspec(dllexport) int GetParamSize(void);
__declspec(dllexport) int GetParamIndex(int ParamNumber);
__declspec(dllexport) int GetTotalParams(void);
__declspec(dllexport) int SetParameter(void *pParams, int ParamNumber, long value);
__declspec(dllexport) int GetParameter(void *pParams, int ParamNumber);
__declspec(dllexport) void EditParamDLG(void *pParams);
__declspec(dllexport) CMapTerritory *Attack(void *pParam, CMap *pM, CPlayer *pPlayer);
__declspec(dllexport) CMapTerritory *AttackFrom(void *pParam, CMap *pM, CPlayer *pPlayer,CMapTerritory *pAT);
__declspec(dllexport) CMapTerritory *Choose(void *pParam, CMap *pM,CPlayer *pPlayer,CMapTerritory *(*CallBack)(void));
__declspec(dllexport) int Place(void *pParam, CMap *pM, CPlayer *pPlayer);
__declspec(dllexport) int Cards(void *pParam, CMap *pM, CPlayer *pPlayer);
__declspec(dllexport) int FreeMove(void *pParam, CMap *pM,CPlayer *pPlayer);
__declspec(dllexport) char *Name(void);
__declspec(dllexport) int War(void *pParam, CMapTerritory *pA,CMapTerritory *pD, CMap *pM,int (*DefCallBack)(CMapTerritory *pA, CMapTerritory *pD),int (*RuleCallBack)( CMapTerritory *pA, CMapTerritory *pD));
__declspec(dllexport) int Defend(void *pParam, CMap *pM, CMapTerritory *pT, CMapTerritory *pA);

#ifdef __cplusplus
}
#endif

#endif	//AIFUNCSDLL_H
