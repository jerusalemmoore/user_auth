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
#define WIN32_LEAN_AND_MEAN 
#include "errmessenger.h"
#define WHITE 15
#define RED 12
/*
	function for printing general errors in Interface
*/
void ErrMessenger::printError(ErrorCode code)
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
	case INCORRECTPASSWORD:
		error = incorrectPassword;
		break;
	case PASSEQNEWPASS:
		error = passEqNewPass;
		break;
	default:
		std::cout << "INVALID INTERFACE ERROR CODE: " << code << std::endl;
		std::cout << "Hint: You might've forgotten to add break after assigning"
		" error string on given error code" << std::endl;
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
void ErrMessenger::printUserError(UserErrorCode code, std::string username) {
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
