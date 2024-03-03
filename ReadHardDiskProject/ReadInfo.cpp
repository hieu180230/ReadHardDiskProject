#include "BootSectorInfo.h"
#include "ReadInfo.h"
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