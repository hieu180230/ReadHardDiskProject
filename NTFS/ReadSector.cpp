#include "ReadSector.h"

int readSector(LPCWSTR drive, int readPoint, BYTE sector[512])
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
        cout << "CreateFile : " << GetLastError() << endl;
        cout << endl;
        return 0;
    }

    SetFilePointer(device, readPoint, NULL, FILE_BEGIN);//Set a Point to Read

    if (!ReadFile(device, sector, 512, &bytesRead, NULL))
    {
        cout << "ReadFile : " << GetLastError() << endl;
        return 0;
    }
    else
    {
        cout << "Read successfuly !" << endl;
        cout << endl;
        return 1;
    }
}

//doc du lieu va tra ve mot so nguyen duoc luu tru trong mang cac byte
int64_t Get_Bytes(BYTE* sector, int offset, int number)
{

    int64_t result = 0;
    memcpy(&result, sector + offset, number);
    return result;
}

//doc thong tin trong bang phan vung NTFS roi hien thi ra man hinh
void Read_NTFS(BYTE* sector, LPCWSTR disk)
{
    unsigned int bytes_per_sector = Get_Bytes(sector, 0x0B, 2); // Bytes Per Sector
    unsigned int sectors_per_cluster = Get_Bytes(sector, 0x0D, 1); // Sectors Per Cluster
    unsigned int sectors_per_track = Get_Bytes(sector, 0x18, 2); // Sectors Per Track
    unsigned int total_sectors = Get_Bytes(sector, 0x28, 8); // Total Sectors
    unsigned int MFTStart = Get_Bytes(sector, 0x30, 8); // Cluster start of MFT
    unsigned int MFTMirrorStart = Get_Bytes(sector, 0x38, 8); // Cluster start of MFTMirror
    cout << endl;
    cout << endl << endl << endl;
    cout << "|Bytes Per Sector : " << bytes_per_sector << endl;
    cout << "|Sectors Per Cluster : " << sectors_per_cluster << endl;
    cout << "|Sectors Per Track : " << sectors_per_track << endl;
    cout << "|Total Sectors : " << total_sectors << endl;
    cout << "|Cluster start of MFT : " << MFTStart << endl;
    cout << "|Cluster start of MFTMirror : " << MFTMirrorStart << endl;
    cout << endl << endl << endl;

}

//in ra cac byte cua mot sector trong dia
void printSector(BYTE* sector)
{
    int count = 0;
    int num = 0;

    cout << "offset   0  1  2  3  4  5  6  7    8  9  A  B  C  D  E  F" << endl;

    cout << "0x0" << num << "0  ";
    bool flag = 0;
    for (int i = 0; i < 512; i++)
    {
        count++;
        if (i % 8 == 0)
        {
            cout << "  ";
        }
        cout << hex << setw(2) << setfill('0') << uppercase << static_cast<int>(sector[i]) << " ";
        if (i == 255)
        {
            flag = 1;
            num = 0;
        }

        if (i == 511) break;
        if (count == 16)
        {
            int index = i;
            cout << endl;
            if (flag == 0)
            {
                num++;
                if (num < 10)
                    cout << "0x0" << num << "0  ";
                else
                {
                    char hex = char(num - 10 + 'A');
                    cout << "0x0" << hex << "0  ";
                }
            }
            else
            {
                if (num < 10)
                    cout << "0x1" << num << "0  ";
                else
                {
                    char hex = char(num - 10 + 'A');
                    cout << "0x1" << hex << "0  ";
                }
                num++;
            }
            count = 0;
        }
    }
    cout << endl;
}

