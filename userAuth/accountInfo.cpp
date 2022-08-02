/*
	Programmer: Jerusalem Moore
	Class: AccountInfo
	Date: 6/28/2022
	Description:
		Class meant to hold individual account information
		Information will be used to store and query a db
		Class currently has an interface builtin this might need to be implemented as it's own class(Registration System)

*/
#include "accountInfo.h"
#define _CRTDBG_MAP_ALLOC

/*
	Format first/last name
	First char uppercase, all other lowercase
	input:
	string name: name to clean
	output:
	cleaned string name
*/
AccountInfo::AccountInfo() {
	firstName = "";
	lastName = "";
	username = "";

}
AccountInfo::~AccountInfo() {

}
/*
	clear all data inside accountInfo
	used for clearing info when current user logs out 
*/
void AccountInfo::clean() {
	this->firstName = "";
	this->lastName = "";
	this->username = "";
}
/*
	check if all data in AccountInfo is empty
*/
bool AccountInfo::isClear() {
	if ((firstName.empty() && lastName.empty() && username.empty())) {
		return true;
	}
	return false;
}


/*
	set accountInfo firstname private member to firstname val
	input:
	string to assign to private member
*/
void AccountInfo::setFirstName(std::string firstname) {
	this->firstName = firstname;
}
/*
	set accountInfo lastname private member to lastname val
	input:
	string to assign to private member
*/

void AccountInfo::setLastName(std::string lastname) {
	this->lastName = lastname;
}

void AccountInfo::setUsername(std::string username) {
	this->username = username;
}
std::string AccountInfo::getUsername() {
	return username;
}
std::string AccountInfo::getFirstName() {
	return firstName;
}


std::string AccountInfo::getLastName() {
	return lastName;
}


void AccountInfo::printFullName() {
	std::cout << "Account info" << std::endl;
	std::cout << "First Name: " << getFirstName() << std::endl;
	std::cout << "Last Name: " << getLastName() << std::endl;
}
void AccountInfo::printData() {
	std::cout << "Account info" << std::endl;
	std::cout << "First Name: " << getFirstName() << std::endl;
	std::cout << "Last Name: " << getLastName() << std::endl;
	std::cout << "Username: " << getUsername() << std::endl;
}
