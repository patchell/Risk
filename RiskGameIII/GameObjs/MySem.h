// MySem.h: interface for the CMySem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSEM_H__6B8DFEBC_204D_475A_8D96_938328062FDF__INCLUDED_)
#define AFX_MYSEM_H__6B8DFEBC_204D_475A_8D96_938328062FDF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef DLLexport
#define DLLexport	__declspec(dllexport)
#endif

class DLLexport CMySem  
{
public:
	void Create(int initial, int max);
	HANDLE GetHandle(void);
	void Post(void);
	DWORD Pend(void);
	CMySem();
	virtual ~CMySem();

private:
	HANDLE SemObj;
};

#endif // !defined(AFX_MYSEM_H__6B8DFEBC_204D_475A_8D96_938328062FDF__INCLUDED_)
