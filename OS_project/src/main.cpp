#include "../lib/hw.h"
#include "../h/MemoryAllocator.h"
#include "../h/Riscv.h"
#include "../h/syscall_c.h"
#include "../lib/console.h"
#include "../h/_sem.hpp"
#include "../h/_thread.hpp"
#include "../h/syscall_cpp.hpp"
#include "../h/printing.hpp"
extern void userMain();
extern "C" void IVTP_TABLE();

// main funkcija, inicijalizuje MemAlokator, u stvec upise adresu IVTP tabele na koju treba da se ide za prekide, napravi mian thread
// i postavi main na running, prebaci se u korisnicki rezim i pozove userMain za testove

int main(){
    MemoryAllocator::init();
    Riscv::writeStvec((uint64)&IVTP_TABLE | 0x01);
    _thread::mainThread = _thread::createThread(nullptr, nullptr, nullptr);
    _thread::running = _thread::mainThread;
    changeUser();
    userMain();
    return 0;
}
