#include <stdio.h>
#include <stdlib.h>
#include "analizador.h"



typedef struct part //estructura para la partición
{
    char part_status;
    char part_type;
    char part_fit;
    int  part_start;
    int  part_size;
    char part_name[16];
};
typedef struct part*apunta_part;
typedef struct part ptn;

struct arranque_MBR //estructura del mbr
{
    int  mbr_longitud;
    char mbr_fecha_creacion[50];
    int  mbr_disk_signature;
    ptn mbr_part_1;
    ptn mbr_part_2;
    ptn mbr_part_3;
    ptn mbr_part_4;
};
typedef struct arranque_MBR *apaunta_MBR;
typedef struct arranque_MBR a_mbr;


typedef struct arranque_EBR  //estructura par los ebr's de cada logica
{
    char part_status;
    char part_fit;
    int part_start;
    int part_size;
    int part_next;
    char part_name [16];
};
typedef struct arranqueEBR a_ebr;


void asignar_arranque_mbr(int longitud, char *ubicacion)//asigna el mbr y crea sus elementos
{
    FILE * fichero = fopen(ubicacion,"rb+");

    if(fichero)
    {
        fseek(fichero,0*sizeof(a_mbr),SEEK_SET);
        a_mbr amp;
        ptn pt;

        //inicia las particiones y tamaño
        amp.mbr_part_1=pt;
        amp.mbr_part_2=pt;
        amp.mbr_part_3=pt;
        amp.mbr_part_4=pt;
        amp.mbr_longitud=longitud;
        //completar disk_asignature


        //inicia atributos de la particion
        pt.part_status='0';
        pt.part_fit ='0';
        pt.part_size=0;
        pt.part_start=0;
        pt.part_type='0';
        strcpy(pt.part_name,"0");




        fwrite(&amp,sizeof(a_mbr),1,fichero);
        fclose(fichero);
    }
    else
    {
        printf("Error inesperado al abrir el archivo.");
    }
}

int main()
{

    char entrada [500];//verificar tamaño


//asignar_arranque_mbr(100, "/home/duglas/prueba.txt");//seguir pruebas
    fgets(entrada,500,stdin);
    strcat(entrada,";");//ultimo elemento- final de la entrada
    automata(&entrada[0]);

    return 0;
}
