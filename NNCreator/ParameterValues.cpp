#include "stdafx.h"
#include "ParameterValues.h"
#include "xmltags.h"

CInputData::CInputData(tinyxml2::XMLElement* pNode) : CInputData()
{

}


/*
template <typename T>
CTuple1D<T>::CTuple1D(tinyxml2::XMLElement* pNode)
{

}

template <typename T>
CTuple2D<T>::CTuple2D(tinyxml2::XMLElement* pNode) : CTuple2D<T>()
{

}

template <typename T>
CTuple3D<T>::CTuple3D(tinyxml2::XMLElement* pNode) : CTuple3D<T>()
{

}

template <typename T>
CTuple4D<T>::CTuple4D(tinyxml2::XMLElement* pNode) : CTuple4D<T>()
{

}
*/

/*
CTuple1D<int>::CTuple1D(tinyxml2::XMLElement* pParentNode) : CTuple1D<int>()
{
	tinyxml2::XMLElement *pNode = pParentNode->FirstChildElement(XML_TAG_Tuple_1);
	m_x1 = stoi(pNode->GetText());
}

CTuple2D<int>::CTuple2D(tinyxml2::XMLElement* pParentNode) : CTuple<int>()
{
	tinyxml2::XMLElement *pNode = pParentNode->FirstChildElement(XML_TAG_Tuple_1);
	m_x1 = stoi(pNode->GetText());
	pNode = pParentNode->FirstChildElement(XML_TAG_Tuple_2);
	m_x2 = stoi(pNode->GetText());
}

CTuple3D<int>::CTuple3D(tinyxml2::XMLElement* pParentNode) : CTuple<int>()
{
	tinyxml2::XMLElement *pNode = pParentNode->FirstChildElement(XML_TAG_Tuple_1);
	m_x1 = stoi(pNode->GetText());
	pNode = pParentNode->FirstChildElement(XML_TAG_Tuple_2);
	m_x2 = stoi(pNode->GetText());
	pNode = pParentNode->FirstChildElement(XML_TAG_Tuple_3);
	m_x3 = stoi(pNode->GetText());
}

CTuple4D<int>::CTuple4D(tinyxml2::XMLElement* pParentNode) : CTuple<int>()
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
*/

template <typename T>
static CTuple1D<T>* getInstance(tinyxml2::XMLElement* pNode)
{
	//some type checking would be good, but due to C#, this is not possible atm.
	return new CTuple1D<T>(pNode);
}

template <typename T>
static CTuple2D<T>* getInstance(tinyxml2::XMLElement* pNode)
{
	//some type checking would be good, but due to C#, this is not possible atm.
	return new CTuple2D<T>(pNode);
}

template <typename T>
static CTuple3D<T>* getInstance(tinyxml2::XMLElement* pNode)
{
	//some type checking would be good, but due to C#, this is not possible atm.
	return new CTuple3D<T>(pNode);
}

template <typename T>
static CTuple4D<T>* getInstance(tinyxml2::XMLElement* pNode)
{
	//some type checking would be good, but due to C#, this is not possible atm.
	return new CTuple4D<T>(pNode);
}