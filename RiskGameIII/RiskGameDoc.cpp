// RiskGameDoc.cpp : implementation of the CRiskGameDoc class
//

#include "stdafx.h"
#include "RiskGame.h"

#include "RiskGameDoc.h"
#include "RiskUtils.h"
#include "DefaultAi.h"
#include "ListTerritory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRiskGameDoc

static COLORREF StaticStockColors[16] = {
	RGB(64,70,30),
	RGB(255,0,0),
	RGB(0,255,0),
	RGB(0,100,250),
	RGB(255,255,0),
	RGB(255,0,255),
	RGB(0,255,255),
	RGB(128,0,0),
	RGB(0,128,0),
	RGB(0,0,128),
	RGB(128,128,0),
	RGB(128,0,128),
	RGB(0,128,128),
	RGB(255,255,64),
	RGB(255,64,255),
	RGB(64,255,255)
};

IMPLEMENT_DYNCREATE(CRiskGameDoc, CDocument)

BEGIN_MESSAGE_MAP(CRiskGameDoc, CDocument)
	//{{AFX_MSG_MAP(CRiskGameDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRiskGameDoc construction/destruction

CRiskGameDoc::CRiskGameDoc()
{
	// TODO: add one-time construction code here
	m_ListCards = 0;
	m_pMapData = 0;
	m_pPolyList = 0;
	m_pPolyEnd = 0;
	m_pLexBuff = new char[256];
	m_Unget_Buffer = 0;
	m_pAiList = 0;
	m_TotalPlayers = 4;	//gonna start with 4 players
	m_PlayerAiThreads = new CAiThread *[20];
	memset(m_PlayerAiThreads,0,sizeof(CAiThread *) * 20);
}

CRiskGameDoc::~CRiskGameDoc()
{
	delete[] m_pLexBuff;
	delete [] m_PlayerAiThreads;
}

BOOL CRiskGameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	m_pMapBM = new CMyBitmap;
	m_pMapBM->CreateBitmap(3600,2250,1,32,0);
	this->m_pMapBM->LoadBitmap("world.bmp");
	FILE *pIn = fopen("world.map","r");
	if(pIn)
	{
		this->m_pMapData = this->Parser(pIn);
		fclose(pIn);
		this->CreateCards(m_pMapData);
	}
	//******************************
	// Add AI plugins
	//******************************
	//Default Plugin
	//------------------------------

	CAiList *pAI = new CAiList;
	pAI->SetFuncs(AIFUNC_ATTACK,(void *)DefaultAttack);
	pAI->SetFuncs(AIFUNC_CHOOSE,(void *)DefaultChoose);
	pAI->SetFuncs(AIFUNC_PLACE,(void *)DefaultPlace);
	pAI->SetFuncs(AIFUNC_CARDS,(void *)DefaultCards);
	pAI->SetFuncs(AIFUNC_NAME,(void *)DefaultName);
	pAI->SetFuncs(AIFUNC_ATFROM,(void *)DefaultAttackFrom);
	pAI->SetFuncs(AIFUNC_WAR,(void *)DefaultWar);
	pAI->SetFuncs(AIFUNC_FREEMOVE,(void *)DefaultFreeMove);
	pAI->SetFuncs(AIFUNC_DEFEND,(void *)DefaultDefend);
	pAI->SetFuncs(AIFUNC_GETPARAM,(void *)DefaultGetParams);
	pAI->SetFuncs(AIFUNC_PARAMSIZ,(void *)DefaultGetParamSize);
	pAI->SetFuncs(AIFUNC_PARAMIDX,(void *)DefaultGetParamIndex);
	pAI->SetFuncs(AIFUNC_PARAMTOT,(void *)DefaultGetTotalParams);
	pAI->SetFuncs(AIFUNC_PARAMSET,(void *)DefaultSetParameter);
	pAI->SetFuncs(AIFUNC_PARAMGET,(void *)DefaultGetParameter);
	pAI->SetFuncs(AIFUNC_PARMEDIT,(void *)DefaultEditParamDLG);
	pAI->SetFuncs(AIFUNC_OCCUPY,(void *)DefaultOccupy);
	AddAi(pAI);	//add to AI list
	//******************************
	// Create initial players
	//******************************
	int i;

	for(i=0;i<m_TotalPlayers;++i)
		CreateNewPlayer(i,100);
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CRiskGameDoc serialization


void CRiskGameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRiskGameDoc diagnostics

#ifdef _DEBUG
void CRiskGameDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRiskGameDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRiskGameDoc commands

void CRiskGameDoc::AddPolygon(CPolygon *pP)
{
	if(m_pPolyList)
	{
		m_pPolyEnd->SetNext(pP);
		m_pPolyEnd = pP;
	}
	else
	{
		m_pPolyList = pP;
		m_pPolyEnd = pP;
	}

}


//******************************************
//** PARSER for reading in Map Data
//** Token defines for file reading parser
//******************************************

#define TOKEN_STRING	256
#define TOKEN_NUM		257
#define TOKEN_MAP		258
#define TOKEN_CONTINENT	259
#define TOKEN_TERRITORY	260
#define TOKEN_MERIDIAN	261
#define TOKEN_LONGITUDE	262
#define TOKEN_WIDTH		263
#define TOKEN_SPACING	264
#define TOKEN_START		265
#define TOKEN_END		266
#define TOKEN_RGB		267
#define TOKEN_HEIGHT	268
#define TOKEN_BORDER	269
#define TOKEN_COLOR		270
#define TOKEN_EOF		271
#define TOKEN_VALUE		272
#define TOKEN_LOCATION	273
#define TOKEN_POLYGON	274
#define TOKEN_ATTACHED	275
#define TOKEN_ADJ		276
#define TOKEN_ARMIES	277

//--------------
// keywords
//--------------

typedef struct {
	const char *pName;
	int tokenval;
}KEYWORD;

KEYWORD Keywords[] = {
	{"MAP",TOKEN_MAP},
	{"CONTINENT",TOKEN_CONTINENT},
	{"TERRITORY",TOKEN_TERRITORY},
	{"MERIDIAN",TOKEN_MERIDIAN},
	{"LONGITUDE",TOKEN_LONGITUDE},
	{"SPACING",TOKEN_SPACING},
	{"WIDTH",TOKEN_WIDTH},
	{"START",TOKEN_START},
	{"END",TOKEN_END},
	{"RGB",TOKEN_RGB},
	{"HEIGHT",TOKEN_HEIGHT},
	{"BORDER",TOKEN_BORDER},
	{"COLOR",TOKEN_COLOR},
	{"VALUE",TOKEN_VALUE},
	{"LOCATION",TOKEN_LOCATION},
	{"POLYGON",TOKEN_POLYGON},
	{"ATTACHED",TOKEN_ATTACHED},
	{"ADJ",TOKEN_ADJ},
	{"ARMIES",TOKEN_ARMIES},
	{NULL,-1}
};

int CRiskGameDoc::Lookup(char *s)
{
	/************************************************
	** Lookup
	**
	** This function is used to check a string
	** against a list of keywords for the
	** Risk File Format.
	**
	** Parameter:
	**	s......string to check against keywords
	**
	** Returns:TOKEN VALUE if it is a keyword
	**
	***********************************************/
	int i;
	int loop = 1;
	int rV=0;

	for(i=0;Keywords[i].pName && loop ;++i)
	{
		if(strcmp(s,Keywords[i].pName)==0)
		{
			rV = Keywords[i].tokenval;
			loop = 0;
		}
	}
	return rV;
}

