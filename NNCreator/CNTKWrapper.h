#pragma once
#include "CNTKLibrary.h"
#include "Link.h"

#include <locale>
#include <codecvt>
#include <string>


using namespace CNTK;

namespace CNTKWrapper
{
	CNTK::FunctionPtr InputLayer(const CLink* pLink, vector<const CLink*> dependencies, CNTK::DeviceDescriptor& device);
	CNTK::FunctionPtr ActivationLayer(const CLink* pLink, vector<const CLink*> dependencies, CNTK::DeviceDescriptor& device);
	CNTK::FunctionPtr Convolution1DLayer(const CLink* pLink, vector<const CLink*> dependencies, CNTK::DeviceDescriptor& device);
	CNTK::FunctionPtr Convolution2DLayer(const CLink* pLink, vector<const CLink*> dependencies, CNTK::DeviceDescriptor& device);
	CNTK::FunctionPtr Convolution3DLayer(const CLink* pLink, vector<const CLink*> dependencies, CNTK::DeviceDescriptor& device);
	CNTK::FunctionPtr DenseLayer(const CLink* pLink, vector<const CLink*> dependencies, CNTK::DeviceDescriptor& device);
	CNTK::FunctionPtr DropoutLayer(const CLink* pLink, vector<const CLink*> dependencies, CNTK::DeviceDescriptor& device);
	CNTK::FunctionPtr FlattenLayer(const CLink* pLink, vector<const CLink*> dependencies, CNTK::DeviceDescriptor& device);
	CNTK::FunctionPtr ReshapeLayer(const CLink* pLink, vector<const CLink*> dependencies, CNTK::DeviceDescriptor& device);
	CNTK::FunctionPtr MergeLayer(const CLink* pLink, vector<const CLink*> dependencies, CNTK::DeviceDescriptor& device);

	namespace Internal
	{
		inline std::wstring string2wstring(string value)
		{
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			std::wstring wide = converter.from_bytes(value);
			return wide;
		}

		const std::function<FunctionPtr(const FunctionPtr&)>& createNonLinearity(ActivationFunction activationFunction)
		{
			switch (activationFunction)
			{
			case ActivationFunction::elu:
				return std::bind(ELU, std::placeholders::_1, L"");
			case ActivationFunction::hard_sigmoid:
				//TODO: is this the correct function?
				return std::bind(Hardmax, std::placeholders::_1, L"");
			case ActivationFunction::relu:
				return std::bind(ReLU, std::placeholders::_1, L"");
			case ActivationFunction::selu:
				return std::bind(SELU, std::placeholders::_1, 1.0507009873554804934193349852946, 1.6732632423543772848170429916717, L"");
			case ActivationFunction::sigmoid:
				return std::bind(Sigmoid, std::placeholders::_1, L"");
			case ActivationFunction::softmax:
				throw "not supported at the moment";
				//TODO: solve this problem
				//return std::bind<FunctionPtr(const Variable&, const std::wstring&)>(Softmax, std::placeholders::_1, L"");
			case ActivationFunction::softplus:
				return std::bind(Softplus, std::placeholders::_1, L"");
			case ActivationFunction::softsign:
				throw "not supported at the moment";
			case ActivationFunction::tanh:
				return std::bind(Tanh, std::placeholders::_1, L"");
			}
		}

		//#define ACTIVATION(x) std::bind(x, std::placeholders::_1, L"")
		inline FunctionPtr FullyConnectedLinearLayer(Variable input, size_t outputDim, const DeviceDescriptor& device, const std::wstring& outputName = L"")
		{
			assert(input.Shape().Rank() == 1);
			size_t inputDim = input.Shape()[0];

			auto timesParam = Parameter({ outputDim, inputDim }, DataType::Float, GlorotUniformInitializer(DefaultParamInitScale, SentinelValueForInferParamInitRank, SentinelValueForInferParamInitRank, 1), device, L"timesParam");
			auto timesFunction = Times(timesParam, input, L"times");

			auto plusParam = Parameter({ outputDim }, 0.0f, device, L"plusParam");
			return Plus(plusParam, timesFunction, outputName);
		}

		inline FunctionPtr FullyConnectedDNNLayer(Variable input, size_t outputDim, const DeviceDescriptor& device, const std::function<FunctionPtr(const FunctionPtr&)>& nonLinearity, const std::wstring& outputName = L"")
		{
			return nonLinearity(FullyConnectedLinearLayer(input, outputDim, device, outputName));
		}
	}
}