#ifndef ANALIZADOR_H_INCLUDED
#define ANALIZADOR_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>




static char letras [] = {'a','b','c','d','e','f','g',
                  'h','i','j','k','l','n','m',
                  'o','p','q','r','s','t','u',
                  'v','w','x','y','z',
                  'A','B','C','D','E','F','G',
                  'H','I','J','K','L','N','O',
                  'P','M','Q','R','S','T','U'
                  ,'V','W','X','Y','Z'};

static char * palabras [] = {"mkdisk","rmdisk","fdisk","-mount","-unmount","-size",
                             "-unit","-path","-id","-type","-fit","-delete","-name",
                             "-add","-mkfs","-mkfile","-cat","-rem","-edit","-ren",
                             "mkdir","-cp","-mv","-find","-cont","-p","-dest","-iddest"};
static int numeros [] = {'0','1','2','3','4','5','6','7','8','9'};

#endif // ANALIZADOR_H_INCLUDED
