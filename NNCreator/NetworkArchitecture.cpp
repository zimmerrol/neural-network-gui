#include "stdafx.h"
#include "NetworkArchitecture.h"
#include "xmltags.h"
#include "Chain.h"


CNetworkArchitecture::CNetworkArchitecture()
{
	m_pChains = new vector<CChain*>();
}


CNetworkArchitecture::~CNetworkArchitecture()
{
	delete m_pChains;
}

CNetworkArchitecture::CNetworkArchitecture(tinyxml2::XMLElement* pParentNode) : CNetworkArchitecture()
{
	tinyxml2::XMLElement *pNode = pParentNode->FirstChildElement(XML_TAG_Chains);
	loadChildren<CChain>(pNode, XML_TAG_Chain, *m_pChains);
}


CNetworkArchitecture* CNetworkArchitecture::getInstance(tinyxml2::XMLElement* pNode)
{
	if (!strcmp(pNode->Name(), XML_TAG_NETWORK_ARCHITECTURE))
		return new CNetworkArchitecture(pNode);

	return nullptr;
}
