/*
	Programmer: Jerusalem Moore
	Date: 7/5/2022
	Description:
		Class for providing error messages to users depending on given inputs
		ErrMessenger outputs different errors depending on given codes

	Note: I created this class for error messenging to user because simply implementing
	with a cpp and h file was causing crtdump to catch leaks. 
	Class is allocated and deleted in the Interface class.
*/
#pragma once
#include <windows.h>
#include <string>
#include <iostream>
/*
	codes to pass to ErrMessenger, error message depends on these codes
	current types:
		errorCode - codes for general errors
		userErrorCode - codes for errors related to a provided user
*/

enum errorCode {
	FIVECHAR,
	INVALIDENTRY,
	NONALPHA

};
enum userErrorCode {
	USERNAMEEXISTS
};
class ErrMessenger {

private:
	//handle for controlling text color for error messages
	HANDLE 	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const std::string fiveChar = "Error, entry should be at least 5 characters";
	const std::string invalidEntry = "Invalid entry please try again...";
	const std::string nonAlpha = "Error, name can only contain alphabetic characters";
	
public:


	
	void printError(errorCode code);
	void printUserError(userErrorCode code, std::string username);

};


