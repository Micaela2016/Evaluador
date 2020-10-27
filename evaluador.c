#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include "mapeo.h"

//                        Funciones auxiliares de mapeo
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

/*  Funcion de comparacion
    Tiene como objetivo comparar dos elementos pasados por parametro.
    Utiliza la funcion strcmp de la libreria string.
    Retorna:
    -0 Si las cadenas son iguales
    -Valor positivo si la primera cadena es mayor
    -Valor negativo si la primera cadena es menor.
*/
int fComparacion2(void* p01,void* p02){
    int result;
    char * pa = p01;
    char * pb = p02;
    return result= strcmp(pa,pb);
}

int fComparacion(void* p01,void* p02){

    int * pa;
    pa= p01;
    int * pb;
    pb= p02;
    int pos=0;
    int primero=*pa;
    int segundo=*pb;
    int esigual=0;
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

/*  Funcion hash
    Tiene como objetivo generar un codigo unico que identifica al elemento pasado por parametro
*/
 int fHash2(void* p01){
    char* arr= (char*) p01;
    int suma=0;
    int pos=0;
    /*int primero=*parr;
    while (primero!=0 )
    {
        primero=*(parr+pos);
        suma=suma+primero;
        pos++;
    }*/
    return  (suma/(pos-1) );
}

 int fHash(void* p01){
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

//                                 Funciones de evaluador


//Procedimiento que permite salir del programa.
void salir(FILE *fp){
    fclose(fp);
    printf("\n");
    printf("Programa finalizado!\n");
    exit(0);
}


int main(int argc, char *argv[]){

    tMapeo map;
    crear_mapeo(&map, 9, &fHash,&fComparacion );

printf("============================================ EVALUADOR DE ARCHIVO DE CARACTERES ASCII ==========================================================\n");

   if(argc==2)
    {
        char* nombre_arc = argv[1];
        FILE* arch_ascii;
        if((arch_ascii= fopen(nombre_arc,"r"))==NULL)
        {

            printf ("El archivo es archivo invalido.\n"); //Abro el archivo en modo lectura
            return 0;
        }
        else
        {

            printf("%s\n",arch_ascii);

            if(feof(arch_ascii))
                    printf("El archivo %s esta vacio\n",arch_ascii);
            else
            {   int palabra_en_ascii[250];
                rewind(arch_ascii);
                int indice_superior=0;
                while(!feof(arch_ascii))
                {
                   fscanf(arch_ascii,"%d",&palabra_en_ascii[indice_superior]);
                   indice_superior++;
                }
                rewind(arch_ascii);
                fclose(arch_ascii);

                int i=0;
                int indice_inferior=0;
                int sup=indice_superior;
                while(i<sup)
                {
                    if (palabra_en_ascii[i]==255)
                    {
                        indice_superior=i-1;
                        int *una_palabra_ascii;
                        una_palabra_ascii=(int*) malloc( sizeof(int)*(indice_superior - indice_inferior + 2) );
                        int ini=0;
                        for(int pos=indice_inferior;pos<=indice_superior;pos++)
                        {
                                *(una_palabra_ascii+ini)=palabra_en_ascii[pos];
                                ini++;
                        }
                        una_palabra_ascii[ini]=0;
                        int valor1=1;//PREGUNTAR QUE VA EN VALOR??
                        m_insertar(map,una_palabra_ascii,&valor1);

                        indice_inferior=indice_superior+2;

                    }

                    i++;
                }


                printf("\n");
                printf("Cantidad actual de palabras en mapeo: %d\n",map->cantidad_elementos);
                printf("\n");

               /*************YA TENGO CARGADO EN MAPEO LO QUE LEI DEL ARCHIVO***********************/



            }

        }

    }
    else
    {
        printf ("Hay error en el numero de argumentos\n");
        return 1;
    }





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
            //operar en mapeo: buscar esta clave en el mapeo y devolver su valor


            fflush(stdin);
            break;
        }
        case 2:{
            salir = 1;
            printf("opcion 2>>");
            printf("Eso es todo! \n");
            break;
        }
        default:{
            printf("La opcion ingresada no es correcta \n");
        }
        }
    }


}






