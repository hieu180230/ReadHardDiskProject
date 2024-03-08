#pragma once
#include <iostream>
#include <string>
#include <Windows.h>



class FAT32BootSectorInfo
{
public:
	std::string _OSName;
	int _BytesPerSector;
	int _SectorsPerCluster;
	int _ReservedSectors;
	int _NumberOfFATs;
	int _RootEntries; //0 for FAT32
	int _TotalSectors16; //0 for FAT32
	std::string _MediaDescriptor; //kind of volume
	int _SectorsPerFAT; //0 for FAT32
	int _SectorsPerTrack;
	int _NumberOfHeads;
	int _HiddenSectors;
	int _TotalSectors32; //if this = 0, use TotalSectors16
	int _FATSize; //sectors per FAT
	int _ExtendedFlags;
	int _FATVersion;
	int _RootCluster;
	int _FSInfo;
	int _BackupBootSector;
	std::string _Reserved;
	std::string _DriveNumber;
	int _Reserved1;
	std::string _BootSignature;
	int _VolumeID;
	std::string _VolumeLabel;
	std::string _FileSystemType;
	std::string _BootCode;
public:
	FAT32BootSectorInfo();
	~FAT32BootSectorInfo() {};
	void printInfo();
	int firstDataSector(); //figure where the data starts
	int firstSectorOfCluster(int n); //figure where the nth cluster starts
};


