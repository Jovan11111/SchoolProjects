#include "../lib/hw.h"
#include "../h/syscall_c.h"

// mesto gde su definisani svi sistemski pozivi, svi rade isto, upisu sta treba u koje vec treba registre
// onda pozovu ecall i cekaju povratnu vrednost ako treba nest da vrate

void* mem_alloc(size_t size){
    asm volatile("mv a1, %0" : : "r" (size)); // u a1 size, jedini argument
    asm volatile("li a0, 0x01"); // u a0 upisi kod za ovaj sistemski poziv
    asm volatile("ecall"); // predji u kernel rezim, pozovi sistemski poziv
    uint64 ret = 0;
    asm volatile("mv %0, a0" : "=r" (ret)); // u ret upisi povratnu vrednost
    return (void*)ret;
}

int mem_free(void* ptr){
    asm volatile("mv a1, %0" : : "r" (ptr)); // u a1 ptr, jedini argument
    asm volatile("li a0, 0x02"); // u a0 upisi kod za ovaj sistemski poziv
    asm volatile("ecall"); // predji u kernel rezim, pozovi sistemski poziv
    int ret;
    asm volatile("mv %0, a0" : "=r" (ret)); // u ret upisi povratnu vrednost
    return ret;
}

int thread_create(thread_t* handle, void(*start_routine)(void*), void*arg){
    asm volatile("mv a3, %0" : : "r" (arg)); // u a3 treci argument
    asm volatile("mv a2, %0" : : "r" (start_routine)); // u a2 drugi argument
    asm volatile("mv a1, %0" : : "r" (handle)); // i a1 prvi argument
    asm volatile("li a0, 0x11"); // u a0 ide kod operacije
    asm volatile("ecall"); // predji u kernel rezim, pozovi sistemski poziv
    int ret;
    asm volatile("mv %0, a0" : "=r" (ret)); // u ret upisi povratnu vrednsot
    return ret;
}

int thread_exit(){
    int ret;
    asm volatile("li a0, 0x12"); // u a0 upisi kod operacije
    asm volatile("ecall"); // predji u kernel rezim, pozovi sistemski poziv
    asm volatile("mv %0, a0" : "=r" (ret)); // u ret ide povratna vrednsot
    return ret;
}

void thread_dispatch(){
    asm volatile("li a0, 0x13"); // u a0 upisi kod operacije
    asm volatile("ecall"); // predji u kernel rezim, pozovi sistemski poziv;
    // to je to, nema povratne vrednosti
}

void thread_join(thread_t handle) {
    asm volatile("li a0, 0x14"); // u a0 upisi kod opercaije
    asm volatile("mv a1, %0" : : "r" (handle)); // u a1 upisi jedini argument
    asm volatile("ecall"); // predji u kernel rezim, pozovi sistemski poziv
    // to je to, nema povratne vrednosti
}

int sem_open(sem_t* handle, unsigned init) {
    asm volatile("mv a2, %0" : : "r" (init)); // u a2 upisi drugi argument
    asm volatile("mv a1, %0" : : "r" (handle)); // u a1 upisi prvi argument
    asm volatile("li a0, 0x21"); // u a0 upisi kod operacije
    asm volatile("ecall"); // predji u kernel rezim, pozovi sistemski poziv
    int ret;
    asm volatile("mv %0, a0" : "=r" (ret)); // u ret upisi povratnu vrednsot
    return ret;
}

int sem_close(sem_t handle) {
    asm volatile("mv a1, %0" : : "r" (handle)); // u a1 upisi jedini argument
    asm volatile("li a0, 0x22"); // u a0 upisi kod operacije
    asm volatile("ecall"); // predji u kernel rezim, pozovi sistemski poziv
    int ret;
    asm volatile("mv %0, a0" : "=r" (ret)); // u ret upisi povratnu vrednsot
    return ret;
}

int sem_wait(sem_t id) {
    asm volatile("mv a1, %0" : : "r" (id)); // u a1 upisi jedini argument
    asm volatile("li a0, 0x23"); // u a0 upisi kod operacije
    asm volatile("ecall"); // predji u kernel rezim, pozovi sistemski poziv
    int ret;
    asm volatile("mv %0, a0" : "=r" (ret)); // u ret upisi povratnu vrednsot
    return ret;
}

int sem_signal(sem_t id) {
    asm volatile("mv a1, %0" : : "r" (id)); // u a1 upisi jedini argument
    asm volatile("li a0, 0x24"); // u a0 upisi kod operacije
    asm volatile("ecall"); // predji u kernel rezim, pozovi sistemski poziv
    int ret;
    asm volatile("mv %0, a0" : "=r" (ret)); // u ret upisi povratnu vrednsot
    return ret;
}

void changeUser() {
    asm volatile("li a0, 0x74"); // u a0 upisi kod oepracije
    asm volatile("ecall");
    // nema povratne vrednosti
}

char getc() {
    asm volatile("li a0, 0x41"); // u a0 ide kod operacije
    asm volatile("ecall");
    uint64 ret;
    asm volatile("mv %0, a0" : "=r" (ret)); // u ret ide povratna vrednost
    return ret;
}

void putc(char c){
    asm volatile("mv a1, %0" : : "r" ((uint64)c)); // u a1 ide jedini argument
    asm volatile("li a0, 0x42"); // u a0 ide kod operacije
    asm volatile("ecall");
    // nema povratne vrednosti
}

int time_sleep(time_t){
    return 0; // nisam napravio
}


