//#include <mysqlx/xdevapi.h>
#include <stdio.h>
#include <string>
#include <iostream>     // std::cout, std::end
#include "accountInfo.h"

#include "sqlite3.h"
//callback used for error handling sqlite3
//static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
//	int i;
//	for (i = 0; i < argc; i++) {
//		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
//	}
//	printf("\n");
//	return 0;
//}
////take a name and open db based off of string
////return null if error
////this should run in exec, then close it so we don't need 
////to worry about forgetting to close
////start db with given name
////input:
////string dbname: name of db file to open
////return:
////pointer to db
//sqlite3* startDB(std::string dbname) {
//	sqlite3* db;
//	int rc;
//	rc = sqlite3_open(dbname.c_str(), &db);
//	if (rc) {
//		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
//		return nullptr;
//	}
//	fprintf(stderr, "Opened database successfully\n");
//	return db;
//}
////take dbname and a string to execute sql to our db. return true if succesful
////open the db, enter a statement, and close the db after execution
//bool sql_ex(std::string dbname, std::string statement) {
//	sqlite3* db = startDB(dbname);
//	if (db == nullptr) {
//		std::cout << "error, startDB returned null" << std::endl;
//		return 1;
//	}
//	int rc;
//	char* zErrMsg = 0;
//	rc = sqlite3_exec(db, statement.c_str(), callback, 0, &zErrMsg);
//	if (rc != SQLITE_OK) {
//		fprintf(stderr, "SQL error: %s\n", zErrMsg);
//		sqlite3_free(zErrMsg);
//	}
//	else {
//		fprintf(stdout, "Operation ran successfully\n");
//	}
//	sqlite3_close(db);
//}
//
////make sure my custom functions interact with db as expected
////make test db
////make user table
////run commands
////drop table
//void dbhealthcheck() {
//	std::string firstName = "Jerusalem";
//	std::string lastName = "Moore";
//	std::string db = "testdb";
//	std::string sql =
//		"CREATE TABLE IF NOT EXISTS USERS(" \
//		"ID INTEGER PRIMARY KEY  AUTOINCREMENT," \
//		"FULL_NAME	TEXT NOT NULL UNIQUE);";
//	std::cout << "running:" << std::endl << sql << std::endl;
//	sql_ex(db, sql);
//	sql =
//		"INSERT INTO USERS(FULL_NAME)" \
//		"VALUES('" + firstName + " " + lastName + "'); ";
//	std::cout << "running:" << std::endl << sql << std::endl;
//	sql_ex(db, sql);
//	sql = "SELECT * from USERS";
//	std::cout << "running:" << std::endl << sql << std::endl;
//	sql_ex(db, sql);
//	std::cout << "running:" << std::endl << sql << std::endl;
//	sql = "DROP TABLE USERS";
//	std::cout << "running:" << std::endl << sql << std::endl;
//	sql_ex(db, sql);
//	sql = "SELECT * FROM USERS";
//	sql_ex(db, sql);
//
//}
////test inserts into a db table 
////prints output of table after insertions
////should fail when inserting duplicate "first" "first" for full name 
//void dbtest1() {
//	std::string dbname = "testdb";
//	std::string sql =
//		"CREATE TABLE IF NOT EXISTS USERS(" \
//		"ID INTEGER PRIMARY KEY  AUTOINCREMENT," \
//		"FULL_NAME	TEXT NOT NULL UNIQUE);";
//	sql_ex(dbname, sql);
//	std::string testinput[6][2] = { {"first", "first"}, {"second","second"}, {"third", "third"}, {"fourth", "fourth"}, {"fifth", "fifth"}, {"first", "first"} };
//	for (int i = 0; i < 5; i++) {
//		for (int j = 0; j < 2; j++) {
//			std::string sql = "INSERT INTO USERS(FULL_NAME)" \
//				"VALUES('" + testinput[i][j] + " " + testinput[i][j] + "'); ";
//			sql_ex(dbname, sql);
//		}
//
//	}
//	sql = "SELECT * FROM USERS";
//	sql_ex(dbname, sql);
//	sql = "DROP TABLE USERS";
//}

int main() {
	AccountInfo AccountInfo;
	AccountInfo.runInterface();
	AccountInfo.printFullName();
	/*std::string firstName = "Jerusalem";
	std::string lastName = "Moore";*/
	//dbhealthcheck();

}

