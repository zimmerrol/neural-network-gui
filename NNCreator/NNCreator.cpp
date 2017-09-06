// NNCreator.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream>
#include "../NNCreatorLib/NetworkArchitecture.h"
#include "../NNCreatorLib/Network.h"
#include "../NNCreatorLib/Problem.h"
#include "../NNCreatorLib/Exceptions.h"
#include "../NNCreatorLib/OptimizerSetting.h"

using namespace std;

int main()
{

	try
	{
		cout << "Problem configuration file [network.xml]:";
		string networkFileName;
		std::getline(cin, networkFileName);
		if (networkFileName.empty())
			networkFileName = "network.xml";

		auto problem = CProblem::loadFromFile(networkFileName);
		cout << "Problem description loaded\n";
		cout << "Traversing the network...\n";
		auto model = problem->createNetwork();
		cout << "\nNetwork meta data:\n";
		cout << "\tNumber of inputs\t\t" << model->getInputs().size() << "\n";
		cout << "\tNumber of layers/links\t\t" << model->getFunctionPtrs().size() << "\n";
		cout << "\tNumber of output layers/links\t" << model->getOutputsFunctionPtr().size() << "\n\n";

		cout << "Building the CNTK model...\n";
		model->buildNetworkFunctionPtr(problem->getOptimizerSetting());
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
	catch (exception ex)
	{
		cout << ex.what() << "\n";
	}
	cout << "Press any key to exit\n";
	std::cin.get();
	return 0;
}

