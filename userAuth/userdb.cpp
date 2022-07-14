/*
	Programmer: Jerusalem Moore
	Class: UserDB
	Date: 6/28/2022
	Definition:
		Class meant to store and process user Account info for query and account
		registration
*/
//#define USR "USERS"
#define __STDC_WANT_LIB_EXT1__ 1


#include "userdb.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//run with init table if you want to start fresh user table
#define FRESH 1
const std::string UserDB::USR = "USERS";


//initialize with name for sqlite db file
//initlialize original schema for user table if it doesn't exist
UserDB::UserDB(std::string dbname) {
	this->dbname = dbname;
	passProcessor = new PasswordProcessor();
	initTable(FRESH);
}
UserDB::~UserDB() {
	delete passProcessor;
}
void UserDB::initTable(int fresh) {
	std::string sql;
	if (fresh) {
		sql = "DROP TABLE IF EXISTS USERS";
		sqlEx(sql);
	}
	sql =
		"CREATE TABLE IF NOT EXISTS " + USR + "(\n"
		"id INTEGER PRIMARY KEY,"
		"firstname TEXT,\n"
		"lastname TEXT, \n"
		"username TEXT UNIQUE,\n"
		"password TEXT, \n"
		"salt TEXT UNIQUE\n"
		");";
	sqlEx(sql);
	sql = "pragma table_info('USERS')";
	sqlEx(sql);
	std::string salt = passProcessor->produceSalt();
	std::string password = passProcessor->hash("JJjj@749847", salt);
	sql = "\n"
		"INSERT INTO USERS (username, firstname, lastname, password, salt)\n"
		"VALUES ('jerusalemmoore', 'jerusalem', 'moore', '"+password+"', '"+salt+"'); \n";
	
	sqlEx(sql);
	sql = "\
	SELECT * FROM USERS\
		";
}
void UserDB::insertUser(std::string firstName, std::string lastName, std::string username, std::string password) {
	std::string salt = passProcessor->produceSalt();
	std::string hashPass = passProcessor->hash(password, salt);
	std::string sql = "\
	INSERT INTO " + USR + " (firstname,lastname,username,password,salt)\
	VALUES ('" + firstName + "','" + lastName + "', '" + username + "','"+hashPass+"','" +salt+"')\
	";
	sqlEx(sql);
	sql = "SELECT * FROM " + USR + ";";
	sqlEx(sql);
}
//callback used for error handling sqlite3
int UserDB::callback(void* notUsed, int argc, char** argv, char** azColName) {
	int i;
	std::cout << "callback was called" << std::endl;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		
	}
	//std::cout << "val: " << (char*)data << std::endl;

	printf("\n");
	//exit(EXIT_FAILURE);
	return 0;
}
/*
	will likely need this for updating info
*/
void UserDB::updateData(std::string data) {

}

//take a name and open db based off of string
//return null if error
//this should run in exec, then close it so we don't need 
//to worry about forgetting to close
//start db with given name
//input:
//string dbname: name of db file to open
//return:
//pointer to db
sqlite3* UserDB::startDB(std::string dbname) {
	sqlite3* db;
	int rc;
	rc = sqlite3_open(dbname.c_str(), &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return nullptr;
	}
	fprintf(stderr, "Opened database successfully\n");
	return db;
}


//take dbname and a string to execute sql to our db. return true if succesful
//open the db, enter a statement, and close the db after execution
void UserDB::sqlEx(std::string statement) {
	std::cout << "Running\n" << statement << std::endl;
	sqlite3* db = startDB(dbname);
	if (db == nullptr) {
		std::cout << "error, startDB returned null" << std::endl;
	}
	int rc;
	char* zErrMsg = 0;
	rc = sqlite3_exec(db, statement.c_str(), callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		exit(EXIT_FAILURE);
	}
	else {
		//std::cout << "val: " << (char*)data << std::endl;
		//printf("mydata: %s\n", mydata);
		fprintf(stdout, "Operation ran successfully\n");
	}

	sqlite3_close(db);

}
/*
	NOTES:OVERLOAD FOR GENERALIZED USAGE
		thinking about using data structs to pass to func so they may be parsed
		differently depending on how we want to select (a specific col, multiple cols, lists, etc)
		hopefully simplifying how to make expected queries will ease future development
		struct ideas:
		username/first/last/fk structs for query 1 col 1 row query
		multi for multiple col 1 row query
		username/first/last+List for multiple row query 1 col
		multi+Username/First/Last/List for multiple row multiple col
	run SELECT query to USER table
	input:
		colnames - vector of strings for storing columns included in query

*/
//sqlite3_stmt* UserDB::select(std::vector<std::string> colNames, std::string tableName, std::string username) {
//	sqlite3* db = startDB(dbname);
//	sqlite3_stmt* statement;
//	std::string sql;
//	int rc;
//	//stop if colname is empty, something bad happened
//	if (colNames.empty()) {
//		std::cout << "Error, colnames list given is empty" << std::endl;
//		exit(EXIT_FAILURE);
//	}
//	if (colNames.size() == 1) {
//		sql = "SELECT " + colNames[0] + " FROM " + tableName + " ";
//	}
//	else {
//		sql = "SELECT";
//		for (auto colname = colNames.begin(); colname != colNames.end(); colname++) {
//			if (std::next(colname) == colNames.end()) {
//				sql += " " + *colname + " ";
//			}
//			else {
//				sql += " " + *colname + ", ";
//
//			}
//		}
//		sql += "FROM " + tableName;
//	}
//	sql += " WHERE username == '" + username + "';";
//	std::cout << sql << std::endl;
//	rc = sqlite3_prepare_v2(db, sql.c_str(), int(sql.length()), &statement, NULL);
//	if (rc != SQLITE_OK) {
//		std::cout << "Error preparing statment: " << std::endl;
//		std::cout << "Error: " << sqlite3_errmsg(db) << std::endl;
//		std::cout << "statement: " << sql << std::endl;
//		return NULL;
//	}
//
//
//	rc = sqlite3_step(statement);
//	const unsigned char* entry1 = sqlite3_column_text(statement, 0);
//	const unsigned char* entry2 = sqlite3_column_text(statement, 1);
//	std::cout << "entry1: " << entry1 << std::endl;
//	std::cout << "entry2: " << entry2 << std::endl;
//
//	return statement;
//
//
//}
/*
	findUsername
		public func for finding username in user table
	input:
		username to search for
	output:
		bool -> true name found, false otherwise
*/
//check if any row contains single col val matching given username
bool UserDB::usernameExists(Username username) {
	//sqlite3_stmt* stmt = select(username);
	//sqlite3_finalize(stmt);
	std::string entry = select(username);
	if (entry == "") {
		std::cout << "Username doesn't exist!" << std::endl;
		return false;
	}
	std::cout << "Username exists" << std::endl;
	return true;


}
//return name of dbfile
std::string UserDB::getid() {
	return this->dbname;
}
//make sure my custom functions interact with db as expected
//make test db
//make user table
//run commands
//drop table

