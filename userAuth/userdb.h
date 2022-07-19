/*
	Programmer: Jerusalem Moore
	Class: UserDB
	Date: 6/28/2022
	Description:
		Class for utilizing a sqlite3 db and making queries for user authentication
		and account management
*/
#include "sqlite3.h"
#include "queryStructs.h"
#include "passwordprocessor.h"
#include "accountInfo.h"
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream> 
#include <vector>


class UserDB{
public:
	UserDB(std::string dbname);
	~UserDB();
	
	
	void dbhealthcheck();
	void dbtest1();
	void updateData(std::string data);
	void insertUser(std::string firstName, std::string lastName, std::string username,std::string password);
	bool validateAccount(Username username, std::string password, AccountInfo* account);
	bool usernameExists(Username username);

private:
	sqlite3_stmt* sqlPrep(sqlite3* db, std::string stmt);
	bool sqlStep(sqlite3* db, sqlite3_stmt* stmt);
	void initTable(int fresh = 0);
	//func for intializing db when making queries
	sqlite3* startDB(std::string dbname);
	std::string select(Username username);
	sqlite3* userdb;
	PasswordProcessor* passProcessor;
	std::string getid();
	void sqlEx(std::string statement);
	static int callback(void* NotUsed, int argc, char** argv, char** azColName);
	std::string dbname;
	std::string tblname;
	//string for userdb main table
	static const std::string USR;

};