/*
	Programmer: Jerusalem Moore
	Class: Interface 
	Description:
		Class used for user interacton. Traverse different options, store to db, query db, parsing input
		all happen here.
*/
#pragma once
#include "interface.h"
#define FIRST true //flag for processing string as first name in functions
//when interface created, make sure USERS table exists 
//develop schema and verify schema in constructor
Interface::Interface() {
	account = new AccountInfo();
	userdb = new UserDB("USERS");
	std::string initTable =
		" \
		CREATE TABLE IF NOT EXISTS USERS (\
		uid INTEGER PRIMARY KEY, \
		firsName TEXT NOT NULL, \
		lastName TEXT NOT NULL, \
		username TEXT NOT NULL UNIQUE, \
		password TEXT NOT NULL \
		);\
		" ;
	userdb->sqlEx(initTable);
	std::string getTableInfo = "\
		pragma table_info('users');\
		";
	userdb->sqlEx(getTableInfo);
}
Interface::~Interface() {
	delete account;
	delete userdb;
}
bool Interface::confirmUsername(std::string username) {
	userdb->sqlEx("SELECT * FROM USERS WHERE username == '" + username + "';");
	return true;
}
bool Interface::processUsername() {
	std::string username;
	std::cout << "Please enter valid username" << std::endl;
	std::cout << "Rules:" << std::endl;
	std::cout << "1. only one word" << std::endl;
	std::cout << "2. must be unique" << std::endl;
	std::cin >> username;
	bool confirmed = confirmUsername(username);
	return confirmed;
}
/*
	run firstNameConfirmed until valid name is produced
	run lastNameConfirmed until valid name is produced
*/
void Interface::registerUser() {
	std::cout << "Please enter requested credentials" << std::endl;
	bool firstNameConfirmed = false;
	do {
		firstNameConfirmed = processFirstName();
	} while (!firstNameConfirmed);
	bool lastNameConfirmed = false;
	do {
		lastNameConfirmed = processLastName();
	} while (!lastNameConfirmed);
	bool usernameConfirmed = false;
	do {
		usernameConfirmed = processUsername();
	} while (!usernameConfirmed);

}
void Interface::runInterface() {
	int userInput = -1;
	while (userInput != 2) {
		std::cout << "Please choose an option: (1,2,3...)" << std::endl;
		std::cout << "1. Register" << std::endl;
		std::cout << "2. Exit" << std::endl;
		std::cin >> userInput;
		switch (userInput) {
			case 1: {
				registerUser();
			}
		}		
	}
}

std::string Interface::cleanName(std::string name) {
	//make sure first name is uppercase, everything else is lowercase
	for (int i = 0; i < name.length(); i++) {
		name[i] = tolower(name[i]);
	}
	name[0] = toupper(name[0]);
	std::cout << "cleaned name " << name << std::endl;
	return name;
}/*
	routine for extracting first name from user input
	return false until first name is verified and cleaned
*/

bool Interface::processFirstName() {
	std::cout << "Please enter valid first name" << std::endl;
	std::string firstName;
	std::cin >> firstName;
	bool confirmed = confirmName(firstName, FIRST);
	return confirmed;

}
bool Interface::processLastName() {
	std::cout << "Please enter valid last name" << std::endl;
	std::string lastName;
	std::cin >> lastName;
	bool confirmed = confirmName(lastName, !FIRST);
	return confirmed;
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
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//confirm the first name is correct
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
			std::cout << "invalid entry please try again..." << std::endl;
		}
	}
}

/*
	make sure name is only letters
	input:
	string name
*/

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
	std::cout << "Error, name can only contain alphabetic characters" << std::endl;
	return false;


}
void Interface::checkdb() {
	userdb->dbhealthcheck();
}
void Interface::checkAccount() {
	account->printFullName();
}