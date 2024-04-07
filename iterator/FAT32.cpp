#include "FAT32.h"
#include "Iterator.h"
#include <iostream>
#include "windows.h"
#include "stdio.h"
using namespace std;

bool FAT32::ReadClusterSize()
{
    BYTE sector[512];
    DWORD bytesRead;
    DWORD bytesToRead = sizeof(sector);

    LARGE_INTEGER sectorSizeOffset;
    sectorSizeOffset.QuadPart = 0;

    if (!SetFilePointerEx(fileHandler, sectorSizeOffset, NULL, FILE_BEGIN)) {
        throw std::invalid_argument("Set FilePointer error");
        CloseHandle(fileHandler);
        return false;
    }
    if (!ReadFile(fileHandler, sector, bytesToRead, &bytesRead, NULL))
    {
        throw std::invalid_argument("ReadFile error");
        CloseHandle(fileHandler);
        return false;
    }

    BootRecord* pBootRecord = reinterpret_cast<BootRecord*>(sector);
    unsigned int bytesPerSector = (pBootRecord->bytesPerSector[1] << 8) | pBootRecord->bytesPerSector[0];
    unsigned int sectorsPerCluster = (unsigned int)(pBootRecord->sectorsPerCluster);
    clusterSize = bytesPerSector * sectorsPerCluster;
    return true;
}