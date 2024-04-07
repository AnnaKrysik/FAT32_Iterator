#pragma once
#include "FS.h"
#include <iostream>
#include "Iterator.h"
#include <cstdint>
#include <cstring>
class FAT32 :
	public FS
{
private:
#pragma pack(push, 1)
	typedef struct {
		BYTE Padding1[11];
		BYTE bytesPerSector[2];
		BYTE sectorsPerCluster[1];
	} BootRecord;
#pragma pack(pop)
protected:
	bool ReadClusterSize();
};