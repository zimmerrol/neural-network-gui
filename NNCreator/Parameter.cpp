#include "stdafx.h"
#include "Parameter.h"
#include "ParameterValues.h"
#include "xmltags.h"
#include "ParameterValues.h"

template <typename T>
CParameterBase<T>::~CParameterBase()
{

}

CDoubleParameter::CDoubleParameter(tinyxml2::XMLElement* pNode) : CParameterBase<double>()
{

}

CActivationFunctionParameter::CActivationFunctionParameter(tinyxml2::XMLElement* pParentNode) : CParameterBase<ActivationFunction>()
{
	tinyxml2::XMLElement *pNode = pParentNode->FirstChildElement(XML_TAG_Value);
	const char* type = pNode->GetText();
	if (!strcmp(type, "elu"))
		m_value = ActivationFunction::elu;
	else if (!strcmp(type, "selu"))
		m_value = ActivationFunction::selu;
	else if (!strcmp(type, "softplus"))
		m_value = ActivationFunction::softplus;
	else if (!strcmp(type, "softsign"))
		m_value = ActivationFunction::softsign;
	else if (!strcmp(type, "relu"))
		m_value = ActivationFunction::relu;
	else if (!strcmp(type, "tanh"))
		m_value = ActivationFunction::tanh;
	else if (!strcmp(type, "sigmoid"))
		m_value = ActivationFunction::sigmoid;
	else if (!strcmp(type, "hard_sigmoid"))
		m_value = ActivationFunction::hard_sigmoid;
	else if (!strcmp(type, "softmax"))
		m_value = ActivationFunction::softmax;
	else
		throw "activation function has not been recognized";
}

CInputDataParameter::CInputDataParameter(tinyxml2::XMLElement* pNode) : CParameterBase<CInputData>()
{

}

CIntParameter::CIntParameter(tinyxml2::XMLElement* pParentNode) : CParameterBase<int>()
{
	tinyxml2::XMLElement *pNode = pParentNode->FirstChildElement(XML_TAG_Value);
	const char* rawValue = pNode->GetText();
	m_value = stoi(rawValue);
}

CIntTuple1DParameter::CIntTuple1DParameter(tinyxml2::XMLElement* pParentNode) : CParameterBase<CTuple1D<int>>()
{
	tinyxml2::XMLElement *pNode = pParentNode->FirstChildElement(XML_TAG_Value);
	//m_value = *CTuple1D<int>::getInstance(pNode);
	auto a = CTuple1D<int>::getInstance(pNode);
}

CIntTuple2DParameter::CIntTuple2DParameter(tinyxml2::XMLElement* pParentNode) : CParameterBase<CTuple2D<int>>()
{
	tinyxml2::XMLElement *pNode = pParentNode->FirstChildElement(XML_TAG_Value);
	//m_value = *CTuple2D<int>::getInstance(pNode);
}

CIntTuple3DParameter::CIntTuple3DParameter(tinyxml2::XMLElement* pParentNode) : CParameterBase<CTuple3D<int>>()
{
	tinyxml2::XMLElement *pNode = pParentNode->FirstChildElement(XML_TAG_Value);
	//m_value = *CTuple3D<int>::getInstance(pNode);
}

CIntTuple4DParameter::CIntTuple4DParameter(tinyxml2::XMLElement* pParentNode) : CParameterBase<CTuple4D<int>>()
{
	tinyxml2::XMLElement *pNode = pParentNode->FirstChildElement(XML_TAG_Value);
	//m_value = *CTuple4D<int>::getInstance(pNode);
}

CParameterBaseInteface* CParameterBaseInteface::getInstance(tinyxml2::XMLElement* pNode)
{
	if (!strcmp(pNode->Name(), XML_TAG_ParameterBase))
	{
		const char* type = pNode->Attribute("xsi:type");
		if (!strcmp(type, XML_ATTRIBUTE_ActivationFunctionParameter))
			return new CActivationFunctionParameter(pNode);
		else if (!strcmp(type, XML_ATTRIBUTE_DoubleParameter))
			return new CDoubleParameter(pNode);
		else if (!strcmp(type, XML_ATTRIBUTE_InputDataParameter))
			return new CInputDataParameter(pNode);
		else if (!strcmp(type, XML_ATTRIBUTE_IntParameter))
			return new CIntParameter(pNode);
		else if (!strcmp(type, XML_ATTRIBUTE_IntTuple1DParameter))
			return new CIntTuple1DParameter(pNode);
		else if (!strcmp(type, XML_ATTRIBUTE_IntTuple2DParameter))
			return new CIntTuple2DParameter(pNode);
		else if (!strcmp(type, XML_ATTRIBUTE_IntTuple3DParameter))
			return new CIntTuple3DParameter(pNode);
		else if (!strcmp(type, XML_ATTRIBUTE_IntTuple4DParameter))
			return new CIntTuple4DParameter(pNode);
		//else if (!strcmp(type, XML_ATTRIBUTE_LinkConnectionListParameter))
		//	return CLinkConnectionListParameter(pNode);

	}

	return nullptr;
}
