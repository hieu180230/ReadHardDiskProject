
#include <iostream>
#include <stdio.h>
#include "ReadInfo.h"
#include "utils.h" 

int main(int argc, char** argv)
{   
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);
    BYTE sector[512];
    ReadSector(L"\\\\.\\I:", 0, sector);
    for (int i = 0; i < 512; i++)
    {
		printf("%02x ", sector[i]);
        if ((i + 1) % 16 == 0)
        {
			printf("\n");
		}
	}
    std::cout << std::endl;
    FAT32BootSectorInfo* bootSectorInfo = ReadInfo::GetBootSectorInfo(sector);
    bootSectorInfo->printInfo();
    std::cout << utils::DectoHex(bootSectorInfo->firstSectorOfCluster(bootSectorInfo->_RootCluster));
    std::cout << std::endl;
    mainx();
    return 0;
}