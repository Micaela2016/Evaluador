#include <stdio.h>
#include <stdlib.h>
#include "mapeo.h"


//Permite salir del programa.
void salir(FILE *fp){
    fclose(fp);
    printf("\n");
    printf("Programa finalizado!\n");
    exit(0);
}


int main(int argc, char *argv[]){
    tMapeo map;
    map= crear_mapeo(map,10,NULL,NULL);

    int opcion;


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
