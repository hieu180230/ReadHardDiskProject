// #include "ReadSector.h"
// #include <cmath>


// //doc du lieu va tra ve mot so nguyen duoc luu tru trong mang cac byte
// int64_t Get_Bytes(BYTE* sector, int offset, int number)
// {

//     int64_t result = 0;
//     memcpy(&result, sector + offset, number);
//     return result;
// }


// //in ra cac byte cua mot sector trong dia
// void printSector(BYTE* sector)
// {
//     int count = 0;
//     int num = 0;

//     cout << "offset   0  1  2  3  4  5  6  7    8  9  A  B  C  D  E  F" << endl;

//     cout << "0x0" << num << "0  ";
//     bool flag = 0;
//     for (int i = 0; i < 512; i++)
//     {
//         count++;
//         if (i % 8 == 0)
//         {
//             cout << "  ";
//         }
//         cout << hex << setw(2) << setfill('0') << uppercase << static_cast<int>(sector[i]) << " ";
//         if (i == 255)
//         {
//             flag = 1;
//             num = 0;
//         }

//         if (i == 511) break;
//         if (count == 16)
//         {
//             int index = i;
//             cout << endl;
//             if (flag == 0)
//             {
//                 num++;
//                 if (num < 10)
//                     cout << "0x0" << num << "0  ";
//                 else
//                 {
//                     char hex = char(num - 10 + 'A');
//                     cout << "0x0" << hex << "0  ";
//                 }
//             }
//             else
//             {
//                 if (num < 10)
//                     cout << "0x1" << num << "0  ";
//                 else
//                 {
//                     char hex = char(num - 10 + 'A');
//                     cout << "0x1" << hex << "0  ";
//                 }
//                 num++;
//             }
//             count = 0;
//         }
//     }
//     cout << endl;
// }

// // void ReadRootDirNTFS(BPB* bpb, LPCWSTR disk)
// // {
// //     BYTE sector[1024];
// //     int64_t indexSector = bpb->MFTStart * bpb->sectorsPerCluster + 5;
// //     readNSector(disk, indexSector * 512, sector, bpb->MFTEntrySize);
// //     printSector(sector);
// //     // read MFT entry header
// //     NTFS_MFTEntryHeader* mftEntryHeader = new NTFS_MFTEntryHeader;
// //     mftEntryHeader->signature = Get_Bytes(sector, 0x00, 4);
// //     mftEntryHeader->fixupArrayOffset = Get_Bytes(sector, 0x04, 2);
// //     mftEntryHeader->fixupArraySize = Get_Bytes(sector, 0x06, 2);
// //     mftEntryHeader->LSN = Get_Bytes(sector, 0x08, 8);
// //     mftEntryHeader->sequenceNumber = Get_Bytes(sector, 0x10, 2);
// //     mftEntryHeader->linkCount = Get_Bytes(sector, 0x12, 2);
// //     mftEntryHeader->attributesOffset = Get_Bytes(sector, 0x14, 2);
// //     mftEntryHeader->flags = Get_Bytes(sector, 0x16, 2);
// //     mftEntryHeader->usedSize = Get_Bytes(sector, 0x18, 4);
// //     mftEntryHeader->allocatedSize = Get_Bytes(sector, 0x1C, 4);
// //     mftEntryHeader->baseFileRecord = Get_Bytes(sector, 0x20, 8);
// //     mftEntryHeader->nextAttributeID = Get_Bytes(sector, 0x28, 2);
// //     mftEntryHeader->MFTEntryNumber = Get_Bytes(sector, 0x2A, 2);
// //     mftEntryHeader->updateSequenceArray = Get_Bytes(sector, 0x2C, 4);
// //     printf("Signature: %x\n", mftEntryHeader->signature);
// //     // cout << "Signature: " << mftEntryHeader->signature[0] << mftEntryHeader->signature[1] << mftEntryHeader->signature[2] << mftEntryHeader->signature[3] << endl;
// //     // cout << "Fixup Array Offset: " << mftEntryHeader->fixupArrayOffset << endl;
// //     // cout << "Fixup Array Size: " << mftEntryHeader->fixupArraySize << endl;
// //     // cout << "LSN: " << mftEntryHeader->LSN << endl;
// //     // cout << "Sequence Number: " << mftEntryHeader->sequenceNumber << endl;
// //     // cout << "Link Count: " << mftEntryHeader->linkCount << endl;
// //     // cout << "Attributes Offset: " << mftEntryHeader->attributesOffset << endl;
// //     // cout << "Flags: " << mftEntryHeader->flags << endl;
// //     // cout << "Used Size: " << mftEntryHeader->usedSize << endl;
// //     // cout << "Allocated Size: " << mftEntryHeader->allocatedSize << endl;
// //     // cout << "Base File Record: " << mftEntryHeader->baseFileRecord << endl;
// //     // cout << "Next Attribute ID: " << mftEntryHeader->nextAttributeID << endl;
// //     // cout << "MFT Entry Number: " << mftEntryHeader->MFTEntryNumber << endl;
// //     // cout << "Update Sequence Array: " << mftEntryHeader->updateSequenceArray << endl;
// // }