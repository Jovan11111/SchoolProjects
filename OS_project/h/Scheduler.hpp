#ifndef NIJEVAYNO_SCHEDULER_HPP
#define NIJEVAYNO_SCHEDULER_HPP

#include "_thread.hpp"

class _thread;

class Scheduler {
public:
    struct Node{ //struktura koju koristim kao Node u ulancanoj listi
        _thread* data;
        Node* next;
    };

    static _thread* get(); // izbacuje jednu nit iz liste spremnih i daje je kao povratnu vrednost
    static void put(_thread* thread); // stavlja nit u listu spremnih
    static Node* head; // static pokazivac na pocetak liste
};


#endif //NIJEVAYNO_SCHEDULER_HPP