/*
	select function for username query
	input:
		username struct username
	output:
		return username as string if exists, empty otherwise
*/
std::string UserDB::select(Username username) {
	sqlite3* db = startDB(dbname);
	sqlite3_stmt* statement;
	int rc;
	std::string sql = "SELECT username FROM " + USR + " WHERE username = '" + username.content + "';";
	rc = sqlite3_prepare_v2(db, sql.c_str(), int(sql.length()), &statement, NULL);
	if (rc != SQLITE_OK) {
		std::cout << "error in prepare statement" << std::endl;
		std::cout << sql << std::endl;

	}
	//search execute sql username search 
	rc = sqlite3_step(statement);
	//if we get nothing it means the username is unique
	if (rc != SQLITE_ROW) {
		sqlite3_finalize(statement);
		sqlite3_close(db);
		return "";
	}
	const unsigned char* entry = sqlite3_column_text(statement, 0);
	//std::cout << "username value: " << entry << std::endl;
	std::string copy((char*)entry);
	sqlite3_finalize(statement);
	sqlite3_close(db);

	return copy;
	//const unsigned char*  = sqlite3_column_text(statement, 0);
}
//sqlite3_stmt* UserDB::select(firstname firstname) {
//	sqlite3* db = startDB(dbname);
//	sqlite3_stmt* statement;
//	std::string sql;
//	int rc;
//	//stop if colname is empty, something bad happened
//	
//}

///////////////////////////////////////////////////////////////////////////////
// TEST FUNCS
// ////////////////////////////////////////////////////////////////////////////
//test inserts into a db table 
//prints output of table after insertions
//should fail when inserting duplicate "first" "first" for full name 
void UserDB::dbtest1() {
	std::string sql =
		"CREATE TABLE IF NOT EXISTS TEST(" \
		"ID INTEGER PRIMARY KEY  AUTOINCREMENT," \
		"FULL_NAME	TEXT NOT NULL UNIQUE);";
	sqlEx(sql);
	std::string testinput[6][2] = { {"first", "first"}, {"second","second"}, {"third", "third"}, {"fourth", "fourth"}, {"fifth", "fifth"}, {"first", "first"} };
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 2; j++) {
			std::string sql = "INSERT INTO USERS(FULL_NAME)" \
				"VALUES('" + testinput[i][j] + " " + testinput[i][j] + "'); ";
			sqlEx(sql);
		}

	}
	sql = "SELECT * FROM USERS";
	sqlEx(sql);
	sql = "DROP TABLE USERS";
}
void UserDB::dbhealthcheck() {
	std::string firstName = "Jerusalem";
	std::string lastName = "Moore";
	std::string sql =
		"CREATE TABLE IF NOT EXISTS TEST(" \
		"ID INTEGER PRIMARY KEY  AUTOINCREMENT," \
		"FULL_NAME	TEXT NOT NULL UNIQUE);";
	std::cout << "running:" << std::endl << sql << std::endl;
	sqlEx(sql);
	sql =
		"INSERT INTO TEST(FULL_NAME)" \
		"VALUES('" + firstName + " " + lastName + "'); ";
	std::cout << "running:" << std::endl << sql << std::endl;
	sqlEx(sql);
	firstName = "Bob";
	lastName = "Hope";
	sql =
		"INSERT INTO TEST(FULL_NAME)" \
		"VALUES('" + firstName + " " + lastName + "'); ";
	std::cout << "running:" << std::endl << sql << std::endl;
	sqlEx(sql);
	firstName = "Lex";
	lastName = "Buck";
	sql =
		"INSERT INTO TEST(FULL_NAME)" \
		"VALUES('" + firstName + " " + lastName + "'); ";
	std::cout << "running:" << std::endl << sql << std::endl;
	sqlEx(sql);
	sql = "SELECT * from TEST";
	std::cout << "running:" << std::endl << sql << std::endl;
	sqlEx(sql);
	sql = "SELECT EXISTS(SELECT FULL_NAME from TEST WHERE FULL_NAME = 'Jerusalem Mo')";
	std::cout << "running:" << std::endl << sql << std::endl;
	sqlEx(sql);
	sql = "DROP TABLE TEST";
	std::cout << "running:" << std::endl << sql << std::endl;
	sqlEx(sql);
	sql = "SELECT * FROM TEST";
	sqlEx(sql);

}