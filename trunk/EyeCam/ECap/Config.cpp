#include "stdafx.h"
#include "Config.h"
// Other include files, declarations, and non-Xerces-C++ initializations.

using namespace xercesc;

Config* Config::s_pConfig = NULL;

Config::Config(void)
{
}

Config::~Config(void)
{
}

Config* Config::GetInstance()
{
	if (s_pConfig != NULL) {
		Setup();
		s_pConfig = new Config();
	}
	return s_pConfig;
}

bool Config::Setup()
{
	try {
		XMLPlatformUtils::Initialize();
		return true;
	}
	catch (const XMLException& toCatch) {
		// Do your failure processing here
		return false;
	}
}

void Config::Destroy()
{
	XMLPlatformUtils::Terminate();
}
