/*
	Programmer: Jerusalem Moore
	Class: AccountInfo
	Description:
		Class used for storing account info, the info stored here will be used to access
		db information on a specific user

	Info to store into AccountInfo:
	First Name
	Last Name
	Username(unique)
	Password

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
	std::string getUsername();
	std::string getFirstName();
	std::string getLastName();
	void setFirstName(std::string firstName);
	void setLastName(std::string lastName);
	void setUsername(std::string username);
	void printFullName();
	void printData();
private:
	std::string firstName;
	std::string lastName;
	std::string username;

};
