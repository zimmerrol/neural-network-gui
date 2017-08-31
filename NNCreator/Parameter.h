#pragma once
#include <string>
#include "../3rd/tinyxml2/tinyxml2.h"
#include "ParameterValues.h"

using namespace std;

class CParameterBaseInteface
{
protected:
	string m_name;
public:
	string getName() { return m_name; }
	void setName(string name) { m_name = name; }
	static CParameterBaseInteface* getInstance(tinyxml2::XMLElement* pNode);
};

template <typename T>
class CParameterBase : public CParameterBaseInteface
{
protected:
	T m_value;

public:
	CParameterBase() : CParameterBaseInteface() {};
	~CParameterBase();

	T getValue() { return m_value; }
	void setValue(T value) { m_value = value; }

};

class CDoubleParameter :public CParameterBase<double>
{
public:
	CDoubleParameter(tinyxml2::XMLElement* pNode);

};

class CIntParameter : public CParameterBase<int>
{
public:
	CIntParameter(tinyxml2::XMLElement* pNode);
	CIntParameter() : CParameterBase<int>() {};

};

class CIntTuple1DParameter : public CParameterBase<CTuple1D<int>>
{
public:
	CIntTuple1DParameter(tinyxml2::XMLElement* pNode);

};

class CIntTuple2DParameter : public CParameterBase<CTuple2D<int>>
{
public:
	CIntTuple2DParameter(tinyxml2::XMLElement* pNode);

};

class CIntTuple3DParameter : public CParameterBase<CTuple3D<int>>
{
public:
	CIntTuple3DParameter(tinyxml2::XMLElement* pNode);

};

class CIntTuple4DParameter : public CParameterBase<CTuple4D<int>>
{
public:
	CIntTuple4DParameter() : CParameterBase<CTuple4D<int>>() {};
	CIntTuple4DParameter(tinyxml2::XMLElement* pNode);
};

class CActivationFunctionParameter : public CParameterBase<ActivationFunction>
{
public:
	CActivationFunctionParameter(tinyxml2::XMLElement* pNode);

};

class CInputDataParameter : public CParameterBase<CInputData>
{
public:
	CInputDataParameter(tinyxml2::XMLElement* pNode);

};