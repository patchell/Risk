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

#include "stdAfx.h"
#include "DefaultAI.h"
#include "MapContinent.h"
#include "List.h"
#include "ListTerritory.h"
#include "Score.h"
#include "Resource.h"
#include "AiParamEditDlg.h"
#include "MSG.h"
#include "TheRules.h"

FILE *pLog = 0;

void SetLog(FILE *pL)
{
	pLog = pL;
}

void CloseLog(void)
{
	pLog = 0;
}

static int DieRoll()
{
	return rand() % 6;
}

static void SortDie(int *d,int n)
{
	int i,j,t;

	for(j=0;j<n-1;++j)
	{
		for(i=0;i<n-1;++i)
		{
			if(d[i] < d[i+1])
			{
				t = d[i];
				d[i] = d[i+1];
				d[i+1] = t;
			}
		}
		--n;
	}
}

extern "C" void DefaultFreeMove(CMap *pM, CPlayer *pPlayer,AMSG *pMsg)
{	/***********************************************
	** A Free Move allows us to move armies from
	** a territory that doesn't really need them
	** to other territories.
	**
	** We can only move armies from one territory
	** to surrounding territories.
	***********************************************/
	CListTerritory *pL = (CListTerritory *)pPlayer->GetOccupiedTerritories()->GetHead();
	CListTerritory *pLn;
	int loop = 1;
	CList *pCand = new CList;
	CScore *pS,*pSmax;
	int score,max = -50000000,i;
	CMapTerritory *pMT;
	int armies;

	while(pL)
	{
		if(pL->GetTerr()->CountHostile(pPlayer) == 0)	//no hostile neighbors
		{
			pLn = (CListTerritory *)pL->GetTerr()->GetNieghborList()->GetHead();
			while(pLn && loop)
			{
				if(pLn->GetTerr()->CountHostile(pPlayer))
				{
					loop = 0;
					pS = new CScore;
					pS->SetTerr(pL->GetTerr());	//canidate to remove armies from
					score = pL->GetTerr()->CountHostileArmies(pPlayer) - pL->GetTerr()->FindArmies()->GetNumber();
					pS->SetScore(score);
					pCand->ADD(pS);
					if(score > max)
					{
						max = score;
						pSmax = pS;
					}
				}
				pLn = (CListTerritory *)pLn->GetNext();
			}
		}
		pL = (CListTerritory *)pL->GetNext();
	}
	if(pCand->GetCount())
	{
		//-----------------------------------
		// we have a free move canidate
		//-----------------------------------
		pMT = pSmax->GetTerr();
		int n = pMT->CountFriendly(pPlayer);
		int a = pMT->FindArmies()->GetNumber() - 1;	//leave one behind
		int c = a / n;
		int r = a / n;
		pL = (CListTerritory *)pMT->GetNieghborList()->GetHead();

		if(c > 0)
		{
			for(i=0;i<n;++i)
			{
				if(pL->GetTerr()->GetPlayer() == pPlayer)
				{
					armies = pMT->FindArmies()->GetNumber() - c;
					pMT->FindArmies()->SetNumber(armies);
					armies = pL->GetTerr()->FindArmies()->GetNumber() + c;
					pL->GetTerr()->FindArmies()->SetNumber(armies);
					if(pLog) fprintf(pLog,"\t#FM#From %s to %s %d armies\n",pMT->GetName(),pL->GetTerr()->GetName(),c);
				}
				pL = (CListTerritory *)pL->GetNext();
			}
		}
		if(r)
		{
			pL = (CListTerritory *)pMT->GetNieghborList()->GetHead();
			while(r && pL)
			{
				armies = pMT->FindArmies()->GetAnArmy();
				armies += pL->GetTerr()->FindArmies()->GetNumber();
				pL->GetTerr()->FindArmies()->SetNumber(armies);
				if(pLog) fprintf(pLog,"\t#FM#From %s to %s %d armies\n",pMT->GetName(),pL->GetTerr()->GetName(),1);
				--r;
				pL = (CListTerritory *)pL->GetNext();
			}
		}
	}
	delete pCand;
}

extern "C" void DefaultWar(void *pParam,CMap *pM,CPlayer *pP,AMSG *pMsg)
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
	STRATAGY *pStrat;
	int n;

	switch(wdm.wd.State)
	{
		case 0:	//attack stratagy
			pStrat = (STRATAGY *)pMsg->Payload;
			n = pMsg->PayloadSize/sizeof(STRATAGY);
			wdm.wd.Strat = rand()%n;
			break;
		case 1:		//defense stategy
			pStrat = (STRATAGY *)pMsg->Payload;
			n = pMsg->PayloadSize/sizeof(STRATAGY);
			wdm.wd.Strat = (rand()%n)+1;
			break;
		case 2:
			break;
	}
	PostMessage(pMsg->hWind,pMsg->ReplyCmd,AIM_WAR,wdm.v);

