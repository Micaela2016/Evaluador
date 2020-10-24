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

int fComparacion(void* p01,void* p02){

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


int main(int argc, char *argv[]){

    tMapeo map;
    printf("CREAR MAPEO\n");
    crear_mapeo(&map, 9, fHash,fComparacion );
    printf("El size del mapeo es %i\n", sizeof(*map));

    int arr01[5]={260,50,0};
    int valor1=10;
    int arr02[5]={260,50,0};
    int valor2=20;
    printf("F hash %d\n",fHash(arr01));
    printf("F Compa %d\n",fComparacion(arr01,arr02));//0 ig - 1 dis
    m_insertar(map,arr01,&valor1);
    tValor *vv=m_recuperar(map,arr02);
    printf("valor de salidaxx:%d\n",*vv);

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

            printf("%s\n",archivo_ascii);

            if(feof(archivo_ascii))
            {
                    printf("El archivo %s esta vacio\n",archivo_ascii);
            }
            else
            {
                rewind(archivo_ascii);
                char arr_archivo[250];
                char *p_archivo;
                int indic=0;
                while(!feof(archivo_ascii))
                {
                    arr_archivo[indic]=fgetc(archivo_ascii);
                    indic++;



                }
                indic=0;
                printf("{");
                  while(arr_archivo[indic]!='\0')
                {

                    printf("%c ",arr_archivo[indic]);
                    indic++;



                }
                printf("}");
                printf("\n");
                printf("================fin contenido==============\n");



                rewind(archivo_ascii);
                fclose(archivo_ascii);


                /*************CARGAR EN MAPEO LO QUE LEI DEL ARCHIVO***********************/
                //TENGO UN ARREGLO DE CARCTERES YA CAGADO: arr_archivo
                //RESTA PASAR LAS PALABRAS AL MAPEO



                int i=0;
                int pri=0;
                //sin punteros recorro el arreglo
                while(arr_archivo[i]!=0)
                {
                    if (arr_archivo[i]==255)
                        { int sup=i-1;
                          printf("%i ",pri);
                          printf("%i \n",sup);
                          //n-esima palabra
                          for(int pos=pri;pos<=sup;pos++)
                            {
                                printf("%c ",arr_archivo[pos]);
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
                        printf("%c ",arr_archivo[ult]);
                    }
                printf("\n");






                /***************************************/




            }

        }

    }
    else
    {
        printf ("Hay error en el numero de argumentos\n");
        return 1;
    }

    //insertar palabras del archivo al mapeo





    //asumo que tengo el archivo en un arreglo



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






