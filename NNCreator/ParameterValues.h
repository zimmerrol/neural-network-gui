#pragma once
#include <string>
#include "../3rd/tinyxml2/tinyxml2.h"

using namespace std;
enum class ActivationFunction
{
	sigmoid = 0,
	elu,
	selu,
	softplus,
	softsign,
	relu,
	tanh,
	hard_sigmoid,
	softmax
};

class CIntTuple1D
{
protected:
	int m_x1;
	CIntTuple1D(tinyxml2::XMLElement* pNode);

public:
	CIntTuple1D() {};
	CIntTuple1D(int x1) : CIntTuple1D() {
		m_x1 = x1;
	}
	
	static CIntTuple1D* getInstance(tinyxml2::XMLElement* pNode);

	int getX1() { return m_x1; }
	void setX1(int x1) { m_x1 = x1; }
};

class CIntTuple2D
{
protected:
	int m_x1;
	int m_x2;
	CIntTuple2D(tinyxml2::XMLElement* pNode);
public:
	CIntTuple2D() {};
	CIntTuple2D(int x1, int x2) : CIntTuple2D() {
		m_x1 = x1;
		m_x2 = x2;
	}
	
	static CIntTuple2D* getInstance(tinyxml2::XMLElement* pNode);

	int getX1() { return m_x1; }
	void setX1(int x1) { m_x1 = x1; }
	int getX2() { return m_x2; }
	void setX2(int x2) { m_x2 = x2; }
};

class CIntTuple3D 
{
protected:
	int m_x1;
	int m_x2;
	int m_x3;
	CIntTuple3D(tinyxml2::XMLElement* pNode);
public:
	CIntTuple3D() {};
	CIntTuple3D(int x1, int x2, int x3) : CIntTuple3D() {
		m_x1 = x1;
		m_x2 = x2;
		m_x3 = x3;
	}
	
	static CIntTuple3D* getInstance(tinyxml2::XMLElement* pNode);

	int getX1() { return m_x1; }
	void setX1(int x1) { m_x1 = x1; }
	int getX2() { return m_x2; }
	void setX2(int x2) { m_x2 = x2; }
	int getX3() { return m_x3; }
	void setX3(int x3) { m_x3 = x3; }
};

class CIntTuple4D 
{
protected:
	int m_x1;
	int m_x2;
	int m_x3;
	int m_x4;
	CIntTuple4D(tinyxml2::XMLElement* pNode);

public:
	CIntTuple4D() {};
	CIntTuple4D(int x1, int x2, int x3, int x4) : CIntTuple4D() {
		m_x1 = x1;
		m_x2 = x2;
		m_x3 = x3;
		m_x4 = x4;
	}
	
	static CIntTuple4D* getInstance(tinyxml2::XMLElement* pNode);

	int getX1() { return m_x1; }
	void setX1(int x1) { m_x1 = x1; }
	int getX2() { return m_x2; }
	void setX2(int x2) { m_x2 = x2; }
	int getX3() { return m_x3; }
	void setX3(int x3) { m_x3 = x3; }
	int getX4() { return m_x4; }
	void setX4(int x4) { m_x4 = x4; }
};

class CInputDataValue
{
protected:
	string m_id;
	CInputDataValue(tinyxml2::XMLElement* pNode);
public:
	CInputDataValue() {};
	
	static CInputDataValue* getInstance(tinyxml2::XMLElement* pNode);

	string getID() { return m_id; }
	void setID(string id) { m_id = id; }
};

class CLinkConnection
{
protected:
	string m_targetID;
	CLinkConnection(tinyxml2::XMLElement* pNode);
public:
	CLinkConnection();
	~CLinkConnection();
	const string& getTargetId() const { return m_targetID; }

	static CLinkConnection* getInstance(tinyxml2::XMLElement* pNode);
};