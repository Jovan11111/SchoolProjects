#include "../h/MemoryAllocator.h"

// MemAlokator, sluzi za alociranje, oslobadjanje i oragnizaciju memorije

MemoryAllocator::Node* MemoryAllocator::freeBlocks = nullptr;
MemoryAllocator::Node* MemoryAllocator::allocatedBlocks = nullptr;
MemoryAllocator* MemoryAllocator::memoryAllocator = nullptr;

void* MemoryAllocator::mem_alloc(size_t size){
    if(size == 0) return nullptr; // nepravilno unet podatak

    // racunanje broja bajtova koji treba da se alociraju zaokruzeno na MEM_BLOCK_SIZE
    size_t sizeToAllocate = MEM_BLOCK_SIZE*((size + sizeof(Node)) / MEM_BLOCK_SIZE + 1);

    // trazenje mesta novom alociranom bloku
    Node* cur = freeBlocks;
    while(cur){
        if(cur->size >= sizeToAllocate) break;
        cur = cur->next;
    }

    if(cur == nullptr) return nullptr; // ako nema mesta vrati nullptr
    Node* newAllocated = cur; // novi alocirani ce pocinjati tamo gde je pocinjao slobodni
    Node*rem = freeBlocks;
    while(freeBlocks != cur) freeBlocks = freeBlocks->next;
    uint64 temp = freeBlocks->size;
    freeBlocks = freeBlocks + sizeToAllocate;
    freeBlocks->size = temp - sizeToAllocate;
    freeBlocks->next = nullptr;
    if(rem + sizeToAllocate != freeBlocks) freeBlocks = rem;

    // postavljaju se vrednosti novog alociranog
    newAllocated->size = sizeToAllocate;
    newAllocated->next = nullptr;
    newAllocated->isValid = 1;

    // ako je prvi alloc, onda je on head
    if(allocatedBlocks == nullptr){
        allocatedBlocks = newAllocated;
        return newAllocated + sizeof(Node*);
    } // ako nije onda se stavlja na kraj liste
    else{
        Node*tmp = allocatedBlocks;
        while(tmp->next) tmp = tmp->next;
        tmp->next = newAllocated;
        return newAllocated + sizeof(Node*);
    }
}
int MemoryAllocator::mem_free(void* ptr) {
    if(ptr == nullptr) return -1; // ako se poslat null vrati se

    Node* blockToFree = (Node*) ptr;

    // ako blok nije dobijen funkcijom mem_alloc
    if(blockToFree->isValid == 0) return -2;


    // uklanjenje iz liste alociranih
    if(blockToFree == allocatedBlocks){ // ako je glava lise
        allocatedBlocks = allocatedBlocks->next;
    }
    else{ // ako nije nadji ga i ukloni
        Node* cur = allocatedBlocks;
        while(cur->next && cur->next != blockToFree) cur = cur->next;
        if(!cur->next) return -3; // ako blok nije nadjen u alociranom prostoru
        cur->next = blockToFree->next;
    }

    // ubacivanje u listu slobodnih
    Node* cur = freeBlocks;

    // trazi se blok koji je nakon blockToFree na hipu
    while(cur && cur < blockToFree) cur = cur->next;

    Node* curPrev = cur == freeBlocks ? nullptr : freeBlocks;

    // postavljanje prethodnika od cur na pravu vrednost
    while(curPrev && curPrev->next != cur) curPrev = curPrev->next;

    // bool vrednosti ako treba da se spoji sa prethodnim ili sledecim
    int mergePrev = 0, mergeNext = 0;
    // provera dal treba da se spoji sa prethodnim
    if(cur && curPrev && curPrev + curPrev->size == blockToFree){
        mergePrev = 1;
        curPrev->size += blockToFree->size;
        blockToFree = curPrev;
    }
    // provera dal treba da se spoji sa sledecim
    if(cur && blockToFree + blockToFree->size == cur){
        mergeNext = 1;
        blockToFree->size += cur->size;
        blockToFree->next = cur->next;
    }

    if (mergePrev) {
        blockToFree->next = cur; // isto ko da se nista ni nije desilo, mozda izbaciti
    } else if (mergeNext) blockToFree->next = cur->next; // ovde je blockToFree pojeo cur
    else blockToFree->next = cur;

    // posto je sad lepo ulancano sve, treba proveriti da mozda ne treba prebaciti glavu liste na blockToFree jer je mozda dodat na pocetak
    if(!freeBlocks || blockToFree < freeBlocks) freeBlocks = blockToFree;

    return 0;
}

MemoryAllocator *MemoryAllocator::getInstance() {
    return memoryAllocator;
}

void MemoryAllocator::init() {
    freeBlocks = (Node*) HEAP_START_ADDR;
    freeBlocks->size = (size_t) HEAP_END_ADDR - (size_t) HEAP_START_ADDR;
    freeBlocks->next = nullptr;
    //freeBlocks->prev = nullptr;
    allocatedBlocks = nullptr;
    //memoryAllocator = (MemoryAllocator*) MemoryAllocator::mem_alloc(sizeof(MemoryAllocator));
}
