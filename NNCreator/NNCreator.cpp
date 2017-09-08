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

std::vector<double> error_values;
inline void PrintTrainingProgress(const CNTK::TrainerPtr trainer, size_t minibatchIdx, size_t outputFrequencyInMinibatches)
{
	double trainLossValue = trainer->PreviousMinibatchLossAverage();
	error_values.push_back(trainLossValue);
	if (minibatchIdx % outputFrequencyInMinibatches == 0 && trainer->PreviousMinibatchSampleCount() != 0)
	{
		
		double evaluationValue = trainer->PreviousMinibatchEvaluationAverage();
		double avgLoss = 0.0;
		for (int i = 0; i < error_values.size(); i++)
			avgLoss += error_values[i];
		avgLoss /= error_values.size();
		error_values.clear();
		printf("Minibatch %d: loss = %.8g, Avg. loss = %.8g\n", (int)minibatchIdx, trainLossValue, avgLoss);
	}
}

void trainModel(CNetwork* model, int steps=100000)
{
	cout << "Starting the training\n";
	std::vector<float> inputData(2);
	std::vector<float> outputData(1);

	CNTK::ValuePtr inputSequence, outputSequence;
	std::unordered_map<CNTK::Variable, CNTK::ValuePtr> map;

	int max = 100.0;
	int min = -max;

	auto input = model->getInputs().at(0)->getInputFunctionPtr();
	auto output = model->getTargetOutput();
	auto trainer = model->getTrainer();

	int outputFrequencyInMinibatches = 250;
	for (int i = 0; i < steps; i++)
	{
		inputData[0] = min + (((double)rand() / (RAND_MAX))) * (max-min);
		inputData[1] = min + (((double)rand() / (RAND_MAX))) * (max - min);
		outputData[0] = inputData[0] + inputData[1];

		inputSequence = CNTK::Value::CreateSequence(CNTK::NDShape({ 2 }), inputData, CNTK::DeviceDescriptor::CPUDevice());
		outputSequence = CNTK::Value::CreateSequence(CNTK::NDShape({ 1 }), outputData, CNTK::DeviceDescriptor::CPUDevice());

		map = { { input, inputSequence },{ output, outputSequence } };
		trainer->TrainMinibatch(map, CNTK::DeviceDescriptor::CPUDevice());
		PrintTrainingProgress(trainer, i, outputFrequencyInMinibatches);
	}
}

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

		trainModel(model);


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

