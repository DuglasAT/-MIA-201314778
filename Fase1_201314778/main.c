#include <stdio.h>
#include <stdlib.h>
#include "analizador.h"

int main()
{
    printf("Hello world!\n");

    printf("%d\n",letter('a'));

    char buffer [] = "GOLAE";

    verifica_minuscula(&buffer[0]);

    printf("%s\n",buffer);

    return 0;
}
