#ifndef NIJEVAYNO_SYSCALL_C_H
#define NIJEVAYNO_SYSCALL_C_H
#include "../lib/hw.h"

// PREPISANO IZ POSTAVKE PROJEKTA, ovo je skup sistemskih poziva koji
// trebaju da se naprave, trebace mozda jos koji u licne svrhe
// u odgovarajucem .cpp fajlu ja pisem svoje sistemske pozive

void* mem_alloc(size_t size); //0x01

int mem_free(void*); //0x02

class _thread;
typedef _thread* thread_t;
int thread_create(
    thread_t* handle,
    void(*start_routine)(void*),
    void* arg
); //0x11

int thread_exit(); //0x12

void thread_dispatch(); //0x13

void thread_join(
    thread_t handle
); //0x14

class _sem; //0x21
typedef _sem* sem_t;
int sem_open(
    sem_t* handle,
    unsigned init
);

int sem_close(sem_t handle); //0x22

int sem_wait(sem_t id); //0x23

int sem_signal(sem_t id); //0x24

typedef unsigned long time_t; //0x31
int time_sleep (time_t);

const int EOF = -1; //0x41
char getc();

void putc(char); //0x42

void changeUser();
//class syscall_c {};


#endif //NIJEVAYNO_SYSCALL_C_H
