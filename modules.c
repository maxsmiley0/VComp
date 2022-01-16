#include "modules.h"

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