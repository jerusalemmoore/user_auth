//#ifdef _DEBUG
//#define _CRTDBG_MAP_ALLOC
//#define _CRTDBG_MAP_ALLOC_NEW
//#include <crtdbg.h>
//#include <assert.h>
//#endif
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//#include <stdio.h>
//#include <string>
//#include <iostream>     // std::cout, std::end
//#include "accountInfo.h"
//#include "userdb.h"
//#include "sqlite3.h"
#pragma comment(lib, "crypt32")
#pragma comment(lib, "ws2_32.lib")
#define _CRTDBG_MAP_ALLOC
#include <winsock2.h>
#include <windows.h>
#include <cstdlib>
#include <crtdbg.h>
#include "passwordprocessor.h"
#include <bitset>
#include <cstddef>


#include "interface.h"
#include "queryStructs.h"
static int callback(void* data, int argc, char** argv, char** azColName) {
	int i;
	fprintf(stderr, "%s: \n", (const char*)data);
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

/// THIS IS WHAT WE'RE DOING
/// //////////////////////////////
///YOU BUILT USERNAME SQL QUERY SEARCH(SHOULD CLEAN AND DOCUMENT)
///YOU NEED BETTER GENERALIZATION OF SELECT FUNC
int main() {


	/*Interface* myinterface = new Interface();
	myinterface ->runInterface();
	delete(myinterface);*/
	PasswordProcessor* pprocessor = new PasswordProcessor();
	delete(pprocessor);


	/*if (!rc) {
		std::cout << "There was an error..." << std::endl;
	}*/
	int leaking = _CrtDumpMemoryLeaks();
	if (leaking) {
		std::cout << "LEAKING\n\n\n" << std::endl;
	}
	else {
		std::cout << "no leaks" << std::endl;
	}


	return 0;
}

