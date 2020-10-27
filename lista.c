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
     if ((*l)!= NULL){
        (*l)->elemento=NULL;
        (*l)->siguiente=NULL;
     }
    else    exit(LST_ERROR_MEMORIA);
}

/**
 Inserta el elemento E, en la posición P, en L.
 Con L = A,B,C,D y la posición P direccionando C, luego:
 L' = A,B,E,C,D.
 Finaliza indicando LST_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.

 Situaciones:
 -Si la posicion pasada por parametro no existe entpnces debe abortar la ejecucion.
 -Si fue posible reservar memoria entonces debe insertar el elemento.
 -Si no fue posible reservar memoria entonces debe abortar la ejecucion.
 Observacion: Omitimos chequear si la lista no fue creada previamente
**/

void l_insertar(tLista l, tPosicion p, tElemento e){
    if (l==NULL || p==NULL)
        exit(LST_POSICION_INVALIDA);
    tPosicion posNueva= (tPosicion) malloc(sizeof(struct celda));
    if (posNueva!=NULL){
        posNueva->elemento=e;
        posNueva-> siguiente = p->siguiente;
        p->siguiente= posNueva;
    }
    else  exit(LST_ERROR_MEMORIA);
}

/**
 Elimina la celda P de L.
 El elemento almacenado en la posición P es eliminado mediante la función fEliminar.
 Finaliza indicando LST_POSICION_INVALIDA si P es fin(L).

**/
void l_eliminar(tLista l, tPosicion p, void (*fEliminar)(tElemento)){
    if (p->siguiente!=NULL){
        tPosicion elim;
        elim= p->siguiente;
        p->siguiente= elim->siguiente;
        fEliminar(elim->elemento);
        elim->siguiente=NULL;
        elim->elemento=NULL;
        free(elim);
    }
    else exit (LST_POSICION_INVALIDA);
}
/**
 Procedimiento auxiliar recursivo para destruir todos los los elementos de la lista.
 Caso base:
    Si tengo un solo elemento en la lista, Eliminar ese elemento de la lista y tambien su posicion.
 Caso recursivo:
    Si tengo mas de un solo elemento en la lista entonces:
        Debo eliminar el elemento de la lista y su posicion.

**/
static void destruirAux(void (*fEliminar)(tElemento),tPosicion pos){
    if(pos->siguiente!=NULL)
        destruirAux(fEliminar, pos->siguiente);

    fEliminar(pos->elemento);
    pos->elemento = NULL;
    pos->siguiente =NULL;
    free(pos);
}


/**
 Destruye la lista L, elimininando cada una de sus celdas.
 Los elementos almacenados en las celdas son eliminados mediante la función fEliminar.
**/
void l_destruir(tLista * l, void (*fEliminar)(tElemento)){

    tPosicion pos = *l;                         //Primera posicion

    if(pos->siguiente!=NULL){
        destruirAux(fEliminar, pos->siguiente);
    }

    pos->siguiente = NULL;                      //Elimina celda de encabezamiento.
    pos->elemento = NULL;
    free(pos);
    *l = NULL;                                  //Destruye lista
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
    tPosicion pos=l;
    if (p!=l){
        while (pos->siguiente!=p)
            pos=pos->siguiente;
    }
    else exit(LST_NO_EXISTE_ANTERIOR);
    return pos;
}

/**
 Recupera y retorna la última posición de L.
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_ultima(tLista l){
    tPosicion ultima, retorno;
    retorno= (tPosicion)l;
    ultima= (tPosicion)l->siguiente;
    while (ultima->siguiente!=NULL){
        retorno=ultima;
        ultima= ultima->siguiente;
    }
    return retorno;
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
