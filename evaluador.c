#include <stdio.h>
//#include <stdlib.h>
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
    //char* arr= (char*) p01;
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


/**Procedimiento que permite salir del programa.*/
void salir(FILE *fp){
    fclose(fp);
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
    char arr_no_separador[64]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N(50)','O','P','Q','R','S','T','U','V','W','X','Y','Z','\0'};
    int b_esvalido=1;
    int pos=0;
    while (arr_no_separador[pos]!='\0'&&b_esvalido==1){
        if (c==arr_no_separador[pos])
            b_esvalido=0;
        pos++;
    }

    return b_esvalido;
}

/*Permite cargar en mapeo todas las palabras de archivo                 */
void cargarArchivo(FILE* archivo, tMapeo map){

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
char chr_valido;//int puso_separador=0;
while(!feof(archivo))
{
   chr_valido=fgetc(archivo);
   if (noesSeparador(chr_valido)==0) // es letra o numero
            pArreglo[indice]=chr_valido;

   else     pArreglo[indice]='#';


   indice++;
}
pArreglo[indice]='\0';

rewind(archivo);
fclose(archivo);
return indice;
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
        {//ver porque devuelve null

            printf ("El archivo es archivo invalido.\n"); //Abro el archivo en modo lectura
            return 0;
        }
        else
        {

            if(feof(arch_ascii))
                    printf("El archivo %s esta vacio\n",arch_ascii);
            else
            {


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
                        int ini=0;
                        for(int pos=inicio_palabra;pos<=fin_palabra;pos++)
                        {
                                *(una_palabra+ini)=p_arreglo[pos];
                                ini++;
                        }
                        una_palabra[ini]='\0';

                        //Muestra todas las palabras ingresadas al map
                        int entra=0;
                        for (int pos_r=0;una_palabra[pos_r]!='\0';pos_r++)
                            {printf("%c",una_palabra[pos_r]);
                            entra=1;
                            }
                        if (entra!=0)  printf("\n");


                        tValor valor_x= m_recuperar(map,una_palabra);
                        if (valor_x!=NULL)
                              valor_x= valor_x+1;
                        else valor_x=1;
                        m_insertar(map,una_palabra,valor_x);


                        inicio_palabra=fin_palabra+2;

                    }

                    i++;
                }



                printf("\n");
                printf("Cantidad actual de palabras en mapeo: %d\n",map->cantidad_elementos);
                printf("\n");



            }

        }

    }
    else
    {
        printf ("Hay error en el numero de argumentos\n");
        return 1;
    }






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
            char *cadena;
            cadena=(char*) malloc( sizeof(char)*50 );
            scanf("%[^\n]",cadena);

            tValor valor_rec= m_recuperar(map,cadena);

            if (valor_rec==NULL)
                    {
                        printf("No esta la palabra: '");
                        for (int pos_cad=0;cadena[pos_cad]!='\0';pos_cad++)
                            {printf("%c",cadena[pos_cad]);
                            }
                        printf("'\n");


                    }
            else    {
                       printf("Si esTa la palabra: '");
                       for (int pos_cad=0;cadena[pos_cad]!='\0';pos_cad++)
                            {printf("%c",cadena[pos_cad]);
                            }
                       printf("'\n");
                       printf("Aparece %d veces!\n",valor_rec);
                    }



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






