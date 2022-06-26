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
	static int callback(void* NotUsed, int argc, char** argv, char** azColName);
	std::string getid();
	void sqlEx(std::string statement);
	bool findUsername(username username);
	void dbhealthcheck();
	void dbtest1();
	void updateData(std::string data);
private:
	sqlite3* startDB(std::string dbname);
	sqlite3_stmt* select(std::vector<std::string> colNames, std::string tableName, std::string username);
	sqlite3_stmt* select(firstname firstname);
	sqlite3_stmt* select(struct lastname);
	sqlite3_stmt* select(struct username);
	sqlite3_stmt* select(struct id);
	sqlite3* userdb;
	void* data;
	std::string dbname;
	std::string tblname;
	static const std::string USR;

};