/********************************************
	AiFuncs.h
	Created January 6, 2014

	Author: Jim Patchell
	patchell@cox.net

********************************************/

#include "StdAfx.h"
#include "AiFuncs.h"
#include "AiDllBasicRSC.h"
#include "AiParamsDLG.h"

extern "C" void *GetParams(void)
{
	return 0;
}

extern "C" int GetParamSize(void)
{
	return 0;
}

extern "C" int GetParamIndex(int ParamNumber)
{
	return 0;
}

extern "C" int GetTotalParams(void)
{
	return 0;
}

extern "C" int SetParameter(void *pParams, int ParamNumber, long value)
{
	return 0;
}

extern "C" int GetParameter(void *pParams, int ParamNumber)
{
	return 0;
}

extern "C" void EditParamDLG(void *pParams)
{
	CAiParamsDLG Dlg;

	Dlg.DoModal();
}

extern "C" CMapTerritory *Attack(void *pParam, CMap *pM, CPlayer *pPlayer)
{
	return 0;
}

extern "C" CMapTerritory *AttackFrom(void *pParam, CMap *pM, CPlayer *pPlayer,CMapTerritory *pAT)
{
	return 0;
}

extern "C" CMapTerritory *Choose(void *pParam, CMap *pM,CPlayer *pPlayer,CMapTerritory *(*CallBack)(void))
{
	return 0;
}

extern "C" int Place(void *pParam, CMap *pM, CPlayer *pPlayer)
{
	return 0;
}

extern "C" int Cards(void *pParam, CMap *pM, CPlayer *pPlayer)
{
	return 0;
}

extern "C" int FreeMove(void *pParam, CMap *pM,CPlayer *pPlayer)
{
	return 0;
}

extern "C" char *Name(void)
{
	return "My First DLL";
}

extern "C" int War(void *pParam, CMapTerritory *pA,CMapTerritory *pD, CMap *pM,int (*DefCallBack)(CMapTerritory *pA, CMapTerritory *pD),int (*RuleCallBack)( CMapTerritory *pA, CMapTerritory *pD))
{
	if(DefCallBack)
		(*DefCallBack)(0,0);
	return 0;
}

extern "C" int Defend(void *pParam, CMap *pM, CMapTerritory *pT, CMapTerritory *pA)
{
	return 0;
}

