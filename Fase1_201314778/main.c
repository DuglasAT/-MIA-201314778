#include <stdio.h>
#include <stdlib.h>
#include "analizador.h"

int main()
{

    char entrada [500];



    fgets(entrada,500,stdin);
    automata(&entrada[0]);

    return 0;
}
