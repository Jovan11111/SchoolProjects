#include "../h/Scheduler.hpp"

// Skedzuler koji koristi za stavljanje i uzimanje spremnih niti, kada je potrebno

Scheduler::Node* Scheduler::head = nullptr;

void Scheduler::put(_thread *thread) {
    if(!head){ // ako je head nullptr, alociraj head i onda u njega upisi sta treba
        head = (Node*) MemoryAllocator::mem_alloc(sizeof(Node*));
        head->data = thread;
        head->next = nullptr;
        return;
    }
    Node*cur = head; // ako head nije nullptr onda idi do kraja liste
    while(cur->next) cur = cur->next;
    // alociraj novi Node, postavi mu vrednosti koje trebaju
    cur->next =(Node*) MemoryAllocator::mem_alloc(sizeof(Node*));
    cur->next->data = thread;
    cur->next->next = nullptr;
}

_thread *Scheduler::get() {
    if(!head) return nullptr; // ako je head nullptr onda nema sta da se uzima, nema elemenata
    //Node* temp = head; // sacuvaj da bi mogao da ga dealociras posle
    _thread* ret = head->data; // uzmi podatak koji treba da se vrati
    head = head->next; // pomeri head za jedno mesto
    //MemoryAllocator::mem_free(temp); // dealociraj bivsu vrednost head
    return ret;
}
