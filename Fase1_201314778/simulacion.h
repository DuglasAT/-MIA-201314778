#ifndef SIMULACION_H_INCLUDED
#define SIMULACION_H_INCLUDED


#include <time.h>


int n_prim=0,n_ext=0,sizext=0,sizelog=0,ebrpos=0,xOS=32;

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

struct arranque_EBR  //estructura par los ebr's de cada logica
{
    char part_status;
    char part_fit;
    int part_start;
    int part_size;
    int part_next;
    char part_name [16];
};
typedef struct arranque_EBR e_ebr;

//--------------------------------------------------------------------------------------------------------
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
        amp.mbr_disk_signature = rand()%10000;

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
//--------------------------------------------------------------------------------------------------------
ptn iniciapart(ptn p)
{

    p.part_fit = p.part_status = p.part_type = '0';
    p.part_size =p.part_start = 0;
    strcpy(p.part_name,"0");

    return p;

}

//--------------------------------------------------------------------------------------------------------

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
    char  namepart4aux [150] ="hola";
    strcpy(namepart4aux,am2.mbr_part_4.part_name);


    caso2 = !strcmp(namepart1aux,namepartition) ? 1 : 0;
    caso2 = !strcmp(namepart2aux,namepartition) ? 2 : caso2;
    caso2 = !strcmp(namepart3aux,namepartition) ? 3 : caso2;
    caso2 = !strcmp(namepart4aux,namepartition) ? 4 : caso2;


    switch(caso2)
    {
    case 1:

        am2.mbr_part_1=iniciapart(am2.mbr_part_1);
        strcpy(am2.mbr_part_1.part_name,"0");
        amwrite(am2,ubicacion);
        return 1;
        break;

    case 2:

        am2.mbr_part_2=iniciapart(am2.mbr_part_2);
        amwrite(am2,ubicacion);
        return 1;
        break;

    case 3:
        am2.mbr_part_3=iniciapart(am2.mbr_part_3);
        amwrite(am2,ubicacion);
        return 1;
        break;

    case 4:

        am2.mbr_part_4=iniciapart(am2.mbr_part_4);
        amwrite(am2,ubicacion);
        return 1;
        break;

    default:
        break;
    }
    n_prim-=n_prim;
    return 0;
}
//--------------------------------------------------------------------------------------------------------
void amwrite(a_mbr am2, char * ubicacion)
{

    FILE * fichero2;
    fichero2 = fopen(ubicacion,"rb+");
    if(fichero2)
    {
        fseek(fichero2,0*sizeof(a_mbr),SEEK_SET);
        fwrite(&am2,sizeof(a_mbr),1,fichero2);
        fclose(fichero2);
    }
}


//--------------------------------------------------------------------------------------------------------


void incia_part_EBR(char ubicacion[], int inicio)
{
    e_ebr ebr1;

    ebr1.part_status = '0';
    ebr1.part_fit = 'b';
    ebr1.part_start=inicio;
    ebr1.part_size=0;
    ebr1.part_next=-1;
    strcpy(ebr1.part_name,"0");

    FILE * fichero3=(FILE*)malloc(sizeof(FILE));
    fichero3 = fopen(ubicacion,"rb+");
    if(fichero3)
    {
        fseek(fichero3,inicio,SEEK_SET);
        fwrite(&ebr1,sizeof(e_ebr),1,fichero3);
        fclose(fichero3);
    }
}
//--------------------------------------------------------------------------------------------------------
ptn asigna_part(char sts,char ty,char ft,int sz,char *n,int str)
{
    ptn p;

    p.part_status = sts;
    p.part_type =ty;
    p.part_fit = ft;
    p.part_size = sz;
    strcpy(p.part_name,n);;
    p.part_start = str;

    return p;
}

//--------------------------------------------------------------------------------------------------------

int l_part_e(a_mbr am2)
{
    int sze;
    sze = am2.mbr_part_1.part_type=='e' ? am2.mbr_part_1.part_size : sze;
    sze = am2.mbr_part_2.part_type=='e' ? am2.mbr_part_2.part_size : sze;
    sze = am2.mbr_part_3.part_type=='e' ? am2.mbr_part_3.part_size : sze;
    sze = am2.mbr_part_4.part_type=='e' ? am2.mbr_part_4.part_size : sze;

    return sze;

}
//--------------------------------------------------------------------------------------------------------

