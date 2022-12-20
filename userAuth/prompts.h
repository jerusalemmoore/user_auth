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
	void editPasswordPrompt();
	void registrationBanner();
	void passwordPrompt(promptRequest request);
	void usernamePrompt(promptRequest request);
	void setAccount(AccountInfo* account);
	void loginBanner();
	void clean();
	void editFirstnamePrompt(AccountInfo* account);
	void editLastnamePrompt(AccountInfo* account);
	void editUsernamePrompt(AccountInfo* account);
	
private:
	
	AccountInfo* account;
};
