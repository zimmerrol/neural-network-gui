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
	tinyxml2::XMLDocument doc;
	
	doc.LoadFile("C:\\Users\\Roland\\Documents\\Visual Studio 2017\\Projects\\neural-network-gui\\NNGui\\bin\\Debug\\network.xml");
	if (doc.Error() == tinyxml2::XML_SUCCESS)
	{
		tinyxml2::XMLElement *pRoot = doc.FirstChildElement(XML_TAG_Problem);
		if (pRoot)
		{
			auto problem = CProblem::getInstance(pRoot);
			auto networkArchitecture = problem->getNetworkArchitecture();
			auto param = networkArchitecture->getChains().at(0)->getChainLinks().at(0)->getParameterByName<CInputDataParameter>("Input Data");
			auto model = problem->createNetwork();
			cout << networkArchitecture;
		}
	}
    return 0;
}

