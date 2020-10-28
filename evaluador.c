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

/*  Funcion de comparacion
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



//                                 Funciones de evaluador


//Procedimiento que permite salir del programa.
void salir(FILE *fp){
    fclose(fp);
    printf("\n");
    printf("Programa finalizado!\n");
    exit(0);
}

char noes_Separador(char c){
    char arr_no_separador[60]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9','\0'};
    int b_esvalido=1;
    int pos=0;
    while (arr_no_separador[pos]!='\0'&&b_esvalido==1){
        if (c==arr_no_separador[pos])
            b_esvalido=0;
        pos++;
    }


    return b_esvalido; //0 no un separador(letra o numero), 1 lo es
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





            //INGRESAR CARACTERES DESDE EL ARCHIVO
            if(feof(arch_ascii))
                    printf("El archivo %s esta vacio\n",arch_ascii);
            else
            {

                char palabra_en_ascii[250];
                rewind(arch_ascii);
                int indice_superior=0;
                char chr_valido;
                int puso_separador=0;

                while(!feof(arch_ascii))
                {
                   chr_valido=fgetc(arch_ascii);
                   if (noes_Separador(chr_valido)==0) // es letra o numero
                            palabra_en_ascii[indice_superior]=chr_valido;

                   else     palabra_en_ascii[indice_superior]='#';


                   indice_superior++;
                }
                palabra_en_ascii[indice_superior]='\0';

                rewind(arch_ascii);
                fclose(arch_ascii);

                int i=0;
                int indice_inferior=0;
                int sup=indice_superior;
                while(i<sup)
                {
                    if (palabra_en_ascii[i]=='#')
                    {
                        indice_superior=i-1;
                        char *una_palabra_ascii;
                        una_palabra_ascii=(char*) malloc( sizeof(char)*(indice_superior - indice_inferior + 2) );
                        int ini=0;
                        for(int pos=indice_inferior;pos<=indice_superior;pos++)
                        {
                                *(una_palabra_ascii+ini)=palabra_en_ascii[pos];
                                ini++;
                        }
                        una_palabra_ascii[ini]='\0';

                        //Muestra todas las palabras ingresadas al map
                        int entra=0;
                        for (int pos_r=0;una_palabra_ascii[pos_r]!='\0';pos_r++)
                            {printf("%c",una_palabra_ascii[pos_r]);
                            entra=1;
                            }
                        if (entra!=0)  printf("\n");


                        tValor valor_x= m_recuperar(map,una_palabra_ascii);
                        if (valor_x!=NULL)
                              valor_x= valor_x+1;
                        else valor_x=1;
                        m_insertar(map,una_palabra_ascii,valor_x);


                        indice_inferior=indice_superior+2;

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






