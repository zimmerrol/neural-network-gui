#pragma once
#include "../3rd/tinyxml2/tinyxml2.h"
#include <vector>

class CNetworkArchitecture;
class CInputData;
class CNetwork;
class CLinkConnection;

class CProblem
{
protected:
	std::vector<CInputData*> m_inputs;
	CNetworkArchitecture* m_pNetworkArchitecture;
	CLinkConnection* m_output;

	CProblem(tinyxml2::XMLElement* pNode);
public:
	CProblem();
	~CProblem();

	CNetworkArchitecture* getNetworkArchitecture() { return m_pNetworkArchitecture; }
	const std::vector<CInputData*>& getInputs() const { return m_inputs; }
	const CLinkConnection* getOutput() const { return m_output; }

	static CProblem* getInstance(tinyxml2::XMLElement* pNode);

	CNetwork* createNetwork();
};

