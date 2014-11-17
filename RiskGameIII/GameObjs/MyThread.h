#if !defined(AFX_MYTHREAD_H__8E751A48_34FC_4728_8936_F86BBCA1A433__INCLUDED_)
#define AFX_MYTHREAD_H__8E751A48_34FC_4728_8936_F86BBCA1A433__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyThread.h : header file
//

#include "MSG.h"

enum {  MT_SHUTDOWN = 0, MT_RUNNING, MT_MESSAGE, MT_ERROR = 0xffffffe,MT_TIMEOUT };

#ifndef DLLexport
#define DLLexport	__declspec(dllexport)
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyThread thread

class DLLexport CMyThread : public CWinThread
{
	DECLARE_DYNCREATE(CMyThread)
protected:
	CMyThread(){};           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	virtual UINT Proc(void){return 0;};
	CMsgQueue * m_MSGQ;
	int m_NwaitObjs;
	HANDLE m_WaitObjects[16];
	DWORD m_WaitRetVals[16];
	void ClearWaitObjects();
	int SetWaitObject(HANDLE hObj,DWORD RetVal);
	void Continue();
	void Pause(void);
	DWORD Wait(void);
	void ShutDown();
	int BeginThread(int MsgQDepth);
	static UINT Worker(void *pP);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	HANDLE m_PauseEvent;
	HANDLE m_ShutdownEvent;
	CMyThread(AFX_THREADPROC pProc);
	virtual ~CMyThread();

	// Generated message map functions
	//{{AFX_MSG(CMyThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTHREAD_H__8E751A48_34FC_4728_8936_F86BBCA1A433__INCLUDED_)
