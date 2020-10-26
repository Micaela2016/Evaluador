//#include <stdlib.h>
#include <stdio.h>
#include "mapeo.h"
#include "lista.h"
void f_eliminar(tElemento e);
void m_destruirAux(tMapeo m,void (*fEliminarC)(void *), void (*fEliminarV)(void *));
void destruirEntrada(tElemento e);
void f_eliminar_nada(tElemento e);




static int MAX (int x, int y){
    return x<y?y:x;
}

/**
 Inicializa un mapeo vacío, con capacidad inicial igual al MAX(10, CI).
 Una referencia al mapeo creado es referenciada en *M.
 A todo efecto, el valor hash para las claves será computado mediante la función fHash.
 A todo efecto, la comparación de claves se realizará mediante la función fComparacion.
 Finaliza indicando MAP_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
**/
void crear_mapeo(tMapeo * m, int ci, int (*fHash)(void *), int (*fComparacion)(void *, void *)){
       (*m) = (tMapeo)malloc(sizeof(struct mapeo)) ;

        if((*m)==NULL){
            exit(MAP_ERROR_MEMORIA);
          }
        (*m)->longitud_tabla=MAX(10,ci);
        (*m)->tabla_hash=(tLista*)malloc((sizeof(tLista)*(*m)->longitud_tabla));
        for(int i=0;i<10;i++){
            crear_lista(&((*m)->tabla_hash[i]));
        }

        (*m)->cantidad_elementos=0;
        (*m)->comparador=fComparacion;
        (*m)->hash_code=fHash;
}

void f_eliminar_nada(tElemento e){}

/**
 Inserta una entrada con clave C y valor V, en M.
 Si una entrada con clave C y valor Vi ya existe en M, modifica Vi por V.
 Retorna NULL si la clave C no existía en M, o Vi en caso contrario.
 Finaliza indicando MAP_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
**/
tValor m_insertar(tMapeo m, tClave c, tValor v){
    int n_bloque=m->hash_code(c)%(m->longitud_tabla);
    tValor salida=NULL;

    if(m_recuperar(m,c)!=NULL){
            tPosicion pos= l_primera(m->tabla_hash[n_bloque]);
            int b_encontre=1;
            while(pos!=l_fin(m->tabla_hash[n_bloque])&&(b_encontre==1)){
                tEntrada new_ent=l_recuperar(m->tabla_hash[n_bloque],pos);
                tClave * cc=new_ent->clave;
                if (m->comparador(cc,c)==0 )//0 igual - 1 distinto
                    {b_encontre=0;
                     salida=new_ent->valor;
                     new_ent->valor=v;
                    }
                pos=l_siguiente(m->tabla_hash[n_bloque],pos);
             }
    }
    else{
                    tEntrada m_entrada = (tEntrada) malloc(sizeof(struct entrada));
                    if((m_entrada)==NULL){
                        exit(MAP_ERROR_MEMORIA);
                    }
                    else{
                        m_entrada->clave = c;
                        m_entrada->valor = v;
                        l_insertar(m->tabla_hash[n_bloque],l_primera(m->tabla_hash[n_bloque]),m_entrada);
                        m->cantidad_elementos++;
                    }
         }

        int sobrecarga=(m->longitud_tabla*70)/100;
        if((m->cantidad_elementos)>sobrecarga){
                int DimensionAnterior = m->longitud_tabla;
                int NuevaDimension = (m->longitud_tabla *2);

                tLista* ArregloAnterior= m->tabla_hash;

                m->longitud_tabla = NuevaDimension;
                m->tabla_hash=(tLista*)malloc((sizeof(tLista)*(m)->longitud_tabla));
                if((m)==NULL) exit(MAP_ERROR_MEMORIA);
                else{

                        for(int i = 0; i<NuevaDimension; i++){
                            crear_lista(&(m->tabla_hash[i]));
                        }

                        for(int ii = 0; ii<DimensionAnterior; ii++){
                            tPosicion pos= l_primera(ArregloAnterior[ii]);
                            while (pos!=l_fin(ArregloAnterior[ii]))
                              {
                                tEntrada entrada_a=l_recuperar(ArregloAnterior[ii],pos);
                                int bloque_nuevo=m->hash_code(entrada_a->clave)%(m->longitud_tabla);
                                l_insertar(m->tabla_hash[bloque_nuevo],l_primera(m->tabla_hash[bloque_nuevo]),entrada_a);
                                pos=l_siguiente(ArregloAnterior[ii],pos);
                              }

                            l_destruir(&ArregloAnterior[ii],&f_eliminar_nada);

                         }
                 }

        }


    return salida;
}

