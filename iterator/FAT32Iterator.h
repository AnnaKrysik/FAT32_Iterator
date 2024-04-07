#pragma once
#include "Iterator.h"
#include "FAT32.h"
#include <cstdlib>
#include <algorithm>
#include <random>

class FAT32Iterator : //��������, ������� ��������� ������� ������� ��������
    public Iterator<Cluster> 
{
private:
    FAT32* fat32;
    int count; //����� ���-�� ���������
    int* shuffledIndices; //��������� �� ������ �������� ���������
    int cursor; //��������� ������� ������� ���������
public:
    FAT32Iterator(FAT32* fsItem) : Iterator<Cluster>(fsItem->ClusterCount()) {
        fat32 = fsItem;
        count = fat32->ClusterCount();
        shuffledIndices = new int[count];
        for (int i = 0; i < count; i++) {
            shuffledIndices[i] = i;
        }
        std::random_device rd; 
        std::mt19937 g(rd()); //��������� ���������� ��������
        std::shuffle(shuffledIndices, shuffledIndices + count, g); //��������� ������������� ��������
        cursor = 0;
    }

    ~FAT32Iterator() {
        delete[] shuffledIndices;
    }

    void First() { cursor = 0; }
    void Next() { cursor++; }
    bool IsDone() const { return (cursor >= count); }
    Cluster GetCurrent();
};