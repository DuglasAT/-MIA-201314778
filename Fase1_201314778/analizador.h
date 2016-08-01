#ifndef ANALIZADOR_H_INCLUDED
#define ANALIZADOR_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>




static int newline = '\n';
static int sharp = '#';
static int space = ' ';
static int caso=0;
static int long_reservadas=88;
int band=0;




 char * reservadas [] = {"mkdisk","-size","+unit","-path","-name",
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

static int reserved(char *w)
{
  int i =0;
  while(i<76)
  {
      if(strcmp(w,reservadas[i])==0)
      {
          return 1;
      }

        i++;
    }
  return 0;
}

static void to_lower(char *cad)
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
}

void read_file(char entrada[])
{
    FILE *script = fopen("/home/duglas/script.sh", "r" );
    char aux[22000];



    if ( script!= NULL )
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


void automata(char entrada [] ){

    int  i;
    int  j=0;
    int longitud = strlen(&entrada[0]);
    to_lower(&entrada[0]);
    char comand [2000]={};

    for (i=0;i<longitud;i++){

    switch(caso){

    case 0:

    if(letter(entrada[i]))
    {

    printf("%s es letra\n",&entrada[i]);

    comand[j]=entrada[i];
    caso = 1;
    j++;
    }
    else if(num(entrada[i]))
    {

    printf("%s es numero\n",&entrada[i]);

    }
    else if(entrada[i]==space)
    {
    printf("%s es espacio\n",&entrada[i]);
    }

    break;

    case 1:

    if(entrada[i]==' ' || entrada[i]== '\n')
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
    else if(letter(entrada[i]))
    {

     comand[j]=entrada[i];
     j++;
    }

    break;
    default:
    break;

    }
}

}

#endif // ANALIZADOR_H_INCLUDED
