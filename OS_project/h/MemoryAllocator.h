#ifndef NIJEVAYNO_MEMORYALLOCATOR_H
#define NIJEVAYNO_MEMORYALLOCATOR_H

#include "../lib/hw.h"

class MemoryAllocator{
public:
    struct Node{
        Node*next;
        //Node*prev;
        size_t size;
        int isValid;
    }; //element liste blokova
    static Node* freeBlocks; // lista slobodnih blokova
    static Node* allocatedBlocks; // lista zauzetih blokova
    static MemoryAllocator* memoryAllocator; // instanca objekta

    static void init(); // inicijaliyacija objekta
    static MemoryAllocator* getInstance(); // "getter" za objekat
    static void* mem_alloc(size_t size); // funkcija za alociranje memorije
    static int mem_free(void* ptr); // funkcija za oslobadjanje memorije

    MemoryAllocator() = delete; // zabrana podrazumevanog konstruktora
    MemoryAllocator(MemoryAllocator &) = delete; // zabrana kopirajuceg konstruktora
    void operator=(const MemoryAllocator&) = delete; // zabrana oepratora dodela
};
#endif //NIJEVAYNO_MEMORYALLOCATOR_H