/*
	WAR_PAYLOAD *pPayload;
	CMapTerritory *pMTAttack,*pMTDefend;

	pPayload = (WAR_PAYLOAD *)pMsg->Payload;
	pMTAttack = pPayload->pAttackFrom;
	pMTDefend = pPayload->pAttackTo;
	int AttackerArmies = pMTAttack->FindArmies()->GetNumber();
	int DefenderArmies = pMTDefend->FindArmies()->GetNumber();
	int nAdie,nDdie;
	int A[3],D[2];
	int i;
	int rV;

	while(DefenderArmies > 0 && AttackerArmies > 1)
	{
		if(AttackerArmies >= 4)
			nAdie = 3;
		else
			nAdie = AttackerArmies-1;
		if(DefenderArmies >= 3)
			nDdie = 2;
		else
			nDdie = 1;
		for(i=0;i<nAdie;++i)
			A[i] = DieRoll();
		for(i=0;i<nDdie;++i)
			D[i] = DieRoll();
		SortDie(A,nAdie);
		SortDie(D,nDdie);
		if(A[0] <= D[0]) AttackerArmies--;
		else DefenderArmies--;
		if(nDdie == 2 && nAdie == 2)
		{
			if(A[1] <= D[1]) AttackerArmies--;
			else DefenderArmies--;
		}
	}
	pMTAttack->FindArmies()->SetNumber(AttackerArmies);
	pMTDefend->FindArmies()->SetNumber(DefenderArmies);
	if(DefenderArmies == 0) rV = 1;
	else rV = 0;
	if(pLog) fprintf(pLog,"%s(%d) ATTACK of %s(%d) %s\n",pMTAttack->GetPlayer()->GetName(),AttackerArmies,pMTDefend->GetName(),DefenderArmies,rV?"Won":"Lost");
	if(pLog) fflush(pLog);
	*/
}

extern "C" void DefaultAttackFrom(void *pParam,CMap *pM, CPlayer *pPlayer,AMSG *pMsg)
{
	AIPARAMS *pParms = (AIPARAMS *)pParam;
	CMapTerritory *pMTtoAttack;
	memcpy(&pMTtoAttack,pMsg->Payload,pMsg->PayloadSize);
	CListTerritory *pL = (CListTerritory *)pMTtoAttack->GetNieghborList()->GetHead();
	CList *pMyTerr = new CList;
	CScore *pS,*pSmax;
	CMapTerritory *prT;
	int max=0;

	while(pL)
	{
		if(pL->GetTerr()->GetPlayer() == pPlayer)
		{
			pS = new CScore;
			pS->SetTerr(pL->GetTerr());
			pS->SetScore(pL->GetTerr()->FindArmies()->GetNumber());
			pMyTerr->ADD(pS);
			if(pS->GetScore() > max)
			{
				max = pS->GetScore();
				pSmax = pS;
			}
		}
		pL = (CListTerritory *)pL->GetNext();
	}
	prT = pSmax->GetTerr();
	delete pMyTerr;
	if(pLog) fprintf(pLog,"%s Attack From %s\n",pPlayer->GetName(),prT->GetName());
	PostMessage(pMsg->hWind,pMsg->ReplyCmd,AIM_SELECT_FROM,LPARAM(prT));
}

