#include "../h/Blocked.hpp"

_thread *Blocked::getThread() {
    if(!this->head) return nullptr; // ako nema nista vrati se
    Node* cur = head; // samo uzmi sa pocetka liste i pomeri pocetak, onda dealociraj visak
    head = head->next;
    _thread* thr = cur->thread;
    //MemoryAllocator::mem_free(cur);
    return thr;
}

void Blocked::putThread(_thread *thread) {
    if(!this->head){ // ako nema nista onda stavi na pocetak
        this->head = new Node();
        this->head->thread = thread;
        this->head->next = nullptr;
        return;
    }
    Node* cur = this->head; // ako ima onda stavi na kraj liste
    while(cur->next) cur = cur->next;
    cur->next = new Node(); // postavi odgovarajuca polja na odgovarajuce vrednosti
    cur->next->thread = thread;
    cur->next->next = nullptr;
}
