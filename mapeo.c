#include <stdlib.h>
#include "mapeo.h"
#include "lista.h"



/**
 Inicializa un mapeo vacío, con capacidad inicial igual al MAX(10, CI).
 Una referencia al mapeo creado es referenciada en *M.
 A todo efecto, el valor hash para las claves será computado mediante la función fHash.
 A todo efecto, la comparación de claves se realizará mediante la función fComparacion.
 Finaliza indicando MAP_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
**/

typedef void* tabla[10];

void crear_mapeo(tMapeo * m, int ci, int (*fHash)(void *), int (*fComparacion)(void *, void *)){
    if((*m)!=NULL){
        (*m)=(tMapeo)malloc(sizeof(struct mapeo));
        (*m)->cantidad_elementos=0;
        (*m)->longitud_tabla=10;
         tLista l;
         crear_lista(&l);
        (*m)->tabla_hash=(&l);

        (*m)->comparador=fComparacion;
        (*m)->hash_code=fHash;

        for(int i=0;i<10;i++){
            tLista tl;
            crear_lista(&tl);
            tabla[i]=&tl;
        }
    }
    else
        exit(MAP_ERROR_MEMORIA);
}

/**
 Inserta una entrada con clave C y valor V, en M.
 Si una entrada con clave C y valor Vi ya existe en M, modifica Vi por V.
 Retorna NULL si la clave C no existía en M, o Vi en caso contrario.
 Finaliza indicando MAP_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
**/
tValor m_insertar(tMapeo m, tClave c, tValor v){

    int hashC=m->hash_code(c)%(m->longitud_tabla);

    tEntrada * ent;
    (*ent)=(tEntrada)malloc(sizeof(struct entrada));
    (*ent)->clave=&c;
    (*ent)->valor=&v;
    tLista lisAux=tabla[hashC];
    l_insertar(lisAux,l_fin,(*ent));
    l_insertar(m->tabla_hash,l_fin,(*ent))

    int sobrecarga=(m->longitud_tabla*75)/100;
    if((m->cantidad_elementos)>sobrecarga){
       void* aux[10*(m->longitud_tabla)];
       int cont=0;
       while(cont!=m->cantidad_elementos){
          for(int j=0;j<m->longitud_tabla;j++){
            tLista laux=*(tabla[j]);
            for(int i=0;i<l_longitud(laux);i++){
                aux[j]=l_fin();
                l_eliminar(laux,l_fin(laux),fEliminar(tElemento));

                cont++;
             }
          }
       }
       tabla[m->longitud_tabla*10];
       m->longitud_tabla=10*10;
       for(int k=0;k<=m->cantidad_elementos;k++){
            tLista tl;
            crear_lista(&tl);
            tabla[i]=&tl;
       }
       for(int h=0;h<m->cantidad_elementos;h++){
            int hc=m->hash_code(&c)%(m->longitud_tabla);
            tLista laux=tabla[hc];
            l_insertar(laux,l_fin,);
            tabla[hc]=aux[h];
       }
    }

}




/**
 Elimina la entrada con clave C en M, si esta existe.
 La clave y el valor de la entrada son eliminados mediante las funciones fEliminarC y fEliminarV.
**/
void m_eliminar(tMapeo m, tClave c, void (*fEliminarC)(void *), void (*fEliminarV)(void *)){

}

/**
 Destruye el mapeo M, elimininando cada una de sus entradas.
 Las claves y valores almacenados en las entradas son eliminados mediante las funciones fEliminarC y fEliminarV.
**/
void m_destruir(tMapeo * m, void (*fEliminarC)(void *), void (*fEliminarV)(void *)){

}

/**
 Recupera el valor correspondiente a la entrada con clave C en M, si esta existe.
 Retorna el valor correspondiente, o NULL en caso contrario.
**/
tValor m_recuperar(tMapeo m, tClave c){

    int hashC=m->hash_code(c)%(m->longitud_tabla);

    tLista laux=tabla[hashC];
    tValor salida=NULL;

    tEntrada tAux1=l_primera(laux)->elemento;
    tEntrada taux2=l_fin(laux)->elemento;

    int encontrado=0;
    while(((m->comparador(tAux1->clave,taux2->clave)!=0)&&(encontrado==0)){
        if((m->comparador(c,tAux1->clave))==0){
            encontrado=1;
            salida=tAux1->valor;
        }
    }

    return salida;
}
