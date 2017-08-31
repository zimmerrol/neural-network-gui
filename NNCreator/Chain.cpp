#include "stdafx.h"
#include "Chain.h"
#include "xmltags.h"


CChain::CChain()
{
	m_pChainLinks = new vector<CLink*>();
}


CChain::~CChain()
{
}

CChain::CChain(tinyxml2::XMLElement* pParentNode) : CChain()
{
	//read name
	m_name = pParentNode->Attribute(XML_ATTRIBUTE_Name);

	//read links
	tinyxml2::XMLElement *pNode = pParentNode->FirstChildElement(XML_TAG_ChainLinks);
	loadChildren<CLink>(pNode, XML_TAG_LinkBase, *m_pChainLinks);
}

CChain* CChain::getInstance(tinyxml2::XMLElement* pNode)
{
	if (!strcmp(pNode->Name(), XML_TAG_Chain))
		return new CChain(pNode);

	return nullptr;
}
