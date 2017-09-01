#pragma once
#include "Link.h"


#include <vector>

class CNetworkArchitecture;

class CChain
{
protected:
	vector<CLink*> m_chainLinks;
	string m_name;
	CChain(tinyxml2::XMLElement* pNode);
public:
	CChain();
	~CChain();

	const std::vector<CLink*> getChainLinks() const { return m_chainLinks; }
	void setChainLinks(vector<CLink*> pChainLinks) { m_chainLinks = pChainLinks; }
	const string& getName() const { return m_name; }

	const CLink* getLinkById(const char* id) const;

	std::vector<const CLink*> getLinkDependencies(const CLink* pLink, const CNetworkArchitecture* pNetwork) const;

	CLink* getNextLink(const CLink* value) const;
	CLink* getPreviousLink(const CLink* value) const;

	static CChain* getInstance(tinyxml2::XMLElement* pNode);
};

