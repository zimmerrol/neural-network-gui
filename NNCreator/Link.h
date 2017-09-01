#pragma once
#include <string>
#include "Parameter.h"
#include "ParameterValues.h"
#include <vector>
#include <memory>
#include "CNTKLibrary.h"
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
	CNTK::FunctionPtr m_functionPtr = nullptr;

	CLink(tinyxml2::XMLElement* pNode);	

public:
	CLink();
	~CLink();

	LinkType getLinkType() const { return m_linkType; }
	const CParameterBaseInteface* getParameterByName(const string name) const;
	const vector<CParameterBaseInteface*> getParameters() const { return m_parameters; }

	const string& getId() const { return m_id; }
	const string& getName() const { return m_name; }

	const CNTK::FunctionPtr& getFunctionPtr() const { return m_functionPtr; }
	void setFunctionPtr(const CNTK::FunctionPtr& value) { m_functionPtr = value; }

	static CLink* CLink::getInstance(tinyxml2::XMLElement* pNode);
};