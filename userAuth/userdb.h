/*
	Programmer: Jerusalem Moore
	Class: UserDB
	Description:
		Class for utilizing a sqlite3 db and making queries for user authentication
		and account management
*/
#include "sqlite3.h"
#include "queryStructs.h"
#include <stdio.h>
#include <string>
#include <iostream> 
#include <vector>

class UserDB{
public:
	UserDB(std::string dbname);
	~UserDB();
	static int callback(void* NotUsed, int argc, char** argv, char** azColName);
	std::string getid();
	void sqlEx(std::string statement);
	bool usernameExists(Username username);
	void dbhealthcheck();
	void dbtest1();
	void updateData(std::string data);
private:
	//func for intializing db when making queries
	sqlite3* startDB(std::string dbname);
	sqlite3_stmt* select(std::vector<std::string> colNames, std::string tableName, std::string username);
	//utilities for specific col/row val
	const unsigned char* select(Firstname firstname);
	sqlite3_stmt* select(Lastname lastname);
	std::string select(Username username);
	sqlite3_stmt* select(Id);
	sqlite3* userdb;
	void* data;
	std::string dbname;
	std::string tblname;
	//string for userdb main table
	static const std::string USR;

};