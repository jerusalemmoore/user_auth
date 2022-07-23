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

void myFunc() {
	//while (true)
	//{
	//	if (GetAsyncKeyState(VK_ESCAPE))
	//	{
	//		std::cout << "DUDE! You've pressed the escape key";
	//		//std::cin.ignore();
	//	}
	//}
	Interface* myinterface = new Interface();
	myinterface->runInterface();
	delete(myinterface);

	///WINDOWS PASSWORD HIDING
	/*const char BACKSPACE = 8;
	const char RETURN = 13;
	std::string password;
	unsigned char ch = 0;
	std::cout << "Enter password" << std::endl;
	DWORD con_mode;
	DWORD dwRead;
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hIn, &con_mode);
	SetConsoleMode(hIn, con_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));
	while (ReadConsoleA(hIn, &ch, 1, &dwRead, NULL) && ch != RETURN) {
		if (ch == BACKSPACE) {
			if (password.length() != 0) {
				std::cout << "\b \b";
				password.resize(password.length() - 1);
			}
			
		}
		else {
			password += ch;
			std::cout << '*';
		}
	}*/
}
/// THIS IS WHAT WE'RE DOING
/// //////////////////////////////
///ADD PASSWORD CONFIRMATION THAT REQUIRES TWO ENTRIES OF PASSWORD
///ADD TEXT HIDING OF PASSWORD ENTRY   
///NEED TO BUILD FUNCTION THAT ALLOWS ACCOUNT EDITING
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

