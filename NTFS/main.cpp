#include "ReadSector.h"

int main(int argc, int** agrv)
{
    wstring name;
    cout << "Enter drive name: ";
    wcin >> name;
    name = L"\\\\.\\" + name + L":";
    LPCWSTR drive = name.c_str();
    BYTE sector[512];
    bool check = readSector(drive, 0, sector);
    if (check == true)
    {
        printSector(sector);
        Read_NTFS(sector, drive);
    }
    else
    {
        cout << "Error reading this drive !" << endl;
        return 0;
    }
}