#include "StdAfx.h"
#include "EPackDispatcher.h"
#include "../3rdparty/xgetopt/XGetopt.h"

using namespace std;

EPackDispatcher::EPackDispatcher(void)
{
}

EPackDispatcher::~EPackDispatcher(void)
{
}

void EPackDispatcher::Usage()
{
	cerr << "Usages: Pack photos"
		<< "EPack.exe [options]" << endl
		<< "[options]:" << endl
		<< "  -h: help" << endl
		<< "  -i <input>: input name" << endl
		<< "  -o <output>: output file" << endl;
}

#define MAX_LINE_LEN 80
void EPackDispatcher::Run( int argc, TCHAR* argv[], TCHAR* envp[] )
{	
	int c;
	while ((c = getopt(argc, argv, _T("hi:o:"))) != EOF) {
		switch(c) {
			case _T('h'): Usage(); return;
			case _T('i'): break;
			case _T('o'): break;
		}
	}

	// echo
	for (int i = 0; i < argc; i++) {
		wcout << argv[i] << endl;
	}

		//local variables
	FILE* fid;
	char cmdLine[MAX_LINE_LEN];
	//CreateProcess parameters
	LPSECURITY_ATTRIBUTES processA=NULL;//Default
	LPSECURITY_ATTRIBUTES threadA=NULL;//Default
	BOOL shareRights=TRUE;//Default
	DWORD creationMask=CREATE_NEW_CONSOLE;//Window per process.
	LPVOID enviroment=NULL;//Default
	LPSTR curDir=NULL;//Default
	STARTUPINFO startInfo;//Result
	PROCESS_INFORMATION procInfo;//Result
	/*
	if(!CreateProcess(
			NULL£¬//File name of executable
			cmdLine£¬//command line
			processA£¬//Process inherited security
			threadA£¬ //Thread inherited security
			shareRights£¬//Rights propagation
			creationMask£¬//various creation flags
			enviroment£¬//Enviroment variable
			curDir£¬ //Child's current directory
			&startInfo£¬
			&procInfo 
			));*/
}

