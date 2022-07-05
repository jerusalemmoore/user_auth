#define WIN32_LEAN_AND_MEAN 

//th

#include "errorcode.h"
#define WHITE 15
#define RED 12
/*
	function for printing general users
*/
void Error::printError(errorCode code)
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
	default:
		std::cout << "INVALID ERROR CODE: " << code << std::endl;
		SetConsoleTextAttribute(hConsole, WHITE);
		exit(EXIT_FAILURE);
		break;

	}
	std::cout << error << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
}
/*
	function for printing error related to user
*/
void Error::printUserError(userErrorCode code, std::string username) {
	std::string error; 

	SetConsoleTextAttribute(hConsole, RED);
	switch (code) {
	case USERNAMEEXISTS:
		if (username.empty()) {
			std::cout << "HOLD ON, I THINK SOMETHING WENT WRONG!!!" << std::endl;
			std::cout << "USERNAME SHOULD BE INITIALIZED WITH VALUE" << std::endl;
			exit(EXIT_FAILURE);
		}
		error = "Username \"" + username + "\" already exists.";
		break;

	default:
		std::cout << "INVALID ERROR CODE: " << code << std::endl;
		break;
	
	}
	std::cout << error << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);

}