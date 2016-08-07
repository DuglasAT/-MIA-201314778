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


void asignar_arranque_mbr(int longitud, char *ubicacion)//asigna el mbr y crea sus elementos
{
    FILE * fichero = fopen(ubicacion,"rb+");

    if(fichero)
    {
        fseek(fichero,0*sizeof(a_mbr),SEEK_SET);
        a_mbr amp;
        ptn pt;

        //inicia las particiones y tamaño
        amp.mbr_part_1=amp.mbr_part_2=amp.mbr_part_3=amp.mbr_part_4=pt;
        amp.mbr_longitud=longitud;
        //completar disk_asignature

        //inicia atributos de la particion
        pt.part_status=pt.part_fit=pt.part_type='0';
        pt.part_size=pt.part_start=0;
        strcpy(pt.part_name,"0");

        fwrite(&amp,sizeof(a_mbr),1,fichero);
        fclose(fichero);
    }
    else
    {
        printf("Error inesperado al abrir el archivo.");
    }
}




int change_arranque_MBR(char * namepartition, char *ubicacion)
{
int caso2=0;
    FILE* fichero = fopen(ubicacion,"rb");
        a_mbr am2 ={0,"",0,0,0,0};
        if(fichero){
            fseek(fichero,0,SEEK_SET);
            fread(&am2,sizeof(a_mbr),1,fichero);
            fclose(fichero);
        }else{
          printf("oops");
        }


    char  namepart1aux [150] ;
    strcpy(namepart1aux,am2.mbr_part_1.part_name);
    char  namepart2aux [150] ;
    strcpy(namepart2aux,am2.mbr_part_2.part_name);
    char  namepart3aux [150] ;
    strcpy(namepart3aux,am2.mbr_part_3.part_name);
    char  namepart4aux [150] ;
    strcpy(namepart4aux,am2.mbr_part_4.part_name);


    caso2 = !strcmp(namepart1aux,namepartition) ? 1 : 0;
    caso2 = !strcmp(namepart2aux,namepartition) ? 2 : caso2;
    caso2 = !strcmp(namepart3aux,namepartition) ? 3 : caso2;
    caso2 = !strcmp(namepart4aux,namepartition) ? 4 : caso2;


    switch(caso2)
    {
    case 1:

        //a_mbrp1_void(&am2,&am2.mbr_part_1.part_fit,&am2.mbr_part_1.part_status,&am2.mbr_part_1.part_size,&am2.mbr_part_1.part_start,&am2.mbr_part_1.part_type,&am2.mbr_part_1.part_name);
        am2.mbr_part_1.part_fit =am2.mbr_part_1.part_status=am2.mbr_part_1.part_type='0';
        am2.mbr_part_1.part_size=am2.mbr_part_1.part_start=0;
        strcpy(am2.mbr_part_1.part_name,"0");
        FILE * fichero2;
        fichero2 = fopen(ubicacion,"rb+");
        if(fichero2)
        {
            fseek(fichero2,0*sizeof(a_mbr),SEEK_SET);
            fwrite(&am2,sizeof(a_mbr),1,fichero2);
            fclose(fichero2);
        }
        return 1;
        break;

        default:
        break;
    }
    return 0;
}



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

int main()
{

    char entrada [500];//verificar tamaño
int a,b,c = 0;


  a=b=c=4;

//asignar_arranque_mbr(100, "/home/duglas/prueba.txt");//seguir pruebas
    fgets(entrada,500,stdin);
    strcat(entrada,";");//ultimo elemento- final de la entrada
    automata(&entrada[0]);

  //  change_arranque_MBR("hola","/home/duglas/prueba.txt");

    return 0;
}
