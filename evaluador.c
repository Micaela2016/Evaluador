#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapeo.h"

//                        Funciones auxiliares de mapeo
/** Es un procedimiento que elimina y libera la memoria de la clave que es pasada por parametro*/
void fEliminarC (void* clave){
    tClave c= (tClave) clave;
    free(c);
    c= NULL;
}

/** Es un procedimiento que elimina y libera la memoria del valor que es pasado por parametro*/
void fEliminarV(void* valor){
    tClave v= (tValor) valor;
    free(v);
    v= NULL;
}

/**  fComparacion: Funcion de comparacion
    Tiene como objetivo comparar dos elementos pasados por parametro.
    Utiliza la funcion strcmp de la libreria string.
    Retorna:
            -0 Si las cadenas son iguales
            -Valor positivo si la primera cadena es mayor
            -Valor negativo si la primera cadena es menor.
*/
int fComparacion(void* p01,void* p02){
    int result;
    char * pa = p01;
    char * pb = p02;
    return result= strcmp(pa,pb);
}

/**   fhash: Funcion hash
    Tiene como objetivo generar un codigo unico que identifica al elemento pasado por parametro
*/
 int fHash(void* p01){
    int g = 31;
    int longitud = strlen(p01);
    int result = 0;
    char * string = p01;

    for(int i = 0 ; i < longitud ; i++){
        result = g * result + string[i];
    }

    return result;
}



//                                Funciones de evaluador

/*Permite determinar si la palabra ingresada pertenece o no al archivo.Si pertenece retorna cuantas veces aparece.*/
tValor cantApariciones (tMapeo mapeo, char* aBuscar){
    tValor toReturn=0;
    if(mapeo!= NULL){
        if(mapeo->cantidad_elementos!=0){                   //Si el mapeo no esta vacio.

            if(m_recuperar(mapeo, aBuscar) != NULL){          //Si la palabra pertenece al mapeo .
                toReturn=m_recuperar(mapeo, aBuscar);
            }
            else {
                toReturn=NULL;
            }
        }
    }
return toReturn;
}

/**Procedimiento que permite salir del programa.*/
void salir(FILE *fp, tMapeo map){
    fclose(fp);
    m_destruir(&map, &fEliminarC, &fEliminarV);
    printf("\n");
    printf("Programa finalizado!\n");
    exit(0);
}

/**
      Esta funcion tiene como objetivo decir que si c, caracter pasado por parametro, es letra o numero.
    Retorna:
    -0 Si el caracter c es letra o numero (no es un separador).
    -1 Si c no es letrra o numero(es un separador).
*/
int noesSeparador(char c){
    char arr_no_separador[64]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','\0'};
    int b_esvalido=1;
    int pos=0;
    while (arr_no_separador[pos]!='\0'&&b_esvalido==1){
        if (c==arr_no_separador[pos])
            b_esvalido=0;
        pos++;
    }

    return b_esvalido;
}


//INGRESAR CARACTERES DESDE EL ARCHIVO A UN ARREGLO (PERO QUIERO UNPUNTERO)
/**
      Esta funcion carga el contenido de un archivo, a un puntero de char y
    devuelve la cantidad de caracteres que habia en el.
    Cuando el un caracter del archivo era un separador al puntero a char se le agrega un #
    para luego que sea util separar las palabras.
*/
int cargarEn_pArreglo(FILE* archivo,char * pArreglo){

rewind(archivo);
int indice=0;
char chr_valido;
while(!feof(archivo))
{
   chr_valido=fgetc(archivo);
   if (noesSeparador(chr_valido)==0) // es letra o numero
            pArreglo[indice]=chr_valido;

   else     pArreglo[indice]='#';


   indice++;
}
pArreglo[indice]='\0';

rewind(archivo);                                                                           // NO SE CIERRA el archivo aca
fclose(archivo);
return indice;
}



