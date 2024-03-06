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

struct NTFS_MFTEntryHeader
{
    uint64_t signature; //0x00
    uint16_t fixupArrayOffset; //0x04
    uint16_t fixupArraySize; //0x06
    uint64_t LSN; //0x08
    uint16_t sequenceNumber; //0x10
    uint16_t linkCount; //0x12
    uint16_t attributesOffset; //0x14
    uint16_t flags; //0x16
    uint32_t usedSize; //0x18
    uint32_t allocatedSize; //0x1C
    uint64_t baseFileRecord; //0x20
    uint16_t nextAttributeID; //0x28
    uint16_t MFTEntryNumber; //0x2A
    uint32_t updateSequenceArray; //0x2C
};

