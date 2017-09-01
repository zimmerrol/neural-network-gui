#include "stdafx.h"
#include "xmltags.h"
#include "CNTKLibrary.h"

#include "NetworkArchitecture.h"
#include "Parameter.h"
#include "Chain.h"
#include "Link.h"
#include "Network.h"
#include "Parameter.h"
#include "ParameterValues.h"

#include "CNTKWrapper.h"

CLink::CLink()
{
}


CLink::~CLink()
{
}

const CParameterBaseInteface* CLink::getParameterByName(const string name) const
{
	for each (auto item in this->m_parameters)
	{
		if (item->getName()._Equal(name))
		{
			return item;
		}
	}

	return NULL;
}

CLink::CLink(tinyxml2::XMLElement* pParentNode)
{
	//read type
	const char* type = pParentNode->Attribute(XML_ATTRIBUTE_Type);
	if (!strcmp(type, "InputLayer"))
		m_linkType = LinkType::InputLayer;
	else if (!strcmp(type, "ActivationLayer"))
		m_linkType = LinkType::ActivationLayer;
	else if (!strcmp(type, "Convolution1DLayer"))
		m_linkType = LinkType::Convolution1DLayer;
	else if (!strcmp(type, "Convolution2DLayer"))
		m_linkType = LinkType::Convolution2DLayer;
	else if (!strcmp(type, "Convolution3DLayer"))
		m_linkType = LinkType::Convolution3DLayer;
	else if (!strcmp(type, "DenseLayer"))
		m_linkType = LinkType::DenseLayer;
	else if (!strcmp(type, "DropoutLayer"))
		m_linkType = LinkType::DropoutLayer;
	else if (!strcmp(type, "FlattenLayer"))
		m_linkType = LinkType::FlattenLayer;
	else if (!strcmp(type, "ReshapeLayer"))
		m_linkType = LinkType::ReshapeLayer;
	else if (!strcmp(type, "MergeLayer"))
		m_linkType = LinkType::MergeLayer;
	else
		throw "type has not been recognized";

	//read name
	m_name = pParentNode->Attribute(XML_ATTRIBUTE_Name);

	//read id
	m_id = pParentNode->Attribute(XML_ATTRIBUTE_Id);

	//read parameters
	tinyxml2::XMLElement *pNode = pParentNode->FirstChildElement(XML_TAG_Parameters);
	loadChildren<CParameterBaseInteface>(pNode, XML_TAG_ParameterBase, m_parameters);
}

std::vector<const CLink*> CLink::getDependencies() const
{
	std::vector<const CLink*> result = std::vector<const CLink*>();

	if (m_linkType == LinkType::MergeLayer)
	{
		auto dependenciesList = (CLinkConnectionListParameter*)getParameterByName("Links");
		for each (CLinkConnection* var in dependenciesList->getValue())
			result.push_back(m_pParentChain->getParentNetworkArchitecture()->getLinkById(var->getTargetId().c_str()));

	}
	else
	{
		//just add the item which is placed in front of this item in the chain
		CLink* previousLink = getPreviousLink();
		if (previousLink != nullptr)
			result.push_back(previousLink);
	}

	return result;
}

void CLink::createCNTKFunctionPtr()
{
	createCNTKFunctionPtr(getDependencies());
}

void CLink::createCNTKFunctionPtr(vector<const CLink*> dependencies)
{
	auto device = CNTK::DeviceDescriptor::CPUDevice();
	switch (m_linkType)
	{
	case LinkType::ActivationLayer:
		CNTKWrapper::ActivationLayer(this, dependencies, device);
		break;
	case LinkType::Convolution1DLayer:
		CNTKWrapper::Convolution1DLayer(this, dependencies, device);
		break;
	case LinkType::Convolution2DLayer:
		CNTKWrapper::Convolution2DLayer(this, dependencies, device);
		break;
	case LinkType::Convolution3DLayer:
		CNTKWrapper::Convolution3DLayer(this, dependencies, device);
		break;
	case LinkType::DenseLayer:
		CNTKWrapper::DenseLayer(this, dependencies, device);
		break;
	case LinkType::DropoutLayer:
		CNTKWrapper::DropoutLayer(this, dependencies, device);
		break;
	case LinkType::FlattenLayer:
		CNTKWrapper::FlattenLayer(this, dependencies, device);
		break;
	case LinkType::ReshapeLayer:
		CNTKWrapper::ReshapeLayer(this, dependencies, device);
		break;
	case LinkType::MergeLayer:
		CNTKWrapper::MergeLayer(this, dependencies, device);
		break;
	}
}


CLink * CLink::getNextLink() const
{
	//determine position and get the next element
	vector<CLink*> chainLinks = m_pParentChain->getChainLinks();
	ptrdiff_t position = std::distance(chainLinks.begin(), std::find(chainLinks.begin(), chainLinks.end(), this));
	if (position >= chainLinks.size() - 1)
		return nullptr;
	return chainLinks.at(position + 1);
}

CLink * CLink::getPreviousLink() const
{
	//determine position and get the previous element
	vector<CLink*> chainLinks = m_pParentChain->getChainLinks();
	ptrdiff_t position = std::distance(chainLinks.begin(), std::find(chainLinks.begin(), chainLinks.end(), this));
	if (position <= 0)
		return nullptr;
	return chainLinks.at(position - 1);
}

CChain* CChain::getInstance(tinyxml2::XMLElement* pNode)
{
	if (!strcmp(pNode->Name(), XML_TAG_Chain))
		return new CChain(pNode);

	return nullptr;
}

CLink* CLink::getInstance(tinyxml2::XMLElement* pNode)
{
	if (!strcmp(pNode->Name(), XML_TAG_LinkBase))
		return new CLink(pNode);

	return nullptr;
}