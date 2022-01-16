#include <stdio.h>
#include "gates.h"

int main()
{
    gate x, y, z, f, g;
    init_gate(&x, false);
    init_gate(&y, true);
    init_gate(&z, false);

    init_xor(&f, &x, &y);
    init_eqv(&g, &f, &z);

    x.val = true;
    update_network(&g);
    printf("%d\n", g.val);
}