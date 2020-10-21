#include <stdio.h>
//#include <stdlib.h>
#include "mapeo.h"


//Permite salir del programa.
void salir(FILE *fp){
    fclose(fp);
    printf("\n");
    printf("Programa finalizado!\n");
    exit(0);
}

//Funciones auxiliares de lista
void fEliminar(tElemento e){
    free(e);
    e = NULL;
}

//Funciones auxiliares de mapeo
void fEliminarC (void* clave){
    tClave c= (tClave) clave;
    free(c);
    c= NULL;
}

void fEliminarV(void* valor){
    tClave v= (tValor) valor;
    free(v);
    v= NULL;
}

/**
void *fComparacion(void* p01,void* p02){

    int * pa;
    pa= p01;

    int * pb;
    pb= p02;

    int pos=0;
    int primero=*pa;
    int segundo=*pb;

    int esigual=0;
    //recorro elemento por elemento
    while (segundo!=0&&primero!=0&&esigual!=1)
    {
        primero=*(pa+pos);
        segundo=*(pb+pos);
        if (primero!=segundo)
            esigual=1;
        pos++;
    }
    return esigual;
}
/*
 void *fHash(void* p01){
    int * parr;
    parr= p01;
    int suma=0;
    int pos=0;
    int primero=*parr;
    while (primero!=0 )
    {
        primero=*(parr+pos);
        suma=suma+primero;
        pos++;
    }
    return  (suma/(pos-1) ) ;
}
*/

int fComparacion(void *e1, void *e2){
   return (strcmp(e1,e2));
   return (strcmp(e1,e2)==0);
}

int fHash(void *p){

 return ((int)strlen(p));
}


int main(int argc, char *argv[]){

    tMapeo map;



    //crear_mapeo(&map,10,&fComparacion,&fHash);

    printf("CREAR MAPEO\n");
    crear_mapeo(&map, 11, &fComparacion, &fHash);
    printf("El size del mapeo es %i\n", sizeof(*map));
    printf("Longitud del map es %i\n", (map->longitud_tabla));
    printf("=================================\n");


    printf("VERIFICAR FUNCIONES fComparador y fHash\n");
    char arr_01[5]={'H','O','L','A','\0'};
    char arr_02[5]={'H','x','L','A','\0'};//0 igual -1 distinto
    printf("arreglo 1: %s\n",arr_01);
    printf("arreglo 2: %s\n",arr_02);
    printf("Comparador (0 iguales y -1 distintos): %d\n",fComparacion(arr_01,arr_02));
    printf("t Hash: %d\n",fHash(arr_01));
    printf("=================================\n");



    printf("INSERTAR ENTRADAS\n");
    char * clave1 = "clave";
    char * clave2 = "hola";

    char * vv1 = "valor1";
    char * vv2 = "valor2";

    m_insertar(map,clave1,vv1);

    printf("El size del mapeo es %i\n", sizeof(*map));
    printf("Longitud del map es %i\n", (map->longitud_tabla));
    printf("=================================\n\n");

    //
printf("============================================ EVALUADOR DE ARCHIVO DE CARACTERES ASCII ==========================================================\n");

    //inicio leer el archivo desde cmd
    if(argc==2)
    {
        char* archivo_nombre = argv[1];
        FILE* archivo_ascii;
        if((archivo_ascii= fopen(archivo_nombre,"r"))==NULL)
        {

            printf ("El archivo es archivo invalido.\n"); //Abro el archivo en modo lectura
            return 0;
        }
        else
        {
            //en archivo_ascii tengo un puntero a un archivo leido por consola
            //lo leido es el nombre del archivo.
            printf("s\n",archivo_ascii); //archivo_ascii

        }

    }
    else
    {
        printf ("Hay error en el numero de argumentos\n");
        return 1;
    }

    //insertar palabras del archivo al mapeo





    //asumo que tengo el archivo en un arreglo
    int palabra_in[250]={104,111,108,97,255,109,117,110,100,111,255,147,114,87,84,0};

    int i=0;
    int pri=0;
    //sin punteros recorro el arreglo
    while(palabra_in[i]!=0)
    {
        if (palabra_in[i]==255)
            { int sup=i-1;
              printf("%i ",pri);
              printf("%i \n",sup);
              //n-esima palabra
              for(int pos=pri;pos<=sup;pos++)
                {
                    printf("%c ",palabra_in[pos]);
                }

              printf(" \n");
              pri=sup+2;
              }

        i++;
    }
    //ultima palabra
    printf("%i ",pri);
    printf("%i \n",i-1);
    for(int ult=pri;ult<=i-1;ult++)
        {
            printf("%c ",palabra_in[ult]);
        }
    printf("\n");


    //buscar palabra en el archivo

    char cadena [250];
    int  salir = 0;
    int opcion=0;
    while (!salir){
        printf("========== Ingrese una opcion =============\n");
        printf("1: cantidad de apariciones de una palabra o 2: salir ");

        scanf("%d", &opcion);
        fflush(stdin);
        if (opcion == 1|opcion == 2 ){
            printf("========== =============== =============\n");
            printf("Eligio >>");
            fflush(stdin);
        }
        switch(opcion){
        case 1: {
            printf("opcion 1 \n");
            printf("Ingrese una palabra: ");
            scanf("%[^\n",cadena);
            //opero con cadena= es un string

            fflush(stdin);
            break;
        }
        case 2:{
            salir = 1;
            printf("opcion 2>>");
            printf("Eso es todo amigos! \n");
            break;
        }
        default:{
            printf("La opcion ingresada no es correcta \n");
        }
        }
    }


}






