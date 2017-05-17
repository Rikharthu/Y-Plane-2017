#pragma once
#include <winsqlite/winsqlite3.h>
#include "Plane.h"
#include <vector>

using namespace std;

class LuftwaffeDatabase {

private:
	static bool ready;
	sqlite3 * database;
	static vector<Plane*> *data;
public:
	LuftwaffeDatabase();
	~LuftwaffeDatabase();
	void open();
	void create();
	void close();
	void add(Plane&);
	void update(Plane&);
	vector<Plane*> * getData();
	vector<Plane*> * getData2();
	static int callback(void*data, int argc, char ** argv, char **azColName);
};