#include "testing.h"
#include "cola.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

void pruebas_cola_vacia(){
    printf("~~~PRUEBAS COLA VACIA~~~\n");
    //Declaración de la cola a usar
    cola_t* cola = cola_crear();
    print_test("Cola creada", cola != NULL);

    //Inicio de pruebas
    print_test("La cola esta vacía", cola_esta_vacia(cola) == true);
    print_test("Ver primero devuelve NULL", cola_ver_primero(cola) == NULL);
    print_test("Desencolar es NULL", cola_desencolar(cola) == NULL);

    //Destrucción de la cola
    cola_destruir(cola, NULL);
    print_test("Cola destruída", true);
}

void pruebas_basicas(){
    printf("~~~PRUEBAS BASICAS COLA~~~\n");
    //Declaración de la cola a usar
    cola_t* cola = cola_crear();
    print_test("Cola creada", cola != NULL);

    //Inicio de pruebas
    //Pruebas de encolado (incluido NULL), ver_primero y esta_vacia
    int num = 18;
    char letra = 'a';
    long vector[5] = {1532, 4565134, -7744113, 12345, 0};
    print_test("Encolar NULL", cola_encolar(cola, NULL));
    print_test("La cola no está vacía", cola_esta_vacia(cola) == false);
    print_test("Encolar puntero a numero 18", cola_encolar(cola, &num) == true);
    print_test("Encolar puntero a letra 'a'", cola_encolar(cola, &letra) == true);
    print_test("Encolar puntero a vector", cola_encolar(cola, vector));
    print_test("El primero es NULL", cola_ver_primero(cola) == NULL);

    //Prueba de desencolado, ver_primero y esta_vacia
    print_test("Desencolar NULL", cola_desencolar(cola) == NULL);
    print_test("La cola no está vacía", cola_esta_vacia(cola) == false);
    print_test("El primero es el puntero al numero 18", cola_ver_primero(cola) == &num);
    print_test("Desencolar el puntero al numero 18", cola_desencolar(cola) == &num);
    print_test("La cola no está vacía", cola_esta_vacia(cola) == false);
    print_test("El primero es el puntero a la letra 'a'", cola_ver_primero(cola) == &letra);
    print_test("Desencolar el puntero a la letra 'a'", cola_desencolar(cola) == &letra);
    print_test("La cola no está vacía", cola_esta_vacia(cola) == false);
    print_test("El primero es el puntero al vector", cola_ver_primero(cola) == vector);
    print_test("Desencolar el puntero al vector", cola_desencolar(cola) == vector);
    print_test("La cola está vacía", cola_esta_vacia(cola) == true);

    //Destrucción de la cola
    cola_destruir(cola, NULL);
    print_test("Cola destruída", true);
}

void pruebas_volumen(){
    printf("~~~PRUEBAS DE VOLUMEN~~~\n");
    //Declaración de la cola a usar
    cola_t* cola = cola_crear();
    print_test("Cola creada", cola != NULL);

    //Inicio de pruebas
    size_t tam;
    bool verdad;

    //Prueba con cien mil enteros
    tam = 100000; //Prueba realizada con 1 millon exitosa
    verdad = true;
    int* vector_prueba = malloc(tam * sizeof(int));
    for (int i=0; i<tam; i++){
        vector_prueba[i] = i;
        cola_encolar(cola, &vector_prueba[i]);
        if (cola_ver_primero(cola) != &vector_prueba[0]){
            verdad = false;
            break;
        }
    }
    print_test("Prueba de encolado", verdad);
    print_test("El primero es el puntero al 0 del vector", cola_ver_primero(cola) == &vector_prueba[0]);
    print_test("La cola no está vacía", cola_esta_vacia(cola) == false);

    //Prueba de desencolado
    verdad = true;
    for (int i=0; i<tam; i++){
        if ((cola_ver_primero(cola) != &vector_prueba[i]) || (cola_desencolar(cola) != &vector_prueba[i])){
            verdad = false;
            break;
        }
    }
    print_test("Prueba de desencolado", verdad);
    print_test("La cola está vacía", cola_esta_vacia(cola) == true);
    print_test("Ver primero devuelve NULL", cola_ver_primero(cola) == NULL);

    //Liberar vector utilizado
    free(vector_prueba);

    //Destrucción de la cola
    cola_destruir(cola, NULL);
    print_test("Cola destruída", true);
}

