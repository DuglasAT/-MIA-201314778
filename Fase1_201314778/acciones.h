#ifndef ACCIONES_H_INCLUDED
#define ACCIONES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

//aqui estaran los metodos principales


//struct para el comando mkdisk
struct comando_mkdisk
{
    int tam;
    char unidad;
    char nombre [350];
    char ubicacion [350];
};
typedef struct comando_mkdisk * mkd_apunt;
typedef struct comando_mkdisk mkd;


//struct para el comando rmkdisk
struct comando_rmdisk
{
    char ubicacion [350];
};
typedef struct comando_rmdisk * rm_apunt;
typedef struct comando_rmdisk rmd;


//struct para el comando fdisk
struct comando_fdisk
{
    int tam;
    int  agregar;
    char unidad;
    char tipo;
    char ajuste;
    char ubicacion[350];
    char eliminar[350];
    char nombre [350];



};
typedef struct comando_fdisk * fd_apunt;
typedef struct comando_fddisk fd;



//struct para el comando mount
struct comando_mount
{
    int fscan;
    char nombre[350];
    char ubicacion[350];
};
typedef struct comando_mount * m_apunt;
typedef struct comando_mount m;


//struct para el comando mount
struct comando_unmount
{
    int tope;
    char nombre[350];
    mycad dstring [350];
};
typedef struct umount * um_apunt;
typedef struct umount um;


//struct para guardar cadenas
struct stringc
{
    char valor [50];
};
typedef struct stringc mycad;



#endif // ACCIONES_H_INCLUDED
