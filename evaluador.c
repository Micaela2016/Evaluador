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
    int longitud=10; //aca necesito la longitud de la tabla hash no es 10 porque se va modificando si se hace rehash
    return  (suma/(pos-1) )/longitud ;
}

int main(int argc, char *argv[]){

    tMapeo map;

    crear_mapeo(&map,10,&fComparacion,&fHash);
    //map= crear_mapeo(map,10,NULL,NULL);

    //tMapeo map= (tMapeo) malloc (sizeof(struct celda));
    //map= crear_mapeo();


    int opcion;

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

//leer la ruta del archivo
    printf("Ingrese la ruta del archivo seguido de un enter\n");
    char ruta [20];
    scanf("%[^\n",ruta);
    fflush(stdin);
    //buscar archivo

    char cadena [250];
    int  salir = 0;
    opcion=0;
    while (!salir){
        printf("Ingrese una opcion\n");
        printf("1: cantidad de apariciones de una palabra o 2: salir ");
        scanf("%d", &opcion);
        fflush(stdin);
        if (opcion == 1|opcion == 2 ){
            printf("Eligio >>");
            fflush(stdin);
        }
        switch(opcion){
        case 1: {
            printf("opcion 1 \n");
            printf("Ingrese una palabra: ");
            scanf("%[^\n",cadena);
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
