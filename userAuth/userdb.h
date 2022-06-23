/*
	Programmer: Jerusalem Moore
	Class: UserDB
	Description:
		Class for utilizing a sqlite3 db and making queries for user authentication
		and account management
*/
#include "sqlite3.h"
#include <stdio.h>
#include <string>
#include <iostream> 
class UserDB{
public:
	//UserDB();
	static int callback(void* NotUsed, int argc, char** argv, char** azColName);
	std::string getid();
	void sqlEx(std::string statement);
	void findUsername(std::string username);
	void dbhealthcheck();
	void dbtest1();
	void updateData(std::string data);
private:
	sqlite3* startDB(std::string dbname);
	sqlite3* userdb;
	void* data;
	std::string dbname = "userdb";
	

};