void f_eliminar(tElemento e){
        free(e);
        e = NULL;
}

/**
 Elimina la entrada con clave C en M, si esta existe.
 La clave y el valor de la entrada son eliminados mediante las funciones fEliminarC y fEliminarV.
**/
void m_eliminar(tMapeo m, tClave c, void (*fEliminarC)(void *), void (*fEliminarV)(void *)){
    int n_bloque=m->hash_code(c)%(m->longitud_tabla);
    tPosicion pos=l_primera(m->tabla_hash[n_bloque]);
    tEntrada entrada_a;
    int b_encontre=1;
    while(pos!=l_fin(m->tabla_hash[n_bloque])&&(b_encontre==1))
      { entrada_a=l_recuperar(m->tabla_hash[n_bloque],pos);
        tClave cc=entrada_a->clave;
        if( m->comparador(cc,c)==0){
                b_encontre=0;
                fEliminarC(entrada_a->clave);
                fEliminarV(entrada_a->valor);
                m->cantidad_elementos--;
        }
           else pos=l_siguiente(m->tabla_hash[n_bloque],pos);
      }
    if (b_encontre==0)
           l_eliminar(m->tabla_hash[n_bloque],pos,&f_eliminar);
}



void destruirEntrada(tElemento e){
    free(e);
    e=NULL;
}

/**
 Destruye el mapeo M, elimininando cada una de sus entradas.
 Las claves y valores almacenados en las entradas son eliminados mediante las funciones fEliminarC y fEliminarV.
**/
void m_destruir(tMapeo * m, void (*fEliminarC)(void *), void (*fEliminarV)(void *)){
     tMapeo mp=(*m);
     tLista laux;
     int limCant=(*m)->longitud_tabla;

     for(int i=0;i<limCant;i++){
        laux =   (*m)->tabla_hash[i];
        l_destruir(&laux,&destruirEntrada);
     }
     free(mp->tabla_hash);
     free(mp);
     (*m)=NULL;

}
extern void m_destruirAux(tMapeo m,void (*fEliminarC)(void *), void (*fEliminarV)(void *)){
   /** for(int i=0;i<m->longitud_tabla;i++){
        tLista laux=tabla[i];
        tPosicion pos=l_primera(laux);

        while(pos->siguiente!=NULL){
            tEntrada eaux=pos->elemento;
            fEliminarC(&(eaux->clave));
            fEliminarV(&(eaux->valor));

            pos=l_siguiente(laux,pos);
        }
        free(laux);
    }*/
}
/**
 Recupera el valor correspondiente a la entrada con clave C en M, si esta existe.
 Retorna el valor correspondiente, o NULL en caso contrario.
**/
extern tValor m_recuperar(tMapeo m, tClave c){
    tValor salida=NULL;
    int n_bloque=m->hash_code(c)%(m->longitud_tabla);
    if (l_longitud(m->tabla_hash[n_bloque])!=0)
    {   tPosicion pos=l_primera(m->tabla_hash[n_bloque]);
        int b_encontre=1;
        while(pos!=l_fin(m->tabla_hash[n_bloque])&&(b_encontre==1))
          {     tEntrada new_ent=l_recuperar(m->tabla_hash[n_bloque],pos);
                tClave * cc=new_ent->clave;
                if (m->comparador(cc,c)==0 )//0 igual - 1 distinto
                    {   b_encontre=0;
                        salida=new_ent->valor;
                    }
                pos=l_siguiente(m->tabla_hash[n_bloque],pos);
          }
    }
    return salida;
}
