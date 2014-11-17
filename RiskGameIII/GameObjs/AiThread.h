// AiThread.h: interface for the CAiThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AITHREAD_H__A6FDC8A4_0ACF_437C_A585_1CADB21CCF77__INCLUDED_)
#define AFX_AITHREAD_H__A6FDC8A4_0ACF_437C_A585_1CADB21CCF77__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyThread.h"

class CAiThread : public CMyThread  
{
public:
	CAiThread();
	virtual ~CAiThread();

};

#endif // !defined(AFX_AITHREAD_H__A6FDC8A4_0ACF_437C_A585_1CADB21CCF77__INCLUDED_)
