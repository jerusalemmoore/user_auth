#include <regex>
#include "accountInfo.h"
#define FIRST true //flag for processing string as first name in functions

//Format first/last name 
//First char uppercase, all other lowercase
//input:
//string name: name to clean
//output:
//cleaned string name 
std::string AccountInfo::cleanName(std::string name) {
	//make sure first name is uppercase, everything else is lowercase
	for (int i = 0; i < name.length(); i++) {
		name[i] = tolower(name[i]);
	}
	name[0] = toupper(name[0]);
	std::cout << "cleaned name " << name << std::endl;
	return name;
}


//make sure name is only letters
//input:
//string name
bool AccountInfo::isNameAlpha(std::string name, bool first) {
	//is name alphabetical, if not return false 
	if (std::regex_match(name, std::regex("^[A-Za-z]+$"))) {
		std::cout << "all good" << std::endl;
		//std::cout << "Continuing" << std::endl;
		name = cleanName(name);
		if (first) {
			setFirstName(name);
		}
		else if (!first) {
			setLastName(name);
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


//confirm first or last name depending on type
//name: name to confirm
//type: FIRST or LAST const for first or last name 
bool AccountInfo::confirmName(std::string name, bool isFirst) {
	//just get the first string of input to evaluate as the first name 
//this line clears the buffer so the remaining inputs don't register for the following confirmation
//choice made by user
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//confirm the first name is correct
	//when confirmed clean it, make sure first char is uppercase and the following are lowercase
	while (1) {
		std::cout << "Please confirm " << ( isFirst ? "first" : "last") << "name is correct(y / n) : " << name << std::endl;
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


//routine for extracting first name from user input
//return false until first name is verified and cleaned
bool AccountInfo::getFirstName() {
	std::cout << "Please enter valid first name" << std::endl;
	std::string firstName;
	std::cin >> firstName;
	bool confirmed = confirmName(firstName, FIRST);
	return confirmed;

}


//routine for extracting last name from user input
//return false until first name is verified and cleaned 
bool AccountInfo::getLastName() {
	std::cout << "Please enter valid last name" << std::endl;
	std::string lastName;
	std::cin >> lastName;
	bool confirmed = confirmName(lastName, !FIRST);
	return confirmed;
}


//set accountInfo firstname private member to firstname val
//input:
//string to assign to private member
void AccountInfo::setFirstName(std::string firstname) {
	firstName = firstname;
}


//set accountInfo lastname private member to lastname val
//input:
//string to assign to private member
void AccountInfo::setLastName(std::string lastname) {
	lastName = lastname;
}

//run firstNameConfirmed until valid name is produced
//run lastNameConfirmed until valid name is produced
void AccountInfo::runInterface() {
	std::cout << "Please enter requested credentials" << std::endl;
	bool firstNameConfirmed;
	do {
		firstNameConfirmed = getFirstName();
	} while (!firstNameConfirmed);
	bool lastNameConfirmed;
	do {
		lastNameConfirmed = getLastName();
	} while (!lastNameConfirmed);
}


std::string AccountInfo::getRegFirstName() {
	return firstName;
}


std::string AccountInfo::getRegLastName() {
	return lastName;
}


void AccountInfo::printFullName() {
	std::cout << "Account info" << std::endl;
	std::cout << "First Name: " << getRegFirstName() << std::endl;
	std::cout << "Last Name: " << getRegLastName() << std::endl;
}