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
#include "errhandlingapi.h"
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
	run firstNameConfirmed until valid name is produced
	run lastNameConfirmed until valid name is produced
*/
void Interface::registerUser() {
	std::string password;
	if (!firstnameLoop())
		return;
	if (!lastnameLoop())
		return;
	if (!usernameLoop())
		return;
	if (!passwordLoop(&password))
		return;
	std::cout << "Assigning password: " << password << std::endl;
	std::cout << "Username to add to users table" << std::endl;
	account->printData();
	createAccount(account, password);
	return;

}
bool Interface::firstnameLoop() {
	std::string firstname;
	do {
		std::cout << "Please enter valid first name" << std::endl;
		//std::string firstName;
		std::cin >> firstname;
		if (firstname == "back") {
			account->clean();
			return false;
		}
	} while (!processFirstName(firstname));
	account->setFirstName(cleanName(firstname));
	return true;
}
/*
	routine for retrieving a first name from user input
	return false until first name is verified and cleaned
*/
bool Interface::processFirstName(std::string firstName) {
	bool confirmed = confirmName(firstName, FIRST);
	return confirmed;

}
bool Interface::lastnameLoop() {
	std::string lastname;
	do {
		std::cout << "Please enter valid last name" << std::endl;
		std::cin >> lastname;
		if (lastname == "back") {
			account->clean();
			return false;
		}
	} while (!processLastName(lastname));
	account->setLastName(cleanName(lastname));
	return true;
}
bool Interface::processLastName(std::string lastName) {
	bool confirmed = confirmName(lastName, !FIRST);
	return confirmed;
}
bool Interface::usernameLoop() {
	std::string username;
	do {
		std::cout << "Please enter valid username" << std::endl;
		std::cout << "/////////////////////////////" << std::endl;
		std::cout << "Rules:" << std::endl;
		std::cout << "\t1. only one word" << std::endl;
		std::cout << "\t2. must be unique" << std::endl;
		std::cout << "\t3. must be at least 5 characters" << std::endl;
		std::cout << "//////////////////////////////" << std::endl;
		std::cin >> username;
		if (username == "back") {
			account->clean();
			return false;
		}
	} while (!processUsername(username));
	account->setUsername(username);
	return true;
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
		//account->setUsername(usernameStruct.content);
		return true;
	}
	messenger->printUserError(USERNAMEEXISTS, username);
	//std::cout << "unique val: " << unique << std::endl;
	return false;
	//return true;
}
/*
	check if there is account linked to given username
*/
bool Interface::checkUserExists(Username username) {
	return userdb->usernameExists(username);
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
bool Interface::passwordLoop(std::string* passwordBuffer) {
	bool confirmed = false;
	std::string password;
	do {
		std::string prompt =
			"Please enter valid password\n"
			"/////////////////////////////\n"
			"Rules:\n"
			"\t1. must have length of 8 characters\n"
			"\t2. must have both uppercase and lowercase characters\n"
			"\t3. must include numbers (1,2,3...)\n"
			"\t4. must include a special symbol (!,@,#...)\n"
			"/////////////////////////////";
		password = requestPassword(prompt);
		if (password == "back") {
			account->clean();
			return false;
		}
		confirmed = passwordConfirmed(password);
	} while (!confirmed);
	*passwordBuffer = password;
	return true;
}
std::string Interface::requestPassword(std::string prompt) {
	std::cout << prompt << std::endl;
	std::string input;
	const char BACKSPACE = 8;
	const char RETURN = 13;
	unsigned char ch = 0;
	DWORD con_mode;
	DWORD dwRead;
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	if (GetConsoleMode(hIn, &con_mode) == 0) {
		std::cout << "get console error: " << GetLastError() << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "console mode: " << con_mode << std::endl;
	if (SetConsoleMode(hIn, con_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT)) == 0) {
		std::cout << "set console error: " << GetLastError() << std::endl;

	}
	while (ReadConsoleA(hIn, &ch, 1, &dwRead, NULL) && ch != RETURN) {
		if (ch == BACKSPACE) {
			if (input.length() != 0) {
				std::cout << "\b \b";
				input.resize(input.length() - 1);

			}
		}
		else {
			input += ch;
			std::cout << '*';
		}
	}
	std::cout << std::endl;
	SetConsoleMode(hIn, con_mode & (ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT));
	if (GetConsoleMode(hIn, &con_mode) == 0) {
		std::cout << "get console error: " << GetLastError() << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "console mode: " << con_mode << std::endl;
	return input;
}
bool Interface::passwordConfirmed(std::string password) {
	std::string prompt = "Please reenter password";
	std::string input = requestPassword(prompt);
	std::cout << "password: " << password << std::endl;
	std::cout << "input: " << input << std::endl;
	if (input == password) {
		if (processPassword(password)) {
			return true;
		}
		return false;
	}
	messenger->printError(PASSWORDMATCH);
	return false;
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
	Entry point for home menu
	input:
		account with linked information

*/
void Interface::home(AccountInfo* account) {
	//system("CLS");
	if (account == NULL) {
		std::cout << "home: error, account was NULL" << std::endl;
		exit(EXIT_FAILURE);
	}
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
			editAccount();
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
	Begin login process
*/
void Interface::login() {
	std::string input;
	Username username;
	std::string password;
	bool passwordSuccess;
	bool passwordConfirmed;
	do {
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << "Please Enter Requested Login Credentials" << std::endl;
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << "Username: ";
		std::cin >> input;
		username.content = input;
		std::cout << std::endl;
		std::string prompt = "Password: ";
		password = requestPassword(prompt);
	} while (!tryPassword(username, password, LOGINFAILED));
	std::cout << "Logging in..." << std::endl;
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
bool Interface::tryPassword(Username username, std::string password, errorCode error ) {
	if (userdb->validateAccount(username, password, account)) {
		//print account info for verification
		account->printData();
		return true;
	}
	messenger->printError(error);
	return false;
}

//gather account info through login
void Interface::editFirstname() {
	std::string newFirstname;
	do {
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << "Edit Firstname" << std::endl;
		std::cout << "Current: " << account->getFirstName() << std::endl;
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << "New Firstname: ";
		std::cin >> newFirstname;
		if (newFirstname == "back") {
			return;
		}
	} while (!processFirstName(newFirstname));
	std::cout << "Changing current firstname " << account->getFirstName()
		<< " to " << newFirstname << std::endl;
	userdb->changeFirstname(account, cleanName(newFirstname));
	//if (processFirstName(input)) {
	//	std::cout << "Changing current firstname account " << account->getFirstName()
	//		<< " to " << input << std::endl;
	//	userdb->changeFirstname(account, cleanName(input));
	//}
	
}
void Interface::editLastname() {
	std::string newLastname;
	do {
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << "Edit Lastname" << std::endl;
		std::cout << "Current: " << account->getLastName() << std::endl;
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << "New Lastname: ";
		std::cin >> newLastname;
		if (newLastname == "back") {
			return;
		}
	} while (!processLastName(newLastname));
	std::cout << "Changing current lastname " << account->getLastName()
		<< " to " << newLastname << std::endl;
	userdb->changeLastname(account, cleanName(newLastname));
	/*if (processLastName(input)) {
		std::cout << "Changing current firstname account " << account->getFirstName()
			<< " to " << input << std::endl;
		userdb->changeLastname(account, cleanName(input));
	}*/
}

void Interface::editUsername() {
	std::string newUsername;
	do {
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << "Edit Username" << std::endl;
		std::cout << "Current: " << account->getUsername() << std::endl;
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << "New Username: ";
		std::cin >> newUsername;
		if (newUsername == "back") {
			return;
		}
	} while (!processUsername(newUsername));
	std::cout << "Changing current username account " << account->getUsername()
		<< " to " << newUsername << std::endl;
	userdb->changeUsername(account, newUsername);
	/*if () {
		std::cout << "Changing current username account " << account->getUsername()
			<< " to " << input << std::endl;
		userdb->changeUsername(account, input);
	}*/
}
///////////////////
///WORKING HERE
//////////////////
void Interface::changePassword() {
	std::cout << "----------------------------------------------------" << std::endl;
	std::cout << "Edit Password" << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;
	std::string prompt = "Please enter original password:";
	std::string password = requestPassword(prompt);
	Username username;
	username.content = account->getUsername();
	std::string newPassword;
	if (tryPassword(username, password, INCORRECTPASSWORD)) {
		//if this returned false it means the action was aborted
		if (!passwordLoop(&newPassword))
			return;
		if (password == newPassword) {
			//std::cout << "Error, new password, can't be current password" << std::endl;
			messenger->printError(PASSEQNEWPASS);
			return;
		}
		userdb->changePassword(account, newPassword);
	}
	
}
/*
	
	Menu for editing account info

*/
void Interface::editAccount() {
	int input = -1;
	while (input != 5) {
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << "Choose information you'd like to edit" << std::endl;
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << "1. Edit Firstname" << std::endl;
		std::cout << "2. Edit Lastname" << std::endl;
		std::cout << "3. Edit Username" << std::endl;
		std::cout << "4. Change Password" << std::endl;
		std::cout << "5. Go Back" << std::endl;
		
		std::cin >> input;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		switch (input) {
		case 1:
			editFirstname();
			break;
		case 2:
			editLastname();
			break;
		case 3:
			editUsername();
			break;
		case 4:
			changePassword();
			break;
		case 5:
			break;
		default:
			messenger->printError(INVALIDENTRY);
			break;
		}
	}
	
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