/**
      Permite pasar palabras de un puntero a otro
      inicio: Indica la pocion desde donde empieza a copiar los caracteres.
      Fin: indica la posicion hasta donde termina de copiar los caracteres.
*/
void Pasar_unaPalabra(int inicio,int fin, char * pArreglo,char *P_unaPalabra){

    int ini=0;
    for(int pos=inicio;pos<=fin;pos++)
    {
            P_unaPalabra[ini]=pArreglo[pos];
            ini++;
    }
    P_unaPalabra[ini]='\0';

}


int main(int argc, char *argv[]){

    tMapeo map;
    crear_mapeo(&map, 9, &fHash,&fComparacion );

    //----------------------------------ARCHIVO---------------------------------
    FILE* arch_ascii;

    if(argc <= 1){
        printf("Falta parametros por ingresar!\n");
        exit(0);
    }

    arch_ascii= fopen (argv[1],"r");                //Abro el archivo en modo lectura

    if((arch_ascii)==NULL){
        printf ("El archivo es archivo invalido.\n");
        exit(0);
    }



                //INGRESAR CARACTERES DESDE EL ARCHIVO A UN PUNTERO DE CHAR
                char *p_arreglo;
                p_arreglo=(char*) malloc( sizeof(char)*150 );
                int long_pArreglo= cargarEn_pArreglo(arch_ascii, p_arreglo);


                //INGRESAR PALABRAS DE P_ARREGLO A PUNTEROS DE TIPO TCLAVE Y LUEGO SE LAS AGREGA EN EL MAPEO
                int i=0;
                int inicio_palabra=0;
                int fin_palabra=0;
                while(i<long_pArreglo)
                {
                    if (p_arreglo[i]=='#')
                    {
                        fin_palabra=i-1;
                        char *una_palabra;
                        una_palabra=(char*) malloc( sizeof(char)*(fin_palabra - inicio_palabra + 2) );
                        Pasar_unaPalabra(inicio_palabra,fin_palabra,p_arreglo,una_palabra);


                        //Muestra todas las palabras ingresadas al map
                        int entra=0;
                        for (int pos_r=0;una_palabra[pos_r]!='\0';pos_r++)
                            {printf("%c",una_palabra[pos_r]);
                            entra=1;
                            }
                        if (entra!=0)  printf("\n");


                        int *valor;
                        valor=(int*) malloc( sizeof(int) );
                        valor[0]=(int) m_recuperar(map,una_palabra);
                        if (valor[0]!=0)
                              valor[0]= valor[0]+1;
                        else
                              valor[0]=1;
                        m_insertar(map,una_palabra,(tValor)valor[0]);




                        inicio_palabra=fin_palabra+2;

                    }

                    i++;
                }



                printf("\n");
                printf("Cantidad actual de palabras en mapeo: %d\n",map->cantidad_elementos);
                printf("\n");

//----------------------------------MENU-------------------------------------

    char cadena [250];
    int  salida = 0;
    int opcion=0;
    while (!salida){
        printf("                                  Menu\n");
        printf("1: Mostrar cantidad de apariciones de una palabras\n");
        printf("2: Salir\n");
        printf("============= Ingrese una opcion =============\n");

        scanf("%d", &opcion);
        fflush(stdin);

        if (opcion == 1||opcion == 2 ){
            printf("========== =============== =============\n");
            printf("Eligio >>");
            fflush(stdin);
        }

        switch(opcion){
        case 1:{
            printf("Opcion 1 \n");
            printf("Ingrese una palabra: ");
            scanf("%s",(char*)&cadena);
            printf("\n");
            tValor apariciones= cantApariciones (map, cadena);
            if(apariciones != NULL){
                int cant= (int) apariciones;
                printf("La palabra '%s' pertenece al archivo y aparece %i veces.\n", cadena,cant);
            }
            else
                printf("La palabra '%s' no pertenece al archivo!\n", cadena);
            fflush(stdin);
            break;
        }
        case 2:{
            salida = 1;
            printf("opcion 2\n");
            printf("Eso es todo! \n");
            salir(arch_ascii, map);
            break;
        }
        default:{
            printf("La opcion ingresada no es correcta \n");
        }
        }
    }




}






