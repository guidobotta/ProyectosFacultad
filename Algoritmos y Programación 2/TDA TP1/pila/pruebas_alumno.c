#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_con_pila_vacia(){
    printf("~~~PRUEBAS PILA VACIA~~~\n");
    //Declaración de la pila a utilizar
    pila_t* pila = pila_crear();
    print_test("Pila creada", pila != NULL);

    //Inicio de pruebas
    print_test("La pila esta vacía", pila_esta_vacia(pila) == true);
    print_test("Ver tope es NULL", pila_ver_tope(pila) == NULL);
    print_test("Desapilar es NULL", pila_desapilar(pila) == NULL);

    //Destrucción de la pila
    pila_destruir(pila);
    print_test("Se ha destruído la pila", true);
}

void pruebas_basicas_pila(){
    printf("~~~PRUEBAS BASICAS PILA~~~\n");
    //Declaración de la pila a utilizar
    pila_t* pila = pila_crear();
    print_test("Pila creada", pila != NULL);

    //Inicio de pruebas
    //Pruebas de apilado, ver_tope y esta_vacia
    print_test("Apilar NULL", pila_apilar(pila, NULL) == true);
    print_test("Tope es NULL", pila_ver_tope(pila) == NULL);
    print_test("La pila no está vacía", pila_esta_vacia(pila) == false);
    int prueba_num = 5;
    print_test("Apilar un puntero a numero", pila_apilar(pila, &prueba_num) == true);
    print_test("La pila no está vacía", pila_esta_vacia(pila) == false);
    print_test("Tope es el puntero al numero 5", pila_ver_tope(pila) == &prueba_num);
    char prueba_char = 'a';
    long prueba_vector[10] = {1,2,3,4,5,6,7,8,9,123};
    print_test("Apilar un puntero a char", pila_apilar(pila, &prueba_char) == true);
    print_test("Apilar un puntero a vector", pila_apilar(pila, prueba_vector) == true);
    print_test("Tope es el puntero al vector", pila_ver_tope(pila) == prueba_vector);

    //Pruebas de desapilado, ver_tope y esta_vacia
    print_test("Desapilo el vector", pila_desapilar(pila) == prueba_vector);
    print_test("Tope es el puntero al char 'a'", pila_ver_tope(pila) == &prueba_char);
    print_test("Desapilo el char", pila_desapilar(pila) == &prueba_char);
    print_test("Desapilo el numero", pila_desapilar(pila) == &prueba_num);
    print_test("Desapilo NULL", pila_desapilar(pila) == NULL);
    print_test("La pila está vacía", pila_esta_vacia(pila) == true);

    //Destrucción de la pila
    pila_destruir(pila);
    print_test("Se ha destruído la pila", true);
}

void pruebas_volumen_pila(){
    printf("~~~PRUEBAS DE VOLUMEN~~~\n");
    //Declaración de la pila a utilizar
    pila_t* pila = pila_crear();
    print_test("Pila creada", pila != NULL);

    //Inicio de pruebas
    size_t tam = 10000;
    bool verdad = true;

    //Prueba con diez mil enteros
    printf("PRUEBA CON DIEZ MIL ENTEROS\n");
    int* prueba_vector = malloc(tam * sizeof(int));
    for (int i=0; i<tam; i++){
        prueba_vector[i] = i;
        if((!pila_apilar(pila, &prueba_vector[i])) || (pila_ver_tope(pila) != &prueba_vector[i])){
            verdad = false;
            break;
        }
    }
    print_test("Prueba de apilado", verdad);
    print_test("La pila no está vacía", pila_esta_vacia(pila) == false);
    print_test("El tope es el puntero al numero 9999", pila_ver_tope(pila) == &prueba_vector[9999]);

    //Prueba desapilar el resto de enteros
    for (int i=0; i<tam; i++){
        if(pila_desapilar(pila) != &prueba_vector[9999-i]){
            verdad = false;
            break;
        }
    }
    print_test("Prueba de desapilado", verdad);
    print_test("La pila está vacía", pila_esta_vacia(pila) == true);
 
    //Prueba con un millon de chars
    printf("PRUEBA CON UN MILLON DE CHARS\n");
    tam = 1000000;
    verdad = true;
    char* prueba_vector_2 = malloc(tam * sizeof(long));
    for (int i=0; i<tam; i++){
        prueba_vector_2[i] = (char)i;
        if (!pila_apilar(pila, &prueba_vector_2[i]) || (pila_ver_tope(pila) != &prueba_vector_2[i])){
            verdad = false;
            break;
        }
    }
    print_test("Prueba de apilado", verdad);
    print_test("La pila no está vacía", pila_esta_vacia(pila) == false);

    //Prueba de desapilado
    verdad = true;
    for (size_t i = 1; i<=tam; i++){
        if (pila_desapilar(pila) != &prueba_vector_2[tam-i]){
            verdad = false;
            break;
        }
    }
    print_test("Prueba de comparación en desapilado", verdad);

    //Liberar vectores de prueba
    free(prueba_vector);
    free(prueba_vector_2);

    //Destrucción de la pila
    pila_destruir(pila);
    print_test("Se ha destruído la pila", true);
}

