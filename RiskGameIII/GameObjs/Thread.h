// Thread.h: interface for the CThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREAD_H__1DD5F1E0_A0E0_4C43_90A3_16335A426D40__INCLUDED_)
#define AFX_THREAD_H__1DD5F1E0_A0E0_4C43_90A3_16335A426D40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyThread.h"

#ifndef DLLexport
#define DLLexport	__declspec(dllexport)
#endif

class DLLexport CThread : public CMyThread  
{
	DECLARE_DYNCREATE(CThread)
public:
	virtual UINT Proc(void);
	CThread();
	virtual ~CThread();

};

#endif // !defined(AFX_THREAD_H__1DD5F1E0_A0E0_4C43_90A3_16335A426D40__INCLUDED_)
