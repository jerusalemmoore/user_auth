//class for extracting info and validating the input given by user
#pragma once
#include <iostream>
class AccountInfo {
public:
	std::string cleanName(std::string name);
	bool isNameAlpha(std::string firstName, bool type);
	bool confirmName(std::string name, bool type);
	//get and verify info from input
	bool getFirstName();
	bool getLastName();
	//get confirmed first and last name
	std::string getRegFirstName();
	std::string getRegLastName();
	void setFirstName(std::string firstName);
	void setLastName(std::string lastName);
	void printFullName();
	void runInterface();
private:
	std::string firstName;
	std::string lastName;

};