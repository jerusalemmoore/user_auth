#define WIN32_LEAN_AND_MEAN 

//th

#include "errmessenger.h"
#define WHITE 15
#define RED 12
/*
	function for printing general errors in Interface
*/
void ErrMessenger::printError(errorCode code)
{
	std::string error;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, RED);
	switch (code) {
	case FIVECHAR:
		error = fiveChar;
		break;
	case INVALIDENTRY:
		error = invalidEntry;
		break;
	case NONALPHA:
		error = nonAlpha;
		break;
	case PASSWORDLENGTH:
		error = passwordLength;
		break;
	case NOUPPERCASE:
		error = noUppercase;
		break;
	case NOLOWERCASE:
		error = noLowercase;
		break;
	case NOSPECIAL:
		error = noSymbol;
		break;
	case NONUMBER:
		error = noNumber;
		break;
	case LOGINFAILED:
		error = loginFailed;
		break;
	case PASSWORDMATCH:
		error = passwordMatch;
		break;
	default:
		std::cout << "INVALID INTERFACE ERROR CODE: " << code << std::endl;
		SetConsoleTextAttribute(hConsole, WHITE);
		exit(EXIT_FAILURE);
		break;

	}
	std::cout << error << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
}
/*
	function for printing errors related to user
*/
void ErrMessenger::printUserError(userErrorCode code, std::string username) {
	std::string error; 
	if (username.empty()) {
		std::cout << "HOLD ON, I THINK SOMETHING WENT WRONG!!!" << std::endl;
		std::cout << "USERNAME SHOULD BE INITIALIZED WITH VALUE" << std::endl;
		exit(EXIT_FAILURE);
	}
	SetConsoleTextAttribute(hConsole, RED);
	switch (code) {
	case USERNAMEEXISTS:
		error = "Username \"" + username + "\" already exists.";
		break;
	default:
		std::cout << "INVALID ERROR CODE: " << code << std::endl;
		break;
	
	}
	std::cout << error << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);

}
