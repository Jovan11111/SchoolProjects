#include "../h/_thread.hpp"

// inicijalizacija statickih polja
_thread* _thread::running = nullptr;
_thread* _thread::mainThread = nullptr;

// standardan dispatch, sacuva se stara, ako ima potrebe, vrati se u skedzuler, uzme se nova,
// nova se postavi na onu koja se sad radi, i zamene im se konteksti
void _thread::dispatch() {
    _thread* old = _thread::running;
    if(!(old->isFinished() || old->isBlocked())) Scheduler::put(old);
    _thread* newt = Scheduler::get();
    old->setRunning(false);
    _thread::running = newt;
    newt->setRunning(true);
    _thread::contextSwitch(&old->context, &newt->context);
}

// posto pratim finished stanja niti, mogu da uradim samo sistemski poziv za dispatch
void _thread::yield() {
    thread_dispatch();
}

// ne moze da se uradi exit na mainThread. Postavi se runnning na finished, i onda se dispecuje, i oslobodi se memorija
// koju je zauzimala stara nit
int _thread::exit() {
    if(_thread::running == _thread::mainThread) return -1;
    _thread::running->setFinished(true);
    _thread::dispatch();
    //MemoryAllocator::mem_free(running->sp);
    return 0;
}

void _thread::threadWrapper() {
    Riscv::popSppSpie();
    changeUser(); // idi u korisnicki rezim
    running->function(running->args); // pozovi funkciju niti sa odgovarajucim argumentima
    running->setFinished(true); // kad zavrsis funkcjiu onda je i nit zavrsena
    _thread::yield(); // izbaci je
}

// ako nista trenutno nije running, onda postavi ovu nit kao runnning, i onda je ubaci u skedzuler ako ima dodeljenu fju koju treba da radi
int _thread::start() {
    if(!_thread::running) {
        _thread::running = this;
        this->setRunning(true);
    }
    if(this->function) Scheduler::put(this);
    return 0;
}

// vraca nit koja je spremna za koriscenje
_thread* _thread::createThread(void (*fun)(void *), void* args, uint64* stack, uint64 timeSlic) {
    return new _thread(fun, args, stack);
}

// dok se nit koja je pozvala ne zavrsi menjaj niti
void _thread::join(_thread* handle) {
    while(handle->isFinished()) dispatch();
}
