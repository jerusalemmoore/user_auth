/*
	Programmer: Jerusalem Moore
	Class: Interface
	Description:
		Class used for user interacton. Traverse different options, store to db, query db, parsing input
		all happen here.
*/
#pragma once
#include "interface.h"
//#include "errormsg.cpp"
#define FIRST true //flag for processing string as first name in functions
#define LOGOUT 2
#define WHITE 15
#define RED 12



void Interface::printError(std::string errMsg) {
	SetConsoleTextAttribute(hConsole, RED);
	std::cout << errMsg << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
}
void Interface::printError(Username username) {
	SetConsoleTextAttribute(hConsole, RED);
	std::cout << "Username \"" << username.content << "\" already exists." << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
}
/*
	initialize account info class for holding logged in user info
	access userdb sqlite3 file
*/
Interface::Interface() {
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	account = new AccountInfo();
	userdb = new UserDB("userdb");
}

/*
	clean account info
	clean sqlite3 file ptr
*/
Interface::~Interface() {
	delete account;
	delete userdb;

}


//make sure given input follows username rules
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
			printError(INVALIDENTRY);
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	//rules for username
	//length of 5+
	if (input.length() < 5) {
		printError(FIVECHAR);
		return false;
	}
	return true;
}

/*
	check if username exists in usertable
*/
bool Interface::confirmUsername(Username username) {
	bool usernameConfirmed = userdb->usernameExists(username);
	if (!usernameConfirmed) {
		printError(username);
		//std::cout << "Username \"" << username.content << "\" already exists." << std::endl;
	}
	return usernameConfirmed;
}

/*
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
	get given username input and validate until valid one is produced
*/
bool Interface::processUsername() {
	std::string newUsername;
	std::cout << "Please enter valid username" << std::endl;
	std::cout << "/////////////////////////////" << std::endl;
	std::cout << "Rules:" << std::endl;
	std::cout << "\t1. only one word" << std::endl;
	std::cout << "\t2. must be unique" << std::endl;
	std::cout << "\t3. must be at least 5 characters" << std::endl;
	std::cout << "//////////////////////////////" << std::endl;
	std::cin >> newUsername;
	Username username;
	username.content = newUsername;

	bool valid = usernameValid(username.content);
	if (!valid) {
		return valid;
	}
	bool confirmed = confirmUsername(username);
	if (confirmed) {
		std::cout << "username confirmed" << std::endl;
		std::cout << username.content << std::endl;
		account->setUsername(username.content);
	}
	return confirmed;
	//return true;
}
/*
	run firstNameConfirmed until valid name is produced
	run lastNameConfirmed until valid name is produced
*/
void Interface::registerUser() {
	std::cout << "Please enter requested credentials" << std::endl;
	while (!processFirstName());
	while (!processLastName());
	while (!processUsername());
	std::cout << "Username to add to users table" << std::endl;
	account->printData();
	createAccount(account);
	return;

}

void Interface::createAccount(AccountInfo* account) {
	userdb->insertUser(account->getFirstName(), account->getLastName(), account->getUsername());
	std::cout << "User " << account->getUsername() << " registered" << std::endl;
	std::cout << "Navigating to user home..." << std::endl;
	Sleep(3000);
	home(account);
}

void Interface::login() {

}
void Interface::home(AccountInfo* account) {
	system("CLS");
	int input = -1;
	while (input != LOGOUT) {
		std::cout << "Hello " << account->getFirstName() << " " << account->getLastName() << std::endl;
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
			break;
		}
		}
	}
}

void Interface::runInterface() {
	int userInput = -1;
	do {
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
			//login();
			break;
		}
		case 3: {
			return;
		}
		default: {
			//SetConsoleTextAttribute(hConsole, RED);
			printError(INVALIDENTRY);
			//SetConsoleTextAttribute(hConsole, WHITE);
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
		}

	} while (userInput != 2);
}

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
	printError(NONALPHA);
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
			printError(INVALIDENTRY);
		}
	}
}

/*
	make sure name is only letters
	input:
	string name
*/
void Interface::checkdb() {
	userdb->dbhealthcheck();
}

//print account information
void Interface::checkAccount() {
	account->printFullName();
}
void Interface::dbStat() {

}