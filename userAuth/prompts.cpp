#include "prompts.h"
#include "interface.h"





Prompter::Prompter() {
	this->account = NULL;
}
Prompter::~Prompter() {

}
void Prompter::mainMenuPrompt() {
	std::cout << "----------------------------------------------------" << std::endl;
	std::cout << "User Authentication System" << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;
	std::cout << "Please choose an option: (1,2,3...)" << std::endl;
	std::cout << "1. Register" << std::endl;
	std::cout << "2. Login" << std::endl;
	std::cout << "3. Exit" << std::endl;
}
void Prompter::userMenuPrompt() {
	std::cout << "----------------------------------------------------" << std::endl;
	std::cout << "Hello " << account->getFirstName() << " " << account->getLastName() << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;
	std::cout << "Please choose an option(1, 2, 3...)" << std::endl;
	std::cout << "1. Edit account" << std::endl;
	std::cout << "2. Logout" << std::endl;
}
void Prompter::userEditPrompt() {
	
	std::cout << "----------------------------------------------------" << std::endl;
	std::cout << "Choose information you'd like to edit" << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;
	std::cout << "1. Edit Firstname" << std::endl;
	std::cout << "2. Edit Lastname" << std::endl;
	std::cout << "3. Edit Username" << std::endl;
	std::cout << "4. Change Password" << std::endl;
	std::cout << "5. Remove Account" << std::endl;
	std::cout << "6. Go Back" << std::endl;
}
void Prompter::passwordPrompt(promptRequest request) {
	switch (request) {
	case INITIAL: {
		std::cout << "Please enter valid password\n"
			"/////////////////////////////\n"
			"Rules:\n"
			"\t1. must have length of 8 characters\n"
			"\t2. must have both uppercase and lowercase characters\n"
			"\t3. must include numbers (1,2,3...)\n"
			"\t4. must include a special symbol (!,@,#...)\n"
			"/////////////////////////////" << std::endl;
		break;

		}	
	case CONFIRM: {
		std::cout << "Please reenter password" << std::endl;
		break;
	}
	case SIMPLE: {
		std::cout << "Password: " << std::endl;
		break;
	}
	default:
		std::cout << "ERROR, UNDEFINED promptRequest enum" << std::endl;
		break;
	}
		
	

	
}
void Prompter::usernamePrompt(promptRequest request) {
	switch (request) {
	case INITIAL: {
		std::cout << "Please enter valid username\n" 
			"/////////////////////////////\n"
			"Rules:\n"
			"\t1. only one word\n"
			"\t2. must be unique\n"
			"\t3. must be at least 5 characters\n"
			"//////////////////////////////\n" << std::endl;
		break;

	}
	case CONFIRM: {
		std::cout << "Please reenter username" << std::endl;
		break;
	}
	case SIMPLE: {
		std::cout << "Username: " << std::endl;
		break;
	}
	default:
		std::cout << "ERROR, UNDEFINED promptRequest enum" << std::endl;
		break;
	}

}
void Prompter::loginBanner() {
	std::cout << "----------------------------------------------------\n"
	"Please Enter Requested Login Credentials\n" 
	"----------------------------------------------------" << std::endl;
}
//void Prompter::inputPrompt(promptRequest request){
//}
void Prompter::editLastnamePrompt() {

}
void Prompter::editFirstnamePrompt() {

}
void Prompter::editUsernamePrompt() {

}
void Prompter::setAccount(AccountInfo* account) {
	this->account = account;
}
void Prompter::clean() {
	this->account = NULL;
}