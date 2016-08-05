#ifndef ANALIZADOR_H_INCLUDED
#define ANALIZADOR_H_INCLUDED

#include <string.h>
#include "acciones.h"




static char newline = '\n';
static char sharp = '#'; // utilizada para comentarios
static char space = ' ';
static char mas = '+';
static char menos = '-';
static char punto = '.';
static char pcoma = ';';
static char divide = '\\';
static char slash = '/';
static char comillas = '\"';

static int caso=0;
int band=0;
int v=0;
int o=0;



//palabras reservadas - sujeta a cambios
char * reservadas [] = {
    "mkdisk","-size","+unit","-path","-name",
    "rmdisk", //-path
    "fdisk","+type","+fit","+delete","+add", //-size,+unit,-path,-name
    "mount", //-path,-name
    "umount","-id",

    "df","+k","+m","+h","+i",
    "du","+n","-h", //-path
    "mkfs","+fs", //-id,+type,+add,+unit

    "login","-usr","-pwd",
    "logout",
    "mkgrp", //-id,-name
    "rmgrp", //-id,-name
    "mkusr","-grp", //-id,-usr,-pwd
    "rmusr", //-id,-usr
    "chmod","ugo","+r", //-id,-path
    "mkfile","+p","+size","+cont", //-id,-path
    "cat","-file", //-id
    "rm","+rf",  //-id,-path
    "edit",  //-id,-path,+size,+cont
    "ren",  //-id,-path,-name
    "mkdir",  //-id,-path,+p
    "cp","-dest","-iddest", //-id,-path
    "mv",  //-id,-path,-dest,-iddest
    "find","?","*","+perm","user",  //-id,-path,-name,-usr
    "chown", //-id,-path,+r,-usr
    "chgrp", //-usr,-grp
    //agregar enlace simbolico ln en fase2
    "ulink","-link",
    //agregar convert ext2 to ext3 en fase2
    "loss", //-ide
    "rep", "+ruta", //-name,-path,-id,
    "mbr","disk", //para rep
    "inode","journaling","block","bm_inode","bm_block","tree","sb","file", //para rep
    "ls +i","ls +l", //para rep - verificar en fase2
    "exec" //-path

};

//contendor para los comandos
struct contenedor
{
    char id [450];
    char cont[450];
};
typedef struct contenedor cont;
cont varios[20];


//conjunto de comandos - verificar idea luego
struct conjunto
{

    int c;
    char id [450];
    char cont[450];

};
typedef struct conjunto conto;
conto contos[10];


//llena el contenedor con valores 0 para utilizarlo luego
void contenedor_add()
{
    int  c=0;
    while(c<20)
    {
        strcpy(varios[c].id,"0");
        c++;
    }
}


//verifica si un caracter es letra
static int letter(char car)
{

    int aux = 0;
    aux = (int)car;
    if(aux>64 && aux<91 || aux>96 && aux<123)
    {
        return 1;
    }

    return 0;
}

//verifica si un caracter es numero
static int num(char n)
{
    int aux = 0;
    aux = (int)n;
    if(aux>47 && aux<58)
    {
        return 1;
    }

    return 0;
}

static int tipo_par_p(char t)
{

    if(t==mas||t==menos||t==punto)
    {
        return 1;
    }

    return 0;
}

static int ispace(char t)
{
    if(t==space)
    {
        return 1;
    }
    return 0;
}


static int isnewline_final(char t)
{
    if(t==newline||t==pcoma)
    {
        return 1;
    }
    return 0;
}

static int isharp(char t)
{
    if(t==sharp)
    {
        return 1;
    }
    return 0;
}

static int islash(char t)
{
    if(t==slash)
    {
        return 1;
    }
    return 0;
}

static int fin(char t)
{

    if (t == pcoma)
    {
        return 1;
    }
    return 0;
}

//verifica si una cĵĵĵĵĵ de caracteres es una palabra reservada
static int reserved(char *w)
{
    int c =0;
    while(c<76)
    {
        if(strcmp(w,reservadas[c])==0)
        {
            return 1;
        }

        c++;
    }
    return 0;
}



//convierte una cadena de caracteres en minusculas para no diferenciar mayusculas de minusculas
static char * to_lower(char *cad)
{
    char cdobles='\"';
    while(*cad!='\0')
    {
        if(*cad>64 && *cad<91)
        {
            if((*cad)==cdobles)
            {
                while(*cad==cdobles)
                {
                    *cad+=32;
                    cad++;
                }
            }
            else
            {
                *cad+=32;
            }
        }
        if((*cad)==cdobles)
        {
            cad++;
            while(*cad!=cdobles)
            {
                cad++;
            }
        }
        cad++;
    }

    return cad;
}


//para utilizar el script con comandos - falta implementar - no terminado
void read_file(char entrada[])
{
    FILE *script = fopen("/home/duglas/script.sh", "r" );
    char aux[22000];



    if (!script)
    {
        while (feof(script)==0)
        {
            fgets(aux,22000,script);
            strcat(entrada,aux);
        }
        fclose(script);
    }
    else
    {
        printf( "Error al abrir el archivo.\n");
    }
}


//correr el comando elegido - falta implementar - no iniciado
void iniciar_comando(cont scan[])
{

}


//metodo para crear el archivo binario que simula el disco - falta implementar - no iniciado
void mkdisk(int longitud, cont scan[])
{

}



//automata que reconoce la entrada de comandos - no terminado
void automata(char entrada [] ){


    char aux [2000];
    aux[0] = entrada[0];

    int  c;
    int  k=0;
    aux [0] = to_lower(&entrada[0]); // prueba de conversion
    to_lower(&entrada[0]);
    char comand [2000];

    for (c=0;c<strlen(&entrada[0]);c++){

        switch(caso){

        case 0:

            if(letter(entrada[c]))
            {

                printf("%s es letra\n",&entrada[c]);

                comand[k]=entrada[c];
                caso = 1;
                k++;
            }
            else if(num(entrada[c]))
            {

                printf("%s es numero\n",&entrada[c]);

            }
            else if(ispace(entrada[c]))
            {
                printf("%s es espacio\n",&entrada[c]);
                caso = 0;
            }
            else if(isnewline_final(entrada[c]) || isharp(entrada[c]))
            {
                printf("%s es salto de linea\n",&entrada[c]);

            }
            else if(entrada[c]==sharp)
            {
                caso = 10;
            }
            else if(islash(entrada[c]))
            {
                printf("%s es slash",&entrada[c]);
                caso = 0;
            }
            else if(tipo_par_p(entrada[c]))
            {
                comand[k]=entrada[c];
                k++;
                caso = 1;
            }

            break;

        case 1:

            if(ispace(entrada[c]))
            {
                if(reserved(&comand[0]))
                {
                    printf("es reservada\n");
                }
                else
                {
                    printf("no es reservada\n");
                }
            }
            else if(letter(entrada[c]))
            {

                comand[k]=entrada[c];
                k++;
            }

            break;
        default:
            break;

        }
    }

}




#endif // ANALIZADOR_H_INCLUDED
