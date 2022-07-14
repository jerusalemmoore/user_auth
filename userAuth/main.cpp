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
void myFunc() {
	std::string password = "Jerusaelm@moore 1";
	Interface* myinterface = new Interface();
	myinterface->runInterface();
	delete(myinterface);
}
/// THIS IS WHAT WE'RE DOING
/// //////////////////////////////
///YOU BUILT USERNAME SQL QUERY SEARCH(SHOULD CLEAN AND DOCUMENT)
///YOU NEED BETTER GENERALIZATION OF SELECT FUNC
int main() {


	
	/*PasswordProcessor* pprocessor = new PasswordProcessor();
	delete(pprocessor);*/
	myFunc();
	
	int leaking = _CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	if (leaking) {
		std::cout << "LEAKING\n\n\n" << std::endl;
	}
	else {
		std::cout << "no leaks" << std::endl;
	}
	//if (password.length() < 8) {
	//	std::cout << "too short" << std::endl;
	//	return false;
	//}
	
	/*if (!rc) {
		std::cout << "There was an error..." << std::endl;
	}*/
	


	return 0;

}

