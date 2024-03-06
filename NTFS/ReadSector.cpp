#include "ReadSector.h"
#include <cmath>

//https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-setfilepointerex
int readNSector(LPCWSTR drive, int64_t readPoint, BYTE* sector, int numbersOfSector)
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
        std::cout << "CreateFile : " << GetLastError() << std::endl;
        std::cout << std::endl;
        return 0;
    }

    LARGE_INTEGER li;
    li.QuadPart = readPoint;
    if (!SetFilePointerEx(device, li, NULL, FILE_BEGIN)) // Set a Point to Read
    {
        std::cout << "SetFilePointerEx : " << GetLastError() << std::endl;
        CloseHandle(device);
        return 0;
    }

    if (!ReadFile(device, sector, numbersOfSector * 512, &bytesRead, NULL))
    {
        std::cout << "ReadFile : " << GetLastError() << std::endl;
        CloseHandle(device);
        return 0;
    }
    else
    {
        std::cout << "Read successfully!" << std::endl;
        std::cout << std::endl;
        CloseHandle(device);
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
void Read_BPBNTFS(BYTE* sector, LPCWSTR disk, BPB* &bpb)
{
    uint16_t bytes_per_sector = Get_Bytes(sector, 0x0B, 2); // Bytes Per Sector
    uint8_t sectors_per_cluster = Get_Bytes(sector, 0x0D, 1); // Sectors Per Cluster
    uint16_t sectors_per_track = Get_Bytes(sector, 0x18, 2); // Sectors Per Track
    uint64_t total_sectors = Get_Bytes(sector, 0x28, 8); // Total Sectors
    uint64_t MFTStart = Get_Bytes(sector, 0x30, 8); // Cluster start of MFT
    uint64_t MFTMirrorStart = Get_Bytes(sector, 0x38, 8); // Cluster start of MFTMirror
    int8_t MFTEntrySizeByte = Get_Bytes(sector, 0x40, 1); // MFT Entry byte
    int MFTEntrySize;
    if(MFTEntrySizeByte < 0)
    {
        MFTEntrySizeByte = -MFTEntrySizeByte;
        MFTEntrySize = pow(2, MFTEntrySizeByte) / bytes_per_sector;
    } else 
    {
        MFTEntrySize = MFTEntrySizeByte * sectors_per_cluster;
    }
    cout << endl;
    cout << endl << endl << endl;
    printf("|Bytes Per Sector : %d\n", bytes_per_sector);
    printf("|Sectors Per Cluster : %d\n", sectors_per_cluster);
    printf("|Sectors Per Track : %d\n", sectors_per_track);
    printf("|Total Sectors : %ld\n", total_sectors);
    printf("|Cluster start of MFT : %ld\n", MFTStart);
    printf("|Cluster start of MFTMirror : %ld\n", MFTMirrorStart);
    printf("|MFT Entry Size(sectors) : %d\n", MFTEntrySize);
    cout << endl << endl << endl;
    bpb = new BPB{ bytes_per_sector, sectors_per_cluster, sectors_per_track, total_sectors, MFTStart, MFTMirrorStart, MFTEntrySize};
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

// void ReadRootDirNTFS(BPB* bpb, LPCWSTR disk)
// {
//     BYTE sector[1024];
//     int64_t indexSector = bpb->MFTStart * bpb->sectorsPerCluster + 5;
//     readNSector(disk, indexSector * 512, sector, bpb->MFTEntrySize);
//     printSector(sector);
//     // read MFT entry header
//     NTFS_MFTEntryHeader* mftEntryHeader = new NTFS_MFTEntryHeader;
//     mftEntryHeader->signature = Get_Bytes(sector, 0x00, 4);
//     mftEntryHeader->fixupArrayOffset = Get_Bytes(sector, 0x04, 2);
//     mftEntryHeader->fixupArraySize = Get_Bytes(sector, 0x06, 2);
//     mftEntryHeader->LSN = Get_Bytes(sector, 0x08, 8);
//     mftEntryHeader->sequenceNumber = Get_Bytes(sector, 0x10, 2);
//     mftEntryHeader->linkCount = Get_Bytes(sector, 0x12, 2);
//     mftEntryHeader->attributesOffset = Get_Bytes(sector, 0x14, 2);
//     mftEntryHeader->flags = Get_Bytes(sector, 0x16, 2);
//     mftEntryHeader->usedSize = Get_Bytes(sector, 0x18, 4);
//     mftEntryHeader->allocatedSize = Get_Bytes(sector, 0x1C, 4);
//     mftEntryHeader->baseFileRecord = Get_Bytes(sector, 0x20, 8);
//     mftEntryHeader->nextAttributeID = Get_Bytes(sector, 0x28, 2);
//     mftEntryHeader->MFTEntryNumber = Get_Bytes(sector, 0x2A, 2);
//     mftEntryHeader->updateSequenceArray = Get_Bytes(sector, 0x2C, 4);
//     printf("Signature: %x\n", mftEntryHeader->signature);
//     // cout << "Signature: " << mftEntryHeader->signature[0] << mftEntryHeader->signature[1] << mftEntryHeader->signature[2] << mftEntryHeader->signature[3] << endl;
//     // cout << "Fixup Array Offset: " << mftEntryHeader->fixupArrayOffset << endl;
//     // cout << "Fixup Array Size: " << mftEntryHeader->fixupArraySize << endl;
//     // cout << "LSN: " << mftEntryHeader->LSN << endl;
//     // cout << "Sequence Number: " << mftEntryHeader->sequenceNumber << endl;
//     // cout << "Link Count: " << mftEntryHeader->linkCount << endl;
//     // cout << "Attributes Offset: " << mftEntryHeader->attributesOffset << endl;
//     // cout << "Flags: " << mftEntryHeader->flags << endl;
//     // cout << "Used Size: " << mftEntryHeader->usedSize << endl;
//     // cout << "Allocated Size: " << mftEntryHeader->allocatedSize << endl;
//     // cout << "Base File Record: " << mftEntryHeader->baseFileRecord << endl;
//     // cout << "Next Attribute ID: " << mftEntryHeader->nextAttributeID << endl;
//     // cout << "MFT Entry Number: " << mftEntryHeader->MFTEntryNumber << endl;
//     // cout << "Update Sequence Array: " << mftEntryHeader->updateSequenceArray << endl;
// }