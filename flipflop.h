#include "gates.h"

//Virtualizes flip flops, using logic gates, to implement registers

typedef struct {
    //Stored data
    bool bit;

    //Synchronous part
    gate D, D_inv, sync_1, sync_2, clk;

    //Latch part - latch_1.val := stored bit, latch_2.val := ~stored bit
    gate latch_1, latch_2;

} d_flipflop;

typedef struct {
    //Stored data
    bool bit;

    //Synchronous part (sync_a_b refers to the bth series gate in the ath row - necessary for 3-fold logical operations)
    gate J, K, clk, sync_1_1, sync_1_2, sync_2_1, sync_2_2;

    //Latch part - latch_1.val := stored bit, latch_2.val := ~stored bit
    gate latch_1, latch_2;

} jk_flipflop;

void init_df(d_flipflop* df)
{
    //Sets up synchronized layer
    init_gate(&(df->D), false);
    init_gate(&(df->clk), true);
    init_not(&(df->D_inv), &(df->D));
    init_nand(&(df->sync_1), &(df->D), &(df->clk));
    init_nand(&(df->sync_2), &(df->D_inv), &(df->clk));
    
    //Sets up latch layer
    init_nand(&(df->latch_2), &(df->sync_2), &(df->latch_1));
    init_nand(&(df->latch_1), &(df->sync_1), &(df->latch_2));
    init_nand(&(df->latch_2), &(df->sync_2), &(df->latch_1));

    df->bit = df->latch_1.val;
}

void clock_df(d_flipflop* df, bool d_val) {
    //Updates synchronized layer
    init_gate(&(df->D), d_val);
    update_network(&(df->sync_1));
    update_network(&(df->sync_2));

    //Updates latch layer
    init_nand(&(df->latch_2), &(df->sync_2), &(df->latch_1));
    init_nand(&(df->latch_1), &(df->sync_1), &(df->latch_2));
    init_nand(&(df->latch_2), &(df->sync_2), &(df->latch_1));

    df->bit = df->latch_1.val;
}

void init_jkf(jk_flipflop* jkf) {
    //Sets up synchronized layer
    jkf->latch_1.val = true;
    jkf->latch_2.val = false;
    init_gate(&(jkf->J), false);
    init_gate(&(jkf->K), false);
    init_gate(&(jkf->clk), true);
    init_and(&(jkf->sync_1_1), &(jkf->clk), &(jkf->J));
    init_nand(&(jkf->sync_1_2), &(jkf->sync_1_1), &(jkf->latch_2));
    init_and(&(jkf->sync_2_1), &(jkf->clk), &(jkf->K));
    init_nand(&(jkf->sync_2_2), &(jkf->sync_2_1), &(jkf->latch_1));

    //Sets up latch layer
    init_nand(&(jkf->latch_1), &(jkf->latch_2), &(jkf->sync_1_2));
    init_nand(&(jkf->latch_2), &(jkf->latch_1), &(jkf->sync_2_2));
    init_nand(&(jkf->latch_1), &(jkf->latch_2), &(jkf->sync_1_2));

    jkf->bit = jkf->latch_1.val;
}

void clock_jkf(jk_flipflop* jkf, bool j_val, bool k_val) {
    //Updates synchronized layer
    init_gate(&(jkf->J), j_val);
    init_gate(&(jkf->K), k_val);
    init_and(&(jkf->sync_1_1), &(jkf->clk), &(jkf->J));
    init_nand(&(jkf->sync_1_2), &(jkf->sync_1_1), &(jkf->latch_2));
    init_and(&(jkf->sync_2_1), &(jkf->clk), &(jkf->K));
    init_nand(&(jkf->sync_2_2), &(jkf->sync_2_1), &(jkf->latch_1));

    //Updates latch layer
    init_nand(&(jkf->latch_1), &(jkf->latch_2), &(jkf->sync_1_2));
    init_nand(&(jkf->latch_2), &(jkf->latch_1), &(jkf->sync_2_2));
    init_nand(&(jkf->latch_1), &(jkf->latch_2), &(jkf->sync_1_2));

    jkf->bit = jkf->latch_1.val;
}