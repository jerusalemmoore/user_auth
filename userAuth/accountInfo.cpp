/*
	Programmer: Jerusalem Moore
	Class: AccountInfo
	Description:
		Class meant to hold individual account information
		Information will be used to store and query a db
		Class currently has an interface builtin this might need to be implemented as it's own class(Registration System)

*/
#include "accountInfo.h"
#include "interface.cpp"
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

}
AccountInfo::~AccountInfo() {

}



/*
	make sure name is only letters
	input:
	string name
*/



/*
	confirm first or last name depending on type
	name: name to confirm
	type: FIRST or LAST const for first or last name
*/






/*
	set accountInfo firstname private member to firstname val
	input:
	string to assign to private member
*/
void AccountInfo::setFirstName(std::string firstname) {
	firstName = firstname;
}
/*
	set accountInfo lastname private member to lastname val
	input:
	string to assign to private member
*/

void AccountInfo::setLastName(std::string lastname) {
	lastName = lastname;
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
