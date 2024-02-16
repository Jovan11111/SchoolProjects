#include "../h/_sem.hpp"

int _sem::semOpen(sem_t **handle, unsigned init) {
    *handle = (_sem**)MemoryAllocator::mem_alloc(sizeof(_sem)); // alociraj pokazivac
    **handle = (_sem*)MemoryAllocator::mem_alloc(sizeof(_sem)); // alociraj dupli pokazivac
    if(*handle == nullptr) return -1; // alociraj memoriju za semafor i proveri dal je dobro alocirana
    (**handle)->init = init; // postavi vrednosti koje trebaju i vrati se
    (**handle)->blockedHead = (Blocked*) MemoryAllocator::mem_alloc(sizeof(Blocked));
    (**handle)->blockedHead->head = nullptr;
    (**handle)->blockedHead->head->next = nullptr;
    (**handle)->blockedHead->head->thread = nullptr;
    return 0;
}

int _sem::semClose(sem_t* handle) {
    if(!handle) return -1; // ako nije dat handle dzabe
    while((*handle)->blockedHead->head) (*handle)->deblock(); // deblokiraj sve niti iz blocked reda
    MemoryAllocator::mem_free(handle); // obrisi handle i tjt
    return 0;
}

int _sem::semWait(sem_t* id) {
    if(!id) return -1; // ako ne postoji semafor sa kojim se radi, dzabe
    if(--((*id)->init) < 0) (*id)->block(); // standardno za sve semafore
    return 0;
}

int _sem::semSignal(sem_t* id) {
    if(!id) return -1; // ako ne postoji semafor sa kojim se radi dzabe
    if(++((*id)->init) <= 0) (*id)->deblock(); // standardno za sve semafore
    return 0;
}

void _sem::block() {
    // slicno kao dispatch, samo sto se sada menjaju i blocked stanja niti, na kraju se svakako menja kontekst
    _thread* old = _thread::running;
    old->setBlocked(true);
    blockedHead->putThread(old);
    old->setRunning(false);
    _thread::running = Scheduler::get();
    _thread::running->setRunning(true);
    _thread::contextSwitch(&old->context, &_thread::running->context);
}

void _sem::deblock() {
    // izmi nit iz reda blokiranih, oznaci je kao neblokiranu i ubaci u skedzuler
    _thread* thr = blockedHead->getThread();
    thr->setBlocked(false);
    Scheduler::put(thr);
}

_sem::_sem(unsigned int init) {
    this->init = init; // konstruktor za semafor, msm da se nigde ne koristi
    blockedHead = new Blocked();
}
