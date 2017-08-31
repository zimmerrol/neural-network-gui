#pragma once
#include <vector>
#include "Chain.h"

using namespace std;

class CNetworkArchitecture
{
protected:
	vector<CChain*>* m_pChains;
	CNetworkArchitecture(tinyxml2::XMLElement* pNode);

public:
	CNetworkArchitecture();
	~CNetworkArchitecture();

	const vector<CChain*>* getChains() { return m_pChains; }

	static CNetworkArchitecture* getInstance(tinyxml2::XMLElement* pNode);
};

