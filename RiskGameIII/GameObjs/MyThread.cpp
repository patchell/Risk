// MyThread.cpp : implementation file
//

#include "stdafx.h"
#include "MyThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyThread

IMPLEMENT_DYNCREATE(CMyThread, CWinThread)

CMyThread::CMyThread(AFX_THREADPROC pProc):CWinThread(pProc,NULL)
{
     m_bAutoDelete = FALSE;
     m_ShutdownEvent = ::CreateEvent(NULL,   // security
                                   TRUE,   // manual-reset
                                   FALSE,  // not signaled
                                   NULL);  // anonymous

     m_PauseEvent = ::CreateEvent(NULL,      // security
                                TRUE,      // manual-reset
                                FALSE,      //not signaled
                                NULL);     // anonymouse
	m_NwaitObjs = 0;
	memset(this->m_WaitObjects,0,sizeof(HANDLE) * 16);
	m_MSGQ = 0;	// Queue is created at create time
	//--------------------------------------------
	// m_pThreadParams is an undocumented data
	// member of CWinThread.  We set it to this
	// so that it can be passed to our thread
	// function
	//--------------------------------------------
	m_pThreadParams = this;
}

CMyThread::~CMyThread()
{
	::CloseHandle(m_PauseEvent);
	::CloseHandle(m_ShutdownEvent);
	if(m_MSGQ) delete m_MSGQ;
}

BOOL CMyThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CMyThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CMyThread, CWinThread)
	//{{AFX_MSG_MAP(CMyThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyThread message handlers

/***********************************************
** Worker
**
**	This is the worker thread.  It calls the
** Proc member function.  This is a virtual
** function and should be overriden in the
** class derived from this one with the
** guts of what you want the worker thead to do.
**
** Parameters:
**
**	pP......pointer to the thread class data
**			i.e. 'this'.
***********************************************/

UINT CMyThread::Worker(void *pP)
{
	CMyThread *pMT = (CMyThread *)pP;
	return pMT->Proc();
}

/***********************************************
** BeginThread
**	You call this thread to start execution of
** of the worker thread.
**
** Paramters:
** MsgQDepth....size of the message QUEUE that
**				is used to notify the thread
**				of the jobs it needs to do.
***********************************************/
int CMyThread::BeginThread(int MsgQDepth)
{
	int thread=0;
	SetWaitObject(m_ShutdownEvent,MT_SHUTDOWN);
	m_MSGQ = new CMsgQueue(MsgQDepth);
	SetWaitObject(m_MSGQ->GetSem()->GetHandle(),MT_MESSAGE);
	SetWaitObject(m_PauseEvent,MT_RUNNING);
    if(!CreateThread(0,0 ))
    { /* failed */
       thread = 1;
    } /* failed */
    return thread;
}

void CMyThread::ShutDown()
{
	SetEvent(m_ShutdownEvent);
	::WaitForSingleObject(m_hThread, INFINITE);
}

/**************************************************
** Wait
**
** This function waits on event objects.  The
** three default objects are to cause a QUIT,
** PAUSE, and MESSAGE AVAILIABLE
**
** Return Value:
** Depends on how this function is called.
** It should return 0 when you request that
** the tread terminate.
**************************************************/

DWORD CMyThread::Wait()
{
    DWORD result = ::WaitForMultipleObjects(this->m_NwaitObjs, this->m_WaitObjects, FALSE, INFINITE);

    switch(result)
    { /* result */
		case WAIT_TIMEOUT:
			result =  MT_TIMEOUT;
			break;
		default:
			if(result <= WAIT_OBJECT_0+16)
			{
				result = m_WaitRetVals[result - WAIT_OBJECT_0];
			}
			else
				result =  MT_ERROR;
			break;
	} /* end of switch(result) */
	return result;
 }

void CMyThread::Pause()
{
	ResetEvent(m_PauseEvent);
}

void CMyThread::Continue()
{
	SetEvent(m_PauseEvent);
}

/****************************************************
** SetWaitObject
**
** Sets an object to wait for in the thread.  It should
** be noted that the first element posted in here is
** the first one (Highest Priority) that will be
** reported.  So, if your object doesn't seem to
** be doing anything, maybe there is another one
** that is signaled ahead of it.
** For instance, if the m_PauseEvent is signaled,
** i.e. runing, the MessageQueue will not seem to
** get through in the current order.
**
** Paramters:
**	hObj......handle of the event object to add
**	RetVal....Value that is to be returned by Wait()
**			  If this object is signaled.
**
** Return value:
**	Returns 0 on success
**	Returns 1 on FAIL
****************************************************/

int CMyThread::SetWaitObject(HANDLE hObj, DWORD RetVal)
{
	int rV = 1;
	if(m_NwaitObjs < 16)
	{
		m_WaitObjects[m_NwaitObjs] = hObj;
		m_WaitRetVals[m_NwaitObjs++] = RetVal;
		rV = 0;
	}
	return rV;
}

/********************************************
** ClearWaitObjects
**
** This function is used to clear the objects
** that we are waiting for.  DO NOT DO THIS
** WHILE the THREAD IS RUNNING!
*********************************************/

void CMyThread::ClearWaitObjects()
{
	memset(m_WaitObjects,0,sizeof(HANDLE) * 16);
	m_NwaitObjs = 0;
}
