#include "../h/Riscv.h"
#include "../h/printing.hpp"

// program dolazi ovde kad se pozove sistemski poziv ili kada se desi bilo kakav prekid

void Riscv::popSppSpie() { // u sepc upisi ra, postavi SPP bit status registra na 1 i vrati se iz kernel rezima
    asm volatile("csrw sepc, ra");
    maskSetStatus(SSTATUS_SPP);
    asm volatile("sret");
}

void Riscv::ecall_interrupt() { // funkcija za ecall prekide, na osnovu koda poziva odgovarajucu funkciju
    if(readScause() == 0x02){ // scause je 2 ako je prekid zbog ilegalne instrukcije
        printString("Ilegalna instrukcija, program se ne zavrsava!");
        while(1);
    }
    uint64 Code;
    asm volatile("mv %0, a0" : "=r" (Code)); // u Code upisi kod koji je sys poziv potrebno uraditi
    uint64 sepc =  readSepc() + 4;
    uint64 sstatus = readSstatus();
    switch (Code) {
        case 0x01UL: { // mem_alloc
            size_t size;
            asm volatile("mv %0, a1" : "=r" (size)); // u size upisi a1, jedini argument
            void* ret = MemoryAllocator::mem_alloc(size); // uradi alokaciju memorije
            asm volatile ("mv a0, %0" : : "r" (ret)); //u a0 upisi povratnu vrednost
            break;
        }

        case 0x02UL: { // mem_free
            void* ptr;
            asm volatile("mv %0, a1" : "=r" (ptr)); // u ptr upisi a0, jedini argument
            int ret = MemoryAllocator::mem_free(ptr); // uradi oslobadjanje memorije
            asm volatile ("mv a0, %0" : : "r" (ret)); // u a0 upisi povratnu vrednost
            break;
        }

        case 0x11UL:{ // thread_create
            thread_t *handle;
            void(*fun)(void*);
            void* arg;
            uint64* stack = nullptr;
            //uint64 * stack = new uint64[DEFAULT_STACK_SIZE];
            asm volatile("mv %0, a1" : "=r" (handle)); // u handle prvi argument
            asm volatile("mv %0, a2" : "=r" (fun)); // u fun drugi argument
            asm volatile("mv %0, a3" : "=r" (arg)); // u arg treci argument
            *handle = _thread::createThread(fun, arg, stack);
            asm volatile("mv a0, %0" : : "r" (handle)); // u a0 povratnu vrednost
            break;
        }

        case 0x12UL: { // thread_exit
            int ret = _thread::exit(); // exitu ne trebaju nikakvi argumenti
            asm volatile ("mv a0, %0" : : "r" (ret)); // u a0 upisi povratnu vrednost
            break;
        }

        case 0x13UL: { // thread_dispatch
            _thread::dispatch(); // nema ni argumenata ni povratne vrednosti
            break;
        }

        case 0x14UL: { // thread_join
            thread_t handle;
            asm volatile("mv %0, a1" : "=r" (handle)); // u handle upisi a1, jedini argument
            _thread::join(handle); // nema povratne vrednosti
            break;
        }

        case 0x21UL: { // sem_open
            uint64 handle = 0;
            asm volatile("mv %0, a1" : "=r" (handle)); // u handle upisi a1
            sem_t** handlee = (sem_t**) handle;
            unsigned init;
            asm volatile("mv %0, a2" : "=r" (init)); // u init upisi a2
            int ret = _sem::semOpen(handlee, init);
            asm volatile("mv a0, %0" : : "r" (ret)); // u a0 upisi povratnu vrednost
            break;
        }

        case 0x22UL: { // sem_close
            uint64 handle;
            asm volatile("mv %0, a1" : "=r" (handle)); // u handle upisi a1, jeidni argument
            sem_t* handlee = (sem_t*)handle;
            int ret = _sem::semClose(handlee);
            asm volatile("mv a0, %0" : : "r" (ret)); // u a0 upisi povratnu vrednost
            break;
        }

        case 0x23UL: { // sem_wait
            uint64 id;
            asm volatile("mv %0, a1" : "=r" (id)); // u id upisi a1
            sem_t* idd = (sem_t*)id;
            int ret = _sem::semWait(idd);
            asm volatile("mv a0, %0" : : "r" (ret)); // u a0 upisi povrratnu vrednost
            break;
        }

        case 0x24UL: { // sem_signal
            uint64 id;
            asm volatile("mv %0, a1" : "=r" (id)); // u id upisi a1
            sem_t* idd = (sem_t*)id;
            int ret = _sem::semSignal(idd);
            asm volatile("mv a0, %0" : : "r" (ret)); // u a0 upisi povratnu vrednost
            break;
        }

        case 0x31UL: { // time_sleep
            break; // nisam napravio
        }

        case 0x41UL: { // getc
            char ret = __getc(); // nije moja funkcija, samo se poziva ovde
            asm volatile("mv a0, %0" : : "r" (ret)); // u a0 upisi povratnu vrednost
            break;
        }

        case 0x42UL: { // putc
            char c;
            asm volatile("mv %0, a1" : "=r" (c)); // u c upisi argument
            __putc(c); // nije moja funkcija, samo se poziva ovde
            break;
        }
        case 0x74UL: { // moj sistemski poziv za menjanje rezima, u 8. bit status registra se upise 0.
                       // Na osnovu 8. bita statusa se odredjuje rezim u koji program treba da se vrati nakon sret
            sstatus = sstatus & (0xFFFFFFFFFFFFFEFFUL);
            break;
        }
        default:
            maskClearSip(SIP_SSIP);
            break;
    }
    maskClearSip(SIP_SSIP);
    Riscv::writeSstatus(sstatus);
    Riscv::writeSepc(sepc);
}

void Riscv::timer_interrupt() { // funkcija za timer prekide, maltene u sepc samo upise sledecu instrukciju i stavi 0 na prvi bit SIP regitra
    uint64 sepc =  readSepc()+4;
    uint64 sstatus = readSstatus();
    maskClearSip(SIP_SSIP);
    Riscv::writeSstatus(sstatus);
    Riscv::writeSepc(sepc);
}

void Riscv::console_interrupt() { // funkcija za console prekdide, upise nula u SEIP bit SIP registra i pozove neku funkciju koju nisam ja pisao
    maskClearSip(SIP_SEIP);
    console_handler();
}
