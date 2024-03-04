#include <windows.h>
#include <iostream>
#include <stdio.h>
#include "ReadInfo.h"
#include "utils.h" 
int ReadSector(LPCWSTR  drive, int readPoint, BYTE sector[512])
{
    int retCode = 0;
    DWORD bytesRead;
    HANDLE device = NULL;

    device = CreateFileW(drive,    // Drive to open
        GENERIC_READ,           // Access mode
        FILE_SHARE_READ | FILE_SHARE_WRITE,        // Share Mode
        NULL,                   // Security Descriptor
        OPEN_EXISTING,          // How to create
        0,                      // File attributes
        NULL);                  // Handle to template

    if (device == INVALID_HANDLE_VALUE) // Open Error
    {
        printf("CreateFile: %u\n", GetLastError());
        std::cout << "Error: " << GetLastError() << std::endl;
        return 1;
    }

    SetFilePointer(device, readPoint, NULL, FILE_BEGIN);//Set a Point to Read

    if (!ReadFile(device, sector, 512, &bytesRead, NULL))
    {
        printf("ReadFile: %u\n", GetLastError());
    }
    else
    {
        printf("Success!\n");
    }
}
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