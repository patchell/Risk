#include "stdafx.h"
#include "Rules.h"
#include "TheRules.h"

static STRATAGY Strats[] = {
	{"Rock",STRATTAGY_ROCK},
	{"Paper",STRATTAGY_PAPER},
	{"Scissors",STRATTAGY_SCISSORS}
};

#ifdef __cplusplus
extern "C" {
#endif


__declspec(dllexport) int ConductWar(CMapTerritory *pAttacker, CMapTerritory *pDefender,int AtkrStrat, int DfndrStrat)
{
	int Result;	//0=tie,1 = Attacker, -1 = Defender

	switch(AtkrStrat)
	{
		case STRATTAGY_ROCK:
			switch(DfndrStrat)
			{
				case STRATTAGY_ROCK:
					Result = 0;	//tie
					break;
				case STRATTAGY_PAPER:
					Result = -1;	//paper covers rock
					break;
				case STRATTAGY_SCISSORS:
					Result = 1;	//Rock Breaks Scissors
					break;
			}
			break;
		case STRATTAGY_PAPER:
			switch(DfndrStrat)
			{
				case STRATTAGY_ROCK:
					Result = 1;	//Paper covers rock
					break;
				case STRATTAGY_PAPER:
					Result = 0;	//tie
					break;
				case STRATTAGY_SCISSORS:
					Result = -1;	//scissors cut paper
					break;
			}
			break;
		case STRATTAGY_SCISSORS:
			switch(DfndrStrat)
			{
				case STRATTAGY_ROCK:
					Result = -1;	//rock breaks scissors
					break;
				case STRATTAGY_PAPER:
					Result = 1;	//Scissors cut paper
					break;
				case STRATTAGY_SCISSORS:
					Result = 0;	//tie
					break;
			}
			break;
	}
	if(Result == 1)	//attacker winds
	{
		pDefender->FindArmies()->GetAnArmy();	//just loose the army
	}
	else if(Result == 0)	//tie
	{
		//Both loose
		pAttacker->FindArmies()->GetAnArmy();	//just loose the army
		pDefender->FindArmies()->GetAnArmy();	//just loose the army
	}
	else
	{
		pAttacker->FindArmies()->GetAnArmy();	//just loose the army
	}
	return Result;
}

__declspec(dllexport) void GetAttackStratagies(CMapTerritory *pMT, STRATAGY **ppSB, int *n)
{
	*ppSB = Strats;
	*n = 3 * sizeof(STRATAGY);	//size is in BYTES
}

__declspec(dllexport) void GetDefenseStratagies(CMapTerritory *pMT, STRATAGY **ppSB, int *n)
{
	*ppSB = Strats;
	*n = 3 * sizeof(STRATAGY);	//size is in BYTES
}


#ifdef __cplusplus
}
#endif
