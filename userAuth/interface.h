/*
	Programmer: Jerusalem Moore
	Class: Interface 
	Description:
		Class used for front-end user interacton. Choosing different options, store to db, query db,
		and processing input all happen here.
*/
#pragma once
#include "accountInfo.h"
#include "userdb.h"
#include <regex>
#include <string>
#include <iostream>
class Interface {
public:
	Interface();
	~Interface();
	void runInterface();
	void checkdb();
	void checkAccount();
	void registerUser();
	void dbStat();
	//void createAccount();
	//void logout();
	//void login();
private:
	AccountInfo* account;
	UserDB* userdb;
	std::string cleanName(std::string name);
	bool isNameAlpha(std::string firstName, bool type);
	bool confirmName(std::string name, bool type);
	bool confirmUsername(Username username);
	//get and verify info from input
	bool processFirstName();
	bool processLastName();
	bool processUsername();

};