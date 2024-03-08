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

void ReadInfo::getSDETInfo(LPCWSTR drive, int root_cluster, int sectors_per_cluster, int first_data_sector, std::string path, int level)
{
	
	int count = 0;
	int k = 0;
	path += "\\";
	while (true)
	{
		std::string file_name = "";
		bool end_flag = false;
		bool lfn = false;
		BYTE sector[512];
		ReadSector(drive, (root_cluster + k) * 512, sector);
		for (int i = 64; i < 512; i += 32)
		{
			if (sector[i] == 0xe5) //deleted entry
			{
				//std::cout << "Deleted Entry" << std::endl;
				continue;
			}
			if (sector[i] == 0x00) //end of directory
			{
				//std::cout << "End of Directory" << std::endl;
				end_flag = true;
				break;
			}
			if (sector[i + 11] == 0x0f) //long file name
			{
				file_name = std::string((char*)&sector[i + 1], 10) + std::string((char*)&sector[i + 14], 12) + std::string((char*)&sector[i + 28], 4) + file_name;
				for (int i = file_name.length() - 1; i >= 0; i--)
				{
					if (!isalpha(file_name[i]) && file_name[i] != '.')
					{
						file_name.erase(file_name.begin() + i);
					}
				}
				//std::cout << file_name << std::endl;
				lfn = true;
			}
			else
			{
				if (!lfn)
				{
					file_name = std::string((char*)&sector[i + 0], 8);
					file_name = file_name.substr(0, file_name.find_last_not_of(" ") + 1);
				}
				if (count != 0)
				{
					std::string expansion = "";
					if (!lfn)
					{
						expansion = std::string((char*)&sector[i + 8], 3);
						if (expansion != "   ")
						{
							file_name = file_name + "." + expansion;
						}
					}
					else
					{
						expansion = file_name.substr(file_name.find_last_of(".") + 1);
						for (auto& x : expansion)
						{
							x = std::toupper(x);
						}
						for (int i = 0; i < expansion.length(); i++)
						{
							if (!isalpha(expansion[i]))
							{
								expansion.erase(expansion.begin() + i);
								i--;
							}
						}
					}
					for (int i = 0; i < level; i++)
					{
						std::cout << "\t";
					}
					std::cout << "File Name: " << file_name << std::endl;
					for (int i = 0; i < level; i++)
					{
						std::cout << "\t";
					}
					std::cout << "File Size: " << *(DWORD*)&sector[i + 28] << std::endl;
					for (int i = 0; i < level; i++)
					{
						std::cout << "\t";
					}
					std::cout << "Status: ";
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
					for (int i = 0; i < level; i++)
					{
						std::cout << "\t";
					}
					std::cout << "First Cluster: " << *(WORD*)&sector[i + 26] << std::endl;
					if (sector[i + 11] != 0x14 && sector[i + 11] == 0x10)
					{
						for (int i = 0; i < level; i++)
						{
							std::cout << "\t";
						}
						std::cout << "Files/Sub folders: " << std::endl << std::endl;
						//read sdet (*(WORD*)&sector[i + 26] - 2) * sectors_per_cluster + root_cluster
						std::string temp_path = path;
						for (auto& x : file_name) {
							temp_path += tolower(x);
						}
						level++;
						getSDETInfo(drive, (*(WORD*)&sector[i + 26] - 2) * sectors_per_cluster + 8192, sectors_per_cluster, first_data_sector, temp_path, level);

					}
					// get fil's expansion and give appropriate suggestion
					if (sector[i + 11] == 0x20)
					{
						if (expansion == "TXT")
						{
							std::cout << "\tContent: " << std::endl;
							//read file
							std::string temp_path = path;
							for (auto& x : file_name) {
								temp_path += tolower(x);
							}
							std::cout << ReadFile(temp_path) << std::endl;

						}
						else
						{
							std::string tool = ExtensionToTool[expansion];
							if (tool != "") {
								std::cout << "\tSuggested opening tool: " << tool << std::endl;
							}
							else {
								std::cout << "\tUnknown opening tool!" << std::endl;
							}
						}
					}
					file_name = "";
					lfn = false;
					count = 0;
				}
				else //count = 0
				{
					if (std::string((char*)&sector[i + 8], 3) != "   ")
					{
						std::string expansion = "";
						if (!lfn)
						{
							expansion = std::string((char*)&sector[i + 8], 3);
							if (expansion != "   ")
							{
								file_name = file_name + "." + expansion;
							}
						}
						else
						{
							expansion = file_name.substr(file_name.find_last_of(".") + 1);
							for (auto& x : expansion)
							{
								x = std::toupper(x);
							}
							for (int i = 0; i < expansion.length(); i++)
							{
								if (!isalpha(expansion[i]))
								{
									expansion.erase(expansion.begin() + i);
									i--;
								}
							}
						}
						for (int i = 0; i < level; i++)
						{
							std::cout << "\t";
						}
						std::cout << "File Name: " << file_name << std::endl;
						for (int i = 0; i < level; i++)
						{
							std::cout << "\t";
						}
						std::cout << "File Size: " << *(DWORD*)&sector[i + 28] << std::endl;
						for (int i = 0; i < level; i++)
						{
							std::cout << "\t";
						}
						std::cout << "Status: ";
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
						for (int i = 0; i < level; i++)
						{
							std::cout << "\t";
						}
						std::cout << "First Cluster: " << *(WORD*)&sector[i + 26] << std::endl;
						if (sector[i + 11] != 0x14 && sector[i + 11] == 0x10)
						{
							for (int i = 0; i < level; i++)
							{
								std::cout << "\t";
							}
							std::cout << "Files/Sub folders: " << std::endl << std::endl;
							//read sdet (*(WORD*)&sector[i + 26] - 2) * sectors_per_cluster + root_cluster
							std::string temp_path = path;
							for (auto& x : file_name) {
								temp_path += tolower(x);
							}
							level++;
							getSDETInfo(drive, (*(WORD*)&sector[i + 26] - 2) * sectors_per_cluster + 8192, sectors_per_cluster, first_data_sector, temp_path, level);

						}
						// get fil's expansion and give appropriate suggestion
						if (sector[i + 11] == 0x20)
						{
							if (expansion == "TXT")
							{
								for (int i = 0; i < level; i++)
								{
									std::cout << "\t";
								}
								std::cout << "Content: " << std::endl;
								//read file 
								std::string temp_path = path;
								for (auto& x : file_name) {
									temp_path += tolower(x);
								}
								std::cout << ReadFile(temp_path) << std::endl;
							}
							else
							{
								std::string tool = ExtensionToTool[expansion];
								if (tool != "") {
									for (int i = 0; i < level; i++)
									{
										std::cout << "\t";
									}
									std::cout << "Suggested opening tool: " << tool << std::endl;
								}
								else {
									for (int i = 0; i < level; i++)
									{
										std::cout << "\t";
									}
									std::cout << "Unknown opening tool!" << std::endl;
								}
							}
						}
					}
					else
					{
						std::string expansion = "";
						if (!lfn)
						{
							expansion = std::string((char*)&sector[i + 8], 3);
							if (expansion != "   ")
							{
								file_name = file_name + "." + expansion;
							}
						}
						else
						{
							expansion = file_name.substr(file_name.find_last_of(".") + 1);
							for (auto& x : expansion)
							{
								x = std::toupper(x);
							}
							for (int i = 0; i < expansion.length(); i++)
							{
								if (!isalpha(expansion[i]))
								{
									expansion.erase(expansion.begin() + i);
									i--;
								}
							}
						}
						for (int i = 0; i < level; i++)
						{
							std::cout << "\t";
						}
						std::cout << "File Name: " << file_name << std::endl;
						for (int i = 0; i < level; i++)
						{
							std::cout << "\t";
						}
						std::cout << "File Size: " << *(DWORD*)&sector[i + 28] << std::endl;
						for (int i = 0; i < level; i++)
						{
							std::cout << "\t";
						}
						std::cout << "Status: ";
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
						for (int i = 0; i < level; i++)
						{
							std::cout << "\t";
						}
						std::cout << "First Cluster: " << *(WORD*)&sector[i + 26] << std::endl;
						if (sector[i + 11] != 0x14 && sector[i + 11] == 0x10)
						{
							for (int i = 0; i < level; i++)
							{
								std::cout << "\t";
							}
							std::cout << "Files/Sub folders: " << std::endl << std::endl;
							//read sdet (*(WORD*)&sector[i + 26] - 2) * sectors_per_cluster + root_cluster
							std::string temp_path = path;
							for (auto& x : file_name) {
								temp_path += tolower(x);
							}
							level++;
							getSDETInfo(drive, (*(WORD*)&sector[i + 26] - 2) * sectors_per_cluster + 8192, sectors_per_cluster, first_data_sector, temp_path, level);
						}
						if (sector[i + 11] == 0x20)
						{
							if (expansion == "TXT")
							{
								for (int i = 0; i < level; i++)
								{
									std::cout << "\t";
								}
								std::cout << "Content: " << std::endl;
								//read file 
								std::string temp_path = path;
								temp_path += "\\";
								for (auto& x : file_name) {
									temp_path += tolower(x);
								}
								//std::cout << temp_path << std::endl;
								std::cout << ReadFile(temp_path) << std::endl;
							}
							else
							{
								std::string tool = ExtensionToTool[expansion];
								if (tool != "") {
									for (int i = 0; i < level; i++)
									{
										std::cout << "\t";
									}
									std::cout << "Suggested opening tool: " << tool << std::endl;
								}
								else {
									for (int i = 0; i < level; i++)
									{
										std::cout << "\t";
									}
									std::cout << "Unknown opening tool!" << std::endl;
								}
							}
						}
					}
					file_name = "";
					lfn = false;
				}
				std::cout << std::endl;
			}
		}
		if (end_flag)
		{
			break;
		}
		else
		{
			k++;
		}
	}
}

