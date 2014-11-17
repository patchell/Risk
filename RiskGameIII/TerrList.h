#ifndef CTERRLIST_H
#define CTERRLIST_H


class CMapTerritory;

class CTerrList
{
	CMapTerritory *m_pTerr;
	CTerrList *m_pNext;
	char *m_pName;
	public:
		/** Default constructor */
		CTerrList();
		/** Default destructor */
		virtual ~CTerrList();
		CTerrList *GetNext(void) {return m_pNext;}
		void SetNext(CTerrList *pN) {m_pNext = pN;}
		CMapTerritory *GetTerr(void){return m_pTerr;}
		void SetTerr(CMapTerritory *pT) { m_pTerr = pT;}
		void SetName(char *s);
		inline char *GetName(void){return m_pName;}
	protected:
	private:
};

#endif // CTERRLIST_H
