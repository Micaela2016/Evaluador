#include <stdio.h>
#include <stdlib.h>
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

/*  Funcion comparacion
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

/*  Funcion hash
    Tiene como objetivo generar un codigo unico que identifica al elemento pasado por parametro
*/
 int fHash(void* p01){
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
    printf("CREAR MAPEO\n");
    crear_mapeo(&map, 9, fHash,fComparacion );
    printf("El size del mapeo es %i\n", sizeof(*map));

    int clave01[5]={260,50,0};
    int valor1=10;
    int clave02[5]={350,50,0};
    int valor2=20;
    int clave03[5]={260,50,0};
    int valor3=20;
    int clave04[5]={150,50,0};
    int valor4=20;
    int clave05[5]={550,50,0};
    int valor5=20;
    int clave06[5]={450,50,0};
    int valor6=20;
    int clave07[5]={950,50,0};
    int valor7=20;
    printf("F hash %d\n",fHash(clave01));
    printf("F hash %d\n",fHash(clave02));
    printf("F Comparacion: 0 igual - 1 dis . es: %d\n",fComparacion(clave01,clave02));
    m_insertar(map,clave01,&valor1);
    m_insertar(map,clave02,&valor2);
    m_insertar(map,clave03,&valor3);
    m_insertar(map,clave04,&valor4);
    m_insertar(map,clave05,&valor5);
    m_insertar(map,clave06,&valor6);
    m_insertar(map,clave07,&valor7);

    for(int i = 0; i<map->longitud_tabla; i++){

        tPosicion pos=l_primera(map->tabla_hash[i]);
        while(pos!=l_fin(map->tabla_hash[i]))
          {     tEntrada new_ent=l_recuperar(map->tabla_hash[i],pos);
                tClave * cc=new_ent->clave;
                printf("clave: %d bucket: %d\n",*cc,i);

                pos=l_siguiente(map->tabla_hash[i],pos);
          }

    }

    tValor *vv=m_recuperar(map,clave02); //recupera alguien que no esta
    if (vv==NULL)
    {    printf("La entrada con clave {");
        for (int i=0;clave02[i];i++)
            printf("%d ",clave02[i]);
        printf("} no esta.");
        printf("\n");

    }
    else   printf("La entrada si esta y tiene valor: %d\n",*vv);
    printf("cant actual 01 en map xx:%d\n",map->cantidad_elementos);
    m_eliminar(map,clave01,&fEliminarC,&fEliminarV);
    m_eliminar(map,clave03,&fEliminarC,&fEliminarV);
    m_eliminar(map,clave01,&fEliminarC,&fEliminarV);
    printf("cant actual 02 en mapeoxx:%d\n",map->cantidad_elementos);

    m_destruir(&map,&fEliminarC,&fEliminarV);


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