int CRiskGameDoc::Lexer(FILE *pI)
{
	/***********************************************
	** Lexer
	** This is the Lexer function for breaking
	** up the input stream for a map data file
	** into a series of tokens.
	**
	** parameter:
	**	pI.... pointer to the input stream
	** Returns: A token representing a specific
	** series of characters
	************************************************/
	int c;
	int loop = 1;
	int rV;
	int i;
	int stringflag;

	while(loop)
	{
		c = GetChar(pI);
		switch(c)
		{
			case EOF:
				rV = TOKEN_EOF;
				loop = 0;
				break;
			case ' ':
			case '\t':
				break;
			case '\n':
				++m_Line;
				break;
			case '\r':
				break;
			case '}':
			case '{':
			case ':':
			case ',':
			case '(':
			case ')':
			case '[':
			case ']':
				rV = c;
				loop = 0;
				break;
			case '0':	case '1':	case '2':	case '3':
			case '4':	case '5':	case '6':	case '7':
			case '8':	case '9':	case '-':
				i = 0;
				m_pLexBuff[i++] = c;
				while(isdigit(c = GetChar(pI)) )
					m_pLexBuff[i++] = c;
				m_Unget_Buffer = c;	//unget character
				m_pLexBuff[i] = 0;
				m_TokenValue = atoi(m_pLexBuff);
				rV = TOKEN_NUM;
				loop = 0;
				break;
			case '"':	//string that includes spaces
				i = 0;
				c = GetChar(pI);
				m_pLexBuff[i++] = c;
				stringflag = 1;
				while(stringflag )
				{
					c = GetChar(pI);
					if(c == '"')
						stringflag = 0;
					else
						m_pLexBuff[i++] = c;
				}
				m_pLexBuff[i] = 0;
				rV = TOKEN_STRING;
				loop = 0;
				break;
			default:	//strings and keywords
				i = 0;
				m_pLexBuff[i++] = c;
				stringflag = 1;
				while(stringflag )
				{
					c = GetChar(pI);
					if(isalpha(c))
						m_pLexBuff[i++] = c;
					else
						stringflag = 0;
				}
				m_Unget_Buffer = c;
				m_pLexBuff[i] = 0;
				if((rV = Lookup(m_pLexBuff))>0)
					loop = 0;
				else
				{
					rV = TOKEN_STRING;
					loop = 0;
				}
				break;
		}
	}
	return rV;
}

