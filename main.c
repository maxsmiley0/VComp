#include <stdio.h>
#include "modules.h"

int main()
{
    
    gate x, y, z;
    init_gate(&x, false);
    init_gate(&y, false);
    init_gate(&z, false);

    mux_2x1 m;
    init_mux_2x1(&m, &x, &y, &z);
    
    init_gate(&x, true);
    init_gate(&z, true);
    update_mux_2x1(&m);


    printf("%d\n", m.bit);
}