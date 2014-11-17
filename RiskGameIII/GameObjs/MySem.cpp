// MySem.cpp: implementation of the CMySem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MySem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMySem::CMySem()
{
	SemObj = 0;		//initialize the semaphore event to 0
}

CMySem::~CMySem()
{
	if(SemObj) CloseHandle(SemObj);	//if opened, close the handle
}

/**********************************************
** Pend
**	This function is used to wait for the
** semaphore to be signaled
**********************************************/
DWORD CMySem::Pend()
{
	return WaitForSingleObject(SemObj,INFINITE);
}

/**********************************************
** Post
**	This function is used to signal the
** Semaphore
**********************************************/
void CMySem::Post()
{
	ReleaseSemaphore(SemObj,1,0);
}

/*********************************************
** GetHandle
**
**	This function is used to get the handle
** of the semaphore object.
*********************************************/
HANDLE CMySem::GetHandle()
{
	return SemObj;
}

/*********************************************
** Create
**	This function is used to create the
** semaphore object.  Call this function
** before using it.
**
** parameters:
**	initial....initial value of semaphore
**				0 => Not Signaled
**				0 < and > max : Signaled
**	max.......maximum value of semaphore
**
*********************************************/

void CMySem::Create(int initial, int max)
{
	SemObj = CreateSemaphore(NULL,initial,max,NULL);
}