extern "C" void DefaultAttack(void *pParam,CMap *pM, CPlayer *pPlayer,AMSG *pMsg)
{
	/*********************************
	* So, just who do we Attack?
	*********************************/
	AIPARAMS *pParms = (AIPARAMS *)pParam;
	CMapTerritory *prT;
	CListTerritory *pAdjTerr,*pMyTerr;
	CList *pAttackable;
	CScore *pS;

	pMyTerr = (CListTerritory *)pPlayer->GetOccupiedTerritories()->GetHead();
	//----------------------------------
	// make a list of adjacent territories
	//-----------------------------------
	pAttackable = new CList;
	while(pMyTerr)
	{
		//only attack from territory with 3 armies or more
		if(pMyTerr->GetTerr()->FindArmies()->GetNumber() >= 3)
		{
			pAdjTerr = (CListTerritory *)pMyTerr->GetTerr()->GetNieghborList()->GetHead();
			while(pAdjTerr)
			{
				if(pAdjTerr->GetTerr()->GetPlayer() != pPlayer)
				{
					int diff;
					//-------------------------------
					// add to hostile list
					//-------------------------------
					pS = new CScore;
					pS->SetTerr(pAdjTerr->GetTerr());
					diff = pMyTerr->GetTerr()->FindArmies()->GetNumber() 
						- pAdjTerr->GetTerr()->FindArmies()->GetNumber();
					diff = pAdjTerr->GetTerr()->GetValue() * diff;
					if(pLog) fprintf(pLog,"\tATT CAN %s(%d) FROM %s(%d) SCORE:%d\n",
						pAdjTerr->GetTerr()->GetName(),pAdjTerr->GetTerr()->FindArmies()->GetNumber() ,
						pMyTerr->GetTerr()->GetName(),pMyTerr->GetTerr()->FindArmies()->GetNumber(),diff);
					pS->SetScore(diff);
					if(diff >= 5)
						pAttackable->ADD(pS);
					else
					{
						delete pS;
//						if(pLog) fprintf(pLog,"\t\t\tNOT ADDED\n");
					}
				}
				pAdjTerr = (CListTerritory *)pAdjTerr->GetNext();
			}
		}
		pMyTerr = (CListTerritory *)pMyTerr->GetNext();
	}
	//----------------------------------
	// find the highest score
	//---------------------------------
	pS = (CScore *)pAttackable->GetHead();
	if(pS != NULL)
	{
		int MaxScore=-1000;
		while(pS)
		{
			if(pS->GetScore() > MaxScore)
				MaxScore = pS->GetScore();
			pS = (CScore *)pS->GetNext();
		}
		pS = (CScore *)pAttackable->GetHead();
		while(pS->GetScore() != MaxScore)
			pS = (CScore *)pS->GetNext();
		prT = pS->GetTerr();	//This is where we attack
	}
	else
		prT = NULL;
	delete pAttackable;
	PostMessage(pMsg->hWind,pMsg->ReplyCmd,AIM_SELECT_ATTACK,LPARAM(prT));
}

extern "C" void DefaultCards(void *pParam,CMap *pM, CPlayer *pPlayer,AMSG *pMsg)
{
}

extern "C" void DefaultOccupy(void *pParam, CMap *pM,CPlayer *pP, AMSG *pMsg)
{
	WAR_PAYLOAD *wpl = (WAR_PAYLOAD *)pMsg->Payload;
	int AvailArmies;
	int EnemyAroundOld=0;
	int EnemyAroundNew=0;
	CListTerritory *pT;

	AvailArmies = wpl->pAttackFrom->FindArmies()->GetNumber() - 1;
	pT = (CListTerritory *)wpl->pAttackFrom->GetNieghborList()->GetHead();
	while(pT)
	{
		if(pT->GetTerr()->GetPlayer() != pP)	//enemy?
			EnemyAroundOld += pT->GetTerr()->FindArmies()->GetNumber();
		pT = (CListTerritory *)pT->GetNext();
	}
	pT = (CListTerritory *)wpl->pAttackTo->GetNieghborList()->GetHead();
	while(pT)
	{
		if(pT->GetTerr()->GetPlayer() != pP)	//enemy?
			EnemyAroundNew += pT->GetTerr()->FindArmies()->GetNumber();
		pT = (CListTerritory *)pT->GetNext();
	}
	if(abs(EnemyAroundNew - EnemyAroundOld) < 5)
		AvailArmies /= 2;
	else if(EnemyAroundNew < EnemyAroundOld)
		AvailArmies /= 4;

	PostMessage(pMsg->hWind,pMsg->ReplyCmd,AIM_OCCUPY,AvailArmies);
}

