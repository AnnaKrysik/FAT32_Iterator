#pragma once
#include "Iterator.h"
#include "FAT32.h"
#include <cstdlib>
#include <algorithm>
#include <random>

class FAT32Iterator : //итератор, который случайным образом обходит кластеры
    public Iterator<Cluster> 
{
private:
    FAT32* fat32;
    int count; //общее кол-во кластеров
    int* shuffledIndices; //указатель на массив индексов кластеров
    int cursor; //указатель текущей позиции итератора
public:
    FAT32Iterator(FAT32* fsItem) : Iterator<Cluster>(fsItem->ClusterCount()) {
        fat32 = fsItem;
        count = fat32->ClusterCount();
        shuffledIndices = new int[count];
        for (int i = 0; i < count; i++) {
            shuffledIndices[i] = i;
        }
        std::random_device rd; 
        std::mt19937 g(rd()); //генерация случайного значения
        std::shuffle(shuffledIndices, shuffledIndices + count, g); //случайное перемещивание индексов
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