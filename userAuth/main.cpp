#define _CRTDBG_MAP_ALLOC
#include <winsock2.h>
#include <windows.h>
#include <cstdlib>
#include <crtdbg.h>
#include "passwordprocessor.h"
#include "interface.h"
#include "queryStructs.h"



int main() {
	Interface* myinterface = new Interface();
	myinterface->runInterface();
	delete(myinterface);
	//look evaluate for leaks, 1 leak currently triggering looks to be a false alarm 
	//originating from libraries
	int leaking = _CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	if (leaking) {
		std::cout << "LEAKING\n\n\n" << std::endl;
	}
	else {
		std::cout << "no leaks" << std::endl;
	}

	return 0;

}