CMap *CRiskGameDoc::Parser(FILE *pI)
{
	/********************************************
	** Parser
	**
	** This is the parser for loading in
	** RISK map data.
	**
	** parameter:
	**	pI......pointer to the input stram
	**
	** Returns a pointer to a MAP object
	********************************************/
	CMap *pMap;
	CMapContinent *pMC;
	CPolygon *pPoly;
	unsigned R,G,B;
	int rV = 0;
	int loop;

	loop = 1;
	m_LookAHead = Lexer(pI);
	while(loop)
	{
		switch(m_LookAHead)
		{
			case TOKEN_MAP:
				pMap = new CMap;
				m_LookAHead = match(pI,TOKEN_MAP);
				m_LookAHead = match(pI,':');
				m_LookAHead = match(pI,':');
				if(m_LookAHead == TOKEN_STRING)
					pMap->SetName(m_pLexBuff);
				else
					Error("Expected String");
				m_LookAHead = match(pI,TOKEN_STRING);
				break;
			case TOKEN_LONGITUDE:
				m_LookAHead = match(pI,TOKEN_LONGITUDE);
				switch(m_LookAHead)
				{
					case TOKEN_WIDTH:
						m_LookAHead = match(pI,TOKEN_WIDTH);
						m_LookAHead = match(pI,'(');
						if(Expect(TOKEN_NUM,m_LookAHead))
							pMap->SetLogLineWidth(m_TokenValue);
						m_LookAHead = match(pI,TOKEN_NUM);
						m_LookAHead = match(pI,')');
						break;
					case TOKEN_SPACING:
						m_LookAHead = match(pI,TOKEN_SPACING);
						m_LookAHead = match(pI,'(');
						if(Expect(TOKEN_NUM,m_LookAHead))
							pMap->SetLogSpacing(m_TokenValue);
						m_LookAHead = match(pI,TOKEN_NUM);
						m_LookAHead = match(pI,')');
						break;
					case TOKEN_START:
						m_LookAHead = match(pI,TOKEN_START);
						m_LookAHead = match(pI,'(');
						if(Expect(TOKEN_NUM,m_LookAHead))
							pMap->SetLogStart(m_TokenValue);
						m_LookAHead = match(pI,TOKEN_NUM);
						m_LookAHead = match(pI,')');
						break;
					case TOKEN_END:
						m_LookAHead = match(pI,TOKEN_END);
						m_LookAHead = match(pI,'(');
						if(Expect(TOKEN_NUM,m_LookAHead))
							pMap->SetLogEnd(m_TokenValue);
						m_LookAHead = match(pI,TOKEN_NUM);
						m_LookAHead = match(pI,')');
						break;
				}
				break;
			case TOKEN_MERIDIAN:
				m_LookAHead = match(pI,TOKEN_MERIDIAN);
				switch(m_LookAHead)
				{
					case TOKEN_WIDTH:
						m_LookAHead = match(pI,TOKEN_WIDTH);
						m_LookAHead = match(pI,'(');
						if(Expect(TOKEN_NUM,m_LookAHead))
							pMap->SetMerLineWidth(m_TokenValue);
						m_LookAHead = match(pI,TOKEN_NUM);
						m_LookAHead = match(pI,')');
						break;
					case TOKEN_SPACING:
						m_LookAHead = match(pI,TOKEN_SPACING);
						m_LookAHead = match(pI,'(');
						if(Expect(TOKEN_NUM,m_LookAHead))
							pMap->SetMerSpacing(m_TokenValue);
						m_LookAHead = match(pI,TOKEN_NUM);
						m_LookAHead = match(pI,')');
						break;
					case TOKEN_START:
						m_LookAHead = match(pI,TOKEN_START);
						m_LookAHead = match(pI,'(');
						if(Expect(TOKEN_NUM,m_LookAHead))
							pMap->SetMerStart(m_TokenValue);
						m_LookAHead = match(pI,TOKEN_NUM);
						m_LookAHead = match(pI,')');
						break;
					case TOKEN_END:
						m_LookAHead = match(pI,TOKEN_END);
						m_LookAHead = match(pI,'(');
						if(Expect(TOKEN_NUM,m_LookAHead))
							pMap->SetMerEnd(m_TokenValue);
						m_LookAHead = match(pI,TOKEN_NUM);
						m_LookAHead = match(pI,')');
						break;
				}
				break;
			case TOKEN_WIDTH:
				m_LookAHead = match(pI,TOKEN_WIDTH);
				m_LookAHead = match(pI,'(');
				if(Expect(TOKEN_NUM,m_LookAHead))
					pMap->SetMapWidth(m_TokenValue);
				m_LookAHead = match(pI,TOKEN_NUM);
				m_LookAHead = match(pI,')');
				break;
			case TOKEN_HEIGHT:
				m_LookAHead = match(pI,TOKEN_HEIGHT);
				m_LookAHead = match(pI,'(');
				if(Expect(TOKEN_NUM,m_LookAHead))
					pMap->SetMapHieght(m_TokenValue);
				m_LookAHead = match(pI,TOKEN_NUM);
				m_LookAHead = match(pI,')');
				break;
			case TOKEN_BORDER:
				m_LookAHead = match(pI,TOKEN_BORDER);
				m_LookAHead = match(pI,TOKEN_COLOR);
				m_LookAHead = match(pI,'(');
				m_LookAHead = match(pI,TOKEN_RGB);
				m_LookAHead = match(pI,'(');
				if(Expect(TOKEN_NUM,m_LookAHead))
				{
					R = atoi(this->m_pLexBuff);
					m_LookAHead = match(pI,TOKEN_NUM);
				}
				m_LookAHead = match(pI,',');
				if(Expect(TOKEN_NUM,m_LookAHead))
				{
					G = atoi(this->m_pLexBuff);
					m_LookAHead = match(pI,TOKEN_NUM);
				}
				m_LookAHead = match(pI,',');
				if(Expect(TOKEN_NUM,m_LookAHead))
				{
					B = atoi(this->m_pLexBuff);
					m_LookAHead = match(pI,TOKEN_NUM);
				}
				pMap->SetBorderColor(R<<16 | G << 8 | B);
				m_LookAHead = match(pI,')');
				m_LookAHead = match(pI,')');
				break;
			case '{':
				m_LookAHead = match(pI,'{');
				switch(m_LookAHead)
				{
					case TOKEN_CONTINENT:
						pMC = ParseContinent(pI);
						pMap->SetChild(pMC);
						break;
				}
				m_LookAHead = match(pI,'}');
				break;
			case TOKEN_POLYGON:
					pPoly = ParsePolygon(pI,pMap);
					AddPolygon(pPoly);
					break;
			case TOKEN_EOF:
				loop = 0;
				break;
		}
	}	//end of while 1 loop
	Compile(pMap);
	return pMap;
}


