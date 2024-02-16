#include "../h/syscall_cpp.hpp"

// mesto gde su definisani sistemski pozivi za CPP API. Maltene nista ne rade, samo pozivaju odgovarajuce funkcije
// koje su napisane u syscall_c.cpp

void* operator new(size_t size) {
    return mem_alloc(size);
}

void* operator new[](size_t size){
    return mem_alloc(size);
}

void operator delete(void *ptr) {
    mem_free(ptr);
}

void operator delete[](void* ptr) {
    mem_free(ptr);
}

Thread::Thread(void (*body)(void *), void *arg) {
    thread_create(&myHandle, body, arg);
}

Thread::~Thread() {
    delete myHandle;
}

int Thread::start() {
    if(myHandle) return 0;
    thread_create(&myHandle, &runWrapper, this);
    return 0;
}

void Thread::join() {
    thread_join(myHandle);
}

void Thread::dispatch() {
    thread_dispatch();
}

int Thread::sleep(time_t) {
    return 0;
}

Thread::Thread() {
    this->myHandle = nullptr;
    this->body = nullptr;
    this->arg = nullptr;
}

void Thread::runWrapper(void *thread) {
    if(!thread) return;
    ((Thread*)thread)->run();
}

Semaphore::Semaphore(unsigned int init) {
    sem_open(&myHandle, init);
}

Semaphore::~Semaphore() {
    sem_close(myHandle);
}

int Semaphore::wait() {
    return sem_wait(myHandle);
}

int Semaphore::signal() {
    return sem_signal(myHandle);
}

void PeriodicThread::terminate() {}

PeriodicThread::PeriodicThread(time_t period) {}

char Console::getc() {
    return __getc();
}

void Console::putc(char c) {
    __putc(c);
}
