// Bucket.h: interface for the CBucket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUCKET_H__74F72DED_3DCC_482F_BFB3_481B028F1993__INCLUDED_)
#define AFX_BUCKET_H__74F72DED_3DCC_482F_BFB3_481B028F1993__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef DLLexport
#define DLLexport	__declspec(dllexport)
#endif

class DLLexport CBucket
{
	CBucket *m_pNext;
	CBucket *m_pPrev;
	public:
		/** Default constructor */
		CBucket();
		/** Default destructor */
		virtual ~CBucket();
		/** Operations	*/
		inline CBucket *GetNext(void){return m_pNext;}
		inline CBucket *GetPrev(void){return m_pPrev;}
		inline void SetNext(CBucket *pN){m_pNext = pN;}
		inline void SetPrev(CBucket *pP){m_pPrev = pP;}
	protected:
	private:
};

#endif // !defined(AFX_BUCKET_H__74F72DED_3DCC_482F_BFB3_481B028F1993__INCLUDED_)
