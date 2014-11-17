// Score.h: interface for the CScore class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCORE_H__6E2D9629_0A48_47B7_9429_BE7053FA5580__INCLUDED_)
#define AFX_SCORE_H__6E2D9629_0A48_47B7_9429_BE7053FA5580__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Bucket.h"
#include "MapTerritory.h"

#ifndef DLLexport
#define DLLexport	__declspec(dllexport)
#endif

class DLLexport CScore : public CBucket
{
	int m_Score;			//score value
	CMapTerritory *m_pT;	//territory we are scoring
	public:
		void Copy(CScore *pS);
		/** Default constructor */
		CScore();
		/** Default destructor */
		virtual ~CScore();
		inline void SetScore(int v){m_Score = v;}
		inline int GetScore(void){ return m_Score;}
		inline void SetTerr(CMapTerritory *pT){m_pT = pT;}
		inline CMapTerritory *GetTerr(void){return m_pT;}
	protected:
	private:
};

#endif // !defined(AFX_SCORE_H__6E2D9629_0A48_47B7_9429_BE7053FA5580__INCLUDED_)
