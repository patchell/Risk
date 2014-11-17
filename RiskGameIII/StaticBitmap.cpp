// StaticBitmap.cpp : implementation file
//

#include "stdafx.h"
#include "StaticBitmap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStaticBitmap

CStaticBitmap::CStaticBitmap()
{
	m_pBM = new CBitmap();	//construct bitmap object
	m_Color = RGB(0,0,0);	//default color
}

CStaticBitmap::~CStaticBitmap()
{
	delete m_pBM;
}


BEGIN_MESSAGE_MAP(CStaticBitmap, CStatic)
	//{{AFX_MSG_MAP(CStaticBitmap)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticBitmap message handlers

void CStaticBitmap::OnPaint()
{
	/*********************************
	** OnPaint
	**
	** This function is what displays
	** the bitmap in the dialog box
	*********************************/
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here
	CBitmap *pOld;	//stores the old context
	CBrush Br;		//our brush object
	CRect Rect;		//put the client rectangel here

	CDC MemDC;	//create a memory Device Context
	MemDC.CreateCompatibleDC(&dc);	//make compatable with client
	pOld = MemDC.SelectObject(m_pBM);	//select in bitmap
	Br.CreateSolidBrush(this->m_Color);	//create brush
	GetClientRect(&Rect);	//get sisize of rectangle
	MemDC.FillRect(&Rect,&Br);	//make it a solid color
	dc.BitBlt(0,0,Rect.right,Rect.bottom,&MemDC,0,0,SRCCOPY);	//copy memDC to client
	MemDC.SelectObject(pOld);	//restore context
	// Do not call CStatic::OnPaint() for painting messages
}

COLORREF CStaticBitmap::GetColor()
{
	/*************************************
	** GetColor
	**	This function gets the current color
	** of the bitmap.
	**
	** Returns value of color
	*************************************/
	CClientDC DC(this);	//get the device context
	CDC MemDC;
	COLORREF rC;
	///create a compatable memory DC
	MemDC.CreateCompatibleDC(&DC);
	CBitmap *pOld;
	///select in the memory context
	pOld = MemDC.SelectObject(m_pBM);
	///Get the color of pixel at 0,0
	rC = MemDC.GetPixel(0,0);
	MemDC.SelectObject(pOld);
	return rC;
}

void CStaticBitmap::SetColor(COLORREF vC)
{
	/*****************************************
	** SetColor
	**	Set the color of the bitmap
	**
	** parameter:
	**	vC.....color to set bitmap to
	*****************************************/
	m_Color = vC;
	Invalidate();	//redraw bitmap
}

BOOL CStaticBitmap::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class
//	HBITMAP handle = GetBitmap();
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CStaticBitmap::Init()
{
	/*****************************
	** Init
	**
	** This function is a KLUGE
	** It is used to get the size
	** of the client rectqanble
	** so we can create a bitmap
	******************************/
	int H,W;

	CRect Rect;
	GetClientRect(&Rect);
	H = Rect.Height();
	W = Rect.Width();
	m_pBM->CreateBitmap(W,H,1,32,0);
}
