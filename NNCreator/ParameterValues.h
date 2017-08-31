#pragma once
#include <string>
#include "../3rd/tinyxml2/tinyxml2.h"

using namespace std;
enum class ActivationFunction
{
	elu,
	selu,
	softplus,
	softsign,
	relu,
	tanh,
	sigmoid = 0,
	hard_sigmoid,
	softmax
};

template <typename T>
class CTuple1D
{
protected:
	T m_x1;
	CTuple1D(tinyxml2::XMLElement* pNode);

public:
	CTuple1D() {};
	CTuple1D(T x1) : CTuple1D() {
		m_x1 = x1;
	}
	
	static CTuple1D<T>* getInstance(tinyxml2::XMLElement* pNode);

	T getX1() { return m_x1; }
	void setX1(T x1) { m_x1 = x1; }
};

template <typename T>
class CTuple2D
{
protected:
	T m_x1;
	T m_x2;
	CTuple2D(tinyxml2::XMLElement* pNode);
public:
	CTuple2D() {};
	CTuple2D(T x1, T x2) : CTuple2D() {
		m_x1 = x1;
		m_x2 = x2;
	}
	
	static CTuple2D<T>* getInstance(tinyxml2::XMLElement* pNode);

	T getX1() { return m_x1; }
	void setX1(T x1) { m_x1 = x1; }
	T getX2() { return m_x2; }
	void setX2(T x2) { m_x2 = x2; }
};

template <typename T>
class CTuple3D 
{
protected:
	T m_x1;
	T m_x2;
	T m_x3;
	CTuple3D(tinyxml2::XMLElement* pNode);
public:
	CTuple3D() {};
	CTuple3D(T x1, T x2, T x3) : CTuple3D() {
		m_x1 = x1;
		m_x2 = x2;
		m_x3 = x3;
	}
	
	static CTuple3D<T>* getInstance(tinyxml2::XMLElement* pNode);

	T getX1() { return m_x1; }
	void setX1(T x1) { m_x1 = x1; }
	T getX2() { return m_x2; }
	void setX2(T x2) { m_x2 = x2; }
	T getX3() { return m_x3; }
	void setX3(T x3) { m_x3 = x3; }
};

template <typename T>
class CTuple4D 
{
protected:
	T m_x1;
	T m_x2;
	T m_x3;
	T m_x4;
	CTuple4D(tinyxml2::XMLElement* pNode);

public:
	CTuple4D() {};
	CTuple4D(T x1, T x2, T x3, T x4) : CTuple4D() {
		m_x1 = x1;
		m_x2 = x2;
		m_x3 = x3;
		m_x4 = x4;
	}
	
	static CTuple4D<T>* getInstance(tinyxml2::XMLElement* pNode);

	T getX1() { return m_x1; }
	void setX1(T x1) { m_x1 = x1; }
	T getX2() { return m_x2; }
	void setX2(T x2) { m_x2 = x2; }
	T getX3() { return m_x3; }
	void setX3(T x3) { m_x3 = x3; }
	T getX4() { return m_x4; }
	void setX4(T x4) { m_x4 = x4; }
};

class CInputData
{
protected:
	string m_id;
public:
	CInputData() {};
	CInputData(tinyxml2::XMLElement* pNode);
	static CInputData* getInstance(tinyxml2::XMLElement* pNode);

	string getID() { return m_id; }
	void setID(string id) { m_id = id; }
};

template <typename T>
CTuple1D<T>::CTuple1D(tinyxml2::XMLElement* pNode)
{

}