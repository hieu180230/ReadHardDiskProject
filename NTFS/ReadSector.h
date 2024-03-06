#pragma once
#include<iostream>
#include<cstdlib>
#include<stdio.h>
#include<vector>
#include<windows.h>
#include<iomanip>
#include<sstream>
#include<map>
#include<string>
#include<cstring>
#include<fstream>
#include<io.h>
#include <sstream>
#include <cmath>
#include "NTFS.h"
using namespace std;

//doc sector
int readNSector(LPCWSTR drive, int64_t readPoint, BYTE sector[512], int numbersOfSector);

//doc du lieu va tra ve mot so nguyen duoc luu tru trong mang cac byte
int64_t Get_Bytes(BYTE* sector, int offset, int number);





//doc thong tin trong bang phan vung NTFS roi hien thi ra man hinh
void Read_BPBNTFS(BYTE* sector, LPCWSTR disk, BPB* &bpb);

//in ra cac byte cua mot sector trong dia
void printSector(BYTE* sector);

// doc thu muc goc
void ReadRootDirNTFS(BPB* bpb, LPCWSTR disk);
