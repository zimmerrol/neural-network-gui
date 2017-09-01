#include "stdafx.h"
#include "xmltags.h"
#include "NetworkArchitecture.h"
#include "Parameter.h"
#include "Chain.h"
#include "Link.h"
#include "Network.h"
#include "Parameter.h"
#include "ParameterValues.h"

CIntTuple1D::CIntTuple1D(tinyxml2::XMLElement* pParentNode) : CIntTuple1D()
{
	tinyxml2::XMLElement *pNode = pParentNode->FirstChildElement(XML_TAG_Tuple_1);
	m_x1 = stoi(pNode->GetText());
}

CIntTuple2D::CIntTuple2D(tinyxml2::XMLElement* pParentNode) : CIntTuple2D()
{
	tinyxml2::XMLElement *pNode = pParentNode->FirstChildElement(XML_TAG_Tuple_1);
	m_x1 = stoi(pNode->GetText());
	pNode = pParentNode->FirstChildElement(XML_TAG_Tuple_2);
	m_x2 = stoi(pNode->GetText());
}

CIntTuple3D::CIntTuple3D(tinyxml2::XMLElement* pParentNode) : CIntTuple3D()
{
	tinyxml2::XMLElement *pNode = pParentNode->FirstChildElement(XML_TAG_Tuple_1);
	m_x1 = stoi(pNode->GetText());
	pNode = pParentNode->FirstChildElement(XML_TAG_Tuple_2);
	m_x2 = stoi(pNode->GetText());
	pNode = pParentNode->FirstChildElement(XML_TAG_Tuple_3);
	m_x3 = stoi(pNode->GetText());
}

CIntTuple4D::CIntTuple4D(tinyxml2::XMLElement* pParentNode) : CIntTuple4D()
{
	tinyxml2::XMLElement *pNode = pParentNode->FirstChildElement(XML_TAG_Tuple_1);
	m_x1 = stoi(pNode->GetText());
	pNode = pParentNode->FirstChildElement(XML_TAG_Tuple_2);
	m_x2 = stoi(pNode->GetText());
	pNode = pParentNode->FirstChildElement(XML_TAG_Tuple_3);
	m_x3 = stoi(pNode->GetText());
	pNode = pParentNode->FirstChildElement(XML_TAG_Tuple_4);
	m_x4 = stoi(pNode->GetText());
}

CIntTuple1D* CIntTuple1D::getInstance(tinyxml2::XMLElement* pNode)
{
	//some type checking would be good, but due to C#, this is not possible atm.
	return new CIntTuple1D(pNode);
}


CIntTuple2D* CIntTuple2D::getInstance(tinyxml2::XMLElement* pNode)
{
	//some type checking would be good, but due to C#, this is not possible atm.
	return new CIntTuple2D(pNode);
}

CIntTuple3D* CIntTuple3D::getInstance(tinyxml2::XMLElement* pNode)
{
	//some type checking would be good, but due to C#, this is not possible atm.
	return new CIntTuple3D(pNode);
}

CIntTuple4D* CIntTuple4D::getInstance(tinyxml2::XMLElement* pNode)
{
	//some type checking would be good, but due to C#, this is not possible atm.
	return new CIntTuple4D(pNode);
}

CInputDataValue* CInputDataValue::getInstance(tinyxml2::XMLElement* pNode)
{
	//some type checking would be good, but due to C#, this is not possible atm.
	return new CInputDataValue(pNode);
}

CLinkConnection* CLinkConnection::getInstance(tinyxml2::XMLElement* pNode)
{
	if (!strcmp(pNode->Name(), XML_TAG_LinkConnection))
	{
		return new CLinkConnection(pNode);
	}
	return nullptr;
}

CInputDataValue::CInputDataValue(tinyxml2::XMLElement* pParentNode) : CInputDataValue()
{
	tinyxml2::XMLElement *pNode = pParentNode->FirstChildElement(XML_TAG_Id);
	m_id = pNode->GetText();
}

CLinkConnection::CLinkConnection(tinyxml2::XMLElement* pNode) : CLinkConnection()
{
	m_targetID = pNode->Attribute(XML_ATTRIBUTE_TargetId);
}

CLinkConnection::CLinkConnection()
{
}

CLinkConnection::~CLinkConnection()
{
}