CPolygon * CRiskGameDoc::ParsePolygon(FILE *pI,CMap *pM)
{
	CPolygon *pPoly = new CPolygon;
	CMapTerritory *pT;
	int X,Y;
	int loop = 1;

	m_LookAHead = match(pI,TOKEN_POLYGON);
	m_LookAHead = match(pI,':');
	m_LookAHead = match(pI,':');
	if(m_LookAHead == '(' )	//polygon has ID
	{
		m_LookAHead = match(pI,'(');
		pT = FindTerritory(pM,this->m_pLexBuff);
		pPoly->SetTerritory(pT);
		m_LookAHead = match(pI,TOKEN_STRING);
		m_LookAHead = match(pI,')');
	}
	m_LookAHead = match(pI,'[');
	while(loop)
	{
		switch(m_LookAHead)
		{
			case ']':
				loop = 0;
				m_LookAHead = match(pI,']');
				break;
			case '(':
				m_LookAHead = match(pI,'(');
				if(Expect(TOKEN_NUM,m_LookAHead))
					X = this->m_TokenValue;
				m_LookAHead = match(pI,TOKEN_NUM);
				m_LookAHead = match(pI,',');
				if(Expect(TOKEN_NUM,m_LookAHead))
					Y = this->m_TokenValue;
				m_LookAHead = match(pI,TOKEN_NUM);
				m_LookAHead = match(pI,')');
				pPoly->AddPoint(CPoint(X,Y));
				break;
		}
	}
	return pPoly;
}

CMapContinent * CRiskGameDoc::ParseContinent(FILE *pI)
{
	/********************************************
	** ParseContinent
	**
	** this function parses the tokens for
	** a Continent data structure.
	**
	** parameter:
	**	pI....pointer to input stream
	**
	** Returns
	**		Pointer to a list of contiments
	********************************************/

	CMapContinent *pMC=0,*pMCList=0,*pMCend;
	CMapTerritory *pMT;
	int loop;

	loop = 1;
	while(loop)
	{
		switch(m_LookAHead)
		{
			case TOKEN_CONTINENT:
				pMC = new CMapContinent;
				m_LookAHead = match(pI,TOKEN_CONTINENT);
				m_LookAHead = match(pI,':');
				m_LookAHead = match(pI,':');
				if(m_LookAHead == TOKEN_STRING)
					pMC->SetName(m_pLexBuff);
				else
					Error("Expected String");
				m_LookAHead = match(pI,TOKEN_STRING);
				//--------------------------
				// Make continent list
				//--------------------------
				if(pMCList == 0)
				{
					pMCList = pMC;
					pMCend = pMC;
				}
				else
				{
					pMCend->SetNext(pMC);
					pMCend = pMC;
				}
				break;
			case TOKEN_VALUE:
				m_LookAHead = match(pI,TOKEN_VALUE);
				m_LookAHead = match(pI,'(');
				if(Expect(TOKEN_NUM,m_LookAHead))
					pMC->SetValue(m_TokenValue);
				m_LookAHead = match(pI,TOKEN_NUM);
				m_LookAHead = match(pI,')');
				break;
			case '{':
				m_LookAHead = match(pI,'{');
				switch(m_LookAHead)
				{
					case TOKEN_TERRITORY:
						pMT = ParseTerritory(pI);
						pMC->SetChild(pMT);
						m_LookAHead = match(pI,'}');
						break;
				}
				break;
			case '}':
				loop = 0;
				break;
		}	//end of switch(lookahead)
	}	//end of while(loop);
	return pMCList;
}

