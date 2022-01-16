#include <stdio.h>
#include "gates.h"

int main()
{
    /*
    //inverter
    vcc s;
    mosfet n;
    init_vcc(&s);
    init_pmos(&n, x, &s);

    //xor (x and not y) or (not x and y)
    vcc o1;
    vcc o2;
    mosfet r1;
    mosfet r2;
    mosfet r3;
    mosfet r4;
    juncture jp;
    init_vcc(&o1);
    init_nmos(&r1, x, &o1);
    init_pmos(&r2, y, &r1);
    init_pmos(&r3, x, &o1);
    init_nmos(&r4, y, &r3);
    init_juncture(&jp, &r2, &r4);

*/
    gate x, y, g;
    init_gate(&x, false);
    init_gate(&y, true);

    init_nand(&g, &x, &y);
    printf("%d\n", g.val);
}