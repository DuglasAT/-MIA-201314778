#ifndef ANALIZADOR_H_INCLUDED
#define ANALIZADOR_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>




static int newline = '\n';
static int sharp = '#';
static int space = ' ';
static int caso=0;
int flag=0;


static char * reservadas [] = {"mkdisk","-size","+unit","-path","-name",
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

static void verifica_minuscula(char *cad)
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


void lexer(char buffer [] ){

    int  i =0;
    int longitud = strlen(&buffer[0]);
    minusculas(&buffer[0]);

    char dato [1000]={};
    int pos_vector =0;
    while (i<tamano){

}
}

#endif // ANALIZADOR_H_INCLUDED
