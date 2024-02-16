#ifndef NIJEVAYNO_BLOCKED_HPP
#define NIJEVAYNO_BLOCKED_HPP
#include "_thread.hpp"
#include "MemoryAllocator.h"

class _thread;
class Blocked {
public:
    // struktura koja je jedan element ulancane liste
    struct Node{
        _thread* thread;
        Node* next;
    };

    // glava ulancane liste
    Node* head;

    Blocked() : head(nullptr) {}
    // funkcije za uzimanje iz ulancane liste i stavljanje u ulancanu listu
    _thread* getThread();
    void putThread(_thread* thread);
};


#endif //NIJEVAYNO_BLOCKED_HPP