CMapTerritory * CRiskGameDoc::ParseTerritory(FILE *pI)
{
	/*******************************************
	** ParseTerritory
	** This function parses tokens for a Territory
	** Data structure
	**
	** parameter:
	**	pI.....pointer to input stream
	**
	** Returns:pointer to list of territories
	*********************************************/
	CMapTerritory *pMT = 0,*pMTList=0,*pMTend;
	int xLoc,yLoc;
	int loop;
	int r,b,g;

	loop = 1;
	while(loop)
	{
		switch(m_LookAHead)
		{
			case TOKEN_TERRITORY:
				pMT = new CMapTerritory();
				m_LookAHead = match(pI,TOKEN_TERRITORY);
				m_LookAHead = match(pI,':');
				m_LookAHead = match(pI,':');
				if(m_LookAHead == TOKEN_STRING)
					pMT->SetName(m_pLexBuff);
				else
					Error("Expected String");
				m_LookAHead = match(pI,TOKEN_STRING);
				//------------------------
				// make territory list
				//------------------------
				if(pMTList == 0)
				{
					pMTList = pMT;
					pMTend = pMT;
				}
				else
				{
					pMTend->SetNext(pMT);
					pMTend = pMT;
				}
				break;
			case TOKEN_LOCATION:
				m_LookAHead = match(pI,TOKEN_LOCATION);
				m_LookAHead = match(pI,'(');
				if(Expect(TOKEN_NUM,m_LookAHead))
					xLoc = m_TokenValue;
				m_LookAHead = match(pI,TOKEN_NUM);
				m_LookAHead = match(pI,',');
				if(Expect(TOKEN_NUM,m_LookAHead))
					yLoc = m_TokenValue;
				pMT->SetLocation(xLoc,yLoc);
				m_LookAHead = match(pI,TOKEN_NUM);
				m_LookAHead = match(pI,')');
				break;
			case TOKEN_VALUE:
				m_LookAHead = match(pI,TOKEN_VALUE);
				m_LookAHead = match(pI,'(');
				if(Expect(TOKEN_NUM,m_LookAHead))
					pMT->SetValue(m_TokenValue);
				m_LookAHead = match(pI,TOKEN_NUM);
				m_LookAHead = match(pI,')');
				break;
			case TOKEN_ADJ:	//adjacent terrotry list
				m_LookAHead = match(pI,TOKEN_ADJ);
				m_LookAHead = match(pI,'[');
				while(TOKEN_STRING==m_LookAHead)
				{
					//---------------------------------
					// OK, we have a problem here
					// we need to add neighbors that
					// just don't exist.  So, we
					// will just use the name, and
					// then when done, we do a compile
					//---------------------------------
					CListTerritory *pL = new CListTerritory;
					pL->SetName(m_pLexBuff);
					pMT->AddNeighbor(pL);
					m_LookAHead = match(pI,TOKEN_STRING);
					if(m_LookAHead == ',')
						m_LookAHead = match(pI,',');
				}
				m_LookAHead = match(pI,']');
				break;
			case TOKEN_COLOR:
				m_LookAHead = match(pI,TOKEN_COLOR);
				m_LookAHead = match(pI,'(');
				m_LookAHead = match(pI,TOKEN_RGB);
				m_LookAHead = match(pI,'(');
				if(Expect(TOKEN_NUM,m_LookAHead) )
				{
					r = m_TokenValue;
					m_LookAHead = match(pI,TOKEN_NUM);
				}
				m_LookAHead = match(pI,',');
				if(Expect(TOKEN_NUM,m_LookAHead) )
				{
					g = m_TokenValue;
					m_LookAHead = match(pI,TOKEN_NUM);
				}
				m_LookAHead = match(pI,',');
				if(Expect(TOKEN_NUM,m_LookAHead) )
				{
					b = m_TokenValue;
					m_LookAHead = match(pI,TOKEN_NUM);
				}
				m_LookAHead = match(pI,')');
				m_LookAHead = match(pI,')');
				pMT->SetColor(RGB(r,g,b));
				break;
			case '{':	//childeren of Territory
				break;
			case '}':
				loop = 0;
				break;
		}//end of switch(lookahead)
	}	//end of while(loop)

	return pMTList;
}


