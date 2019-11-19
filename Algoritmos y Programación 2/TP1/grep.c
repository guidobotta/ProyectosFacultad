#define _GNU_SOURCE //Sino falla getline
#include <stdio.h>
#include <stdbool.h>
#include <string.h> 
#include <stdlib.h>
#include <ctype.h>

#include "cola.h"

//Algoritmo de busqueda

bool buscar(char* linea, char* palabra){
    for(int i=0; linea[i] != '\0'; i++){
        if(linea[i] == palabra[0]){
            int j = i; //Posicion linea
            int k = 0; //Posicion palabra
            while(true){
                if (palabra[k] == '\0') return true;
                if (palabra[k] != linea[j]) break;
                j++;
                k++;
            }
        }
    }
    return false;
}

//Chequea si es una cadena de numeros

bool es_numero(char* str){
    for(int i=0; i<strlen(str); i++){
        if (!isdigit(str[i])) return false;
    }
    return true;
}

//Ejecucion del programa

void imprimir(FILE* archivo, char* palabra, int nro_consola){
    cola_t* cola_lineas = cola_crear();
    char* linea = NULL;
    size_t tam = 0;
    int cont = 0;
    while (getline(&linea, &tam, archivo) != -1){
        if(!cola_encolar(cola_lineas, strdup(linea))){
            fprintf(stderr, "Error interno\n");
            return;
        }
        if (cont > nro_consola) free(cola_desencolar(cola_lineas));
        cont++;
        if (buscar(linea, palabra)){
            while(!cola_esta_vacia(cola_lineas)){
                char* linea_print = (char*)cola_desencolar(cola_lineas);
                size_t longitud = strlen(linea_print);
                printf("%s", linea_print);
                if(linea_print[longitud-1] != '\n') printf("\n");
                free(linea_print);
                cont = 0;
            }
        }
    }
    while (!cola_esta_vacia(cola_lineas)) free(cola_desencolar(cola_lineas));
    free(linea); //Documentación: Liberar siempre getline
    cola_destruir(cola_lineas, NULL);
}

int main(int argc, char* argr[]){
    if ((argc < 3) || (argc > 4)){ 
        fprintf(stderr, "Cantidad de parametros erronea\n");
        return 1;
    }
    if (!es_numero(argr[2])){
        fprintf(stderr, "Parametros erroneos\n");
        return 1;
    }

    char* palabra = argr[1];
    int nro_consola = atoi(argr[2]);
    FILE* archivo;

    if (argc == 4){
        archivo = fopen(argr[3], "r"); //Si pasan archivo por parametro
    }else {
        archivo = stdin;
    }

    imprimir(archivo, palabra, nro_consola);
    if (argc == 4) fclose(archivo);
    return 0;
}

