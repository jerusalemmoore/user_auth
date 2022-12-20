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
#define BACK "back"
/// <summary>
/// 
/// </summary>
Interface::Interface() {
	account = new AccountInfo();
	userdb = new UserDB("userdb");
	messenger = new ErrMessenger();
	prompter = new Prompter();
}

/// <summary>
/// 
/// </summary>
Interface::~Interface() {
	delete account;
	delete userdb;
	delete messenger;
	delete prompter;
}

/// <summary>
/// 
/// </summary>
void Interface::runInterface() {
	std::string userInput = "";
	do {
		if (!account->isClear()) {
			std::cout << "Error, user info should be clear if on this menu...\n" << std::endl;
			exit(EXIT_FAILURE);
		}

		prompter->mainMenuPrompt();
		std::cin >> userInput;
		if (!validateMenuChoice(userInput)) {
			userInput = "-1";
		}
		
		
		switch (stoi(userInput)) {
		case 1: {
			registerUser();
			break;
		}
		case 2: {
			login();
			break;
		}
		case 3: {
			std::cout << "hi";
			return;
		}
		default: {
			messenger->printError(INVALIDENTRY);
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
		}

	} while (1);
}
/// <summary>
/// 
/// </summary>
void Interface::registerUser() {
	system("CLS");
	prompter->registrationBanner();
	std::string password;
	if (!firstnameLoop())
		return;
	if (!lastnameLoop())
		return;
	if (!usernameLoop())
		return;
	if (!passwordLoop(&password))
		return;
	std::cout << "registerUser()::Assigning password: " << password << std::endl;
	std::cout << "registerUser()::Username to add to users table" << std::endl;
	account->printData();
	createAccount(account, password);
	return;

}
/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool Interface::firstnameLoop() {
	std::string firstname;
	do {
		std::cout << "Please enter valid first name" << std::endl;
		//std::string firstName;
		std::cin >> firstname;
		if (firstname == BACK) {
			account->clean();
			return false;
		}
	} while (!processFirstName(firstname));
	account->setFirstName(cleanName(firstname));
	return true;
}
/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool Interface::lastnameLoop() {
	std::string lastname;
	do {
		std::cout << "Please enter valid lastname" << std::endl;
		std::cin >> lastname;
		if (lastname == BACK) {
			account->clean();
			return false;
		}
	} while (!processLastName(lastname));
	account->setLastName(cleanName(lastname));
	return true;
}
/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool Interface::usernameLoop() {
	std::string username;
	do {
		prompter->usernamePrompt(INITIAL);
		std::cin >> username;
		if (username == BACK) {
			account->clean();
			return false;
		}
	} while (!processUsername(username));
	account->setUsername(username);
	return true;

}
/// <summary>
/// 
/// </summary>
/// <param name="passwordBuffer"></param>
/// <returns></returns>
bool Interface::passwordLoop(std::string* passwordBuffer) {
	bool confirmed = false;
	std::string password;
	do {
		prompter->passwordPrompt(INITIAL);
		password = getPassword();
		if (password == BACK) {
			account->clean();
			return false;
		}
		confirmed = passwordConfirmed(password);
	} while (!confirmed);
	*passwordBuffer = password;
	return true;
}
/// <summary>
/// 
/// </summary>
/// <param name="firstName"></param>
/// <returns></returns>
bool Interface::processFirstName(std::string firstName) {
	//just get the first string of input to evaluate as the first name 
		//this line clears the buffer so the remaining inputs don't register for the following confirmation
		//choice made by user
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	//confirm the first name is correct
	//when confirmed clean it, make sure first char is uppercase and the following are lowercase
	while (1) {
		std::cout << "Please confirm firstname is correct(y / n) : " << firstName << std::endl;
		std::string choice;
		std::cin >> choice;
		if (choice == "y") {
			//user confirmed, make sure name is alphabetical
			return validateName(firstName);
		}
		else if (choice == "n") {
			std::cout << "Please re-enter firstname" << std::endl;
			return false;
		}
		else {
			messenger->printError(INVALIDENTRY);
		}
	}
}
/// <summary>
/// 
/// </summary>
/// <param name="lastName"></param>
/// <returns></returns>
bool Interface::processLastName(std::string lastName) {
	//just get the first string of input to evaluate as the first name 
	//this line clears the buffer so the remaining inputs don't register for the following confirmation
	//choice made by user
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	//confirm the first name is correct
	//when confirmed clean it, make sure first char is uppercase and the following are lowercase
	while (1) {
		std::cout << "Please confirm lastname is correct(y / n) : " << lastName << std::endl;
		std::string choice;
		std::cin >> choice;
		if (choice == "y") {
			//user confirmed, make sure name is alphabetical
			return validateName(lastName);
		}
		else if (choice == "n") {
			std::cout << "Please re-enter lastname" << std::endl;
			return false;
		}
		else {
			messenger->printError(INVALIDENTRY);
		}
	}
}
/// <summary>
/// 
/// </summary>
/// <param name="username"></param>
/// <returns></returns>
bool Interface::processUsername(std::string username) {
	if (usernameValid(username)) {
		if (!userExists(username)) {
			std::cout << "username confirmed" << std::endl;
			std::cout << username << std::endl;
			return true;
		}
	}
	return false;
	//return true;
}

/// <summary>
/// 
/// </summary>
/// <param name="username"></param>
/// <returns></returns>
bool Interface::userExists(std::string username) {
	if (userdb->usernameExists(username)) {
		messenger->printUserError(USERNAMEEXISTS, username);
		return true;
	}
	return false;
}

/// <summary>
/// 
/// </summary>
/// <param name="input"></param>
/// <returns></returns>
bool Interface::usernameValid(std::string input) {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::string choice;
	while (choice != "y") {
		std::cout << "Please confirm username is correct(y / n) : " << input << std::endl;
		std::cout << "input string: " << input << std::endl;
		std::cin >> choice;
		if (choice == "n") {
			//std::cout << "Please re-enter username" << std::endl;
			prompter->usernamePrompt(CONFIRM);

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
/// <summary>
/// 
/// </summary>
/// <returns></returns>
std::string Interface::getPassword() {
	//prompter->passwordPrompt(request);
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
	//std::cout << "console mode: " << con_mode << std::endl;
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
	SetConsoleMode(hIn, con_mode & (ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT));
	if (GetConsoleMode(hIn, &con_mode) == 0) {
		std::cout << "get console error: " << GetLastError() << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "\n";
	//std::cout << "console mode: " << con_mode << std::endl;
	return input;
}
/// <summary>
/// 
/// </summary>
/// <param name="password"></param>
/// <returns></returns>
bool Interface::passwordConfirmed(std::string password) {
	//std::string prompt = "Please reenter password";
	prompter->passwordPrompt(CONFIRM);
	std::string input = getPassword();
	//std::cout << "password: " << password << std::endl;
	//std::cout << "input: " << input << std::endl;
	if (input == password) {
		if (validatePassword(password)) {
			return true;
		}
		return false;
	}
	messenger->printError(PASSWORDMATCH);
	return false;
}
/// <summary>
///	check if password passes rules
///	1. must have length of 8 characters
///	2. must have both uppercase and lowercase characters
///	3. must include numbers(1, 2, 3...)
///	4. must include a special symbol(!, @, #...)
/// </summary>
/// <param name="password"></param>
/// <returns></returns>
bool Interface::validatePassword(std::string password) {
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
/// <summary>
/// 
/// </summary>
/// <param name="account"></param>
/// <param name="password"></param>
void Interface::createAccount(AccountInfo* account, std::string password) {
	userdb->insertUser(account->getFirstName(), account->getLastName(), account->getUsername(), password);
	std::cout << "User " << account->getUsername() << " registered" << std::endl;
	std::cout << "Navigating to user home..." << std::endl;
	Sleep(3000);
	home(account);
}
/// <summary>
/// 
/// </summary>
/// <param name="account"></param>
void Interface::home(AccountInfo* account) {
	prompter->setAccount(account);
	//system("CLS");
	if (account == NULL) {
		std::cout << "home: error, account was NULL" << std::endl;
		exit(EXIT_FAILURE);
	}
	int input = -1;
	while (input != LOGOUT) {
		if (account->isClear()) {
			//std::cout << "hielij;adfkja;fdkj;f";
			return;
		}
		prompter->userMenuPrompt();
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
			prompter->clean();
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

/// <summary>
/// 
/// </summary>
void Interface::login() {
	std::string input;
	std::string username;
	std::string password;
	bool passwordSuccess;
	bool passwordConfirmed;
	do {
		prompter->loginBanner();
		prompter->usernamePrompt(SIMPLE);
		std::cin >> username;
		if (username == BACK) {
			account->clean();
			return;
		}
		//username.content = input;
		//std::cout << std::endl;
		//std::string prompt = "Password: ";
		prompter->passwordPrompt(SIMPLE);
		password = getPassword();
		std::cout << password;
		if (password == BACK) {
			account->clean();
			return;
		}
	} while (!tryPassword(username, password, LOGINFAILED));
	std::cout << "Logging in..." << std::endl;
	Sleep(3000);
	home(account);
}
/// <summary>
/// 
/// </summary>
/// <param name="username"></param>
/// <param name="password"></param>
/// <param name="error"></param>
/// <returns></returns>
bool Interface::tryPassword(std::string username, std::string password, ErrorCode error ) {
	if (userdb->validateAccount(username, password, account)) {
		//print account info for verification
		account->printData();
		return true;
	}
	std::cout << userdb->validateAccount(username, password, account);
	messenger->printError(error);
	return false;
}

/// <summary>
/// 
/// </summary>
void Interface::editFirstname() {
	std::string newFirstname;
	do {
		//std::cout << "----------------------------------------------------" << std::endl;
		//std::cout << "Edit Firstname" << std::endl;
		//std::cout << "Current: " << account->getFirstName() << std::endl;
		//std::cout << "----------------------------------------------------" << std::endl;
		//std::cout << "New Firstname: ";
		prompter->editFirstnamePrompt(account);
		std::cin >> newFirstname;
		if (newFirstname == BACK) {
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
/// <summary>
/// 
/// </summary>
void Interface::editLastname() {
	std::string newLastname;
	do {
		prompter->editLastnamePrompt(account);
		std::cin >> newLastname;
		if (newLastname == BACK) {
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
/// <summary>
/// 
/// </summary>
void Interface::editUsername() {
	std::string newUsername;
	do {
	/*	std::cout << "----------------------------------------------------" << std::endl;
		std::cout << "Edit Username" << std::endl;
		std::cout << "Current: " << account->getUsername() << std::endl;
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << "New Username: ";*/
		prompter->editUsernamePrompt(account);
		std::cin >> newUsername;
		if (newUsername == BACK) {
			return;
		}
	} while (!processUsername(newUsername));
	std::cout << "editUsername()::Changing current username account " << account->getUsername()
		<< " to " << newUsername << std::endl;
	userdb->changeUsername(account, newUsername);
	/*if () {
		std::cout << "Changing current username account " << account->getUsername()
			<< " to " << input << std::endl;
		userdb->changeUsername(account, input);
	}*/
}
/// <summary>
/// 
/// </summary>
void Interface::editPassword() {
	/*std::cout << "----------------------------------------------------" << std::endl;
	std::cout << "Edit Password" << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;*/
	//std::string prompt = "Please enter original password:";
	prompter->editPasswordPrompt();
	std::string password = getPassword();
	std::string newPassword;
	if (tryPassword(account->getUsername(), password, INCORRECTPASSWORD)) {
		//if this returned false it means the action was aborted
		if (!passwordLoop(&newPassword))
			return;
		if (password == newPassword) {
			messenger->printError(PASSEQNEWPASS);
			return;
		}
		userdb->changePassword(account, newPassword);
	}
	
}
/// <summary>
/// 
/// </summary>
void Interface::editAccount() {
	int input = -1;
	while (input != 5) {
		/*std::cout << "----------------------------------------------------" << std::endl;
		std::cout << "Choose information you'd like to edit" << std::endl;
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << "1. Edit Firstname" << std::endl;
		std::cout << "2. Edit Lastname" << std::endl;
		std::cout << "3. Edit Username" << std::endl;
		std::cout << "4. Change Password" << std::endl;
		std::cout << "5. Go Back" << std::endl;*/
		prompter->userEditPrompt();
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
			editPassword();
			break;
		case 5: 
			removeAccount();
		case 6:
			return;
			//break;
		default:
			messenger->printError(INVALIDENTRY);
			break;
		}
	}
	
}
/// <summary>
/// 
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
std::string Interface::cleanName(std::string name) {
	//make sure first name is uppercase, everything else is lowercase
	for (int i = 0; i < name.length(); i++) {
		name[i] = tolower(name[i]);
	}
	name[0] = toupper(name[0]);
	std::cout << "cleanName()::cleaned name " << name << std::endl;
	return name;
}
//check if name is alphabetical, if yes assign first/last name to accountInfo member
bool Interface::validateName(std::string name) {
	//is name alphabetical, if not return false 
	if (std::regex_match(name, std::regex("^[A-Za-z]+$"))) {
		std::cout << "validateName()::all good" << std::endl;
		return true;
	}
	messenger->printError(NONALPHA);
	return false;


}
/// <summary>
/// 
/// </summary>
/// <param name="input"></param>
/// <returns></returns>
bool Interface::validateMenuChoice(std::string input) {
	if (std::regex_match(input, std::regex("^[0-9]+$"))) {
		return true;
	}
	return false;
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
void Interface::removeAccount() {
	prompter->passwordPrompt(SIMPLE);
	std::string password = getPassword();

	if (tryPassword(account->getUsername(), password, INCORRECTPASSWORD)) {
		std::cout << account->getUsername();
		userdb->removeAccount(account->getUsername());
		account->clean();
		return;
	}
	std::cout << "Account Removal Error" << std::endl;
	
}