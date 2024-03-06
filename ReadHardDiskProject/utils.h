#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>

class utils
{
public:
	static std::string DectoHex(int dec);
};

int mainx();
int ReadSector(LPCWSTR  drive, int readPoint, BYTE sector[512]);