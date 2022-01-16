#include "mosfet.h"

//Virtualizes logic gates, built on transistors, to implement standard modules
//Forward declaration to resolve self reference issues
typedef struct gate gate;
struct gate {
    bool val;
    gate* input_1;
    gate* input_2;
};

//Initializes a T/F node (treated as a gate)
void init_gate(gate* g, bool val)
{
    g->val = val;
    g->input_1 = NULL;
    g->input_2 = NULL;
}

//Logical and of two bits using mosfet
void init_and(gate* g, gate* i_1, gate* i_2)
{
    vcc v;
    mosfet first;
    mosfet second;

    init_vcc(&v);
    init_nmos(&first, i_1->val, &v);
    init_nmos(&second, i_2->val, &first);

    g->val = second.high;
    g->input_1 = i_1;
    g->input_2 = i_2;
}

//Logical or of two bits using mosfet
void init_or(gate* g, gate* i_1, gate* i_2)
{
    vcc v;
    mosfet first;
    mosfet second;
    juncture j;

    init_vcc(&v);
    init_nmos(&first, i_1->val, &v);
    init_nmos(&second, i_2->val, &v);
    init_juncture(&j, &first, &second);

    g->val = j.high;
    g->input_1 = i_1;
    g->input_2 = i_2;
}

//Logical not of one bit using mosfet
void init_not(gate* g, gate* i)
{
    vcc v;
    mosfet first;
    init_vcc(&v);
    init_pmos(&first, i->val, &v);

    g->val = first.high;
    g->input_1 = i;
    g->input_2 = NULL;
}

//Logical nand of two bits using mosfet
void init_nand(gate* g, gate* i_1, gate* i_2)
{
    vcc v;
    mosfet first;
    mosfet second;
    juncture j;

    init_vcc(&v);
    init_pmos(&first, i_1->val, &v);
    init_pmos(&second, i_2->val, &v);
    init_juncture(&j, &first, &second);

    g->val = j.high;
    g->input_1 = i_1;
    g->input_2 = i_2;
}

//Logical nor of two bits using mosfet
void init_nor(gate* g, gate* i_1, gate* i_2)
{
    vcc v;
    mosfet first;
    mosfet second;

    init_vcc(&v);
    init_pmos(&first, i_1->val, &v);
    init_pmos(&second, i_2->val, &first);

    g->val = second.high;
    g->input_1 = i_1;
    g->input_2 = i_2;
}

void init_xor()
{
    
}

void init_eql()
{
    
}

//Something to update a network
