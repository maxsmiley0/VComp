#include "mosfet.h"
#include <stddef.h>

#ifndef GATES_H
#define GATES_H

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
void init_gate(gate* g, bool val);
//Logical and of two bits using mosfet
void init_and(gate* g, gate* i_1, gate* i_2);
//Logical or of two bits using mosfet
void init_or(gate* g, gate* i_1, gate* i_2);
//Logical not of one bit using mosfet
void init_not(gate* g, gate* i);
//Logical nand of two bits using mosfet
void init_nand(gate* g, gate* i_1, gate* i_2);
//Logical nor of two bits using mosfet
void init_nor(gate* g, gate* i_1, gate* i_2);
//Logical xor of two bits using mosfet
void init_xor(gate* g, gate* i_1, gate* i_2);
//Logical eqv of two bits using mosfet
void init_eqv(gate* g, gate* i_1, gate* i_2);
//Given a logic gate, updates all values of gates previous (and including self) in case of an update somewhere
void update_network(gate* g);

#endif