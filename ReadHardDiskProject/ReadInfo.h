#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include "BootSectorInfo.h"
#include <atlstr.h>
class ReadInfo
{
public:
	static FAT32BootSectorInfo* GetBootSectorInfo(BYTE sector[512]);
	static void getSDETInfo(int root_cluster, int sectors_per_cluster, std::string path);
	static void getRDETInfo(LPCWSTR drive, int root_cluster, int sectors_per_cluster);
};

