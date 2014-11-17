// MapContinent.h: interface for the CMapContinent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPCONTINENT_H__3ACF9958_DB92_44D3_9F11_64D18F07761D__INCLUDED_)
#define AFX_MAPCONTINENT_H__3ACF9958_DB92_44D3_9F11_64D18F07761D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MapDataItem.h"
#include "Player.h"

#ifndef DLLexport
#define DLLexport	__declspec(dllexport)
#endif

class DLLexport CMapContinent : public CMapDataItem
{
	int m_Value;
	public:
		int IsOccupiedByPlayer(CPlayer *pP);
		/** Default constructor */
		CMapContinent();
		/** Default destructor */
		virtual ~CMapContinent();
		virtual void Print(FILE *pO);
		void SetValue(int v){m_Value = v;}
		int GetValue(void){return m_Value;}
	protected:
	private:
};

#endif // !defined(AFX_MAPCONTINENT_H__3ACF9958_DB92_44D3_9F11_64D18F07761D__INCLUDED_)
