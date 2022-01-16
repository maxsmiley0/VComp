#include "mosfet.h"

void init_nmos(mosfet* m, bool h, void* i)
{
    m->input = i; 
    m->high = (((mosfet*)i)->high & h);
}

void init_pmos(mosfet* m, bool h, void* i)
{
    m->input = i; 
    m->high =  ((mosfet*)i)->high & ~h;
}

void init_vcc(vcc* v)
{
    v->high = true;
}

void init_juncture(juncture* j, void* i_1, void* i_2)
{
    j->input_1 = i_1;
    j->input_2 = i_2;
    j->high = ((mosfet*)j->input_1)->high | ((mosfet*)j->input_2)->high;
}