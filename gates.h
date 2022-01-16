#include "mosfet.h"

//Virtualizes logic gates, built on transistors, to implement standard modules
//Forward declaration to resolve self reference issues
typedef struct gate gate;
struct gate {
    bool val;
    char* type;
    gate* input_1;
    gate* input_2;
};

//Initializes a T/F node (treated as a gate)
void init_gate(gate* g, bool val)
{
    g->val = val;
    g->type = "node";
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
    g->type = "and";
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
    g->type = "or";
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
    g->type = "not";
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
    g->type = "nand";
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
    g->type = "nor";
    g->input_1 = i_1;
    g->input_2 = i_2;
}

//Logical xor of two bits using mosfet
void init_xor(gate* g, gate* i_1, gate* i_2)
{
    vcc v;
    mosfet up_left;
    mosfet up_right;
    mosfet down_left;
    mosfet down_right;
    juncture j;

    init_vcc(&v);
    init_nmos(&up_left, i_1->val, &v);
    init_pmos(&up_right, i_2->val, &up_left);
    init_pmos(&down_left, i_1->val, &v);
    init_nmos(&down_right, i_2->val, &down_left);
    init_juncture(&j, &up_right, &down_right);

    g->val = j.high;
    g->type = "xor";
    g->input_1 = i_1;
    g->input_2 = i_2;
}

//Logical eqv of two bits using mosfet
void init_eqv(gate* g, gate* i_1, gate* i_2)
{
    vcc v;
    mosfet up_left;
    mosfet up_right;
    mosfet down_left;
    mosfet down_right;
    juncture j;

    init_vcc(&v);
    init_nmos(&up_left, i_1->val, &v);
    init_nmos(&up_right, i_2->val, &up_left);
    init_pmos(&down_left, i_1->val, &v);
    init_pmos(&down_right, i_2->val, &down_left);
    init_juncture(&j, &up_right, &down_right);

    g->val = j.high;
    g->type = "eqv";
    g->input_1 = i_1;
    g->input_2 = i_2;
}

//Given a logic gate, updates all values of gates previous (and including self) in case of an update somewhere
void update_network(gate* g)
{
    if (g->type == "and")
    {
        update_network(g->input_1);
        update_network(g->input_2);
        init_and(g, g->input_1, g->input_2);
    }
    else if (g->type == "or")
    {
        update_network(g->input_1);
        update_network(g->input_2);
        init_or(g, g->input_1, g->input_2);
    }
    else if (g->type == "not")
    {
        update_network(g->input_1);
        init_not(g, g->input_1);
    }
    else if (g->type == "nand")
    {
        update_network(g->input_1);
        update_network(g->input_2);
        init_nand(g, g->input_1, g->input_2);
    }
    else if (g->type == "nor")
    {
        update_network(g->input_1);
        update_network(g->input_2);
        init_nor(g, g->input_1, g->input_2);
    }
    else if (g->type == "xor")
    {
        update_network(g->input_1);
        update_network(g->input_2);
        init_xor(g, g->input_1, g->input_2);
    }
    else if (g->type == "eqv")
    {
        update_network(g->input_1);
        update_network(g->input_2);
        init_eqv(g, g->input_1, g->input_2);
    }
}
