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
    tMapeo map= (tMapeo) malloc (sizeof(struct trie));
    map= crear_mapeo();

    int opcion;














}
