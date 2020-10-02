#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

/**
 Inicializa una lista vacía.
 Una referencia a la lista creada es referenciada en *L.
 Finaliza indicando LST_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
**/
void crear_lista(tLista * l){
    (*l)= (tLista) malloc (sizeof(struct celda)); //Se reserva memoria para la estructura lista, iniciando su cantidad de elementos
    (*l)->elemento=NULL;
    (*l)->siguiente=NULL;
    if ((*l)== NULL)
        exit(LST_ERROR_MEMORIA);
}

/**
 Inserta el elemento E, en la posición P, en L.
 Con L = A,B,C,D y la posición P direccionando C, luego:
 L' = A,B,E,C,D.
 Finaliza indicando LST_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
**/

//PREGUNTAR SI L ES NULL QUE PASA? ES EL MISMO ERROR O TIENE QUE SER OTRO
void l_insertar(tLista l, tPosicion p, tElemento e){
    if (l==NULL || p==NULL)
        exit(LST_POSICION_INVALIDA);
    tPosicion posNueva= (tPosicion) malloc(sizeof(struct celda));
    if (posNueva==NULL)
        exit(LST_ERROR_MEMORIA);
    posNueva->elemento=e;
    posNueva-> siguiente = p->siguiente;
    p->siguiente= posNueva;
}

/**
 Elimina la celda P de L.
 El elemento almacenado en la posición P es eliminado mediante la función fEliminar.
 Finaliza indicando LST_POSICION_INVALIDA si P es fin(L).
**/
void l_eliminar(tLista l, tPosicion p, void (*fEliminar)(tElemento)){

}

/**
 Destruye la lista L, elimininando cada una de sus celdas.
 Los elementos almacenados en las celdas son eliminados mediante la función fEliminar.
**/
void l_destruir(tLista * l, void (*fEliminar)(tElemento)){

}

 /**
 Recupera y retorna el elemento en la posición P.
 Finaliza indicando LST_POSICION_INVALIDA si P es fin(L).
**/
tElemento l_recuperar(tLista l, tPosicion p){
    if (p==NULL || (p->siguiente)==NULL)
        exit(LST_POSICION_INVALIDA);
    return (p->siguiente)->elemento;
}

/**
 Recupera y retorna la primera posición de L.
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_primera(tLista l){
    return l;
}

/**
 Recupera y retorna la posición siguiente a P en L.
 Finaliza indicando LST_NO_EXISTE_SIGUIENTE si P es fin(L).
**/
tPosicion l_siguiente(tLista l, tPosicion p){
    if(p->siguiente==NULL)   //Ver si usar la funcion fin
        exit(LST_NO_EXISTE_SIGUIENTE);
    return p->siguiente;
}

/**
 Recupera y retorna la posición anterior a P en L.
 Finaliza indicando LST_NO_EXISTE_ANTERIOR si P es primera(L).
**/
tPosicion l_anterior(tLista l, tPosicion p){

}

/**
 Recupera y retorna la última posición de L.
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_ultima(tLista l){
    tPosicion ultima;
    //falta toda la funcion
    return ultima;
}

/**
 Recupera y retorna la posición fin de L.
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_fin(tLista l){
    tPosicion ultima = l;
    while(ultima->siguiente!=NULL)
        ultima= ultima->siguiente;
    return ultima;

}

/**
 Retorna la longitud actual de la lista.
**/
int l_longitud(tLista l){
    int contador = 0;
    tPosicion pos = l;
    while(pos->siguiente != NULL){
        contador++;
        pos = pos->siguiente;
    }
    return contador;
}
