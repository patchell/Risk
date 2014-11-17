// Thread.cpp: implementation of the CThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thread.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CThread, CMyThread)

CThread::CThread():CMyThread(CMyThread::Worker)
{

}

CThread::~CThread()
{

}

/*********************************************
** Proc
**
**	This is what actually executes when the 
** thread is running.
********************************************/

UINT CThread::Proc()
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
			//Send a message back to where it came from
			::PostMessage(pMsg->hWind,pMsg->ReplyCmd,pMsg->MsgCmd,count);
			//Delete the message
			DeleteAMSG(pMsg);
		}
	}
	return 0;
}
