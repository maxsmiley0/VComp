#include "flipflop.h"

//2 to 1 mux (1 select line)... select false = 1, select true = 2
typedef struct {
    //Data returned
    bool bit;

    //Input to black box gates
    gate *input_1, *input_2, *select;

    //Under the hood gates
    gate select_true, select_false, not_select, combine;
} mux_2x1;

void init_mux_2x1(mux_2x1* m, gate* i_1, gate* i_2, gate* s) {
    m->input_1 = i_1;
    m->input_2 = i_2;
    m->select = s;

    init_not(&(m->not_select), m->select);
    init_and(&(m->select_false), m->input_1, &(m->not_select));
    init_and(&(m->select_true), m->input_2, m->select);
    init_or(&(m->combine), &(m->select_true), &(m->select_false));
}

void update_mux_2x1(mux_2x1* m) {
    update_network(&(m->combine));
    m->bit = m->combine.val;
}
/*
//Full adder
//The hardware should be in the struct... worry abt that later
typedef struct {
    gate *num_1, *num_2, *carry_in, *carry_out, *sum;
} full_adder;

void init_full_adder(full_adder* fa, gate* n_1, gate* n_2, gate* c_in, gate* c_out, gate* s) {
    fa->num_1 = n_1;
    fa->num_2 = n_2;
    fa->carry_in = c_in;
    fa->carry->out = c_out;
    fa->sum = s;
}

void update_full_adder(full_adder* fa) {
    update_network(&(fa->num_1));
    update_network(&(fa->num_2));
    update_network(&(fa->carry_in));


}
*/
//8 shift / parallel load register
typedef struct {

} reg_8;

/*
Good modules to have:
later subsume flipflop into modules and make a .c file
Encoder
Decide architecture now: 8-bit?
Number representation: unsigned, two's complement
Operators: +, -, *, /
Miltiplexors
Registers
Graphics display
*/