void ReadInfo::getRDETInfo(LPCWSTR drive, int root_cluster, int sectors_per_cluster, int first_data_sector)
{
	//std::cout << root_cluster << std::endl;
	std::string file_name = "";
	std::string path = "";
	int count = 0;
	int k = 0;
	path = CW2A(drive);
	path = path.substr(4, 1);
	path += ":\\";
	while (true)
	{
		bool end_flag = false;
		bool lfn = false;
		BYTE sector[512];
		ReadSector(drive, (root_cluster + k) * 512, sector);
		for (int i = 0; i < 512; i += 32)
		{
			if (sector[i] == 0xe5) //deleted entry
			{
				//std::cout << "Deleted Entry" << std::endl;
				continue;
			}
			if (sector[i] == 0x00) //end of directory
			{
				//std::cout << "End of Directory" << std::endl;
				end_flag = true;
				break;
			}
			if (sector[i + 11] == 0x0f) //long file name
			{
				file_name = std::string((char*)&sector[i + 1], 10) + std::string((char*)&sector[i + 14], 12) + std::string((char*)&sector[i + 28], 4) + file_name;
				for (int i = file_name.length() - 1; i >= 0; i--)
				{
					if (!isalpha(file_name[i]) && file_name[i] != '.')
					{
						file_name.erase(file_name.begin() + i);
					}
				}
				//std::cout << file_name << std::endl;
				lfn = true;
			}
			else
			{
				if (!lfn)
				{
					file_name = std::string((char*)&sector[i + 0], 8);
					file_name = file_name.substr(0, file_name.find_last_not_of(" ") + 1);
				}
				if (count != 0)
				{
					std::string expansion = "";
					if (!lfn)
					{
						expansion = std::string((char*)&sector[i + 8], 3);
						if (expansion != "   ")
						{
							file_name = file_name + "." + expansion;
						}
					}
					else
					{
						expansion = file_name.substr(file_name.find_last_of(".") + 1);
						for (auto& x : expansion)
						{
							x = std::toupper(x);
						}
						for (int i = 0; i < expansion.length(); i++)
						{
							if (!isalpha(expansion[i]))
							{
								expansion.erase(expansion.begin() + i);
								i--;
							}
						}
					}
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
						std::cout << "Files/Sub folders: " << std::endl << std::endl;
						//read sdet (*(WORD*)&sector[i + 26] - 2) * sectors_per_cluster + root_cluster
						std::string temp_path = "";
						for (auto& x : file_name) {
							temp_path += tolower(x);
						}
						//std::cout << temp_path << std::endl;
						getSDETInfo(drive, (*(WORD*)&sector[i + 26] - 2) * sectors_per_cluster + first_data_sector, sectors_per_cluster, first_data_sector, temp_path, 1);
					}
					// get fil's expansion and give appropriate suggestion
					if (sector[i + 11] == 0x20)
					{
						if (expansion == "TXT")
						{
							std::cout << "Content: " << std::endl;
							//read file 
							std::string temp_path = path;
							temp_path += "\\";
							for (auto& x : file_name) {
								temp_path += tolower(x);
							}
							std::cout << ReadFile(temp_path) << std::endl;
						}
						else
						{
							std::string tool = ExtensionToTool[expansion];
							if (tool != "") {
								std::cout << "Suggested opening tool: " << tool << std::endl;
							}
							else {
								std::cout << "Unknown opening tool!" << std::endl;
							}
						}
					}
					file_name = "";
					lfn = false;
					count = 0;
				}
				else //count = 0
				{
					if (std::string((char*)&sector[i + 0x08], 3) != "   ")
					{
						std::string expansion = "";
						if (!lfn)
						{
							expansion = std::string((char*)&sector[i + 8], 3);
							if (expansion != "   ")
							{
								file_name = file_name + "." + expansion;
							}
						}
						else
						{
							expansion = file_name.substr(file_name.find_last_of(".") + 1);
							for (auto& x : expansion)
							{
								x = std::toupper(x);
							}
							for (int i = 0; i < expansion.length(); i++)
							{
								if (!isalpha(expansion[i]))
								{
									expansion.erase(expansion.begin() + i);
									i--;
								}
							}
						}
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
							std::cout << "Files/Sub folders: " << std::endl << std::endl;
							//read sdet (*(WORD*)&sector[i + 26] - 2) * sectors_per_cluster + root_cluster
							std::string temp_path = path;
							for (auto& x : file_name) {
								temp_path += tolower(x);
							}
							//std::cout << temp_path << std::endl;
							getSDETInfo(drive, (*(WORD*)&sector[i + 26] - 2)* sectors_per_cluster + first_data_sector, sectors_per_cluster, first_data_sector, temp_path, 1);

						}
						// get fil's expansion and give appropriate suggestion
						if (sector[i + 11] == 0x20)
						{
							if (expansion == "TXT")
							{
								std::cout << "Content: " << std::endl;
								//read file 
								std::string temp_path = path;
								temp_path += "\\";
								for (auto& x : file_name) {
									temp_path += tolower(x);
								}
								//std::cout << temp_path << std::endl;
								std::cout << ReadFile(temp_path) << std::endl;
							}
							else
							{
								std::string tool = ExtensionToTool[expansion];
								if (tool != "") {
									std::cout << "Suggested opening tool: " << tool << std::endl;
								}
								else {
									std::cout << "Unknown opening tool!" << std::endl;
								}
							}
						}
					}
					else
					{
						std::string expansion = "";
						if (!lfn)
						{
							expansion = std::string((char*)&sector[i + 8], 3);
							if (expansion != "   ")
							{
								file_name = file_name + "." + expansion;
							}
						}
						else
						{
							expansion = file_name.substr(file_name.find_last_of(".") + 1);
							for (auto& x : expansion)
							{
								x = std::toupper(x);
							}
							for (int i = 0; i < expansion.length(); i++)
							{
								if (!isalpha(expansion[i]))
								{
									expansion.erase(expansion.begin() + i);
									i--;
								}
							}
						}
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
							std::cout << "Files/Sub folders: " << std::endl << std::endl;
							//read sdet (*(WORD*)&sector[i + 26] - 2) * sectors_per_cluster + root_cluster
							std::string temp_path = path;
							for (auto& x : file_name) {
								temp_path += tolower(x);
							}
							//std::cout << temp_path << std::endl;
							getSDETInfo(drive, (*(WORD*)&sector[i + 26] - 2) * sectors_per_cluster + first_data_sector, sectors_per_cluster, first_data_sector, temp_path, 1);
						}
						if (sector[i + 11] == 0x20)
						{
							if (expansion == "TXT")
							{
								std::cout << "Content: " << std::endl;
								//read file 
								std::string temp_path = path;
								temp_path += "\\";
								for (auto& x : file_name) {
									temp_path += tolower(x);
								}
								//std::cout << temp_path << std::endl;
								std::cout << ReadFile(temp_path) << std::endl;
							}
							else
							{
								std::string tool = ExtensionToTool[expansion];
								if (tool != "") {
									std::cout << "Suggested opening tool: " << tool << std::endl;
								}
								else {
									std::cout << "Unknown opening tool!" << std::endl;
								}
							}
						}
					}
					lfn = false;
					file_name = "";
				}
				std::cout << std::endl;
			}
		}
		if (end_flag)
		{
			break;
		}
		else
		{
			k++;
		}
	}
}