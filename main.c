#include <stdio.h>
#include "flipflop.h"

int main()
{
    d_flipflop df;
    init_df(&df);
    clock_df(&df, true);
    clock_df(&df, false);

    printf("%d\n", df.bit);
}