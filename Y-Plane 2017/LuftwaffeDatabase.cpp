#include "pch.h"
#include "LuftwaffeDatabase.h"
#include <exception>
#include <string>
#include <cstdio>

using namespace std;
bool LuftwaffeDatabase::ready = false;
vector<Plane*> *LuftwaffeDatabase::data;

LuftwaffeDatabase::LuftwaffeDatabase()
{

}

LuftwaffeDatabase::~LuftwaffeDatabase()
{
	sqlite3_close(database);
}

void LuftwaffeDatabase::open()
{
	int result = sqlite3_open(":memory:", &database);
	if (result) {
		// Error
		throw exception(strcat("Error opening database: ", sqlite3_errmsg(database)));
	}
	else {
		// Ok!
	}
}

void LuftwaffeDatabase::create()
{
	sqlite3_open(":memory:", &database);
	char*sql = "CREATE TABLE LUFTWAFFE("  \
		"ID INT PRIMARY KEY     NOT NULL," \
		"CREATED_AT     INT    NOT NULL," \
		"DESTROYED_AT   INT     NOT NULL );";
	char *zErrMsg = 0;
	//- Execute SQL statement
	int result = sqlite3_exec(database, sql, nullptr, 0, &zErrMsg);
	if (result != SQLITE_OK) {
		//! TODO fix
		char *s = nullptr;
		//sprintf(s, "SQL error: %s\n", zErrMsg);
		//LogMessage(StringFromAscIIChars(s));
		sqlite3_free(zErrMsg);
	}
	else {
		//LogMessage("Table AIRFIELD created successfully\n");
	}
}

void LuftwaffeDatabase::add(Plane & plane)
{
	char* stmt = new char[256];
	sprintf(stmt,
		"INSERT INTO LUFTWAFFE (ID, CREATED_AT,DESTROYED_AT) "\
		"VALUES (%d, %d, %d);",
		plane.id, plane.created_at, plane.destroyed_at);
	char *zErrMsg = 0;
	int result = sqlite3_exec(database, stmt, nullptr, 0, &zErrMsg);
	if (result != SQLITE_OK) {
		//! TODO fix
		//char *s = nullptr;
		//sprintf(s, "SQL error: %s\n", zErrMsg);
		////LogMessage(StringFromAscIIChars(s));
		//sqlite3_free(zErrMsg);
		int a = 4;
	}
	else {
		//LogMessage("Table AIRFIELD created successfully\n");
		int a = 4;
	}
}

void LuftwaffeDatabase::update(Plane & plane)
{
	char* stmt = new char[256];
	sprintf(stmt,
		"UPDATE LUFTWAFFE "\
		"SET CREATED_AT=%d, DESTROYED_AT=%d "\
		"WHERE ID = %d;",
		plane.created_at, plane.destroyed_at, plane.id);
	char *zErrMsg = 0;
	int result = sqlite3_exec(database, stmt, nullptr, 0, &zErrMsg);
	if (result != SQLITE_OK) {
		//! TODO fix
		//char *s = nullptr;
		//sprintf(s, "SQL error: %s\n", zErrMsg);
		////LogMessage(StringFromAscIIChars(s));
		//sqlite3_free(zErrMsg);
		int a = 4;
	}
	else {
		//LogMessage("Table AIRFIELD created successfully\n");
		int a = 4;
	}
}

vector<Plane*> * LuftwaffeDatabase::getData()
{
	LuftwaffeDatabase::ready = false;
	char *zErrMsg = 0;
	char * stmt = "SELECT * from LUFTWAFFE;";
	const char* data = "Callback function called";
	int result = sqlite3_exec(database, stmt, callback, (void*)data, &zErrMsg);
	while (!LuftwaffeDatabase::ready) {}
	return LuftwaffeDatabase::data;
}

vector<Plane*>* LuftwaffeDatabase::getData2()
{
	// TODO add error handling (however not necessary)
	sqlite3_stmt *stmt;
	sqlite3_prepare_v2(database, "SELECT ID, CREATED_AT, DESTROYED_AT FROM LUFTWAFFE",
		-1, &stmt, NULL);
	//sqlite3_step(stmt);
	vector<Plane*> * planes = new vector<Plane*>();

	int rc = sqlite3_step(stmt);
	while (rc != SQLITE_DONE) {
		long id = sqlite3_column_int(stmt, 0);
		long created_at = sqlite3_column_int(stmt, 1);
		long destroyed_at = sqlite3_column_int(stmt, 2);
		planes->push_back(new Plane(id, created_at, destroyed_at));

		rc = sqlite3_step(stmt);
	}

	sqlite3_finalize(stmt);


	return planes;
}

int LuftwaffeDatabase::callback(void * data, int argc, char ** argv, char ** azColName)
{
	if (LuftwaffeDatabase::data == nullptr) {
		LuftwaffeDatabase::data = new vector < Plane*>();
	}
	else {
		LuftwaffeDatabase::data->clear();
	}

	int i;
	char * str = new char[256];
	sprintf(str, "%s\n", (const char *)data);
	Plane * p = nullptr;
	for (i = 0; i < argc; i++) {
		sprintf(str, "%s=%s", azColName[i], argv[i] ? argv[i] : "NULL");
		string x = azColName[i];
		auto z = argv[i];
		if (x == "ID") {
			p = new Plane();
			p->id = stol(argv[i]);
		}
		else if (x == "CREATED_AT") {
			p->created_at = stol(argv[i]);
		}
		else if (x == "DESTROYED_AT") {
			p->destroyed_at = stol(argv[i]);
			LuftwaffeDatabase::data->push_back(p);
		}
		int xyz = 212;
	}
	LuftwaffeDatabase::ready = true;
	return 556;
}