CMapDataItem * CRiskGameDoc::ParseObjects(FILE *pI)
{
	int loop;
	CMapDataItem *pList=0;
	loop = 1;
	while(loop)
	{
		switch(m_LookAHead)
		{
			case TOKEN_ARMIES:
				break;
			case '}':
				loop = 0;
				break;
		}
	}
	return pList;
}

int CRiskGameDoc::Expect(int Tv,int LookAHead)
{
	int rV=0;

	if(Tv == LookAHead)
		rV = 1;
	else
	{
		char *s = new char[256];
		sprintf(s,"Expected %d  Got %d",Tv,LookAHead);
		Error(s);
		delete [] s;
	}
	return rV;
}

int CRiskGameDoc::match(FILE *pI, int token)
{
	/********************************************
	** match
	**
	** this function is used to match
	** the expected token with the current
	** token.  If they match, get the
	** next token.
	**
	** parameter:
	**	pI.....input file stream
	**	token..expected token
	**
	** Returns:Next token, or -1 on error
	********************************************/
	int rV;

	if(token == m_LookAHead)
		rV = Lexer(pI);
	else
	{
		char *s = new char[256];
		sprintf(s,"Expected %d  Got %d",token,m_LookAHead);
		Error(s);
		rV = -1;
		delete[] s;
	}
	return rV;
}

int CRiskGameDoc::GetChar(FILE *pI)
{
	/************************************************
	** GetChar
	**
	** This function is used to get a
	** Character form the map
	** file that is being loaded.
	**
	** parameter:
	**	pI.....pointer to input file stream
	**
	**	RETURNS:next character from input stream
	**********************************************/
	int rv;

	if(m_Unget_Buffer)
	{
		rv = m_Unget_Buffer;
		m_Unget_Buffer = 0;
	}
	else
	{
		rv = fgetc(pI);
	}
	return rv;
}


void CRiskGameDoc::Error(char *em)
{
	/**************************************
	** Error
	**
	** This function displays an
	** Error message from the input
	** file parser.
	**
	** parameter:
	**	s.....String to display in message
	****************************************/
	char *s = new char[256];
	sprintf(s,"%s:Line %d",em,m_Line);
	::MessageBox(NULL,s,"ERROR",MB_ICONHAND);
	delete [] s;
}

int CRiskGameDoc::Compile(CMap *pMap)
{
	/**************************************
	**Compile
	**
	** This function is used to complete the
	** loading of a .map file.  If territories
	** have adjacent territories, it is
	** possible to have a territory in a
	** neighbor list that has not actually
	** been loaded yet.  So, we just load the
	** name.  Now we locate the matching
	** CMapTerritory * objects that match up
	** to the names.
	**
	** parameters:
	**	pMap....pointer to the map to compile.
	**************************************/
	CMapContinent *pMC = (CMapContinent *)pMap->GetChild();
	CMapTerritory *pMT,*pTn;
	CListTerritory *pL;

	while(pMC)
	{
		pMT = (CMapTerritory *)pMC->GetChild();
		while(pMT)
		{
			if((pL = (CListTerritory *)pMT->GetNieghborList()->GetHead()) != NULL)
			{
				while(pL)
				{
					pTn = FindTerritory(pMap,pL->GetName());
					if(pTn == NULL)
					{
						char *s = new char[256];
						sprintf(s,"Could Not Find %s in Map",pL->GetName());
						MessageBox(NULL,s,"ERROR",MB_ICONHAND);
						delete[] s;
					}
					pL->SetTerr(pTn);
					pL = (CListTerritory *)pL->GetNext();
				}
			}
			pMT = (CMapTerritory *)pMT->GetNext();
		}
		pMC = (CMapContinent *)pMC->GetNext();
	}
	return 0;
}

