#include "BootSectorInfo.h"
#include "ReadInfo.h"
#include "utils.h" 
#include <format>

FAT32BootSectorInfo* ReadInfo::GetBootSectorInfo(BYTE sector[512])
{
	FAT32BootSectorInfo* bootSectorInfo = new FAT32BootSectorInfo();
	int offset = 3;
	bootSectorInfo->_OSName = std::string((char*)&sector[offset], 8);
	offset += 8;
	bootSectorInfo->_BytesPerSector = *(WORD*)&sector[offset];
	offset += 2;
	bootSectorInfo->_SectorsPerCluster = sector[offset];
	offset += 1;
	bootSectorInfo->_ReservedSectors = *(WORD*)&sector[offset];
	offset += 2;
	bootSectorInfo->_NumberOfFATs = sector[offset];
	offset += 1;
	bootSectorInfo->_RootEntries = *(WORD*)&sector[offset];
	offset += 2;
	bootSectorInfo->_TotalSectors16 = *(WORD*)&sector[offset];
	offset += 2;
	bootSectorInfo->_MediaDescriptor = "0x" + std::format("{:x}", sector[offset]);
	offset += 1;
	bootSectorInfo->_SectorsPerFAT = *(WORD*)&sector[offset];
	offset += 2;
	bootSectorInfo->_SectorsPerTrack = *(WORD*)&sector[offset];
	offset += 2;
	bootSectorInfo->_NumberOfHeads = *(WORD*)&sector[offset];
	offset += 2;
	bootSectorInfo->_HiddenSectors = *(DWORD*)&sector[offset];
	offset += 4;
	bootSectorInfo->_TotalSectors32 = *(DWORD*)&sector[offset];
	offset += 4;
	bootSectorInfo->_FATSize = *(DWORD*)&sector[offset];
	offset += 4;
	bootSectorInfo->_ExtendedFlags = *(WORD*)&sector[offset];
	offset += 2;
	bootSectorInfo->_FATVersion = *(WORD*)&sector[offset];
	offset += 2;
	bootSectorInfo->_RootCluster = *(DWORD*)&sector[offset];
	offset += 4;
	bootSectorInfo->_FSInfo = *(WORD*)&sector[offset];
	offset += 2;
	bootSectorInfo->_BackupBootSector = *(WORD*)&sector[offset];
	offset += 2;
	bootSectorInfo->_Reserved = std::string((char*)&sector[offset], 12);
	offset += 12;
	bootSectorInfo->_DriveNumber = std::format("{:x}", sector[offset]);
	offset += 1;
	bootSectorInfo->_Reserved1 = sector[offset];
	offset += 1;
	bootSectorInfo->_BootSignature = std::format("{:x}", sector[offset]);
	offset += 1;
	bootSectorInfo->_VolumeID = *(DWORD*)&sector[offset];
	offset += 4;
	bootSectorInfo->_VolumeLabel = std::string((char*)&sector[offset], 11);
	offset += 11;
	bootSectorInfo->_FileSystemType = std::string((char*)&sector[offset], 8);
	offset += 8;
	bootSectorInfo->_BootCode = std::string((char*)&sector[offset], 420);
	offset += 420;
	return bootSectorInfo;
}

void ReadInfo::getRDETInfo(int root_cluster)
{
	std::string file_name = "";
	while (true)
	{
		bool end_flag = false;
		BYTE sector[512];
		ReadSector(L"\\\\.\\I:", root_cluster, sector);
		for (int i = 0; i < 512; i += 32)
		{
			if (sector[i] == 0xe5) //deleted entry
			{
				continue;
			}
			if (sector[i] == 0x00) //end of directory
			{
				end_flag = true;
				break;
			}
			if (sector[i + 11] == 0x0f) //long file name
			{
				file_name = std::string((char*)&sector[i + 1], 10) + std::string((char*)&sector[i + 14], 12) + std::string((char*)&sector[i + 28], 4);
			}
			else
			{
				std::cout << "File Name: " << file_name << std::endl
					<< "File Size: " << *(DWORD*)&sector[i + 28] << std::endl
					<< "Status: ";
				switch (sector[i + 11])
				{
				case 0x01:
				{
					std::cout << "Read Only" << std::endl;
					break;
				}
				case 0x02:
				{
					std::cout << "Hidden" << std::endl;
					break;
				}
				case 0x04:
				{
					std::cout << "System" << std::endl;
					break;
				}
				case 0x08:
				{
					std::cout << "Volume Label" << std::endl;
					break;
				}
				case 0x10:
				{
					std::cout << "Sub Directory" << std::endl;
					break;
				}
				case 0x20:
				{
					std::cout << "Archive" << std::endl;
					break;
				}
				default:
				{
					std::cout << "Unknown" << std::endl;
					break;
				}
				}
				std::cout << "First Cluster: " << *(WORD*)&sector[i + 26] << std::endl;
				if (sector[i + 11] != 0x14 && sector[i + 11] == 0x10)
				{
					std::cout << "Files/Sub folders: " << std::endl;
					//read sdet (*(WORD*)&sector[i + 26] - 2) * sectors_per_cluster + root_cluster
				}


			}
		}
	}
}