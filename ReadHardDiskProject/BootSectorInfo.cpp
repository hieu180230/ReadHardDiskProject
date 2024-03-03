#include "BootSectorInfo.h"

FAT32BootSectorInfo::FAT32BootSectorInfo()
{
	_OSName = "";
	_BytesPerSector = 0;
	_SectorsPerCluster = 0;
	_ReservedSectors = 0;
	_NumberOfFATs = 0;
	_RootEntries = 0;
	_TotalSectors16 = 0;
	_MediaDescriptor = "";
	_SectorsPerFAT = 0;
	_SectorsPerTrack = 0;
	_NumberOfHeads = 0;
	_HiddenSectors = 0;
	_TotalSectors32 = 0;
	_FATSize = 0;
	_ExtendedFlags = 0;
	_FATVersion = 0;
	_RootCluster = 0;
	_FSInfo = 0;
	_BackupBootSector = 0;
	_Reserved = "";
	_DriveNumber = 0;
	_Reserved1 = 0;
	_BootSignature = "";
	_VolumeID = 0;
	_VolumeLabel = "";
	_FileSystemType = "";
	_BootCode = "";
}

void FAT32BootSectorInfo::printInfo() {
	std::cout << "OS Name: " << _OSName << std::endl;
	std::cout << "Bytes per Sector: " << _BytesPerSector << std::endl;
	std::cout << "Sectors per Cluster: " << _SectorsPerCluster << std::endl;
	std::cout << "Reserved Sectors: " << _ReservedSectors << std::endl;
	std::cout << "Number of FATs: " << _NumberOfFATs << std::endl;
	std::cout << "Media Descriptor: " << _MediaDescriptor << std::endl;
	std::cout << "Sectors per Track: " << _SectorsPerTrack << std::endl;
	std::cout << "Number of Heads: " << _NumberOfHeads << std::endl;
	std::cout << "Hidden Sectors: " << _HiddenSectors << std::endl;
	std::cout << "Total Sectors 32: " << _TotalSectors32 << std::endl;
	std::cout << "FAT Size: " << _FATSize << std::endl;
	std::cout << "Root Cluster: " << _RootCluster << std::endl;
	std::cout << "FS Info: " << _FSInfo << std::endl;
	std::cout << "Backup Boot Sector: " << _BackupBootSector << std::endl;
	std::cout << "Drive Number: " << _DriveNumber << std::endl;
	std::cout << "Volume ID: " << _VolumeID << std::endl;
	std::cout << "Volume Label: " << _VolumeLabel << std::endl;
	std::cout << "File System Type (FAT Type): " << _FileSystemType << std::endl;
}