/***********************************************
	Methodes for dealing with AI engines
***********************************************/

void CRiskGameDoc::AddAi(CAiList *pA)
{
	if(m_pAiList == 0)
	{
		m_pAiList = pA;
		m_pAiListEnd = pA;
	}
	else
	{
		m_pAiListEnd->SetNext(pA);
		m_pAiListEnd = pA;
	}
}

/*******************************************
	Methodes for dealing with palyers
*******************************************/

void CRiskGameDoc::CheckForLoosers()
{
	CPlayer *pL;
	int i;

	for(i=0;i<this->m_TotalPlayers;++i)
	{
		pL = this->m_PlayerAiThreads[i]->GetPlayer();
		if(pL->CountTerritories() == 0)
			RemovePlayer(i);
	}
}

void CRiskGameDoc::RemovePlayer(int Index)
{
	this->m_PlayerAiThreads[Index]->ShutDown();
	this->m_PlayerAiThreads[Index] = 0;
}

int CRiskGameDoc::CountPlayers()
{
	int c = 0,i;

	for(i=0;i < m_TotalPlayers;++i);
	{
		if(this->m_PlayerAiThreads[i])
			++c;
	}
	return c;
}

/****************************************************
	Methodes for dealing with RISK cards
****************************************************/

void CRiskGameDoc::CreateCards(CMap *pMap)
{
	CMapContinent *pMC;
	CMapTerritory *pMT;
	CCard *pCard;

	if(m_ListCards == NULL)
	{
		m_ListCards = new CList;
	}
	pMC = (CMapContinent *)pMap->GetChild();
	while(pMC)
	{
		pMT = (CMapTerritory *)pMC->GetChild();
		while(pMT)
		{
			pCard = new CCard;
			pCard->SetTerr(pMT);
			pCard->SetCardType((rand() % 3) + 1);
			m_ListCards->ADD(pCard);
			pMT = (CMapTerritory *)pMT->GetNext();
		}
		pMC = (CMapContinent *)pMC->GetNext();
	}
}

CCard * CRiskGameDoc::DrawCard()
{
	return 0;
}

int CRiskGameDoc::TurnInCardSet(CCard *pC1, CCard *pC2, CCard *pC3)
{
	int rV;
	rV = IsCardSet(pC1->GetCardType(),pC2->GetCardType(),pC3->GetCardType());
	if(rV)
	{
	}
	return rV;
}

void CRiskGameDoc::CreateNewPlayer(int i,int InitArmies)
{
	char *s = new char[256];
	CPlayer *pL = new CPlayer();
	CArmies *pA = new CArmies;

	pA->SetNumber(InitArmies);
	sprintf(s,"Player %d",i+1);
	pL->SetName(s);
	pL->m_Color = StaticStockColors[i];
	pL->SetArmies(pA);
	CAiList *pP = FindAI("Default AI",m_pAiList);
	pL->SetAiFuncs(pP->GetFuncs());
	pL->SetParams((*pL->GetAiFuncs()->GetParams)());
	this->m_PlayerAiThreads[i] = new CAiThread;
	m_PlayerAiThreads[i]->SetPlayer(pL);
	m_PlayerAiThreads[i]->SetMap(m_pMapData);
	m_PlayerAiThreads[i]->BeginThread(16);
	delete[] s;

}

void CRiskGameDoc::OnCloseDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
	int i;

	for(i=0;i<m_TotalPlayers;++i)
	{
		if(m_PlayerAiThreads[i])
			m_PlayerAiThreads[i]->ShutDown();
	}
	CDocument::OnCloseDocument();
}
