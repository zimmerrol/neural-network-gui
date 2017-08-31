#pragma once
#include <string>
#include "Parameter.h"
#include "ParameterValues.h"
#include <vector>
#include <memory>
#include "../3rd/tinyxml2/tinyxml2.h"

using namespace std;

enum class LinkType
{
	InputLayer,
	ActivationLayer,
	Convolution1DLayer,
	Convolution2DLayer,
	Convolution3DLayer,
	DenseLayer,
	DropoutLayer,
	FlattenLayer,
	ReshapeLayer,
	MergeLayer,
};

class CLink
{
protected:
	string m_name;
	string m_id;
	vector<CParameterBaseInteface*> m_parameters;
	LinkType m_linkType;
	CLink(tinyxml2::XMLElement* pNode);

public:
	CLink();
	~CLink();

	LinkType getLinkType() { return m_linkType; }
	const CParameterBaseInteface* getParameterByName(const string name);
	const vector<CParameterBaseInteface*> getParameters() { return m_parameters; }

	static CLink* CLink::getInstance(tinyxml2::XMLElement* pNode);
};