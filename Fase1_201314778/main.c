#include <stdio.h>
#include <stdlib.h>
#include "analizador.h"
#include "simulacion.h"



 int a,b,c = 0;

int main()
{

    char entrada [500];//verificar tamaño



  a=b=c=4;


   // a-= !c ? 0 : b;
    //printf("%d",a);
//change_arranque_MBR("hola","hola");//seguir pruebas
    fgets(entrada,500,stdin);
    strcat(entrada,";");//ultimo elemento- final de la entrada
    automata(&entrada[0]);


    5>4 ? a++:0;


    printf("%d",a);

  //  change_arranque_MBR("hola","/home/duglas/prueba.txt");

    return 0;
}
