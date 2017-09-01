#include "stdafx.h"
#include "CNTKWrapper.h"
#include "Parameter.h"
#include "Link.h"

#include <locale>
#include <codecvt>
#include <string>


using namespace CNTKWrapper::Internal;

CNTK::FunctionPtr CNTKWrapper::InputLayer(const CLink * pLink, vector<const CLink*> dependencies, CNTK::DeviceDescriptor & device)
{
	
}

CNTK::FunctionPtr CNTKWrapper::DenseLayer(const CLink * pLink, vector<const CLink*> dependencies, CNTK::DeviceDescriptor& device)
{
	int output_nodes = ((CIntParameter*)pLink->getParameterByName("Nodes"))->getValue();
	wstring name = string2wstring(pLink->getName());
	auto activationFunction = ((CActivationFunctionParameter*)pLink->getParameterByName("Activation"))->getValue();
	const std::function<FunctionPtr(const FunctionPtr&)>& nonLinearity = createNonLinearity(activationFunction);

	return FullyConnectedDNNLayer(dependencies.at(0)->getFunctionPtr(), output_nodes, device, nonLinearity, name);
}
