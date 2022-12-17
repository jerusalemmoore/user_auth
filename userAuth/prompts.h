#pragma once
#include <iostream>
#include "accountInfo.h"
#include "enums.h"
class Prompter {
public:
	Prompter();
	~Prompter();
	void mainMenuPrompt();
	void userMenuPrompt();
	void userEditPrompt();
	void passwordPrompt(promptRequest request);
	void usernamePrompt(promptRequest request);
	void setAccount(AccountInfo* account);
	void loginBanner();
	void clean();
	void editFirstnamePrompt();
	void editLastnamePrompt();
	void editUsernamePrompt();
	
private:
	
	AccountInfo* account;
};
