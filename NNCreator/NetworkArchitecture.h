#pragma once
#include "Chain.h"
#include "Network.h"
#include <vector>

using namespace std;

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

