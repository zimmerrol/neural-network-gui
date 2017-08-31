#pragma once
#include <vector>
#include "Link.h"

using namespace std;

class CChain
{
protected:
	vector<CLink*>* m_pChainLinks;
	string m_name;
	CChain(tinyxml2::XMLElement* pNode);
public:
	CChain();
	~CChain();

	const vector<CLink*>* getChainLinks() { return m_pChainLinks; }
	void setChainLinks(vector<CLink*>* pChainLinks) { m_pChainLinks = pChainLinks; }
	string getName() { return m_name;}

	static CChain* getInstance(tinyxml2::XMLElement* pNode);
};

