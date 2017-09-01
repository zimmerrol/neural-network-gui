#pragma once
#include <vector>
#include "Network.h"
#include "Link.h"
#include "Chain.h"

//class CChain;
//class CLink;
//class CNetwork;

class CNetworkArchitecture
{
protected:
	vector<CChain*> m_chains;
	CNetworkArchitecture(tinyxml2::XMLElement* pNode);

public:
	CNetworkArchitecture();
	~CNetworkArchitecture();

	const vector<CChain*> getChains() { return m_chains; }

	static CNetworkArchitecture* getInstance(tinyxml2::XMLElement* pNode);

	const CLink* getLinkById(const char* id) const;

	CNetwork* createNetwork();
};

