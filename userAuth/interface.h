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
#include "prompts.h"
#include <windows.h>
#include "accountInfo.h"
#include "errmessenger.h"
#include <limits>
#include <algorithm> 
#include "userdb.h"
#include <regex>
#include <fstream>
//#include "prompts.h"

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
	Prompter* prompter;
	std::string cleanName(std::string name);
	void registerUser();
	bool tryPassword(std::string username, std::string password, ErrorCode error);
	bool validateName(std::string name);
	void createAccount(AccountInfo* account, std::string password);
	bool validatePassword(std::string password);

	bool userExists(std::string username);
	bool usernameValid(std::string input);
	bool passwordConfirmed(std::string password);
	bool validateMenuChoice(std::string input);
	void home(AccountInfo* account);
	void checkAccount();
	void removeAccount();
	void editUsername();
	void editAccount();
	void editFirstname();
	void editLastname();
	void editPassword();
	//user input gathering loops
	bool firstnameLoop();
	bool lastnameLoop();
	bool usernameLoop();
	bool passwordLoop(std::string* passwordBuffer);
	//get and verify info from input
	bool processFirstName(std::string firstName);
	bool processLastName(std::string lastName);
	bool processUsername(std::string username);
	std::string getPassword();


};