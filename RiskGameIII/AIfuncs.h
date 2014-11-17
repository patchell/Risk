#ifndef AIFUNCS_H_INCLUDED
#define AIFUNCS_H_INCLUDED

#include "MSG.h"

#define AIM_NEXTSTATE		0
#define AIM_SELECTTERRITORY	1
#define AIM_PLACETERRITORY	2
#define AIM_DISTRIBUTEBONUS	3
#define AIM_SELECT_ATTACK	4
#define AIM_SELECT_FROM		5
#define AIM_WAR				6
#define AIM_BATTLE			7
#define AIM_OCCUPY			8

//------------------------------
// War States
//------------------------------

#define WAR_CHOOSE_ATTACK_STRAT		0
#define WAR_CHOOSE_DEFENSE_STRAT	1
#define WAR_BATTLE					2

class CMap;
class CMapTerritory;
class CPlayer;

typedef struct {
	int TotalArmies;
	int TotalTerritories;
	int TotalContinents;
	int TotalGenerals;
	int TotalForts;
	int TotalCapitols;
	int TotalCash;
	int TotalFactories;
	int TotalFarms;
	int TotalShips;
} ASSETS;

typedef struct {
	unsigned State:4;
	unsigned Strat:4;
}WAR_DATA;

typedef union {
	WAR_DATA wd;
	unsigned long v;
}WAR_DATA_MSG;

typedef struct {
	// These functions get a called direct
	char *(*Name)(void);	//get the anme of the AI
	void *(*GetParams)(void);
	int (*GetParamSize)(void);
	int (*GetParamIndex)(int ParamNumber);
	int (*GetTotalParams)(void);
	int (*SetParameter)(void *pParams, int ParamNumber, long value);
	int (*GetParameter)(void *pParams, int ParamNumber);
	void (*EditParamDLG)(void *pParams);
	// These functions get called through a THREAD
	void (*Attack)(void *pParam,CMap *pM, CPlayer *pPlayer,AMSG *pMsg);	//attack a territory
	void (*AttackFrom)(void *pParam,CMap *pM, CPlayer *pPlayer,AMSG *pMsg);	//Attack from
	void (*Cards)(void *pParam,CMap *pM, CPlayer *pPlayer,AMSG *pMsg);		//turn in cards
	void (*Choose)(void *pParam,CMap *pM,CPlayer *pP,AMSG *pMsg);	//choose a territory
	void (*Defend)(void *pParam, CMap *pM,CPlayer *pP,AMSG *pMsg);
	void (*FreeMove)(CMap *pM,CPlayer *pPlayer,AMSG *pMsg);	//troop movements
	void (*Occupy)(void *pParam, CMap *pM,CPlayer *pP,AMSG *pMsg);
	void (*Place)(void *pParam, CMap *pM, CPlayer *pPlayer,AMSG *pMsg);		//place assets on territory
	void (*War)(void *pParam,CMap *pM,CPlayer *pP,AMSG *pMsg);
}AIFUNCS;

typedef struct {
	int PlaceEnemyTerrWeight;
	int PlaceAttackTerrWeight;
}AIPARAMS;

typedef struct {
	CMapTerritory *pAttackFrom;
	CMapTerritory *pAttackTo;
}WAR_PAYLOAD;

#endif // AIFUNCS_H_INCLUDED
