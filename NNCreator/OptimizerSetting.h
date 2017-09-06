#pragma once
#include "../3rd/tinyxml2/tinyxml2.h"
#include <vector>

enum class OptimizerType
{
	SGD,
	MomentumSGD,
	Nesterov,
	FSAdaGrad,
	Adam,
	AdaGrad,
	RMSProp,
	AdaDelta,
};

class COptimizerParameter;

class COptimizerSetting
{
protected:
	COptimizerSetting(tinyxml2::XMLElement *pNode);
	OptimizerType m_optimizerType;
	std::vector<COptimizerParameter*> m_parameters;
public:
	COptimizerSetting();
	~COptimizerSetting();
	static COptimizerSetting* getInstance(tinyxml2::XMLElement* pNode);
};

class COptimizerParameter
{
protected:
	std::string m_key;
	double m_value;

	COptimizerParameter(tinyxml2::XMLElement *pNode);

public:
	COptimizerParameter();
	~COptimizerParameter();
	static COptimizerParameter* getInstance(tinyxml2::XMLElement* pNode);
};
