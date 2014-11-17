// MapDataItem.cpp: implementation of the CMapDataItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapDataItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CMapDataItem::CMapDataItem()
{
	/***************************
	** CMapDataItem
	**
	** This is the constructor
	** for the CMapDataItem.
	** This is the base class
	** for the data items that
	** comprise a game map
	** Initiallizes all member
	** variables to the value
	** needed so that object
	** functions properly.
	***************************/
	m_Name = 0;
	m_Type = 0;
	m_Child = 0;	//no shildren
	m_Next = 0;		//no siblings
	m_ChildEnd = 0;
}


CMapDataItem::CMapDataItem(int T)
{
	/***************************
	** CMapDataItem
	**
	** This is the constructor
	** for the CMapDataItem.
	** This is the base class
	** for the data items that
	** comprise a game map
	** Initiallizes all member
	** variables to the value
	** needed so that object
	** functions properly.
	**
	** parameter:
	**	T.......object type
	***************************/
	m_Name = 0;
	m_Type = T;
	m_Child = 0;
	m_Next = 0;
}

CMapDataItem::~CMapDataItem()
{
	/*************************
	** ~CMapDataItem
	** Destructor for the
	** CMapDataItem object.
	** Cleans up things that
	** were allocated by this
	** class.
	*************************/
	if(m_Name) delete[] m_Name;
}

int CMapDataItem::IsType(int t)
{
	/*************************
	** IsType
	**
	** This function checks the
	** class type vrsus the
	** parameter.
	**
	** parameter:
	**	t....type value to compare
	**
	** RETURNS:True if t == Type
	*************************/
	return m_Type == t;
}

void CMapDataItem::SetName(char *s)
{
	/****************************
	** SetName
	**
	** This function sets the
	** object name.
	**
	** parameter:
	**	s.....pointer to name
	*****************************/
	if(m_Name == NULL)
		m_Name = new char[256];
	strcpy(m_Name,s);
}

char *CMapDataItem::GetName(void)
{
	/***********************
	** GetName
	**
	**	Get the name of the
	** object.
	***********************/
	return m_Name;
}


void CMapDataItem::SetType(int t)
{
	/***************************
	** SetType
	**
	** This function is used to
	** Set the object type
	**
	** parameter:
	**	t......type value of object
	***************************/
	m_Type = t;
}

int CMapDataItem::GetType(void)
{
	/*******************************
	** GetType
	**
	** This function is used to
	** return the Type of the object
	******************************/
	return m_Type;
}

/************************
	Strings that correspond
	to the various types
	of objects
*************************/

static const char  *const MapTypeStrings[] = {
	"base class",	//0
	"MAP",			//1
	"CONT",			//2
	"TERRITORY",	//3
	"ARMY",			//4
	"GENERAL",		//5
	"SHIP",			//6
	"CAPITOL",		//7
	"FORT",			//8
	"FACTORY",		//9
	"FARM"			//10
};

void CMapDataItem::PrintAll(FILE *pO)
{
	/**************************
	** PrintAll
	**
	** This function is used
	** to save the map data in
	** text (ascii) format to
	** a file.
	**
	** parameter:
	**	pO....pointer to output file
	**************************/
	CMapDataItem *pDM;
	static int Level = 0;
	char *s = new char[256];
	int i;

	for(i=0;i<Level;++i)
		s[i] = ' ';
	s[i] = 0;

	Level++;
	pDM = this;
	while(pDM)
	{
		fprintf(pO,"%s",s);
		pDM->Print(pO);
//		fprintf(pO,"%s%s::%s\n",s,MapTypeStrings[pDM->m_Type],pDM->m_Name);
		if(pDM->m_Child)
		{
			fprintf(pO,"%s{\n",s);
			pDM->m_Child->PrintAll(pO);
			fprintf(pO,"%s}\n",s);
		}
		pDM = pDM->m_Next;
	}
	Level--;
	delete[] s;
}

void CMapDataItem::Print(FILE *pO)
{
	/**************************
	** Print
	**
	** This function is used for
	** printing out just this
	** data object.  DEFAULT.
	**************************/
	fprintf(pO,"%s::%s\n",MapTypeStrings[this->m_Type],this->m_Name);
}

void CMapDataItem::AddChild(CMapDataItem *pChild)
{
	if(this->m_Child)
	{
		if(m_ChildEnd == 0) m_ChildEnd = m_Child;
		m_ChildEnd->SetNext(pChild);
		m_ChildEnd = pChild;
	}
	else
	{
		m_Child = pChild;
		m_ChildEnd = pChild;
	}
}