void nueva_particion(char sts,char ty,char ft,int sz,char *n,char*ub)
{
    n_prim=0;
    n_ext=0;
    FILE* fichero = fopen(ub,"rb");
    a_mbr am2 ={0,"",0,0,0,0};
    if(fichero)
    {
        fseek(fichero,0,SEEK_SET);
        fread(&am2,sizeof(a_mbr),1,fichero);
        fclose(fichero);
    }
    else
    {
        printf("oops");
    }

    am2.mbr_part_1.part_type=='e' ? n_ext++ : n_ext; am2.mbr_part_1.part_type=='p' ? n_prim++ : n_prim;
    am2.mbr_part_2.part_type=='e' ? n_ext++ : n_ext; am2.mbr_part_2.part_type=='p' ? n_prim++ : n_prim;
    am2.mbr_part_3.part_type=='e' ? n_ext++ : n_ext; am2.mbr_part_3.part_type=='p' ? n_prim++ : n_prim;
    am2.mbr_part_4.part_type=='e' ? n_ext++ : n_ext; am2.mbr_part_4.part_type=='p' ? n_prim++ : n_prim;

    FILE * fichero2 = fopen(ub,"rb+");
    if(fichero2){
        if(fichero2!=NULL&((n_ext==1&n_prim<4&ty!='e')|(n_ext==0&n_prim<5)))
        {
            fseek(fichero2,0*sizeof(a_mbr),SEEK_SET);
            int mbrsp=am2.mbr_longitud-220;
            mbrsp-= am2.mbr_part_1.part_status=='1' ? am2.mbr_part_1.part_size : 0;
            mbrsp-= am2.mbr_part_1.part_status=='1' ? am2.mbr_part_1.part_size : 0;
            mbrsp-= am2.mbr_part_1.part_status=='1' ? am2.mbr_part_1.part_size : 0;
            mbrsp-= am2.mbr_part_1.part_status=='1' ? am2.mbr_part_1.part_size : 0;
            if(sz<mbrsp+1)
            {

                int space1 =  0;
                space1 = am2.mbr_part_1.part_size==0 ? 1:space1;
                space1 = sz<am2.mbr_part_1.part_size+1 ? 1:0;
                int space2 =  0;
                space2 = am2.mbr_part_2.part_size==0 ? 1:space2;
                space2 = sz<am2.mbr_part_2.part_size+1 ? 1:0;
                int space3 =  0;
                space3 = am2.mbr_part_3.part_size==0 ? 1:space3;
                space3 = sz<am2.mbr_part_3.part_size+1 ? 1:0;
                int space4 =  0;
                space4 = am2.mbr_part_4.part_size==0 ? 1:space4;
                space4 = sz<am2.mbr_part_4.part_size+1 ? 1:0;

                if(am2.mbr_part_1.part_status!='1'&space1)
                {
                    asigna_part(sts,ty,ft,sz,n,sizeof(a_mbr));
                    if(ty=='e')
                    {
                        sizext=sz;
                        incia_part_EBR(ub,am2.mbr_part_1.part_start);
                        sizext = l_part_e(am2);
                    }
                }
                else if(am2.mbr_part_2.part_status!='1'&space2)
                {

                    asigna_part(sts,ty,ft,sz,n,sizeof(a_mbr));
                    if(ty=='e')
                    {
                        sizext=sz;
                        incia_part_EBR(ub,am2.mbr_part_2.part_start);
                        sizext = l_part_e(am2);
                    }
                }
                else if(am2.mbr_part_3.part_status!='1'&space2)
                {

                    asigna_part(sts,ty,ft,sz,n,sizeof(a_mbr));
                    if(ty=='e')
                    {
                        sizext=sz;
                        incia_part_EBR(ub,am2.mbr_part_3.part_start);
                        sizext = l_part_e(am2);
                    }
                }
                else if(am2.mbr_part_4.part_status!='1'&space2)
                {

                    asigna_part(sts,ty,ft,sz,n,sizeof(a_mbr));
                    if(ty=='e')
                    {
                        sizext=sz; //tamaño de la extendida
                        incia_part_EBR(ub,am2.mbr_part_4.part_start);
                        sizext = l_part_e(am2);
                    }
                }
                else
                {
                    printf("No hay suficiente espacio.\n");
                }
            }else{
                printf("No hay suficiente espacio.\n");
            }

        }else{
            printf("Existe extentida ya.\n");
        }

        fwrite(&am2,sizeof(a_mbr),1,fichero2);
        fclose(fichero2);
    }else{
        printf("Disco no encontrado.\n\n");
    }
}

