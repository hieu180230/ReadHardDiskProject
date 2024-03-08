#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>
#include <fstream>
#include <map>

static std::map<std::string, std::string> ExtensionToTool = {
	{ "XLSX","Microsoft Excel" },
	{ "XLS","Microsoft Excel" },
	{ "DOCX","Microsoft Word" },
	{ "DOC","Microsoft Word" },
	{ "PPTX","Microsoft PowerPoint" },
	{ "PPT","Microsoft PowerPoint" },
	{ "PDF","Adobe Acrobat" },
	{ "JPG","Windows Photo Viewer" },
	{ "JPEG","Windows Photo Viewer" },
	{ "PNG","Windows Photo Viewer" },
	{ "GIF","Windows Photo Viewer" },
	{ "BMP","Windows Photo Viewer" },
	{ "TIFF","Windows Photo Viewer" },
	{ "TXT","Notepad" },
	{ "RTF","WordPad" },
	{ "MP3","Windows Media Player" },
	{ "WAV","Windows Media Player" },
	{ "MP4","Windows Media Player" },
	{ "AVI","Windows Media Player" },
	{ "WMV","Windows Media Player" },
	{ "MOV","Windows Media Player" },
	{ "FLV","Windows Media Player" },
	{ "MKV","Windows Media Player" },
	{ "MPG","Windows Media Player" },
	{ "MPEG","Windows Media Player" },
	{ "M4V","Windows Media Player" },
	{ "M4A","Windows Media Player" },
	{ "WMA","Windows Media Player" },
	{ "FLAC","Windows Media Player" },
	{ "OGG","Windows Media Player" },
	{ "WAV","Windows Media Player" },
	{ "M4P","Windows Media Player" },
	{ "M4R","Windows Media Player" },
	{ "M4B","Windows Media Player" },
	{ "M4V","Windows Media Player" },
	{ "M4A","Windows Media Player" },
	{ "MP3","Windows Media Player" },
	{ "WMA","Windows Media Player" },
	{ "FLAC","Windows Media Player" },
	{ "OGG","Windows Media Player" },
	{ "WAV","Windows Media Player" },
	{ "M4P","Windows Media Player" },
	{ "M4R","Windows Media Player" },
	{ "M4B","Windows Media Player" },
	{ "M4V","Windows Media Player" },
	{ "M4A","Windows Media Player" },
	{ "MP3","Windows Media Player" },
};

class utils
{
public:
	static std::string DectoHex(int dec);
};

int mainx();
int ReadSector(LPCWSTR  drive, int readPoint, BYTE sector[512]);
std::string ReadFile(std::string path);