void pruebas_memoria_dinamica_pila(){
    printf("~~~PRUEBAS DE MEMORIA DINAMICA~~~\n");
    //Declaración de las pilas a utilizar
    pila_t* pila_1 = pila_crear();
    print_test("Pila 1 creada", pila_1 != NULL);
    pila_t* pila_2 = pila_crear();
    print_test("Pila 2 creada", pila_2 != NULL);

    //Inicio de pruebas
    //Destruir pila 1 teniendo apilada pila 2
    print_test("Apilar Pila 2 en Pila 1", pila_apilar(pila_1, pila_2) == true);
    print_test("La pila 1 no está vacía", pila_esta_vacia(pila_1) == false);
    print_test("La pila 2 está vacía", pila_esta_vacia(pila_2) == true);
    pila_destruir(pila_1);
    print_test("Se ha destruído la pila 1", true);
    int prueba_num = 18;
    print_test("Apilar un puntero a número sobre pila 2", pila_apilar(pila_2, &prueba_num));
    print_test("La pila 2 no está vacía", pila_esta_vacia(pila_2) == false);
    pila_destruir(pila_2);
    print_test("Se ha destruído la pila 2", true);

    //Destruir pila 4 estando dentro de pila 3
    //Declaración de las pilas a utilizar
    pila_t* pila_3 = pila_crear();
    print_test("Pila 3 creada", pila_3 != NULL);
    pila_t* pila_4 = pila_crear();
    print_test("Pila 4 creada", pila_4 != NULL);

    //Inicio de pruebas
    print_test("Apilar pila 4 en pila 3", pila_apilar(pila_3, pila_4) == true);
    print_test("La pila 3 no está vacía", pila_esta_vacia(pila_3) == false);
    print_test("La pila 4 está vacía", pila_esta_vacia(pila_4) == true);
    pila_destruir(pila_4);
    print_test("Se ha destruído la pila 4", true);
    print_test("La pila 3 no está vacía", pila_esta_vacia(pila_3) == false);
    pila_destruir(pila_3);
    print_test("Se ha destruído la pila 3", true);

    //Apilar pila 5 en pila 6 y pila 6 en pila 5
    //Declaración de las pilas a utilizar
    pila_t* pila_5 = pila_crear();
    print_test("Pila 5 creada", pila_5 != NULL);
    pila_t* pila_6 = pila_crear();
    print_test("Pila 6 creada", pila_6 != NULL);

    //Inicio de pruebas
    print_test("Apilar pila 5 en pila 6", pila_apilar(pila_6, pila_5) == true);
    print_test("Apilar pila 6 en pila 5", pila_apilar(pila_5, pila_6) == true);
    print_test("Apilar otra vez pila 5 en pila 6", pila_apilar(pila_6, pila_5) == true);
    pila_destruir(pila_5);
    print_test("Se ha destruído la pila 5", true);
    pila_destruir(pila_6);
    print_test("Se ha destruído la pila 6", true);
}

void pruebas_pila_alumno() {
    pruebas_con_pila_vacia();
    pruebas_basicas_pila();
    pruebas_volumen_pila();
    pruebas_memoria_dinamica_pila();
}