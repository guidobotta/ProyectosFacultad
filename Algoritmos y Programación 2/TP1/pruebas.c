#include "strutil.h"
#include <stdio.h>
#include <stdlib.h>

void pruebas_split(){

    char** prueba_split;
    printf("\n");

    //Prueba 1
    printf("Prueba 1...\n");
    char* prueba_1 = "abc,def0,ghi";
    char sep = ',';
    prueba_split = split(prueba_1, sep);
    printf("%s\n%s\n%s\n%s\n", prueba_split[0], prueba_split[1], prueba_split[2], prueba_split[3]);
    printf("\n");

    //Prueba 2
    printf("Prueba 2...\n");
    char* prueba_2 = "a0bc,,def";
    prueba_split = split(prueba_2, sep);
    printf("%s\n%s\n%s\n%s\n", prueba_split[0], prueba_split[1], prueba_split[2], prueba_split[3]);
    printf("\n");

    //Prueba 3
    printf("Prueba 3...\n");
    char* prueba_3 = "asdabc,def,";
    prueba_split = split(prueba_3, sep);
    printf("%s\n%s\n%s\n%s\n", prueba_split[0], prueba_split[1], prueba_split[2], prueba_split[3]);
    printf("\n");

    //Prueba 4
    printf("Prueba 4...\n");
    char* prueba_4 = ",abc,def";
    prueba_split = split(prueba_4, sep);
    printf("%s\n%s\n%s\n%s\n", prueba_split[0], prueba_split[1], prueba_split[2], prueba_split[3]);
    printf("\n");

    //Prueba 5
    printf("Prueba 5...\n");
    char* prueba_5 = "abc";
    sep = '\0';
    prueba_split = split(prueba_5, sep);
    printf("%s\n%s\n", prueba_split[0], prueba_split[1]);
    printf("\n");

    //Prueba 6
    printf("Prueba 6...\n");
    char* prueba_6 = ",";
    sep = ',';
    prueba_split = split(prueba_6, sep);
    printf("%s\n%s\n%s\n", prueba_split[0], prueba_split[1], prueba_split[2]);
    printf("\n");

    //Prueba 7
    printf("Prueba 7...\n");
    prueba_split = split("", sep);
    printf("%s\n%s\n", prueba_split[0], prueba_split[1]);
    printf("\n");
}

void pruebas_join(){
    char** prueba_split;
    char* prueba_join;
    char sep;

    //Prueba 1
    printf("Prueba 1...\n");
    char* prueba_1 = "abc,def,ghi";
    sep = ',';
    prueba_split = split(prueba_1, sep);
    prueba_join = join(prueba_split, sep);
    printf("|%s|\n", prueba_join);
    printf("\n");
    
    //Prueba 2
    printf("Prueba 2...\n");
    char* prueba_2 = "";
    sep = ',';
    prueba_split = split(prueba_2, sep);
    prueba_join = join(prueba_split, sep);
    printf("|%s|\n", prueba_join);
    printf("\n");
    
    //Prueba 3
    printf("Prueba 3...\n");
    char* prueba_3 = "hola,como,estas?";
    sep = ',';
    prueba_split = split(prueba_3, sep);
    sep = ' ';
    prueba_join = join(prueba_split, sep);
    printf("|%s|\n", prueba_join);
    printf("\n");
    
    //Prueba 4
    printf("Prueba 4...\n");
    char* prueba_4 = "abc";
    sep = '\0';
    prueba_split = split(prueba_4, sep);
    sep = ',';
    prueba_join = join(prueba_split, sep);
    printf("|%s|\n", prueba_join);
    printf("\n");
    
    //Prueba 5
    printf("Prueba 5...\n");
    char* prueba_5 = ",";
    sep = '\0';
    prueba_split = split(prueba_5, sep);
    sep = ',';
    prueba_join = join(prueba_split, sep);
    printf("|%s|\n", prueba_join);
    printf("\n");

    //Prueba 6
    printf("Prueba 6...\n");
    char* prueba_6[1] = {NULL};
    sep = ',';
    prueba_join = join(prueba_6, sep);
    printf("|%s|\n", prueba_join);
    printf("\n");
}

void pruebas_ferror(){
    fprintf(stderr, "Houston, tenemos un problema\n");
}

void pruebas_free_stvr(){
    char** prueba_vector = split("hola como estas", ' ');
    printf("%s\n", prueba_vector[0]);
    free_strv(prueba_vector);
    
    char* prueba_palabra;
    char** prueba_2 = split("hola como", ' ');
    prueba_palabra = join(prueba_2, ' ');
    printf("%s\n", prueba_palabra);
    free(prueba_palabra);
    free_strv(prueba_2);
}

int main(){
    //pruebas_free_stvr();
    pruebas_split();
    pruebas_join();
    //pruebas_ferror();
    return 0;
}