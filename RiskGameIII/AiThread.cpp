// AiThread.cpp: implementation of the CAiThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "riskgame.h"
#include "AiThread.h"
#include "WinMsg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAiThread::CAiThread():CMyThread(CMyThread::Worker)
{

}

CAiThread::~CAiThread()
{

}

/**********************************************
** Proc
**
** this is where we process messages from
** CRiskGameView.  Each player will have one
** of these thread descriptors, which is how
** we will keep them seperate
** currently I have the limit set at 20 players
** The data for each function call will be
** passed in the payload of an AMSG object
**********************************************/

UINT CAiThread::Proc()
{
	DWORD E;
	int count = 0;
	AMSG *pMsg;

	while(E = Wait())
	{
		if(E == MT_MESSAGE)
		{
			++count;
			//Get the message from the queue
			pMsg = m_MSGQ->Remove();
			switch(pMsg->MsgCmd)
			{
				case AIMSG_ATTACK:
					(*GetAiFuncs()->Attack)(m_pPlayer->GetParams(),m_pMap,m_pPlayer,pMsg);
					break;
				case AIMSG_ATTACKFROM:
					(*GetAiFuncs()->AttackFrom)(m_pPlayer->GetParams(),m_pMap,m_pPlayer,pMsg);
					break;
				case AIMSG_CHOOSE:
					(*GetAiFuncs()->Choose)(m_pPlayer->GetParams(),m_pMap,m_pPlayer,pMsg);
					break;
				case AIMSG_CARDS:
					break;
				case AIMSG_DEFEND:
					(*GetAiFuncs()->Defend)(m_pPlayer->GetParams(),m_pMap,m_pPlayer,pMsg);
					break;
				case AIMSG_FREEMOVE:
					break;
				case AIMSG_GETPARAMBLOCK:
					break;
				case AIMSG_GETPARAMETER:
					break;
				case AIMSG_GETPARAMSIZE:
					break;
				case AIMSG_GETPARAMINDEX:
					break;
				case AIMSG_GETTOTALPARAMS:
					break;
				case AIMSG_AINAME:
					break;
				case AIMSG_PLACE:
					(*GetAiFuncs()->Place)(m_pPlayer->GetParams(),m_pMap,m_pPlayer,pMsg);
					break;
				case AIMSG_SETPARAMETER:
					break;
				case AIMSG_WAR:
					(*GetAiFuncs()->War)(m_pPlayer->GetParams(),m_pMap,m_pPlayer,pMsg);
					break;
				case AIMSG_OCCUPY:
					(*GetAiFuncs()->Occupy)(m_pPlayer->GetParams(),m_pMap,m_pPlayer,pMsg);
					break;
			}
			//Delete the message
			DeleteAMSG(pMsg);
		}
	}
	return 0;
}

void CAiThread::Choose(void *payload,int sz)
{
	char *pTemp = (char *)payload;
	AMSG *pMSG = CreateAMSG(sz,(char *)&pTemp,AIMSG_CHOOSE);
	pMSG->hWind = m_hWnd;
	pMSG->ReplyCmd = WM_MSGFROMAI;
	this->m_MSGQ->Insert(pMSG);
}

void CAiThread::Place(int Aux,void *payload,int sz)
{
	char *pTemp = (char *)payload;
	AMSG *pMSG = CreateAMSG(sz,(char *)&pTemp,AIMSG_PLACE);
	pMSG->hWind = m_hWnd;
	pMSG->Aux = Aux;
	pMSG->ReplyCmd = WM_MSGFROMAI;
	this->m_MSGQ->Insert(pMSG);
}

void CAiThread::Attack(int Aux,void *payload,int sz)
{
	char *pTemp = (char *)payload;
	AMSG *pMSG = CreateAMSG(sz,(char *)&pTemp,AIMSG_ATTACK);
	pMSG->hWind = m_hWnd;
	pMSG->Aux = Aux;
	pMSG->ReplyCmd = WM_MSGFROMAI;
	this->m_MSGQ->Insert(pMSG);
}

void CAiThread::AttackFrom(int Aux,void *payload,int sz)
{
	char *pTemp = (char *)payload;
	AMSG *pMSG = CreateAMSG(sz,(char *)&pTemp,AIMSG_ATTACKFROM);
	pMSG->hWind = m_hWnd;
	pMSG->Aux = Aux;
	pMSG->ReplyCmd = WM_MSGFROMAI;
	this->m_MSGQ->Insert(pMSG);
}


void CAiThread::War(int Aux,void *payload,int sz)
{
	AMSG *pMSG = CreateAMSG(sz,(char *)payload,AIMSG_WAR);
	pMSG->hWind = m_hWnd;
	pMSG->Aux = Aux;
	pMSG->ReplyCmd = WM_MSGFROMAI;
	this->m_MSGQ->Insert(pMSG);
}

void CAiThread::Occupy(int Aux,void *payload,int sz)
{
	AMSG *pMSG = CreateAMSG(sz,(char *)payload,AIMSG_OCCUPY);
	pMSG->hWind = m_hWnd;
	pMSG->Aux = Aux;
	pMSG->ReplyCmd = WM_MSGFROMAI;
	this->m_MSGQ->Insert(pMSG);
}
