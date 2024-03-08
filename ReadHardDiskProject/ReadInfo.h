#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include "BootSectorInfo.h"
#include <atlstr.h>
#include <cctype>
class ReadInfo
{
public:
	static FAT32BootSectorInfo* GetBootSectorInfo(BYTE sector[512]);
	static void getSDETInfo(LPCWSTR drive, int root_cluster, int sectors_per_cluster, int first_data_sector, std::string path, int level);
	static void getRDETInfo(LPCWSTR drive, int root_cluster, int sectors_per_cluster, int first_data_sector);
};

