// List.h: interface for the CList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIST_H__A1B4D05A_5656_4D4C_BB95_6797BA578F49__INCLUDED_)
#define AFX_LIST_H__A1B4D05A_5656_4D4C_BB95_6797BA578F49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Bucket.h"

#ifndef DLLexport
#define DLLexport	__declspec(dllexport)
#endif

class DLLexport CList
{
	CBucket *m_pList,*m_pListEnd;
	int m_Count;
	public:
		/** Default constructor */
		CList();
		/** Default destructor */
		virtual ~CList();
		/** Operations	*/
		inline int GetCount(void){return m_Count;}
		CBucket *Del(CBucket *pB);
		void ADD(CBucket *pB);
		inline CBucket *GetHead(void){return m_pList;}
		inline CBucket *GetTail(void){return m_pListEnd;}
	protected:
	private:
};

#endif // !defined(AFX_LIST_H__A1B4D05A_5656_4D4C_BB95_6797BA578F49__INCLUDED_)
