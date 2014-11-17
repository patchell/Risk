/*************************************************
*************************************************/

#ifndef RISKUTILS__H
#define RISKUTILS__H

#include "MapContinent.h"
#include "MapTerritory.h"
#include "Polygon.h"
#include "AiList.h"

__declspec(dllexport) CPolygon *PointInWhichPolygon(CPolygon *pList,CPoint pos);
__declspec(dllexport) CMapContinent *PointInWhichContinent(CMap *pMap,CPolygon *pList,CPoint pos);
__declspec(dllexport) CMapTerritory *PointInWhichTerritory(CMap *pMap,CPolygon *pList,CPoint pos);
__declspec(dllexport) CMapTerritory *FindTerritory(CMap *pMap,char *name);
__declspec(dllexport) CMapContinent *FindContinent(CMap *pMap,CMapTerritory *pMT);
__declspec(dllexport) CAiList *FindAI(char *s,CAiList *pL);
__declspec(dllexport) int IsCardSet(int a, int b, int c);

#endif
