#include "stdafx.h"
#include "Chain.h"
#include "NetworkArchitecture.h"
#include "xmltags.h"


CChain::CChain()
{
	m_chainLinks = std::vector<CLink*>();
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
	loadChildren<CLink>(pNode, XML_TAG_LinkBase, m_chainLinks);
}

const CLink* CChain::getLinkById(const char * id) const
{
	for each (auto item in m_chainLinks)
	{
		if (!strcmp(item->getId().c_str(), id))
		{
			return item;
		}
	}

	return NULL;
}

std::vector<const CLink*> CChain::getLinkDependencies(const CLink* pLink, const CNetworkArchitecture* pNetwork) const
{
	std::vector<const CLink*> result = std::vector<const CLink*>();

	if (pLink->getLinkType() == LinkType::MergeLayer)
	{
		auto dependenciesList = (CLinkConnectionListParameter*)pLink->getParameterByName("Links");
		for each (CLinkConnection* var in dependenciesList->getValue())
			result.push_back(pNetwork->getLinkById(var->getTargetId().c_str()));

	}
	else
	{
		//just add the item which is placed in front of this item in the chain
		CLink* previousLink = getPreviousLink(pLink);
		if (previousLink != nullptr)
			result.push_back(previousLink);
	}

	return result;
}

CLink * CChain::getNextLink(const CLink * pValue) const
{
	//determine position and get the next element
	ptrdiff_t position = distance(m_chainLinks.begin(), find(m_chainLinks.begin(), m_chainLinks.end(), pValue));
	if (position >= m_chainLinks.size()-1)
		return nullptr;
	return m_chainLinks.at(position + 1);
}

CLink * CChain::getPreviousLink(const CLink * pValue) const
{
	//determine position and get the previous element
	ptrdiff_t position = distance(m_chainLinks.begin(), find(m_chainLinks.begin(), m_chainLinks.end(), pValue));
	if (position <= 0)
		return nullptr;
	return m_chainLinks.at(position - 1);
}

CChain* CChain::getInstance(tinyxml2::XMLElement* pNode)
{
	if (!strcmp(pNode->Name(), XML_TAG_Chain))
		return new CChain(pNode);

	return nullptr;
}