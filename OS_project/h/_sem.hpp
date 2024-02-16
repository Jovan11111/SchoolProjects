#ifndef NIJEVAYNO__SEM_HPP
#define NIJEVAYNO__SEM_HPP

#include "Blocked.hpp"
#include "syscall_c.h"

class Blocked;

class _sem {
public:
    friend class _thread;

    //konstruktor koji inicijalizuje jedina polja koja imaju
    _sem(unsigned init);

    // standardne funkcije koje imaju svi semafori
    static int semOpen(sem_t** handle, unsigned init);
    static int semClose(sem_t* handle);
    static int semWait(sem_t* id);
    static int semSignal(sem_t* id);

    void block();
    void deblock();

    // polja koja treba da ima semafor, broj koji se povecava i smanjuje i lista blokiranih niti
    int init;
    Blocked* blockedHead;
};


#endif //NIJEVAYNO__SEM_HPP