void pruebas_memoria_dinamica(){
    printf("~~~PRUEBAS DE MEMORIA DINAMICA~~~\n");
    //Destruir cola 1 teniendo encolada cola 2
    //Declaración de las colas a usar
    cola_t* cola_1 = cola_crear();
    print_test("Cola 1 creada", cola_1 != NULL);
    cola_t* cola_2 = cola_crear();
    print_test("Cola 2 creada", cola_2 != NULL);

    //Inicio de pruebas
    print_test("Encolar cola 2 en cola 1", cola_encolar(cola_1, cola_2));
    print_test("La cola 1 no está vacía", cola_esta_vacia(cola_1) == false);
    print_test("La cola 2 está vacía", cola_esta_vacia(cola_2) == true);
    cola_destruir(cola_1, NULL);
    print_test("Cola 1 destruída", true);
    char letra = 'g';
    print_test("Encolar un puntero a letra en cola 2", cola_encolar(cola_2, &letra) == true);
    print_test("La cola 2 no está vacía", cola_esta_vacia(cola_2) == false);
    print_test("El primero de la cola 2 es el puntero a letra", cola_ver_primero(cola_2) == &letra);
    cola_destruir(cola_2, NULL);
    print_test("Cola 2 destruída", true);

    //Destruir cola 4 estando encolada en cola 3
    //Declaración de las colas a usar
    cola_t* cola_3 = cola_crear();
    print_test("Cola 3 creada", cola_3 != NULL);
    cola_t* cola_4 = cola_crear();
    print_test("Cola 4 creada", cola_4 != NULL);

    //Inicio de pruebas
    print_test("Encolar cola 4 en cola 3", cola_encolar(cola_3, cola_4));
    print_test("Cola 3 no está vacía", cola_esta_vacia(cola_3) == false);
    print_test("Cola 4 está vacía", cola_esta_vacia(cola_4) == true);
    print_test("El primero de cola 3 es cola 4", cola_ver_primero(cola_3) == cola_4);
    cola_destruir(cola_4, NULL);
    print_test("Cola 4 destruída", true);
    print_test("Cola 3 no está vacía", cola_esta_vacia(cola_3) == false);
    cola_destruir(cola_3, NULL);
    print_test("Cola 3 destruída", true);

    //Encolar cola 5 en cola 6 y cola 6 en cola 5
    //Declaración de las colas a usar
    cola_t* cola_5 = cola_crear();
    print_test("Cola 5 creada", cola_5 != NULL);
    cola_t* cola_6 = cola_crear();
    print_test("Cola 6 creada", cola_6 != NULL);

    //Inicio de pruebas
    print_test("Encolar cola 5 en cola 6", cola_encolar(cola_6, cola_5));
    print_test("Cola 5 está vacía", cola_esta_vacia(cola_5) == true);
    print_test("Cola 6 no está vacía", cola_esta_vacia(cola_6) == false);
    print_test("Encolar cola 6 en cola 5", cola_encolar(cola_5, cola_6));
    print_test("El primero de la cola 5 es cola 6", cola_ver_primero(cola_5) == cola_6);
    print_test("El primero de la cola 6 es cola 5", cola_ver_primero(cola_6) == cola_5);
    cola_destruir(cola_5, NULL);
    print_test("Cola 5 destruída", true);
    cola_destruir(cola_6, NULL);
    print_test("Cola 6 destruída", true);
}

void pruebas_destruccion(){
    printf("~~~PRUEBAS DE FUNCION DESTRUIR~~~\n");
    //Declaración de la cola a usar
    cola_t* cola = cola_crear();
    print_test("Cola creada", cola != NULL);

    //Inicio de pruebas
    int* num = malloc(sizeof(int));
    num[0] = 100;
    long* lon = malloc(sizeof(long));
    lon[0] = 1256312;
    char* letra = malloc(sizeof(char));
    letra[0] = 'a';
    print_test("Encolar puntero a numero", cola_encolar(cola, num));
    print_test("Encolar puntero a long", cola_encolar(cola, lon));
    print_test("Encolar puntero a letra", cola_encolar(cola, letra));
    print_test("Cola no esta vacía", cola_esta_vacia(cola) == false);
    print_test("El primero es el puntero a numero", cola_ver_primero(cola) == num);

    //Destrucción de la cola con función free
    cola_destruir(cola, free);
    print_test("Cola destruida, datos destruidos con free", true);

    //Prueba caso borde cola vacía
    //Declaración de la cola a usar
    cola_t* cola_2 = cola_crear();
    print_test("Cola 2 creada", cola != NULL);

    //Inicio de pruebas
    print_test("Cola 2 está vacía", cola_esta_vacia(cola_2) == true);

    //Destrucción de la cola con función free
    cola_destruir(cola_2, free);
    print_test("Cola destruida, datos destruidos con free", true);
}

void pruebas_cola_alumno(){
    pruebas_cola_vacia();
    pruebas_basicas();
    pruebas_volumen();
    pruebas_memoria_dinamica();    
    pruebas_destruccion();
}