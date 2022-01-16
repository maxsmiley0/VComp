#include <stdbool.h>

//Can either be PMOS or NMOS depending on initialization
typedef struct {
    bool high;
    void* prev;
    void* next;
} mosfet;

//Voltage source for our transistors to pull from
typedef struct {
    bool high;
    void* next;
} vcc;

//Specifies behavior upon wire crossing
typedef struct {
    bool high;
    void* prev_1;
    void* prev_2;
    void* next;
} juncture;

//NMOS - essentially stores the voltage value given (as field high)
void init_nmos(mosfet* m, bool h, void* p, void* n)
{
    m->prev = p; 
    m->high = (((mosfet*)p)->high & h);
    m->next = n;
}

//PMOS - essentially inverts the voltage value given (as field high)
void init_pmos(mosfet* m, bool h, void* p, void* n)
{
    m->prev = p; 
    m->high =  ~(((mosfet*)p)->high & h) & 1;
    m->next = n;
}

//Initializes voltage source as high
void init_vcc(vcc* v, void* n)
{
    v->high = true;
    v->next = n;
}

//Given two input wires, specifies the voltage value
void init_juncture(juncture* j, void* p1, void* p2, void* n)
{
    j->prev_1 = p1;
    j->prev_2 = p2;
    j->high = ((mosfet*)j->prev_1)->high | ((mosfet*)j->prev_2)->high;
    j->next = n;
}