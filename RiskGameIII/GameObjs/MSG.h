// MSG.h: interface for the MSG class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSG_H__2A5D1A1E_54DB_48DF_A7F1_1D4FCD987644__INCLUDED_)
#define AFX_MSG_H__2A5D1A1E_54DB_48DF_A7F1_1D4FCD987644__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyHeap.h"
#include "Lock.h"
#include "MySem.h"

#ifndef DLLexport
#define DLLexport	__declspec(dllexport)
#endif

class DLLexport AMSG  
{
public:
	short int MsgCmd;		//command for packet
	short int PayloadSize;	//size of payload in bytes
	short int MaxPayLoad;	//Maximum size of payload
	short int ReplyCmd;		//Reply command
	int Aux;				//Auxillary data
	HWND hWind;				//handle of window to replay to
	AMSG *next;
	char *Payload;
	AMSG();
	virtual ~AMSG();
	void PrepareMessage();
};

DLLexport  AMSG *CreateAMSG(unsigned nPayloadSize,char *npPayLoad,short int Cmd);
DLLexport  void DeleteAMSG(AMSG *pMSG);
DLLexport  void AMSGSetHeap(CMyHeap *pH);


class DLLexport CMsgQueue  
{
	unsigned m_Nmsg;
	unsigned m_Tail;
	unsigned m_Head;
	unsigned m_Size;
	AMSG ** m_pMsgQueue;
	CDMLock * m_pMBlocker;
	CMySem *m_pSem;
public:
	void Insert(AMSG *pM);
	AMSG * Remove(void);
	CMsgQueue(unsigned depth);
	virtual ~CMsgQueue();
	CMySem *GetSem(void);
};

#endif // !defined(AFX_MSG_H__2A5D1A1E_54DB_48DF_A7F1_1D4FCD987644__INCLUDED_)
