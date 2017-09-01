#include "stdafx.h"
#include "Link.h"
#include "xmltags.h"
#include "CNTKLibrary.h"

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

CLink* CLink::getInstance(tinyxml2::XMLElement* pNode)
{
	if (!strcmp(pNode->Name(), XML_TAG_LinkBase))
		return new CLink(pNode);

	return nullptr;
}