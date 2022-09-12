// RiskAI.h : main header file for the RiskAI DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CRiskAIApp
// See RiskAI.cpp for the implementation of this class
//

class CRiskAIApp : public CWinApp
{
public:
	CRiskAIApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
