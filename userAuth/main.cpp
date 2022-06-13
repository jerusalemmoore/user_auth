//#ifdef _DEBUG
//#define _CRTDBG_MAP_ALLOC
//#define _CRTDBG_MAP_ALLOC_NEW
//#include <crtdbg.h>
//#include <assert.h>
//#endif
#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//#include <stdio.h>
//#include <string>
//#include <iostream>     // std::cout, std::end
#include "accountInfo.h"
#include "userdb.h"
#include "sqlite3.h"
#include "interface.h"

int main() {

	/*AccountInfo* accountInfo = new AccountInfo();
	UserDB* user = new UserDB();
	delete(user);
	delete(accountInfo);*/
	Interface* interface = new Interface();
	interface->runInterface();
	//check for leaks
	delete(interface);
	bool  isLeaking = _CrtDumpMemoryLeaks();
	std::cout << isLeaking << std::endl;
	

	return 1;
}

