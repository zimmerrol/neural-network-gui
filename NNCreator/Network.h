#pragma once
#include <vector>
#include "InputData.h"

using namespace std;

class CNetwork
{
protected:
	vector<CInputData*> m_inputs;
	CNTK::FunctionPtr m_pOutputFunctionPtr;
	vector<CNTK::FunctionPtr> m_functionPtrs;

public:
	CNetwork();
	~CNetwork();

	const vector<CInputData*>& getInputs() { return m_inputs; }
	const vector<CNTK::FunctionPtr>& getFunctionPtrs() { return m_functionPtrs; }
	const CNTK::FunctionPtr& getOutputFunctionPtr() { return m_pOutputFunctionPtr; }
};

