#pragma once

#include <string>
#include "CNTKLibrary.h"
#include "../3rd/tinyxml2/tinyxml2.h"

using namespace std;

class CInputData
{
protected:
	string m_id;
	CNTK::FunctionPtr m_pInputFunctionPtr;
	CInputData(tinyxml2::XMLElement* pNode);

public:
	CInputData(string id, CNTK::FunctionPtr pInputFunctionPtr);
	~CInputData();

	static CInputData* getInstance(tinyxml2::XMLElement* pNode);
	
	const string& getId() { return m_id; }
	const CNTK::FunctionPtr getInputFunctionPtr() { return m_pInputFunctionPtr; }
};

