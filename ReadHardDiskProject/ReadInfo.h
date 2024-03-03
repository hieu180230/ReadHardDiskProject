#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include "BootSectorInfo.h"
class ReadInfo
{
public:
	static FAT32BootSectorInfo* GetBootSectorInfo(BYTE sector[512]);
};

