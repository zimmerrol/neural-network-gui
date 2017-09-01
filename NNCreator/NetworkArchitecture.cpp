#include "stdafx.h"
#include "xmltags.h"
#include "NetworkArchitecture.h"
#include "Parameter.h"
#include "Chain.h"
#include "Link.h"
#include "Network.h"
#include "Parameter.h"
#include "ParameterValues.h"

CNetworkArchitecture::CNetworkArchitecture()
{
	m_chains = std::vector<CChain*>();
}


CNetworkArchitecture::~CNetworkArchitecture()
{

}

CNetworkArchitecture::CNetworkArchitecture(tinyxml2::XMLElement* pParentNode) : CNetworkArchitecture()
{
	tinyxml2::XMLElement *pNode = pParentNode->FirstChildElement(XML_TAG_Chains);
	loadChildren<CChain>(pNode, XML_TAG_Chain, m_chains);
	for each (auto var in m_chains)
	{
		var->setParentNetworkArchitecture(this);
	}
}


CNetworkArchitecture* CNetworkArchitecture::getInstance(tinyxml2::XMLElement* pNode)
{
	if (!strcmp(pNode->Name(), XML_TAG_NETWORK_ARCHITECTURE))
		return new CNetworkArchitecture(pNode);

	return nullptr;
}

const CLink* CNetworkArchitecture::getLinkById(const char* id) const
{
	const CLink* result = NULL;
	for each (auto cItem in m_chains)
	{
		result = cItem->getLinkById(id);
		if (result != NULL)
			break;
	}

	return result;
}

CNetwork * CNetworkArchitecture::createNetwork()
{
	/*
		basic idea of this algorithm: we traverse all chains to create the real model
		to achieve this we follow this pseudo-code:

			while output_node has not been reached:
				for each chain  in chains
					traverse chain as far as possible

				stop the processing when no changes are possible anymore -> the structure is faulty!

	*/
	bool output_reached = false;

	auto pDummyValue = CNTK::InputVariable({ 100 }, CNTK::DataType::Double, "input");

	auto progressMap = std::map<CChain*, CLink*>();
	CLink* pCurrentLink;
	vector<const CLink*> dependencies;
	bool architectureDeadEndReached = false;
	while (!output_reached && !architectureDeadEndReached)
	{
		architectureDeadEndReached = true;

		for each (CChain* pChain in m_chains)
		{
			//get current link of the chain
			if (progressMap.find(pChain) == progressMap.end())
			{
				//start at the beginning
				pCurrentLink = pChain->getChainLinks().at(0);
			}
			else
			{
				//resume the progress
				pCurrentLink = progressMap.at(pChain);
			}

			while (pCurrentLink != nullptr)
			{
				//get dependencies
				dependencies = pCurrentLink->getDependencies();

				//check if dependencies have already been traversed
				bool dependencies_satisfied = true;
				for each (const CLink* item in dependencies)
				{
					if (item->getFunctionPtr() == nullptr)
					{
						dependencies_satisfied = false;
						break;
					}
				}

				//dependencies not satisfied -> try to process another chain
				if (!dependencies_satisfied)
					break;
			
				//all dependencies are satisfied and already traversed
				//create the FunctionPtr now and save it!

				//TODO: add real code
				pCurrentLink->setFunctionPtr(pDummyValue);

				//update current link
				pCurrentLink = pCurrentLink->getNextLink();

				//keep the loop alive
				architectureDeadEndReached = false;
			}

			progressMap.insert_or_assign(pChain, pCurrentLink);
		}
	}

	return nullptr;
}
