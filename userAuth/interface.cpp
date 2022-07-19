/*
	Programmer: Jerusalem Moore
	Class: Interface
	Date: 6/28/2022
	Description:
		Class used for user interacton. Traverse different options, store to db, query db, parsing input
		all happen here.
*/
#pragma once
#include "interface.h"
#include <synchapi.h>
//#include "errormsg.cpp"
#define FIRST true //flag for processing string as first name in functions
#define LOGOUT 2

/*
	initialize account info class for holding logged in user info
	access userdb sqlite3 file
*/
Interface::Interface() {
	account = new AccountInfo();
	userdb = new UserDB("userdb");
	messenger = new ErrMessenger();
}

/*
	clean account info
	clean sqlite3 file ptr
*/
Interface::~Interface() {
	delete account;
	delete userdb;
	delete messenger;
}

/*
	make sure given input follows username rules
*/
bool Interface::usernameValid(std::string input) {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::string choice;
	while (choice != "y") {
		std::cout << "Please confirm username is correct(y / n) : " << input << std::endl;
		std::cout << "input string: " << input << std::endl;
		std::cin >> choice;
		if (choice == "n") {
			std::cout << "Please re-enter username" << std::endl;
			return false;
		}
		else if (choice != "n" && choice != "y") {
			messenger->printError(INVALIDENTRY);
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	//rules for username
	//length of 5+
	if (input.length() < 5) {
		messenger->printError(FIVECHAR);
		return false;
	}
	return true;
}

/*
	check if there is account linked to given username
*/
bool Interface::checkUserExists(Username username) {
	return userdb->usernameExists(username);
}

/*
	routine for retrieving a first name from user input
	return false until first name is verified and cleaned
*/
bool Interface::processFirstName(std::string firstName) {
	bool confirmed = confirmName(firstName, FIRST);
	return confirmed;

}

bool Interface::processLastName(std::string lastName) {
	bool confirmed = confirmName(lastName, !FIRST);
	return confirmed;
}
/*
	get given username input and validate until valid one is produced
*/
bool Interface::processUsername(std::string username) {
	Username usernameStruct;
	usernameStruct.content = username;
	bool valid = usernameValid(usernameStruct.content);
	if (!valid) {
		return valid;
	}
	bool unique = !checkUserExists(usernameStruct);
	if (unique) {
		std::cout << "username confirmed" << std::endl;
		std::cout << usernameStruct.content << std::endl;
		account->setUsername(usernameStruct.content);
		return true;
	}
	messenger->printUserError(USERNAMEEXISTS, username);
	//std::cout << "unique val: " << unique << std::endl;
	return false;
	//return true;
}
/*
	check if password passes rules 
	1. must have length of 8 characters
	2. must have both uppercase and lowercase characters
	3. must include numbers (1,2,3...)
	4. must include a special symbol (!,@,#...)
*/
bool Interface::processPassword(std::string password) {
	bool upper, lower, number, special, length;
	length = false;
	upper = false;
	lower = false;
	number = false;
	special = false;
	if (password.length() >= 8) {
		length = true;
	}
	for (int i = 0; i < password.length(); i++) {
		if (isupper(password[i])) {
			std::cout << "upper case present" << std::endl;
			upper = true;
		}
		if (islower(password[i])) {
			std::cout << "lower case present" << std::endl;
			lower = true;
		}
		if (isdigit(password[i])) {
			std::cout << "num present" << std::endl;
			number = true;
		}
		if (!isdigit(password[i]) && !isalpha(password[i])) {
			if (!isspace(password[i])) {//don't count whitespace as special char
				std::cout << "special char present" << std::endl;
				special = true;
			}
		}
	}
	if (upper && lower && number && special) {
		return true;
	}
	if (!length) {
		messenger->printError(PASSWORDLENGTH);
	}
	if (!upper) {
		messenger->printError(NOUPPERCASE);
	}
	if (!lower) {
		messenger->printError(NOLOWERCASE);
	}
	if (!number) {
		messenger->printError(NONUMBER);
	}
	if (!special) {
		messenger->printError(NOSPECIAL);
	}
	return false;
}
/*
	run firstNameConfirmed until valid name is produced
	run lastNameConfirmed until valid name is produced
*/
void Interface::registerUser() {
	std::string input;
	std::cout << "Please enter requested credentials (or type \"back\" to go back)" << std::endl;
	
	do {
		std::cout << "Please enter valid first name" << std::endl;
		//std::string firstName;
		std::cin >> input;
		if (input == "back") {
			account->clean();
			return;
		}
	} while (!processFirstName(input));
	
	do {
		std::cout << "Please enter valid last name" << std::endl;
		std::cin >> input;
		if (input == "back") {
			account->clean();
			return;
		}
	} while (!processLastName(input));
	
	do {
		std::string username;
		std::cout << "Please enter valid username" << std::endl;
		std::cout << "/////////////////////////////" << std::endl;
		std::cout << "Rules:" << std::endl;
		std::cout << "\t1. only one word" << std::endl;
		std::cout << "\t2. must be unique" << std::endl;
		std::cout << "\t3. must be at least 5 characters" << std::endl;
		std::cout << "//////////////////////////////" << std::endl;
		std::cin >> input;
		if (input == "back") {
			account->clean();
			return;
		}
	} while (!processUsername(input));
	//
	do {
		std::cout << "Please enter valid password" << std::endl;
		std::cout << "/////////////////////////////" << std::endl;
		std::cout << "Rules:" << std::endl;
		std::cout << "\t1. must have length of 8 characters" << std::endl;
		std::cout << "\t2. must have both uppercase and lowercase characters" << std::endl;
		std::cout << "\t3. must include numbers (1,2,3...)" << std::endl;
		std::cout << "\t4. must include a special symbol (!,@,#...)" << std::endl;
		std::cout << "/////////////////////////////" << std::endl;
		std::getline(std::cin, input);
		if (input == "back") {
			account->clean();
			return;
		}
	} while (!processPassword(input));
	std::string password = input;
	std::cout << "Assigning password: " << password << std::endl;
	std::cout << "Username to add to users table" << std::endl;
	account->printData();
	createAccount(account, password);
	return;

}
/*
	Use account credentials to store to userdb,
	enter home menu 
	input: 
		account holding required info to store to db
		password to store to db, don't want this to be available after 
			registration 

*/
void Interface::createAccount(AccountInfo* account, std::string password) {
	userdb->insertUser(account->getFirstName(), account->getLastName(), account->getUsername(), password);
	std::cout << "User " << account->getUsername() << " registered" << std::endl;
	std::cout << "Navigating to user home..." << std::endl;
	Sleep(3000);
	home(account);
}

/*
	Check if there is an account linked to username and password
	combination
	input: 
		username to query with password
		password to query with username
	return 
		true if combination exists
		false otherwise
*/
bool Interface::tryPassword(Username username, std::string password) {
	if (userdb->validateAccount(username, password, account)) {
		//print account info for verification
		account->printData();
		return true;
	}
	return false;
}
//gather account info through login
/*
	in progress...
*/

/*
	Begin login process
*/
void Interface::login() {
	std::string input;

	Username username;
	std::string password;
	bool passwordConfirmed;
	do {
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << "Please Enter Requested Login Credentials" << std::endl;
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << "Username: ";
		std::cin >> input;
		username.content = input;
		std::cout << std::endl;
		std::cout << "Password: ";
		std::cin >> password;
		//if user doesn't exist or try password fails 
		passwordConfirmed = tryPassword(username, password);
		if (!passwordConfirmed) {
			//std::cout << "Error, Username/Password combination incorrect" << std::endl;
			messenger->printError(LOGINFAILED);
		}
	/*	std::cout << checkUserExists(username) << std::endl;;
		std::cout << (password == "Aa98064203") << std::endl;*/
	} while (!passwordConfirmed);
	std::cout << "Logging in..." << std::endl;
	Sleep(3000);
	home(account);


}

/*
	Entry point for home menu
	input:
		account with linked information

*/
void Interface::home(AccountInfo* account) {
	//system("CLS");
	int input = -1;
	while (input != LOGOUT) {
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << "Hello " << account->getFirstName() << " " << account->getLastName() << std::endl;
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << "Please choose an option(1, 2, 3...)" << std::endl;
		std::cout << "1. Edit account" << std::endl;
		std::cout << "2. Logout" << std::endl;
		std::cin >> input;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		switch (input) {
		case 1: {
			break;
		}
		case 2: {
			system("CLS");
			account->clean();
			break;
		}
		default: {
			messenger->printError(INVALIDENTRY);
			break;
		}
		}
	}
}

/*
	entry point for running authentication system
*/
void Interface::runInterface() {
	int userInput = -1;
	do {
		if (!account->isClear()) {
			std::cout << "Error, user info should be clear if on this menu...\n" << std::endl;
			exit(EXIT_FAILURE);
		}
		
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << "User Authentication System" << std::endl;
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << "Please choose an option: (1,2,3...)" << std::endl;
		std::cout << "1. Register" << std::endl;
		std::cout << "2. Login" << std::endl;
		std::cout << "3. Exit" << std::endl;
		std::cin >> userInput;

		switch (userInput) {
		case 1: {
			registerUser();
			break;
		}
		case 2: {
			login();
			break;
		}
		case 3: {
			break;
		}
		default: {
			messenger->printError(INVALIDENTRY);
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
		}

	} while (userInput != 3);
}

/*
	Format first/last name 
*/
std::string Interface::cleanName(std::string name) {
	//make sure first name is uppercase, everything else is lowercase
	for (int i = 0; i < name.length(); i++) {
		name[i] = tolower(name[i]);
	}
	name[0] = toupper(name[0]);
	std::cout << "cleaned name " << name << std::endl;
	return name;
}

//check if name is alphabetical, if yes assign first/last name to accountInfo member
bool Interface::isNameAlpha(std::string name, bool first) {
	//is name alphabetical, if not return false 
	if (std::regex_match(name, std::regex("^[A-Za-z]+$"))) {
		std::cout << "all good" << std::endl;
		//std::cout << "Continuing" << std::endl;
		name = cleanName(name);
		if (first) {
			account->setFirstName(name);
		}
		else if (!first) {
			account->setLastName(name);
		}
		//might not need this, first is bool so shouldn't get anything unexpected 
		else {
			std::cout << "Error, invalid type: " << first << std::endl;
			return false;
		}
		//std::cout << "First name confirmed: " << firstName << std::endl;
		return true;
	}
	messenger->printError(NONALPHA);
	return false;


}

/*
	confirm first or last name depending on type
	name: name to confirm
	type: FIRST or !FIRST defined for first or last name
*/
bool Interface::confirmName(std::string name, bool isFirst) {
	//just get the first string of input to evaluate as the first name 
//this line clears the buffer so the remaining inputs don't register for the following confirmation
//choice made by user
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	//confirm the first name is correct
	//when confirmed clean it, make sure first char is uppercase and the following are lowercase
	while (1) {
		std::cout << "Please confirm " << (isFirst ? "first" : "last") << "name is correct(y / n) : " << name << std::endl;
		std::string choice;
		std::cin >> choice;
		if (choice == "y") {
			//user confirmed, make sure name is alphabetical
			return isNameAlpha(name, isFirst);
		}
		else if (choice == "n") {
			std::cout << "Please re-enter " << (isFirst ? "first" : "last") << " name" << std::endl;
			return false;
		}
		else {
		messenger->printError(INVALIDENTRY);
		}
	}
}

/*
	make sure name is only letters
	input:
	string name
*/
//void Interface::checkdb() {
//	userdb->dbhealthcheck();
//}

//print account information
void Interface::checkAccount() {
	account->printData();
}
//void Interface::dbStat() {
//
//}