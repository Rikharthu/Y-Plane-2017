#include "pch.h"
#include "Utils.h"
#include <cstdlib>
#include <locale>
#include <codecvt>
#include <string>

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

Platform::String ^ toPlatformString(std::string inputString)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::wstring intermediateForm = converter.from_bytes(inputString);
	Platform::String^ retVal = ref new Platform::String(intermediateForm.c_str());

	return retVal;
}
