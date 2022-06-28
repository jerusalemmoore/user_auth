/*
	Programmer: Jerusalem Moore
	Class: Interface
	Description:
		Class used for front-end user interacton. Choosing different options, store to db, query db,
		and processing input all happen here.
*/
#pragma once
#define NOMINMAX
#include "accountInfo.h"
#include <windows.h>
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
	void printError(std::string errMsg);
	//for error related to username
	void printError(Username username);
	bool usernameValid(std::string input);

	void login();
private:
	const std::string FIVECHAR = "Error, entry should be at least 5 characters";
	const std::string INVALIDENTRY = "Invalid entry please try again...";
	const std::string NONALPHA = "Error, name can only contain alphabetic characters";
	HANDLE hConsole;
	AccountInfo* account;
	UserDB* userdb;
	std::string cleanName(std::string name);
	bool isNameAlpha(std::string firstName, bool type);
	bool confirmName(std::string name, bool type);
	bool confirmUsername(Username username);
	void createAccount(AccountInfo* account);
	void logout();
	void home(AccountInfo* account);
	//get and verify info from input
	bool processFirstName();
	bool processLastName();
	bool processUsername();


};