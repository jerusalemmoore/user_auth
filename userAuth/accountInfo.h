/*
	Programmer: Jerusalem Moore
	Class: AccountInfo
	Description:
		Class used for storing account info, the info stored here will be used to access
		db information on a specific user
*/
#pragma once
#include <stdio.h>
#include <string>
#include <iostream> 
class AccountInfo {
public:
	AccountInfo();
	~AccountInfo();
	
	
	//get confirmed first and last name
	std::string getFirstName();
	std::string getLastName();
	void setFirstName(std::string firstName);
	void setLastName(std::string lastName);
	void printFullName();
private:
	std::string firstName;
	std::string lastName;

};
