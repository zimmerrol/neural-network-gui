#include "stdafx.h"
#include "InputData.h"


CInputData::CInputData(tinyxml2::XMLElement * pNode)
{
	//read id
}

CInputData::CInputData(string id, CNTK::FunctionPtr pInputFunctionPtr)
{
	m_id = id;
	m_pInputFunctionPtr = pInputFunctionPtr;
}


CInputData::~CInputData()
{
}

CInputData * CInputData::getInstance(tinyxml2::XMLElement * pNode)
{
	return nullptr;
}
