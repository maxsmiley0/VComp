#include <stdbool.h>

#ifndef MOSFET_H
#define MOSFET_H

//Virtualizes mosfet transistors, used to implement logic gates

//Can either be PMOS or NMOS depending on initialization
typedef struct {
    bool high;
    void* input;
} mosfet;

//Voltage source for our transistors to pull from
typedef struct {
    bool high;
} vcc;

//Specifies behavior upon wire crossing
typedef struct {
    bool high;
    void* input_1;
    void* input_2;
} juncture;

//NMOS - essentially stores the voltage value given (as field high)
void init_nmos(mosfet* m, bool h, void* i);
//PMOS - essentially inverts the voltage value given (as field high)
void init_pmos(mosfet* m, bool h, void* i);
//Initializes voltage source as high
void init_vcc(vcc* v);
//Given two input wires, specifies the voltage value
void init_juncture(juncture* j, void* i_1, void* i_2);

#endif