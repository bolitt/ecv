#include "stdafx.h"
#include "ClipTester.h"


ClipTester::ClipTester(void)
{
}


ClipTester::~ClipTester(void)
{
}

void ClipTester::Run()
{
	Clip c;
	bool ret = false;
	{
		ret = c.WriteManifest();
		ASSERT(ret == true);
	}
	{
		//ret = c.ReadManifest();
		ASSERT(ret == true);
	}
	
}
