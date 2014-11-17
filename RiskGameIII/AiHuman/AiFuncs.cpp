/********************************************
	AiFuncs.h
	Created January 6, 2014

	Author: Jim Patchell
	patchell@cox.net

	For Human Interface
********************************************/

#include "StdAfx.h"
#include "AiFuncs.h"
#include "Player.h"
#include "resource.h"
#include "PlaceDLG.h"

/**********************************************
** All of these functions are called direct
** They are used to manage the AI
***********************************************/

extern "C" char *Name(void)
{
	return "Human";
}

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
}

/*****************************************************
** These functions are called from a Thread.  They
** are communicated with via a Message
*****************************************************/

extern "C" void Attack(void *pParam, CMap *pM, CPlayer *pPlayer,AMSG *pMsg)
{
	CMapTerritory *rV=0;
	if(pMsg->PayloadSize == 0)
		PostMessage(pMsg->hWind,pMsg->ReplyCmd,AIM_SELECT_ATTACK,0);
	else
	{
		memcpy(&rV,pMsg->Payload,pMsg->PayloadSize);
		PostMessage(pMsg->hWind,pMsg->ReplyCmd,AIM_SELECT_ATTACK,LPARAM(rV));
	}
}

extern "C" void AttackFrom(void *pParam, CMap *pM, CPlayer *pPlayer,AMSG *pMsg)
{
	CMapTerritory *rV=0;
	if(pMsg->Aux == 0)
		PostMessage(pMsg->hWind,pMsg->ReplyCmd,AIM_SELECT_FROM,0);
	else
	{
		memcpy(&rV,pMsg->Payload,pMsg->PayloadSize);
		PostMessage(pMsg->hWind,pMsg->ReplyCmd,AIM_SELECT_FROM,LPARAM(rV));
	}
}

extern "C" void Choose(void *pParam, CMap *pM, CPlayer *pPlayer,AMSG *pMsg)
{
	CMapTerritory *rV=0;
	if(pMsg->PayloadSize == 0)
		PostMessage(pMsg->hWind,pMsg->ReplyCmd,AIM_SELECTTERRITORY,0);
	else
	{
		memcpy(&rV,pMsg->Payload,pMsg->PayloadSize);
		rV->SetPlayer(pPlayer);	//take possesion of territory
		pPlayer->AddTerritory(rV);
		CArmies *pA_Terr = new CArmies;
		pA_Terr->SetNumber(pPlayer->GetArmies()->GetAnArmy());
		rV->AddChild(pA_Terr);	//add an army to a territory.
		PostMessage(pMsg->hWind,pMsg->ReplyCmd,AIM_NEXTSTATE,0);
	}
}

extern "C" void Place(void *pParam, CMap *pM, CPlayer *pPlayer,AMSG *pMsg)
{
	CMapTerritory *rV=0;
	if(pMsg->PayloadSize == 0)
		PostMessage(pMsg->hWind,pMsg->ReplyCmd,pMsg->Aux,0);
	else
	{
		memcpy(&rV,pMsg->Payload,pMsg->PayloadSize);
		int Army = pPlayer->GetArmies()->GetAnArmy();
		rV->FindArmies()->SetNumber(rV->FindArmies()->GetNumber() +  Army);
		PostMessage(pMsg->hWind,pMsg->ReplyCmd,AIM_NEXTSTATE,0);
	}
}

extern "C" void Cards(void *pParam, CMap *pM, CPlayer *pPlayer,AMSG *pMsg)
{
}

extern "C" void FreeMove(void *pParam, CMap *pM,CPlayer *pPlayer,AMSG *pMsg)
{
}

extern "C" void War(void *pParam,CMap *pM,AMSG *pMsg)
{
}

extern "C" void Defend(void *pParam, CMap *pM,AMSG *pMsg)
{
}
