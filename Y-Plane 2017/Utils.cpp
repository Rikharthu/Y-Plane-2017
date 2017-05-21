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

Platform::String ^ toPlatformString(std::string inputString)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::wstring intermediateForm = converter.from_bytes(inputString);
	Platform::String^ retVal = ref new Platform::String(intermediateForm.c_str());

	return retVal;
}

double disperse(double direction, double delta)
{
	int k = rand() % 2 ? -1 : 1;
	double p = (double)(rand() % 1001) / 1000;
	return direction + k*p*delta;
}