/*
	Programmer: Jerusalem Moore
	Class: Interface
	Date: 6/28/2022
	Description:
		Class used for front-end user interacton. Choosing different options, store to db, query db,
		and processing input all happen here.
*/
#pragma once
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>

#include "accountInfo.h"
#include "errorcode.h"

#include <limits>
#include <algorithm> 
#include "userdb.h"
#include <regex>
//#include <string>
//#include <iostream>
class Interface {
public:
	Interface();
	~Interface();
	void runInterface();
	void checkdb();
	void checkAccount();
	void registerUser();
	void dbStat();
	//void printError(std::string errMsg);
	//for error related to username
	//void printError(Username username);
	//enumeration implementation of error printing
	
	bool checkUserExists(Username username);
	bool exists(Username username);
	bool usernameValid(std::string input);

	void login();
private:
	
//	HANDLE hConsole;
	AccountInfo* account;
	UserDB* userdb;
	Error* error;
	std::string cleanName(std::string name);
	bool isNameAlpha(std::string firstName, bool type);
	bool confirmName(std::string name, bool type);
	//bool confirmUsername(Username username);
	void createAccount(AccountInfo* account);
	//void logout();
	void home(AccountInfo* account);
	//get and verify info from input
	bool processFirstName();
	bool processLastName();
	bool processUsername();


};