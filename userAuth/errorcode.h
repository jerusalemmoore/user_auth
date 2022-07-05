//error code is causing leaks and i need to sort out why
#pragma once
#include <windows.h>
#include <string>

#include <iostream>
class Error {

private:
	HANDLE 	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	
public:
	enum errorCode {
		FIVECHAR,
		INVALIDENTRY,
		NONALPHA

	};
	enum userErrorCode {
		USERNAMEEXISTS
	};

	const std::string fiveChar = "Error, entry should be at least 5 characters";
	const std::string invalidEntry = "Invalid entry please try again...";
	const std::string nonAlpha = "Error, name can only contain alphabetic characters";
	void printError(errorCode code);
	void printUserError(userErrorCode code, std::string username);

};


