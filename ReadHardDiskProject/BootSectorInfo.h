#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <map>

const std::map<std::string, int> OffsetAndSize = {
	{"0", 3},
	{"3", 8},
	{"B", 2},
	{"D", 1},
	{"E", 2},
	{"10", 1},
	{"11", 2},
	{"13", 2},
	{"15", 1},
	{"16", 2},
	{"18", 2},
	{"1A", 2},
	{"1C", 4},
	{"20", 4},
	{"24", 4},
	{"28", 2},
	{"2A", 2},
	{"2C", 4},
	{"30", 2},
	{"32", 2},
	{"34", 12},
	{"40", 1},
	{"41", 1},
	{"42", 1},
	{"43", 4},
	{"47", 11},
	{"52", 8},
	{"5A", 420},
	{"1FE", 2},
};


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
};