extern "C" void DefaultPlace(void *pParam,CMap *pM, CPlayer *pPlayer,AMSG *pMsg)
{
	/*********************************************
	** Place
	**
	** Places an army into a territory
	**
	** parameters:
	**	pM......pointer to the game map
	**	pPlayer.player whoose turn it is
	**
	** Return Value
	**	Returns 0 if no armies to place
	**	Returns 1 on sucsess
	**********************************************/
	AIPARAMS *pParms = (AIPARAMS *)pParam;
	CMapTerritory * rpT = 0;
	CMapTerritory *pCurT;	//current territory of player
	CMapTerritory *pT;
	int MaxScore;
	CListTerritory *pTlist,*pTadj;
	CArmies *pAAdj,*pACur;
	CList *pOpp;
	CScore *pS,*pSmax;
	int score;

	/****************************************
	** Get the list of occupied territories
	** for the player of interest.  And
	** create a list of threats and
	** invasion opportunities.
	***************************************/
	int Army;
	pTlist = (CListTerritory *)pPlayer->GetOccupiedTerritories()->GetHead();
	pOpp = new CList;
	while(pTlist)	//go through our occupied territoryes
	{
		/**************************************
		** Get the territory this list pointer
		** points to
		**************************************/
		pCurT = pTlist->GetTerr();
		/*************************************
		** get the list of adjacent territories
		*************************************/
		pTadj =(CListTerritory *)pCurT->GetNieghborList()->GetHead();	//adjacent list for pCurT
		pACur = pCurT->FindArmies();	//armies on current territory
		pS = new CScore;
		pS->SetTerr(pCurT);
		while(pTadj)	//and check against the adjacent terriories
		{
			pT = pTadj->GetTerr();	//get an adjacent territory
			if(pT->GetPlayer() != pPlayer)	//enemy?
			{
				/*******************************
				** Check to see how many armies
				** the opposition has in store
				** for us
				*******************************/
				pAAdj = pT->FindArmies();
				//find the greatest threat
				if(pAAdj->GetNumber() > pACur->GetNumber() + 2)
				{
					score = pAAdj->GetNumber() - pACur->GetNumber();
					score = pT->GetValue() * score * pParms->PlaceEnemyTerrWeight  + pCurT->GetValue() * score * pParms->PlaceAttackTerrWeight;
					if(score > pS->GetScore())
						pS->SetScore(score);
				}
				///-----------------------------------
				///Check for invasion opportunity
				///-----------------------------------
				if(pAAdj->GetNumber() <= pACur->GetNumber())
				{
					//------------------------------------
					// if our territory has less than
					// four armies and there is an
					// invasion opportunity, up the
					// score for adding more armies
					//------------------------------------
					if(pACur->GetNumber() < 4)	//need to add armies?
					{
						score = pACur->GetNumber() - pAAdj->GetNumber();
						if(score == 0) score = 1;
						score = pT->GetValue() * score * pParms->PlaceEnemyTerrWeight + pCurT->GetValue() * score * pParms->PlaceAttackTerrWeight;
						if(pS->GetScore() < score)
							pS->SetScore(score);
					}
				}
			}
			pTadj = (CListTerritory *)pTadj->GetNext();
		}
		pOpp->ADD(pS);
		pTlist = (CListTerritory *)pTlist->GetNext();
	}
	//------------------------------------------
	// Find the higest Score
	//------------------------------------------
	pS = (CScore *)pOpp->GetHead();
	MaxScore = 0;
	while(pS)
	{
		if(pS->GetScore() >= MaxScore)
		{
			MaxScore = pS->GetScore();
			pSmax = pS;
		}
		pS = (CScore *)pS->GetNext();
	}

	rpT = pSmax->GetTerr();
	Army = pPlayer->GetArmies()->GetAnArmy();
	rpT->FindArmies()->SetNumber(rpT->FindArmies()->GetNumber() +  Army);
	//delete stuff we don't need
	delete pOpp;
	if(pLog) fprintf(pLog,"Player %s Added Army to %s\n",pPlayer->GetName(),rpT->GetName());
	if(pLog) fflush(pLog);
	PostMessage(pMsg->hWind,pMsg->ReplyCmd,AIM_NEXTSTATE,0);
}

