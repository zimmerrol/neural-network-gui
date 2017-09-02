// NNCreator.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream>
#include "../3rd/tinyxml2/tinyxml2.h"
#include "xmltags.h"
#include "NetworkArchitecture.h"
#include "Parameter.h"
#include "Chain.h"
#include "Link.h"
#include "Network.h"
#include "Parameter.h"
#include "ParameterValues.h"
#include "Problem.h"


using namespace std;

int main()
{
	cout << "Problem configuration file [network.xml]:";
	string networkFileName;
	std::getline(cin, networkFileName);
	if (networkFileName.empty())
		networkFileName = "network.xml";

	tinyxml2::XMLDocument doc;
	doc.LoadFile(networkFileName.c_str());
	
	if (doc.Error() == tinyxml2::XML_SUCCESS)
	{
		cout << "Network configuration loaded\n";
		tinyxml2::XMLElement *pRoot = doc.FirstChildElement(XML_TAG_Problem);
		if (pRoot)
		{
			cout << "Parsing network configuration...\n";

			auto problem = CProblem::getInstance(pRoot);
			auto networkArchitecture = problem->getNetworkArchitecture();
			auto param = networkArchitecture->getChains().at(0)->getChainLinks().at(0)->getParameterByName<CInputDataParameter>("Input Data");

			cout << "Traversing the network...\n";
			auto model = problem->createNetwork();
			cout << "\nNetwork meta data:\n";
			cout << "\tNumber of inputs\t\t" << model->getInputs().size() << "\n";
			cout << "\tNumber of layers/links\t\t" << model->getFunctionPtrs().size() << "\n";
			cout << "\tNumber of output layers/links\t" << model->getOutputsFunctionPtr().size() << "\n\n";

			cout << "Building the CNTK model...\n";
			model->buildNetworkFunctionPtr();
			cout << "Model created\n";
			cout << "Saving the model...\n";

			string outputName = "";
			if (networkFileName != "network.xml")
			{
				size_t pos = networkFileName.find_last_of("\\/");
				outputName = (std::string::npos == pos) ? "" : networkFileName.substr(0, pos).append("\\");
			}
			outputName = outputName.append("model.dat");

			model->save(outputName);
			cout << "Model saved.\n";
		}
		else
		{
			cout << "ERROR: Invalid configuration file\n";
		}
	}
	else
	{
		cout << "ERROR: Configuration file not found\n";
	}
	cout << "Press any key to exit\n";
	std::cin.get();
	return 0;
}

