/*
	Programmer: Jerusalem Moore
	Class: Interface
	Date: 6/28/2022
	Description:
		Class used for front-end user interacton. User should be able to login,logout,register, and edit info from here 
*/
#pragma once
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>

#include "accountInfo.h"
#include "errmessenger.h"

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

	void login();
private:
	AccountInfo* account;
	UserDB* userdb;
	ErrMessenger* messenger;
	std::string cleanName(std::string name);
	void registerUser();
	bool tryPassword(Username username, std::string password);
	bool isNameAlpha(std::string name, bool first);
	bool confirmName(std::string name, bool type);
	void createAccount(AccountInfo* account, std::string password);
	bool checkUserExists(Username username);
	bool usernameValid(std::string input);
	bool passwordConfirmed(std::string password);
	std::string requestPassword(std::string prompt);
	bool passwordValid(std::string input);
	void home(AccountInfo* account);
	void checkAccount();
	//get and verify info from input
	bool processFirstName(std::string firstName);
	bool processLastName(std::string lastName);
	bool processUsername(std::string username);
	bool processPassword(std::string password);


};