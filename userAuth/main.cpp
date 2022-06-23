//#ifdef _DEBUG
//#define _CRTDBG_MAP_ALLOC
//#define _CRTDBG_MAP_ALLOC_NEW
//#include <crtdbg.h>
//#include <assert.h>
//#endif
#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//#include <stdio.h>
//#include <string>
//#include <iostream>     // std::cout, std::end
//#include "accountInfo.h"
#include "userdb.h"
//#include "sqlite3.h"
//#include "interface.h"
static int callback(void* data, int argc, char** argv, char** azColName) {
	int i;
	fprintf(stderr, "%s: \n", (const char*)data);
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

/// THIS IS WHAT WE'RE DOING
/// //////////////////////////////
/// TRYING TO PARSE DATA RETURNED FROM SQL QUERY THROUGH CALL BACK
/// WE'RE GOING TO NEED TO LOOK IN PREPARE/BIND QUERY WORKFLOW
int main() {
	sqlite3* db;
	int rc = sqlite3_open("testdb", &db);
	if (rc != SQLITE_OK) {
		std::cout << "Error opening db: " << sqlite3_errmsg(db) << std::endl;
		return 1;
	}
	sqlite3_stmt* statement;
	std::string sql = 
		"CREATE TABLE IF NOT EXISTS TEST( \
		firstname TEXT,\
		lastname TEXT, \
		id PRIMARY KEY \
		);";
	rc = sqlite3_prepare_v2(db, sql.c_str(), size(sql), &statement, NULL);
	if (rc != SQLITE_OK) {
		std::cout << "Error preparing statment: " << sqlite3_errmsg(db) << std::endl;
		return 1;
	}
	rc = sqlite3_step(statement);
	sql =
		"INSERT INTO TEST (firstname, lastname)\
		VALUES('Jerusalem', 'Moore'); \
		INSERT INTO TEST (firstname, lastname)\
		VALUES('Barry', 'Moore');\
		INSERT INTO TEST(firstname, lastname)\
		VALUES('Larry', 'Moore')";
	rc = sqlite3_prepare_v2(db, sql.c_str(), size(sql), &statement, NULL);
	if (rc != SQLITE_OK) {
		std::cout << "Error preparing statment: " << sqlite3_errmsg(db) << std::endl;
		return 1;
	}
	rc = sqlite3_step(statement);
	sql = "SELECT firstname FROM TEST WHERE firstname == 'Jerusalm'";
	char string;
	rc = sqlite3_prepare_v2(db, sql.c_str(), size(sql), &statement, NULL);
	if (rc != SQLITE_OK) {
		std::cout << "Error preparing statment: " << sqlite3_errmsg(db) << std::endl;
		return 1;
	}
	rc = sqlite3_step(statement);
	const unsigned char* val = sqlite3_column_text(statement, 0);
	if (val == NULL) {
		std::cout << "name not in db" << std::endl;
		return 1;
	}
	std::cout << val << std::endl;
	
	/*UserDB* userdb = new UserDB();
	userdb->dbhealthcheck();
	delete(userdb);*/
	/*AccountInfo* accountInfo = new AccountInfo();
	UserDB* user = new UserDB();
	delete(user);
	delete(accountInfo);*/
	//Interface* interface = new Interface();
	//interface->runInterface();
	////interface->checkdb();
	//interface->checkAccount();
	////check for leaks
	//delete(interface);



	//sqlite db template
	//sqlite3* db;
	//char* zErrMsg = 0;
	//int rc;
	//std::string sql;
	//rc = sqlite3_open("test.db", &db);

	//if (rc) {
	//	fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	//	return(0);
	//}
	//else {
	//	fprintf(stderr, "Opened database successfully\n");
	//}
	//sql = "CREATE TABLE COMPANY("  \
	//	"ID INT PRIMARY KEY     NOT NULL," \
	//	"NAME           TEXT    NOT NULL," \
	//	"AGE            INT     NOT NULL," \
	//	"ADDRESS        CHAR(50)," \
	//	"SALARY         REAL );";

	///* Execute SQL statement */
	//rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

	//if (rc != SQLITE_OK) {
	//	fprintf(stderr, "SQL error: %s\n", zErrMsg);
	//	sqlite3_free(zErrMsg);
	//}
	//else {
	//	fprintf(stdout, "Table created successfully\n");
	//}
	//sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
	//	"VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
	//	"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
	//	"VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
	//	"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
	//	"VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
	//	"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
	//	"VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

	///* Execute SQL statement */
	//rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

	//if (rc != SQLITE_OK) {
	//	fprintf(stderr, "SQL error: %s\n", zErrMsg);
	//	sqlite3_free(zErrMsg);
	//}
	//else {
	//	fprintf(stdout, "Records created successfully\n");
	//}
	//sql = "SELECT * from COMPANY";

	///* Execute SQL statement */
	//rc = sqlite3_exec(db, sql.c_str(), callback, (void*)data, &zErrMsg);

	//if (rc != SQLITE_OK) {
	//	fprintf(stderr, "SQL error: %s\n", zErrMsg);
	//	sqlite3_free(zErrMsg);
	//}
	//else {
	//	fprintf(stdout, "Operation done successfully\n");
	//}
	//sql = "DROP TABLE COMPANY";

	///* Execute SQL statement */
	//rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

	//if (rc != SQLITE_OK) {
	//	fprintf(stderr, "SQL error: %s\n", zErrMsg);
	//	sqlite3_free(zErrMsg);
	//}
	//else {
	//	fprintf(stdout, "Operation done successfully\n");
	//}
	//sqlite3_close(db);
	//bool  isLeaking = _CrtDumpMemoryLeaks();
	//std::cout << isLeaking << std::endl;
	//

	return 0;
}

