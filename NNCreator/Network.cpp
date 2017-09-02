#include "stdafx.h"
#include "Network.h"
#include "CNTKWrapper.h"


CNetwork::CNetwork()
{
	m_outputsFunctionPtr = vector<CNTK::FunctionPtr>();
}


CNetwork::~CNetwork()
{
}

void CNetwork::buildNetworkFunctionPtr()
{
	CNTK::Variable pTrueOutput = CNTK::InputVariable(m_outputsFunctionPtr.at(0)->Output().Shape(), CNTK::DataType::Float, L"Target");

	//TODO: replace with real code
	m_lossFunctionPtr = CNTK::SquaredError(m_outputsFunctionPtr.at(0), pTrueOutput, L"Loss");

	m_networkFunctionPtr = CNTK::Combine({ m_lossFunctionPtr, m_outputsFunctionPtr.at(0) }, L"Network");
}

void CNetwork::save(string fileName)
{
	if (m_networkFunctionPtr == nullptr)
		throw "network has not been built yet";
	m_networkFunctionPtr->Save(CNTKWrapper::Internal::string2wstring(fileName));
}

CNetwork CNetwork::load(string fileName, CNTK::DeviceDescriptor &device)
{
	CNetwork result = CNetwork();
	result.m_networkFunctionPtr = CNTK::Function::Load(CNTKWrapper::Internal::string2wstring(fileName), device);
	return result;
}
