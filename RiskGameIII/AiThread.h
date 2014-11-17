// AiThread.h: interface for the CAiThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AITHREAD_H__C4F7DD31_6799_407B_B9AF_C34CEE807648__INCLUDED_)
#define AFX_AITHREAD_H__C4F7DD31_6799_407B_B9AF_C34CEE807648__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyThread.h"
#include "Player.h"

/********************************
** Messages to AI plugin
********************************/

#define AIMSG_ATTACK			0
#define AIMSG_ATTACKFROM		1
#define AIMSG_CHOOSE			2
#define AIMSG_CARDS				3
#define AIMSG_DEFEND			4
#define AIMSG_FREEMOVE			5
#define AIMSG_GETPARAMBLOCK		6
#define AIMSG_GETPARAMETER		7
#define AIMSG_GETPARAMSIZE		8
#define AIMSG_GETPARAMINDEX		9
#define AIMSG_GETTOTALPARAMS	10
#define AIMSG_AINAME			11
#define AIMSG_PLACE				12
#define AIMSG_SETPARAMETER		13
#define AIMSG_WAR				14
#define AIMSG_OCCUPY			15

class CAiThread : public CMyThread  
{
	CMap * m_pMap;
	CPlayer *m_pPlayer;
public:
	HWND m_hWnd;
	void Attack(int Aux=0,void *pD=0,int sz=0);
	void AttackFrom(int Aux=0,void *pD=0,int sz=0);
	void Choose(void* pD=0,int sz=0);
	void Occupy(int Aux=0,void *pD=0,int sz=0);
	void Place(int Aux=0,void* pD=0,int sz=0);
	void War(int Aux=0,void *pD=0,int sz=0);
	virtual UINT Proc(void);
	CAiThread();
	virtual ~CAiThread();
	inline CPlayer *GetPlayer(void){return m_pPlayer;}
	inline void SetPlayer(CPlayer *pP){m_pPlayer = pP;}
	inline void SetMap(CMap *pM){m_pMap = pM;}
	inline AIFUNCS *GetAiFuncs(void){return GetPlayer()->GetAiFuncs();}
};

#endif // !defined(AFX_AITHREAD_H__C4F7DD31_6799_407B_B9AF_C34CEE807648__INCLUDED_)
