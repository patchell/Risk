#if !defined(AFX_STATICBITMAP_H__FD310F6F_F782_4DA5_AB97_5A827E9D84E4__INCLUDED_)
#define AFX_STATICBITMAP_H__FD310F6F_F782_4DA5_AB97_5A827E9D84E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StaticBitmap.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStaticBitmap window

class CStaticBitmap : public CStatic
{
// Construction
public:
	CStaticBitmap();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticBitmap)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	void Init(void);
	COLORREF m_Color;
	void SetColor(COLORREF vC);
	COLORREF GetColor(void);
	CBitmap * m_pBM;
	virtual ~CStaticBitmap();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStaticBitmap)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICBITMAP_H__FD310F6F_F782_4DA5_AB97_5A827E9D84E4__INCLUDED_)
