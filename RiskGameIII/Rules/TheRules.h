#ifndef THERULES__H
#define THERULES__H

#include "MapTerritory.h"

//-----------------------------------
// Stratagy data
//-----------------------------------
// Stratagy IDs
//------------------------------------
#define STRATTAGY_ROCK		1
#define STRATTAGY_PAPER		2
#define STRATTAGY_SCISSORS	3

typedef struct {
	char Name[32];
	int Id;
}STRATAGY;

//------------------------------------
// export functions
//------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

__declspec(dllexport) int ConductWar(CMapTerritory *pAttacker, CMapTerritory *pDefender,int AtkrStrat, int DfndrStrat);
__declspec(dllexport) void GetAttackStratagies(CMapTerritory *pMT, STRATAGY **ppSB, int *n);
__declspec(dllexport) void GetDefenseStratagies(CMapTerritory *pMT, STRATAGY **ppSB, int *n);
#ifdef __cplusplus
}
#endif

#endif
