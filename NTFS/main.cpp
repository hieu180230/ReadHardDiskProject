#include "ReadSector.h"

int main(int argc, int** agrv)
{
    wstring name;
    cout << "Enter drive name: ";
    wcin >> name;
    name = L"\\\\.\\" + name + L":";
    LPCWSTR drive = name.c_str();
    BYTE sector[1024];
    bool check = readNSector(drive, 0, sector, 1);
    if (check == true)
    {
        BPB* bpb = NULL;
        printSector(sector);
        Read_BPBNTFS(sector, drive, bpb);
    }
    else
    {
        cout << "Error reading this drive !" << endl;
        return 0;
    }
}