//--------------------------------------------------------------------------------------------------------
int isthere_part(char name [],char ubicacion [])
{
    FILE* fichero = fopen(ubicacion,"rb");
    a_mbr am3 ={0,"",0,0,0,0};
    if(fichero)
    {
        fseek(fichero,0,SEEK_SET);
        fread(&am3,sizeof(a_mbr),1,fichero);
        fclose(fichero);
    }
    else
    {
        printf("oops");
    }

    int a  = 0;
    a = !strcmp(am3.mbr_part_1.part_name,name) ? 1 : a;
    a = !strcmp(am3.mbr_part_2.part_name,name) ? 1 : a;
    a = !strcmp(am3.mbr_part_3.part_name,name) ? 1 : a;
    a = !strcmp(am3.mbr_part_4.part_name,name) ? 1 : a;

    return a;
}



//--------------------------------------------------------------------------------------------------------
e_ebr ant_EBR(char ub [],int sz){

    e_ebr ant_ebr;
    FILE * fichero4;
    int p=0;
    fichero4 = fopen(ub,"rb");

    if(fichero4!=NULL)
    {
        int sig=ebrpos=0;

        //obtener el MBR
        FILE* fichero = fopen(ub,"rb");
        a_mbr am2 ={0,"",0,0,0,0};
        if(fichero)
        {
            fseek(fichero,0,SEEK_SET);
            fread(&am2,sizeof(a_mbr),1,fichero);
            fclose(fichero);
        }
        else
        {
            printf("oops");
        }

        //obtiene la posicion del EBR
        ebrpos=am2.mbr_part_1.part_type=='e' ?  am2.mbr_part_1.part_start : ebrpos;
        ebrpos=am2.mbr_part_2.part_type=='e' ?  am2.mbr_part_2.part_start : ebrpos;
        ebrpos=am2.mbr_part_3.part_type=='e' ?  am2.mbr_part_3.part_start : ebrpos;
        ebrpos=am2.mbr_part_4.part_type=='e' ?  am2.mbr_part_4.part_start : ebrpos;

        while(sig!=-1)
        {
            fseek(fichero4,ebrpos,SEEK_SET);
            fread(&ant_ebr,sizeof(e_ebr),1,fichero4);
            sig = ant_ebr.part_next;
            ebrpos=ant_ebr.part_start+ant_ebr.part_size+xOS;
            p++;
            if(ant_ebr.part_status=='0'&sz<ant_ebr.part_size+1)
            {
                if(sz<ant_ebr.part_size)
                {
                    // ebr R
                }

                if(ant_ebr.part_next!=-1){
                    ant_ebr.part_next=ant_ebr.part_next-(ant_ebr.part_size-sz);
                }
                break;
            }

        }
        fclose(fichero4);
    }
}
//--------------------------------------------------------------------------------------------------------

