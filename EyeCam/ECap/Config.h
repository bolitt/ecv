#ifndef Config_h__
#define Config_h__

#pragma once

class Config
{
private:
	Config();
	static Config* s_pConfig;
	
public:
	~Config();

public:
	static Config* GetInstance();
	static bool Setup();
	static void Destroy();
};

#endif // Config_h__
