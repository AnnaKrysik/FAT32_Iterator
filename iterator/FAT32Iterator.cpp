#include "FAT32Iterator.h"

Cluster FAT32Iterator::GetCurrent()
{
    return fat32->ReadCluster(cursor);
}