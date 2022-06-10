#include <regex>
#include "accountInfo.h"
#define FIRST "first"
#define LAST "last"
std::string AccountInfo::cleanName(std::string name) {
	//make sure first name is uppercase, everything else is lowercase
	for (int i = 0; i < name.length(); i++) {
		name[i] = tolower(name[i]);
	}
	name[0] = toupper(name[0]);
	std::cout << "cleaned name " << name << std::endl;
	return name;
}
bool AccountInfo::isNameAlpha(std::string name, std::string type) {
	//is name alphabetical, if not return false 
	if (std::regex_match(name, std::regex("^[A-Za-z]+$"))) {
		std::cout << "all good" << std::endl;
		//std::cout << "Continuing" << std::endl;
		name = cleanName(name);
		if (type == "first") {
			setFirstName(name);
		}
		else if (type == "last") {
			setLastName(name);
		}
		else {
			std::cout << "Error, invalid type: " << type << std::endl;
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
bool AccountInfo::confirmName(std::string name, std::string type) {
	//just get the first string of input to evaluate as the first name 
//this line clears the buffer so the remaining inputs don't register for the following confirmation
//choice made by user
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//confirm the first name is correct
	//when confirmed clean it, make sure first char is uppercase and the following are lowercase
	while (1) {
		std::cout << "Please confirm " << type << "name is correct(y / n) : " << name << std::endl;
		std::string choice;
		std::cin >> choice;
		if (choice == "y") {
			//user confirmed, make sure name is alphabetical
			return isNameAlpha(name, type);
		}
		else if (choice == "n") {
			std::cout << "Please re-enter " << type << " name" << std::endl;
			return false;
		}
		else {
			std::cout << "invalid entry please try again..." << std::endl;
		}
	}
}
//routine for extracting first name from user input
//run routine until first name is verified and cleaned
bool AccountInfo::getFirstName() {
	std::cout << "Please enter valid first name" << std::endl;
	std::string firstName;
	std::cin >> firstName;
	bool confirmed = confirmName(firstName, FIRST);
	return confirmed;

}
bool AccountInfo::getLastName() {
	std::cout << "Please enter valid last name" << std::endl;
	std::string lastName;
	std::cin >> lastName;
	bool confirmed = confirmName(lastName, LAST);
	return confirmed;
}
void AccountInfo::setFirstName(std::string firstname) {
	firstName = firstname;
}
void AccountInfo::setLastName(std::string lastname) {
	lastName = lastname;
}
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