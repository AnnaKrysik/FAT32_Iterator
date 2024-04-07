#include <iostream>
#include "FS.h"
#include "FAT32.h"
#include "windows.h"
#include <iomanip>
#include "FAT32Iterator.h"
using namespace std;

void hexdump(const BYTE* array, unsigned int length, unsigned int offset) {
    const int bytes_per_line = 16;
    for (size_t i = 0; i < length; i += bytes_per_line) {
        // ����� ������ ������� ������
        std::cout << std::setw(8) << std::setfill('0') << std::hex << offset + i << ": ";

        // ����� ������ � ����������������� �������
        for (int j = 0; j < bytes_per_line; ++j) {
            if (i + j < length) {
                std::cout << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(array[i + j]) << " ";
            }
            else {
                std::cout << "   "; // ��� �������� �����
            }
        }

        // ����� �������� ASCII
        std::cout << "  ";
        for (int j = 0; j < bytes_per_line; ++j) {
            if (i + j < length) {
                char c = array[i + j];
                std::cout << (c >= 32 && c < 127 ? c : '.');
            }
            else {
                std::cout << " "; // ��� �������� �����
            }
        }

        std::cout << std::endl;
    }
}

int main()
{
    FAT32* fs = new FAT32;
    if (!fs->Init(L"\\.\D:")) {
        cout << "Init: " << GetLastError();
        return false;
    };

    unsigned int clusterSize = fs->ClusterSize();
    Iterator<Cluster>* it = new FAT32Iterator(fs);

    for (it->First(); !it->IsDone(); it->Next()) {
        Cluster currentObject = it->GetCurrent();
        unsigned int offset = currentObject.GetNum() * clusterSize;
        hexdump(currentObject.GetContent(), clusterSize, offset);
    }
    delete it;
    delete fs;

    return 0;
}
