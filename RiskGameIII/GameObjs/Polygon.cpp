// Polygon.cpp: implementation of the CPolygon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Polygon.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static int IDcount=0;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPolygon::CPolygon()
{
	m_pVertex = new CPoint[256];		//pointer to array of vertexes
	m_Count = 0;
	m_size = 256;
	m_pNext = 0;
	m_PolyID = ++IDcount;
	m_pT = 0;
	m_Selected = 0;	//initial not selected
	m_MinX = m_MinY = m_MaxX = m_MaxY = 0;
}

CPolygon::CPolygon(int size)
{
	m_pVertex = new CPoint[size];		//pointer to array of vertexes
	m_Count = 0;
	m_size = size;
	m_pNext = 0;
	m_PolyID = ++IDcount;
	m_pT = 0;
	m_Selected = 0;	//initial not selected
	m_MinX = m_MinY = m_MaxX = m_MaxY = 0;
}

CPolygon::~CPolygon()
{
	delete[] m_pVertex;
}

void CPolygon::Create(CPoint *)
{

}

BOOL CPolygon::PointEnclosed(CPoint nP)
{
	/*****************************************
	** PointEnclosed
	**	This function determines if a point
	** is enclosed within a polygon.
	**
	** parameters:
	**	nP....point to test
	** Returns: TRUE if point inside
	**          FALSE if point is outside
	*****************************************/
	int   i, j=m_Count-1 ;
	BOOL  Enclosed=0      ;
	int Xintercept;

	//--------------------------------------------
	// Do a precheck agains the rectangle that
	// encloses the polygon
	//--------------------------------------------
	if(m_MinX < nP.x && m_MaxX > nP.x && m_MinY < nP.y && m_MaxY > nP.y)
	{
		//----------------------------------
		// very good chance now that point
		// is in polygon, so make a 
		// thorough check
		//---------------------------------
		for (i=0; i<m_Count; i++)
		{
			if (( (m_pVertex[i].y< nP.y && m_pVertex[j].y>=nP.y)
				|| (m_pVertex[j].y< nP.y && m_pVertex[i].y>=nP.y))
				&&  (m_pVertex[i].x<=nP.x || m_pVertex[j].x<=nP.x) )
			{
				Xintercept = m_pVertex[i].x+((nP.y-m_pVertex[i].y)*(m_pVertex[j].x-m_pVertex[i].x))/(m_pVertex[j].y-m_pVertex[i].y);
				Enclosed ^= Xintercept < nP.x;
			}
			j=i;
		}
	}
	return Enclosed;
}

void CPolygon::AddPoint(CPoint nP)
{
	/*************************************
	** AddPoint
	**
	** Adds a new vertex to the polygon.
	**
	** parameters:
	**	nP....point of the new vertex.
	*************************************/
	m_pVertex[m_Count] = nP;
	//------------------------------------------
	// Create a rectangle that enbloses polygon
	//------------------------------------------
	if(m_Count == 0)
	{
		m_MinX = nP.x;
		m_MaxX = nP.x;
		m_MinY = nP.y;
		m_MaxY = nP.y;
	}
	else
	{
		if(nP.x > m_MaxX) m_MaxX = nP.x;
		else if (m_MinX > nP.x) m_MinX = nP.x;
		if(nP.y > m_MaxY) m_MaxY = nP.y;
		else if(m_MinY > nP.y) m_MinY = nP.y;
	}
	++m_Count;
}

int CPolygon::GetCount()
{
	/***********************************
	** GetCount
	**	Retturns the number of points
	** (verticies) in the polygon
	***********************************/
	return m_Count;
}

int CPolygon::DeleteLastPoint()
{
	/**********************************
	** DeleteLastPoint
	**	Deletes last point added to
	** polygon.
	** RETURNS:new vertex count.
	**********************************/
	if(m_Count > 0)
		--m_Count;
	return m_Count;
}

int CPolygon::CompareToLast(CPoint nP)
{
	/*********************************
	** CompareToLast
	**	This function compares a point
	** to the last point that was added
	**to a polygon.
	**
	** parameter:
	**	nP.....point to compare
	**
	** REtuns: TRUE if equal
	**	       FALSE if not equal.
	*********************************/
	int rV = 0;
	if(nP == m_pVertex[m_Count - 1])
		rV = 1;
	return rV;
}

CPoint * CPolygon::GetPoints()
{
	/*************************************
	** GetPoints
	**
	** Returns the list of points that
	** define the polygon.
	*************************************/
	return m_pVertex;
}

void CPolygon::Copy(CPolygon *pP)
{
	/************************************
	** Copy
	**
	** This function is used to copy
	** another polygon into this polygon
	**
	** parameter:
	**	pP.....pointer of polygon to copy
	************************************/
	int i;
	CPoint *pPA = pP->GetPoints();
	this->SetTerritory(pP->GetTerritory());
	this->SetSize(pP->GetSize());
	this->SetCount(pP->GetCount());
	m_MinX = pP->m_MinX;
	m_MinY = pP->m_MinY;
	m_MaxX = pP->m_MaxX;
	m_MaxY = pP->m_MaxY;

	for(i=0;i<m_Count;++i)
	{
		this->m_pVertex[i] = pPA[i];
	}
}

void CPolygon::Reset()
{
	m_Count = 0;
	m_Selected = 0;	//initial not selected
}

void CPolygon::Print(FILE *pO)
{
	/************************************
	** Print
	**
	** Saves polygon to a file in ascii
	** format.
	**
	** parameter:
	** pO......pointer to file to save to
	************************************/
	int i;
	if(this->m_pT)
		fprintf(pO,"POLYGON::(\"%s\")[\n",m_pT->GetName());
	else
		fprintf(pO,"POLYGON::[\n");
	for(i=0;i<m_Count;++i)
	{
		fprintf(pO,"  (%d,%d)\n",m_pVertex[i].x,m_pVertex[i].y);
	}
	fprintf(pO,"]\n");
}
