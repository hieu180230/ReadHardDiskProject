#include "utils.h"
std::string utils::DectoHex(int dec)
{
	std::stringstream ss;
	ss << std::hex << dec;
	return ss.str();
}
int ReadSector(LPCWSTR  drive, int readPoint, BYTE sector[512])
{
    int retCode = 0;
    DWORD bytesRead;
    HANDLE device = NULL;

    device = CreateFile(drive,    // Drive to open
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
}

std::string ReadFile(std::string path)
{
    std::fstream file(path);
    std::string line;
    std::string content;
    while (std::getline(file, line))
    {
		content += line + "\n";
	}
    return content;
}