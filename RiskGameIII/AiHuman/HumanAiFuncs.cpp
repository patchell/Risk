/********************************************
	AiFuncs.h
	Created January 6, 2014

	Author: Jim Patchell
	patchell@cox.net

	For Human Interface
********************************************/

#include "StdAfx.h"
#include "HumanAiFuncs.h"
#include "Player.h"
#include "resource.h"
#include "PlaceDLG.h"
#include "AttackDLG.h"
#include "Occupy.h"

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
	//------------------------------------
	// We use the Aux message parameter
	// to determine where we return a
	// message to.
	// Even though we get the territory
	// to attack in the payload, we could
	// really care less about that, since
	// we are a human.
	//------------------------------------
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

extern "C" void Occupy(void *pParam, CMap *pM,CPlayer *pP,AMSG *pMsg)
{
	COccupy Dlg;
	WAR_PAYLOAD *wpl = (WAR_PAYLOAD *)pMsg->Payload;
	char *s = new char[256];
	sprintf(s,"Occupy:%s",wpl->pAttackTo->GetName());
	sprintf(s,"You have %d Armies Availiable",wpl->pAttackFrom->FindArmies()->GetNumber()-1);
	Dlg.m_pPrompt = s;
	Dlg.m_Armies = wpl->pAttackFrom->FindArmies()->GetNumber()-1;
	Dlg.DoModal();
	PostMessage(pMsg->hWind,pMsg->ReplyCmd,AIM_OCCUPY,Dlg.m_Armies);
	delete[] s;
}

extern "C" void War(void *pParam,CMap *pM,CPlayer *pP,AMSG *pMsg)
{
	/******************************************
	** This is a complicated function
	**	Step 1: We need to select the attacking
	**			Stategy. Or do we give up.
	**	Step 2: We give the defender an opportunity
	**			to select a Defense Strategy
	**			Or does the defender give up.
	**	Step 3:	It goes to the RULES to determine
	**			the outcome of the battle.
	**
	** Parameters:
	**	pParam......pointer to AI params, NOT USED
	**	pM..........pointer to map data
	**	pPlayer.....pointer to player data
	**	pMsg........pointer to message buffer
	**		Sub Parameters in pMsg
	**		pMsg->Aux...This is the step in the
	**					War Process
	******************************************/
	WAR_DATA_MSG wdm;
	wdm.v = 0;
	wdm.wd.State = pMsg->Aux;
	char *s = new char[256];

	switch(wdm.wd.State)
	{
		case 0:
			{
				sprintf(s,"%s:Select Attack Strategy",pP->GetName());
				CAttackDlg Dlg;
				Dlg.m_pTitle = s;
				Dlg.m_NStrat = pMsg->PayloadSize;
				Dlg.m_pStrat = (STRATAGY *)pMsg->Payload;
				Dlg.DoModal();
				wdm.wd.Strat = Dlg.m_Strattegy;
			}
			break;
		case 1:	
			{
				sprintf(s,"%s:Select Defense Strategy",pP->GetName());
				CAttackDlg Dlg;
				Dlg.m_pTitle = s;
				Dlg.m_NStrat = pMsg->PayloadSize;
				Dlg.m_pStrat = (STRATAGY *)pMsg->Payload;
				Dlg.DoModal();
				wdm.wd.Strat = Dlg.m_Strattegy;
			}
			break;
		case 2:
			break;
	}
	PostMessage(pMsg->hWind,pMsg->ReplyCmd,AIM_WAR,wdm.v);

}

extern "C" void Defend(void *pParam, CMap *pM,CPlayer *pP,AMSG *pMsg)
{
}
