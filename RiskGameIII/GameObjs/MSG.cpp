// MSG.cpp: implementation of the MSG class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MSG.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

static CMyHeap *pHeap=0;

AMSG::AMSG()
{
}

AMSG::~AMSG()
{
}

void AMSG::PrepareMessage()
{
	PayloadSize = 0;
	MsgCmd = 0;
	next = 0;
}

AMSG *CreateAMSG(unsigned nPayloadSize,char *npPayLoad,short int Cmd)
{
	AMSG *pMSG;

	pMSG = (AMSG *)pHeap->Malloc(sizeof(AMSG) + nPayloadSize+1);

	pMSG->MaxPayLoad = nPayloadSize;
	pMSG->Payload = &( ((char *)pMSG)[sizeof(AMSG)]);
	if(nPayloadSize)
	{
		memcpy(pMSG->Payload,npPayLoad,nPayloadSize);
	}
	pMSG->PayloadSize = nPayloadSize;
	pMSG->next = 0;
	pMSG->MsgCmd = Cmd;
	return pMSG;
}

void DeleteAMSG(AMSG *pMSG)
{
	pHeap->Free((void *)pMSG);
}

void AMSGSetHeap(CMyHeap *pH)
{
	pHeap = pH;
}

//////////////////////////////////////////////////////////////////////
// CMsgQueue Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgQueue::CMsgQueue(unsigned QueueDepth)
{
	if(pHeap == 0)
	{
		pHeap = new CMyHeap(32768);
	}
	m_pMBlocker = new CDMLock(CString("MsgQueueBlocker"));
	m_pMsgQueue = new AMSG *[QueueDepth];
	m_pSem = new CMySem();
	m_pSem->Create(0,QueueDepth);
	m_Head = 0;
	m_Tail = 0;
	m_Size = QueueDepth;
	m_Nmsg = 0;
}

CMsgQueue::~CMsgQueue()
{
	delete [] m_pMsgQueue;
	delete m_pMBlocker;
}

AMSG * CMsgQueue::Remove()
{
	AMSG *pM;

	m_pMBlocker->Lock();
	pM = m_pMsgQueue[m_Tail++];
	if(m_Tail == m_Size)
		m_Tail = 0;		//wrap tail pointer
	m_Nmsg--;
	m_pMBlocker->Unlock();
	return pM;
}

void CMsgQueue::Insert(AMSG *pM)
{
	m_pMBlocker->Lock();
	m_pMsgQueue[m_Head++] = pM;
	if(m_Head == m_Size)
		m_Head = 0;
	m_Nmsg++;
	m_pSem->Post();
	m_pMBlocker->Unlock();
}

CMySem *CMsgQueue::GetSem(void)
{
	return m_pSem;
}