void add_EBR_Part(char sts,char ft,int srt,int sz,int nx,char nm[],char ub[])
{

    //obtener el MBR
    FILE* fichero = fopen(ub,"rb");
    a_mbr am2 ={0,"",0,0,0,0};
    if(fichero)
    {
        fseek(fichero,0,SEEK_SET);
        fread(&am2,sizeof(a_mbr),1,fichero);
        fclose(fichero);
    }
    else
    {
        printf("oops");
    }
    //--------------------------------------------------------------------------------------------------------


    FILE * fichero2 = fopen(ub,"rb+");
    n_prim=0;
    n_ext=0;

    //Obtener el numero de particiones (primarias,extendida)
    am2.mbr_part_1.part_type=='e' ? n_ext++ : n_ext; am2.mbr_part_1.part_type=='p' ? n_prim++ : n_prim;
    am2.mbr_part_2.part_type=='e' ? n_ext++ : n_ext; am2.mbr_part_2.part_type=='p' ? n_prim++ : n_prim;
    am2.mbr_part_3.part_type=='e' ? n_ext++ : n_ext; am2.mbr_part_3.part_type=='p' ? n_prim++ : n_prim;
    am2.mbr_part_4.part_type=='e' ? n_ext++ : n_ext; am2.mbr_part_4.part_type=='p' ? n_prim++ : n_prim;


    //--------------------------------------------------------------------------------------------------------
    //si ya hay una particion extendida
    if(n_ext==1)
    {

        e_ebr ebr1;
        FILE * fichero3 = fopen(ub,"rb");
        int t = 0;
        int p = 0;
        if(fichero3)
        {
            int sign =n_prim = n_ext = ebrpos=0;
            //obtiene la posicion del EBR
            ebrpos=am2.mbr_part_1.part_type=='e' ?  am2.mbr_part_1.part_start : ebrpos;
            ebrpos=am2.mbr_part_2.part_type=='e' ?  am2.mbr_part_2.part_start : ebrpos;
            ebrpos=am2.mbr_part_3.part_type=='e' ?  am2.mbr_part_3.part_start : ebrpos;
            ebrpos=am2.mbr_part_4.part_type=='e' ?  am2.mbr_part_4.part_start : ebrpos;
            //--------------------------------------------------------------------------------------------------------

            //obtiene la longitud de las particiones logicas
            if(n_ext!=0)
            {
                while(sign!=-1){
                    fseek(fichero3,ebrpos,SEEK_SET);
                    fread(&ebr1,sizeof(e_ebr),1,fichero3);
                    sign = ebr1.part_next;
                    ebrpos=ebr1.part_start+ebr1.part_size+xOS;
                    t+=ebr1.part_status!='0'? ebr1.part_size:0;
                    p+=ebr1.part_status!='0'? p:0;
                }
            }
            fclose(fichero3);
        }

        //si el tamaño disponible es suficiente
        if(sz+xOS<(l_part_e(am2)-t-xOS*p)+1)
        {
            if(fichero2!=NULL)
            {
                e_ebr new_ebr;
                new_ebr.part_fit=ft;
                strcpy(new_ebr.part_name,nm);
                new_ebr.part_next=-1;
                new_ebr.part_size=sz;
                new_ebr.part_start=srt;
                new_ebr.part_status=sts;
                e_ebr ant_ebr= ant_EBR(ub,sz);

                if(ant_ebr.part_status=='1')
                {
                    //obtener el ebr sig
                    fseek(fichero2,ant_ebr.part_next-xOS-ant_ebr.part_size,SEEK_SET);
                    fwrite(&ant_ebr,sizeof(e_ebr),1,fichero2);
                    fseek(fichero2,ant_ebr.part_next,SEEK_SET);
                    fwrite(&new_ebr,sizeof(e_ebr),1,fichero2);
                }
                else if(ant_ebr.part_status=='0')
                {

                    new_ebr.part_fit=ant_ebr.part_fit;
                    strcpy(new_ebr.part_name,ant_ebr.part_name);
                    new_ebr.part_size=ant_ebr.part_size;
                    new_ebr.part_status=ant_ebr.part_status;

                    fseek(fichero2,ant_ebr.part_start,SEEK_SET);
                    fwrite(&ant_ebr,sizeof(e_ebr),1,fichero2);
                }
                else
                {
                    printf("Error al verificar el estado.\n");
                }
                fclose(fichero2);
            }
            else
            {
                printf("No hay disco\n");
            }
        }
        else
        {
            printf("Espacio insuficiente para particion logica\n");
        }
    }
    else
    {
        printf("Cree antes una particion extendida\n");
    }

}

#endif // SIMULACION_H_INCLUDED
