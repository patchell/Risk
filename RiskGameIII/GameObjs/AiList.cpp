// AiList.cpp: implementation of the CAiList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AiList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAiList::CAiList()
{
	m_pNext = 0;
}

CAiList::~CAiList()
{

}

void CAiList::SetFuncs(int function,void *pF)
{
	switch(function)
	{
		case AIFUNC_ATTACK:
			m_Funcs.Attack = (void (*)(void *pParam,CMap *, CPlayer *, AMSG *pMsg))pF;
			break;
		case AIFUNC_CHOOSE:
			m_Funcs.Choose = (void (*)(void *pParam,CMap *pM,CPlayer *pP,AMSG *pMsg))pF;
			break;
		case AIFUNC_PLACE:
			m_Funcs.Place = (void (*)(void *pParam, CMap *pM, CPlayer *pPlayer,AMSG *pMsg))pF;
			break;
		case AIFUNC_CARDS:
			m_Funcs.Cards = (void (*)(void *pParam,CMap *pM, CPlayer *pPlayer,AMSG *pMsg))pF;
			break;
		case AIFUNC_NAME:
			m_Funcs.Name = (char *(*)(void))pF;
			break;
		case AIFUNC_ATFROM:
			m_Funcs.AttackFrom = (void (*)(void *pParam,CMap *, CPlayer *, AMSG *pMsg) )pF;
			break;
		case AIFUNC_WAR:
			m_Funcs.War = (void (*)(void *pParam,CMap *pM,CPlayer *pP,AMSG *pMsg))pF;
			break;
		case AIFUNC_FREEMOVE:
			m_Funcs.FreeMove = (void (*)(CMap *pM,CPlayer *pPlayer,AMSG *pMsg))pF;
			break;
		case AIFUNC_DEFEND:
			m_Funcs.Defend = (void (*)(void *pParam, CMap *pM,CPlayer *pP,AMSG *pMsg))pF;
			break;
		case AIFUNC_GETPARAM:
			m_Funcs.GetParams = (void *(*)(void))pF;
			break;
		case AIFUNC_PARAMSIZ:
			m_Funcs.GetParamSize = (int (*)(void))pF;
			break;
		case AIFUNC_PARAMIDX:
			m_Funcs.GetParamIndex = (int (*)(int ParamNumber))pF;
			break;
		case AIFUNC_PARAMTOT:
			m_Funcs.GetTotalParams = (int (*)(void))pF;
			break;
		case AIFUNC_PARAMSET:
			m_Funcs.SetParameter = (int (*)(void *pParams, int ParamNumber, long value))pF;
			break;
		case AIFUNC_PARAMGET:
			m_Funcs.GetParameter = (int (*)(void *pParams, int ParamNumber))pF;
			break;
		case AIFUNC_PARMEDIT:
			m_Funcs.EditParamDLG = (void (*)(void *pParams))pF;
			break;
		case AIFUNC_OCCUPY:
			m_Funcs.Occupy = (void (*)(void *pParam, CMap *pM,CPlayer *pP,AMSG *pMsg))pF;
			break;
	}
}

AIFUNCS *CAiList::GetFuncs(void)
{
	return &m_Funcs;
}

void *CAiList::GetFuncs(int function)
{
	void *rV = 0;
	switch(function)
	{
		case AIFUNC_ATTACK:
			rV = (void *)m_Funcs.Attack;
			break;
		case AIFUNC_CHOOSE:
			rV = (void *)m_Funcs.Choose;
			break;
		case AIFUNC_PLACE:
			rV = (void *)m_Funcs.Place;
			break;
		case AIFUNC_CARDS:
			rV = (void *)m_Funcs.Cards;
			break;
		case AIFUNC_NAME:
			rV = (void *)m_Funcs.Name;
			break;
		case AIFUNC_ATFROM:
			rV = (void *)m_Funcs.AttackFrom;
			break;
		case AIFUNC_WAR:
			rV = (void *)m_Funcs.War;
			break;
		case AIFUNC_FREEMOVE:
			rV = (void *)m_Funcs.FreeMove;
			break;
		case AIFUNC_DEFEND:
			rV = (void *)m_Funcs.Defend;
			break;
		case AIFUNC_GETPARAM:
			rV = (void *)m_Funcs.GetParams;
			break;
		case AIFUNC_PARAMSIZ:
			rV = (void *)m_Funcs.GetParamSize;
			break;
		case AIFUNC_PARAMIDX:
			rV = (void *)m_Funcs.GetParamIndex;
			break;
		case AIFUNC_PARAMTOT:
			rV = (void *)m_Funcs.GetTotalParams;
			break;
		case AIFUNC_PARAMSET:
			rV = (void *)m_Funcs.SetParameter;
			break;
		case AIFUNC_PARAMGET:
			rV = (void *)m_Funcs.GetParameter;
			break;
		case AIFUNC_PARMEDIT:
			rV = (void *)m_Funcs.EditParamDLG;
			break;
		case AIFUNC_OCCUPY:
			rV = (void *)m_Funcs.Occupy;
			break;
	}
	return rV;
}

