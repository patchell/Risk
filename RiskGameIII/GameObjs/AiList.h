// AiList.h: interface for the CAiList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AILIST_H__41CEB7B4_DAB4_4288_A3DA_6572C2287025__INCLUDED_)
#define AFX_AILIST_H__41CEB7B4_DAB4_4288_A3DA_6572C2287025__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\AiFuncs.h"
#include "MapTerritory.h"

#define AIFUNC_ATTACK	0
#define AIFUNC_CHOOSE	1
#define AIFUNC_PLACE	2
#define AIFUNC_CARDS	3
#define AIFUNC_NAME		4
#define AIFUNC_ATFROM	5	/*	Attack From	*/
#define AIFUNC_WAR		6	/*	Function to carry out battle	*/
#define AIFUNC_FREEMOVE	7	/*	Move your troops around	*/
#define AIFUNC_DEFEND	8	/*	Called during a battle so defending player can respond	*/
#define AIFUNC_GETPARAM	9	/*	Get pointer to AI parameters block	*/
#define AIFUNC_PARAMSIZ	10	/*	Get side of param block in bytes	*/
#define AIFUNC_PARAMIDX	11	//	Get byte index of parameter in block	*/
#define AIFUNC_PARAMTOT	12	//	Get Total number of parameters
#define AIFUNC_PARAMSET	13	//	Set the value of a parameter
#define AIFUNC_PARAMGET	14	//	Get the value of a parameter
#define AIFUNC_PARMEDIT	15	//	Edit a parameter block
#define AIFUNC_OCCUPY	16	//	Occupy a newly conqured territory

#ifndef DLLexport
#define DLLexport	__declspec(dllexport)
#endif


class DLLexport CAiList  
{
	AIFUNCS m_Funcs;
	CAiList *m_pNext;
public:
	CAiList();
	virtual ~CAiList();
	void SetNext(CAiList *pN){m_pNext = pN;}
	CAiList *GetNext(void) {return m_pNext;}
	void SetFuncs(int Func,void *);
	void *GetFuncs(int Func);
	AIFUNCS *GetFuncs(void);

};

#endif // !defined(AFX_AILIST_H__41CEB7B4_DAB4_4288_A3DA_6572C2287025__INCLUDED_)
