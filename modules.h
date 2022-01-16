#include "gates.h"

#ifndef MODULES_H
#define MODULES_H

//Creates standard modules from logic gates

//2 to 1 mux (1 select line)... select false = 1, select true = 2
typedef struct {
    //Data returned
    bool bit;

    //Input to black box gates
    gate *input_1, *input_2, *select;

    //Under the hood gates
    gate select_true, select_false, not_select, combine;
} mux_2x1;

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

//D flip flop - read from referencing bit, and write by clocking the flip flop with a given d value
typedef struct {
    //Stored data
    bool bit;

    //Synchronous part
    gate D, D_inv, sync_1, sync_2, clk;

    //Latch part - latch_1.val := stored bit, latch_2.val := ~stored bit
    gate latch_1, latch_2;

} d_flipflop;

//JK flip flop - read from referencing bit, and set / reset bit with given values for j and k
typedef struct {
    //Stored data
    bool bit;

    //Synchronous part (sync_a_b refers to the bth series gate in the ath row - necessary for 3-fold logical operations)
    gate J, K, clk, sync_1_1, sync_1_2, sync_2_1, sync_2_2;

    //Latch part - latch_1.val := stored bit, latch_2.val := ~stored bit
    gate latch_1, latch_2;

} jk_flipflop;

void init_mux_2x1(mux_2x1* m, gate* i_1, gate* i_2, gate* s);
void update_mux_2x1(mux_2x1* m);
void init_df(d_flipflop* df);
void clock_df(d_flipflop* df, bool d_val);
void init_jkf(jk_flipflop* jkf);
void clock_jkf(jk_flipflop* jkf, bool j_val, bool k_val);

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

#endif