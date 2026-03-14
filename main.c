#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "listeDouble.h"

int main()
{
    T_liste l1;
    l1 = listeRandN(10);

    tri_selection_liste(l1);
    return 0;
}
