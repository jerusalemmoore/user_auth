/*
	Programmer: Jerusalem Moore
	Class: UserDB
	Definition:
		Class meant to store and process user Account info for query and account
		registration
*/
#include "userdb.h"


//callback used for error handling sqlite3
int UserDB::callback(void* NotUsed, int argc, char** argv, char** azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
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
	}
	else {
		fprintf(stdout, "Operation ran successfully\n");
	}
	sqlite3_close(db);

}



std::string UserDB::getid() {
	return this->dbname;
}
//make sure my custom functions interact with db as expected
//make test db
//make user table
//run commands
//drop table
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
	sql = "SELECT * from TEST";
	std::cout << "running:" << std::endl << sql << std::endl;
	sqlEx(sql);
	std::cout << "running:" << std::endl << sql << std::endl;
	sql = "DROP TABLE TEST";
	std::cout << "running:" << std::endl << sql << std::endl;
	sqlEx(sql);
	sql = "SELECT * FROM TEST";
	sqlEx(sql);

}
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