#ifndef NIJEVAYNO__THREAD_HPP
#define NIJEVAYNO__THREAD_HPP


#include "../lib/hw.h"
#include "Riscv.h"
#include "Scheduler.hpp"
#include "MemoryAllocator.h"

class Scheduler;

class _thread {
public:
    friend class _sem;

    struct Context{ // ovo je kontekst niti naguran u jedan struct, lakse je tako raditi
        uint64 sp;
        uint64 ra;
    };

    inline bool isFinished() const {return finished;} // getter za finished
    inline void setFinished(bool fin) {this->finished = fin;} // setter za finished
    inline bool isBlocked() const {return blocked;} // getter za blocked
    inline void setBlocked(bool blck) {this->blocked = blck;} // setter za blocked
    inline bool getMain() const {return isMain;} // getter za isMain
    inline void setMain(bool mn) {this->isMain = mn;} // setter za isMain
    inline bool getRunning() const {return isRunning;} // getter za isRunning
    inline void setRunning(bool rnng) {this->isRunning = rnng;} // setter za isRunning
    inline Context getContext() {return this->context;}

    static void dispatch(); // menja kontekst runnning niti
    static void yield(); // cuva trenutne registre, radi dispatch i onda vraca te registre
    static int exit();
    static void join(_thread* handle);
    int start(); // ubacuje nit u listu spremnih, i postavlja je na running ako treba
    static _thread* createThread(void(*fun)(void*), void*args, uint64* stack, uint64 timeSlic = DEFAULT_TIME_SLICE);

    static void threadWrapper();
    // ovo ce biti napravljeno u asembleru, treba
    // da se dobiju koneksti dve niti, da se jedan konekst sacuva a drugi ubaci i koristi nadalje
    static void contextSwitch(Context* oldCont, Context* newCont);

    inline virtual ~_thread(){MemoryAllocator::mem_free(sp);} //dealocija prostor za stek koji je zauzela nit

    static _thread* running; // staticki pokazivac na nit koja je trenutno pokrenuta
    static _thread* mainThread; // staticki pokazivac na nit koja radi nad funkcijom main()

    // konstrukor za _thread klasu
    _thread(void (*pFunction)(void *), void *args, uint64* stack, uint64 timeSlic = DEFAULT_TIME_SLICE) {
        // postavljanje argumenata na standardne vrednosti
        function = pFunction;
        this->args = args;
        blocked = false;
        finished = false;
        timeSlice = timeSlic;

        // postavljanje steka ima smisla samo ako je nit dobila koju funkciju treba da radi
        if(function) sp = new uint64[DEFAULT_STACK_SIZE] ;
        else sp = nullptr;

        // postavljanje konteksta, sp se stavlja na pocetak (kraj) steka, a ra na . Ima smisla samo ako je nit dobila funkciju koju treba da radi
        if(function) context = {(uint64) &sp[DEFAULT_STACK_SIZE], (uint64) &threadWrapper};
        else context = {0, 0};

        // nit je sredjena i spremna da se ubaci u skedzuler
        //if(function) Scheduler::put(this);
        this->start();
    }
protected:
    void(*function) (void*); // funkcija nad kojom nit radi
    void* args; // argumenti koje funkcija dobija
    uint64 timeSlice; // vreme koje nt dobija da radi sta treba
    uint64* sp; // velicina steka koju nit koristi
    Context context; // kontekst niti, onaj struct gore
    bool finished; // govori dal je nit zavrsila
    bool blocked; // govori dal je nit blokirana
    bool isMain; // govori da li je nit mainThread
    bool isRunning; // govori da li je nit running

};



#endif //NIJEVAYNO__THREAD_HPP
