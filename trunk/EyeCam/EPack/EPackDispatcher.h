#ifndef EPackDispatcher_h__
#define EPackDispatcher_h__

#pragma once

class EPackDispatcher
{
public:
	EPackDispatcher();
	~EPackDispatcher();

public:
	void Run(int argc, TCHAR* argv[], TCHAR* envp[]);
	void Usage();
};

#endif // EPackDispatcher_h__
