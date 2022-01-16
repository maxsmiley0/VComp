#include <stdbool.h>
#include <stdio.h>

typedef struct {
    bool high;
    void* prev;
    void* next;
} mosfet;

typedef struct {
    bool high;
    void* next;
} vcc;

typedef struct {
    bool high;
    void* prev_1;
    void* prev_2;
    void* next;
} juncture;

void init_nmos(mosfet* m, bool h, void* p, void* n)
{
    m->prev = p; 
    m->high = (((mosfet*)p)->high & h);
    m->next = n;
}

void init_pmos(mosfet* m, bool h, void* p, void* n)
{
    m->prev = p; 
    m->high =  ~(((mosfet*)p)->high & h) & 1;
    m->next = n;
}

void init_vcc(vcc* v, void* n)
{
    v->high = true;
    v->next = n;
}

void init_juncture(juncture* j, void* p1, void* p2, void* n)
{
    j->prev_1 = p1;
    j->prev_2 = p2;
    j->high = ((mosfet*)j->prev_1)->high | ((mosfet*)j->prev_2)->high;
    j->next = n;
}