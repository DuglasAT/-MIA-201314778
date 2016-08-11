#include <stdio.h>
#include <stdlib.h>
#include "analizador.h"
#include "simulacion.h"




int main()
{

    char entrada [30000];//verificar tamaño


   // a-= !c ? 0 : b;
    //printf("%d",a);
//change_arranque_MBR("hola","hola");//seguir pruebas
    fgets(entrada,30000,stdin);
    strcat(entrada,";");//ultimo elemento- final de la entrada
    automata(&entrada[0]);

//asignar_arranque_mbr(100,"home/duglas/prueba.bin");

  //  change_arranque_MBR("hola","/home/duglas/prueba.txt");

    return 0;
}
