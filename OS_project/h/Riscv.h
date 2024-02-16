#ifndef NIJEVAYNO_RISCV_H
#define NIJEVAYNO_RISCV_H

#include "../lib/hw.h"
#include "MemoryAllocator.h"
#include "_thread.hpp"
#include "_sem.hpp"
#include "../lib/console.h"
#include "syscall_c.h"

#define SIP_SSIP 1 << 1 // da li postoji zahtev za softverski prekid
#define SIP_SEIP 1 << 9 // da li postoji zahtev za spoljasnji hardverski prekid
#define SSTATUS_SIE 1 << 1 // da li su dozvoljeni softverski prekidi, ne koristi se
#define SSTATUS_SPIE 1 << 5
#define SSTATUS_SPP 1 << 8 // da li su dozvoljeni spoljasnji hardverski prekidi

extern "C" void interrupt();

class Riscv {

public:
    static void interruptHandler();

    // 3 para funkcija napisanih u asembleru, svaki par radi odredjen tip prekida. U paru postoji jedna funkcija cija je adresa u IVTP tabeli,
    // i onda unutar sebe, nakon zapisivanje registrana na stek poziva drugu funkciju u paru, pa vra'a registre sa steka

    static void ecall_interrupt();

    static void timer_interrupt();

    static void console_interrupt();

    static void interrupt_ecall();

    static void interrupt_timer();

    static void interrupt_console();

    static void popSppSpie();

    static void pushRegisters(); // naguraj registre na stek

    static void popRegisters(); // vrati registre sa steka


    // nadalje su funkcije koje sam video na snimcima vezbi, vecina ih se ne koristi, al bolje da stoje tu

    // upisi u scause
    inline static void writeScause(uint64 scause) {
        asm volatile ("csrw scause, %[scause]" : : [scause] "r"(scause));
    }

    // upisi u spec
    inline static void writeSepc(uint64 sepc) {
        asm volatile ("csrw sepc, %[sepc]" : : [sepc] "r"(sepc));
    }

    // upisi u stvec
    inline static void writeStvec(uint64 stvec) {
        asm volatile ("csrw stvec, %[stvec]" : : [stvec] "r"(stvec));
    }

    // upisi u stval
    inline static void writeStval(uint64 stval) {
        asm volatile ("csrw stval, %[stval]" : : [stval] "r"(stval));
    }

    // upisi u sip
    inline static void writeSip(uint64 sip) {
        asm volatile ("csrw sip, %[sip]" : : [sip] "r"(sip));
    }

    // upisi u sstatus
    inline static void writeSstatus(uint64 sstatus) {
        asm volatile ("csrw sstatus, %[sstatus]" : : [sstatus] "r"(sstatus));
    }

    // citaj iz scause
    inline static uint64 readScause() {
        uint64 volatile scause;
        asm volatile("csrr %[scause], scause" : [scause] "=r"(scause));
        return scause;
    }

    // citaj iz sepc
    inline static uint64 readSepc() {
        uint64 volatile sepc;
        asm volatile("csrr %[sepc], sepc" : [sepc] "=r"(sepc));
        return sepc;
    }

    // citaj iz stvec
    inline static uint64 readStvec() {
        uint64 volatile stvec;
        asm volatile("csrr %[stvec], stvec" : [stvec] "=r"(stvec));
        return stvec;
    }

    // citaj iz stval
    inline static uint64 readStval() {
        uint64 volatile stval;
        asm volatile("csrr %[stval], stval" : [stval] "=r"(stval));
        return stval;
    }

    // citaj iz sip
    inline static uint64 readSip() {
        uint64 volatile sip;
        asm volatile("csrr %[sip], sip" : [sip] "=r"(sip));
        return sip;
    }

    // citaj iz sstatus
    inline static uint64 readSstatus() {
        uint64 volatile sstatus;
        asm volatile("csrr %[sstatus], sstatus" : [sstatus] "=r"(sstatus));
        return sstatus;
    }
    // NAPOMENA: ove dole funkcije nisu iste kao write...
    // jer csrc i csrs menjaju samo bitove koje treba da promene,
    // a ostali bitovi ostaju isti i to se ne dira, dok csrw menja sve

    // skidanje kojih vec bita treba da se skinu u sstatus
    inline static void maskClearStatus(uint64 mask){
        asm volatile("csrc sstatus, %[mask]" : : [mask] "r"(mask));
    }

    // postavljanje kojih vec bita treba da se postave u sstatus
    inline static void maskSetStatus(uint64 mask){
        asm volatile("csrs sstatus, %[mask]" : : [mask] "r"(mask));
    }

    // skidanje kojih vec bita treba da se skinu u Sip
    inline static void maskClearSip(uint64 mask){
        asm volatile("csrc sip, %[mask]" : : [mask] "r"(mask));
    }

    // postavljanje kojih vec bita treba da se posatve u sstatus
    inline static void maskSetSip(uint64 mask){
        asm volatile("csrs sip, %[mask]" : : [mask] "r"(mask));
    }


};


#endif //NIJEVAYNO_RISCV_H
