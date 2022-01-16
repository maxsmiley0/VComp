#include "gates.h"

typedef struct {
    //Synchronous part
    gate D, D_inv, sync_1, sync_2, clk;

    //Latch part - latch_1.val := stored bit, latch_2.val := ~stored bit
    gate latch_1, latch_2;

} d_flipflop;

typedef struct {
    int x;
} jk_flipflop;

void init_df(d_flipflop* df)
{
    init_gate(&(df->D), false);
    init_gate(&(df->clk), true);
    init_not(&(df->D_inv), &(df->D));
    init_nand(&(df->sync_1), &(df->D), &(df->clk));
    init_nand(&(df->sync_2), &(df->D_inv), &(df->clk));
    
    init_nand(&(df->latch_2), &(df->sync_2), &(df->latch_1));
    init_nand(&(df->latch_1), &(df->sync_1), &(df->latch_2));
    init_nand(&(df->latch_2), &(df->sync_2), &(df->latch_1));
}

void clock_df(d_flipflop* df, bool d_val) {
    init_gate(&(df->D), d_val);
    update_network(&(df->sync_1));
    update_network(&(df->sync_2));
    
    init_nand(&(df->latch_2), &(df->sync_2), &(df->latch_1));
    init_nand(&(df->latch_1), &(df->sync_1), &(df->latch_2));
    init_nand(&(df->latch_2), &(df->sync_2), &(df->latch_1));
}

void clock_jkf(jk_flipflop* jkf) {

}