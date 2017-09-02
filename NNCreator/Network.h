#pragma once
#include <vector>
#include "InputData.h"

using namespace std;

class CNetwork
{
protected:
	vector<CInputData*> m_inputs;
	vector<CNTK::FunctionPtr> m_functionPtrs;
	vector<CNTK::FunctionPtr> m_outputsFunctionPtr;
	CNTK::FunctionPtr m_networkFunctionPtr;
	CNTK::FunctionPtr m_lossFunctionPtr;

public:
	CNetwork();
	~CNetwork();

	vector<CInputData*>& getInputs() { return m_inputs; }
	vector<CNTK::FunctionPtr>& getOutputsFunctionPtr() { return m_outputsFunctionPtr; }
	vector<CNTK::FunctionPtr>& getFunctionPtrs() { return m_functionPtrs; }
	CNTK::FunctionPtr getNetworkFunctionPtr() { return m_networkFunctionPtr; }
	CNTK::FunctionPtr getLossFunctionPtr() { return m_lossFunctionPtr; }

	void buildNetworkFunctionPtr();
	void save(string fileName);
	static CNetwork load(string fileName, CNTK::DeviceDescriptor &device);
};

