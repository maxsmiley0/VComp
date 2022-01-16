#include <stdio.h>
#include "flipflop.h"

int main()
{
    d_flipflop df;
    init_df(&df);
    clock_df(&df, true);

    printf("%d\n", df.latch_1.val);
}