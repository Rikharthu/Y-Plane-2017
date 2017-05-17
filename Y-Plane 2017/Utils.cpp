#include "pch.h"
#include "Utils.h"
#include <cstdlib>

int random(int low, int high)
{
	return rand() % (high - low + 1) + low;
}

char * to_sql_insert_plane(Plane * plane)
{
	char* stmt=new char[256];
	sprintf(stmt,
		"INSERT INTO LUFTWAFFE(ID, CREATED_AT,DESTROYED_AT)"\
		"VALUES(%d, %d, %d);", 
		plane->id, plane->created_at, plane->destroyed_at);
	return stmt;
}
