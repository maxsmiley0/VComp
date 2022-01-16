#include <stdio.h>
#include "gates.h"

int main()
{
    //And gate
    bool x = false;
    bool y = false;

    vcc v;
    mosfet m1;
    mosfet m2;

    init_vcc(&v);
    init_nmos(&m1, x, &v);
    init_nmos(&m2, y, &m1);

    //or gate
    vcc v1;
    vcc v2;

    mosfet n1;
    mosfet n2;

    juncture j;

    init_vcc(&v1);
    init_vcc(&v2);
    init_nmos(&n1, x, &v1);
    init_nmos(&n2, y, &v2);
    init_juncture(&j, &n1, &n2);

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

    printf("%d\n", jp.high);
}