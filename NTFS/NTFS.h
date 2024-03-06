#pragma once
#include<stdint.h>

struct BPB
{
    uint16_t bytesPerSector; //0x0B
    uint8_t sectorsPerCluster; //0x0D
    uint16_t sectorsPerTrack; //0x18
    uint64_t totalSectors; //0x28
    uint64_t MFTStart; //0x30
    uint64_t MFTMirrorStart; //0x38
    int32_t MFTEntrySize; //0x40
};

