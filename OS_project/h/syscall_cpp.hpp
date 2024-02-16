#ifndef NIJEVAYNO_SYSCALL_CPP_HPP
#define NIJEVAYNO_SYSCALL_CPP_HPP

#include "syscall_c.h"
#include "MemoryAllocator.h"
#include "_thread.hpp"
#include "_sem.hpp"
#include "../lib/console.h"

// prepisano iz postavke projekta, predstavlja klase unutar kojih su funkcije koje treba definisati
// postoji jedna razlika u odnosu na ono sto je napisano u postavci

void* operator new (size_t);
void operator delete (void*);

class Thread{
public:
    Thread (void (*body)(void*), void*arg);
    virtual ~Thread();

    int start();

    void join();

    static void dispatch();

    static int sleep(time_t);

protected:
    Thread();
    virtual void run() {}

private:
    thread_t myHandle;
    void (*body)(void*); void* arg;
    static void runWrapper(void* thread); // dodat je privatan clan koji samo sluzi kao vraper za run, nista zanimljivo al nisam video drugi nacin
                                          // da napravim start
};

class Semaphore{
public:

    Semaphore(unsigned init = 1);
    virtual ~Semaphore();

    int wait();
    int signal();

private:
    sem_t  myHandle;
};

class PeriodicThread : public Thread{
public:
    void terminate();

protected:
    PeriodicThread(time_t period);
    virtual void periodicActivation() {}

private:
    time_t period;
};

class Console{
public:
    static char getc();
    static void putc(char);
};
//class syscall_cpp {};


#endif //NIJEVAYNO_SYSCALL_CPP_HPP