extern "C" void DefaultChoose(void *pParam,CMap *pM,CPlayer *pP,AMSG *pMSG)
{
	CMapTerritory *pMT = 0;
	int TTerr = pM->TotalTerritorries();
	CMapContinent *pC;
	//--------------------------------
	// Generate a random number
	// between and including 0 and 133
	//--------------------------------
	int n = rand() % TTerr;
	int i=0;
	int loop = 1;
	pC = (CMapContinent *)pM->GetChild();
	//--------------------------
	// find that n-th territory
	//--------------------------
	while(pC && loop)
	{
		pMT = (CMapTerritory *)pC->GetChild();
		while(pMT && loop)
		{
			if(i==n)
				loop = 0;
			else
				pMT = (CMapTerritory *)pMT->GetNext();
			++i;
		}
		//--------------------------------------
		// because we still may need to use
		// pC, we don't want to bump out
		// accidently in the next while loop
		// below
		// so only update the continent pointer
		// if we are still actively looping
		//------------------------------------
		if(loop) pC = (CMapContinent *)pC->GetNext();
	}
	/********************************************
	** If the territory that was picked has
	** already been picked, then just continue
	** on until we find one that is not
	*******************************************/
	if(pMT->GetPlayer())	//already occupied?
	{
		if(pLog) fprintf(pLog,"  Choose:Part 2 %s\n",pMT->GetName());
		loop = 1;
		while(pC && loop)
		{
			while(pMT && loop)
			{
				if(pMT->GetPlayer() == 0)
				{
					loop = 0;
					if(pLog) fprintf(pLog,"  Choose:Part 2 %s\n",pMT->GetName());
				}
				else
					pMT = (CMapTerritory *)pMT->GetNext();
			}
			pC = (CMapContinent *)pC->GetNext();
		}
	}
	// IF we still haven't got one then.....
	if(pMT == NULL)	//just get the first one then
	{
		if(pLog) fprintf(pLog,"  Chose Part 3\n");
		loop = 1;
		pC = (CMapContinent *)pM->GetChild();
		while(pC && loop)
		{
			pMT = (CMapTerritory *)pC->GetChild();
			while(pMT && loop)
			{
				if(pMT->GetPlayer() == NULL)
					loop = 0;
				else
					pMT = (CMapTerritory *)pMT->GetNext();
			}
			pC = (CMapContinent *)pC->GetNext();
		}

	}
	pMT->SetPlayer(pP);	//take possesion of territory
	pP->AddTerritory(pMT);
	CArmies *pA_Terr = new CArmies;
	pA_Terr->SetNumber(pP->GetArmies()->GetAnArmy());
	pMT->AddChild(pA_Terr);	//add an army to a territory.
	PostMessage(pMSG->hWind,pMSG->ReplyCmd,AIM_NEXTSTATE,0);
	if(pLog) fprintf(pLog,"  Choose:loop=%d\n",loop);
}


extern "C" void DefaultDefend(void *pParam,CMap *pM,CPlayer *pP,AMSG *pMsg)
{
	/****************************************************
	** To defend or not to defend, that is the question
	** Function:DefaultDefend
	**	This function is used to make the decision of
	** wheather to defend or surrender, and what sort
	** of defense strategy to use.
	****************************************************/
}

extern "C" char *DefaultName(void)
{
	if(pLog == 0)
	{
//		pLog = fopen("Log.txt","w");
	}
	return "Default AI";
}

extern "C" void *DefaultGetParams(void)
{
	AIPARAMS *pAiParm = new (AIPARAMS);
	//set the default values of parameters
	pAiParm->PlaceAttackTerrWeight = 5;
	pAiParm->PlaceEnemyTerrWeight = 5;
	return (void *)pAiParm;
}

extern "C" int DefaultGetParamSize(void)
{
	return sizeof(AIPARAMS);
}

extern "C" int DefaultGetParamIndex(int ParamNumber)
{
	return 0;
}

extern "C" int DefaultGetTotalParams(void)
{
	return 0;
}

extern "C" int DefaultSetParameter(void *pParams, int ParamNumber, long value)
{
	return 0;
}

extern "C" int DefaultGetParameter(void *pParams, int ParamNumber)
{
	return 0;
}

extern "C" void DefaultEditParamDLG(void *pParams)
{
	CAiParamEditDlg Dlg;

	Dlg.m_pParams = (AIPARAMS *)pParams;
	Dlg.DoModal();

}

void Stats(CPlayer *pL)
{
	CListTerritory *pTL;
	CMapTerritory *pMT;

	while(pL)
	{
		int Armies = 0;
		int TT = 0;
		int ALLterr = 0;
		pTL = (CListTerritory *)pL->GetOccupiedTerritories()->GetHead();
		if(pLog) fprintf(pLog,"--------Stats for Player::%s---------\n",pL->GetName());
		while(pTL)
		{
			++TT;
			pMT = pTL->GetTerr();
			Armies += pMT->FindArmies()->GetNumber();
			if(pLog) fprintf(pLog,"  TERR %s  Armies:%d\n",pMT->GetName(),pMT->FindArmies()->GetNumber());
			pTL = (CListTerritory *)pTL->GetNext();
		}
		if(pLog) fprintf(pLog,"Total Territories:%d  Total Armies:%d\n",TT,Armies);
		if(pLog) fprintf(pLog,"************************************\n");
		pL = pL->GetNext();
	}
	if(pLog) fflush(pLog);
}

FILE *GetFile(void)
{
	if(pLog == 0)
	{
//		pLog = fopen("Log.txt","w");
	}
	return pLog;
}
