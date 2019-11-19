#include "testing.h"
#include "heap.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int funcion_comparacion_enteros(const void *a, const void *b){
    if(*(int*)a > *(int*)b) return 1;
    if(*(int*)a < *(int*)b) return -1;
    return 0;
}

int _strcmp_(const void *a, const void *b){
    return strcmp((const char*)a, (const char*)b);
}

void pruebas_heap_vacio(){
    //Declaración del heap a usar
    heap_t *heap = heap_crear(_strcmp_);
    print_test("Heap creado", heap != NULL);

    //Inicio de Pruebas

    //Pruebas Heap vacio normales
    print_test("El heap esta vacio", heap_esta_vacio(heap));
    print_test("La cantidad de elementos es cero", heap_cantidad(heap) == 0);
    print_test("Ver el maximo es NULL", heap_ver_max(heap) == NULL);
    print_test("Desencolar el mayor es NULL", heap_desencolar(heap) == NULL);
    print_test("Ver el maximo sigue siendo NULL", heap_ver_max(heap) == NULL);

    //Destrucción del heap
    heap_destruir(heap, NULL);
    print_test("Heap destruido", true);

    //Pruebas Heap vacio con heap_crear_arr y arreglo vacio
    void* vector[0] = {};
    heap_t *heap_2 = heap_crear_arr(vector, 0, funcion_comparacion_enteros);
    printf("\n");
    print_test("Heap 2 creado a partir de vector vacío", heap != NULL);

    print_test("El heap esta vacio", heap_esta_vacio(heap_2));
    print_test("La cantidad de elementos es cero", heap_cantidad(heap_2) == 0);
    print_test("Ver el maximo es NULL", heap_ver_max(heap_2) == NULL);
    print_test("Desencolar el mayor es NULL", heap_desencolar(heap_2) == NULL);
    print_test("Ver el maximo sigue siendo NULL", heap_ver_max(heap_2) == NULL);

    //Destrucción del heap
    heap_destruir(heap_2, NULL);
    print_test("Heap 2 destruido", true);
}

void pruebas_basicas(){
    //Declaración del heap a usar
    heap_t *heap = heap_crear(funcion_comparacion_enteros);
    print_test("Heap creado", heap != NULL);

    //Inicio de Pruebas
    print_test("El heap esta vacio", heap_esta_vacio(heap));
    int tope = 25;
    int **vector = malloc(sizeof(int*)*tope);

    //Prueba de encolado
    bool ok = true;
    for(int i=0; i<tope; i++){
        vector[i] = malloc(sizeof(int*));
        *vector[i] = i;
        if( (!heap_encolar(heap, vector[i])) || (heap_ver_max(heap) != vector[i]) ){
            ok = false;
            break;
        }
    }

    print_test("Se han incertado los elementos correctamente", ok);
    print_test("El heap no esta vacio", !heap_esta_vacio(heap));
    print_test("La cantida de elementos es correcta", heap_cantidad(heap) == tope);
    print_test("Veo el elemento mayor", heap_ver_max(heap) == vector[tope-1]);

    //Prueba de desencolado
    int *valor = NULL;
    print_test("Desencolo el mayor", (valor = heap_desencolar(heap)) == vector[tope-1]);
    free(valor);

    print_test("El heap no esta vacio", !heap_esta_vacio(heap));
    print_test("La cantida de elementos es correcta", heap_cantidad(heap) == tope-1);
    print_test("Veo el elemento mayor", heap_ver_max(heap) == vector[tope-2]);

    int j = 2;
    while(!heap_esta_vacio(heap)){
        valor = heap_desencolar(heap);
        if (valor != vector[tope-j]){
            ok = false;
            break;
        }
        free(valor);
        j++;
    }
    print_test("Se han desencolado los elementos correctamente", ok);
    print_test("El heap esta vacío", heap_esta_vacio(heap));
    print_test("La cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("El maximo es NULL", heap_ver_max(heap) == NULL);

    //Libero vector
    free(vector);

    //Destrucción del heap
    heap_destruir(heap, free);
    print_test("Heap destruido", true);
}

void pruebas_basicas_heap_arreglo(){
    //Declaración de heap a usar a partir de un vector
    int num1, num2, num3, num4, num5;
    num1 = 5; num2 = 0; num3 = 20; num4 = -5; num5 = 4;
    void* vector[5] = {&num1, &num2, &num3, &num4, &num5};

    heap_t* heap = heap_crear_arr(vector, 5, funcion_comparacion_enteros);
    print_test("Heap creado", heap != NULL);

    //Inicio de pruebas
    print_test("Heap no está vacío", !heap_esta_vacio(heap));
    print_test("Heap ver máximo es 20", heap_ver_max(heap) == &num3);
    print_test("La cantidad de elementos es de 5", heap_cantidad(heap) == 5);
    print_test("Heap desencolar devuelve numero 20", heap_desencolar(heap) == &num3);
    print_test("Heap ver máximo es 5", heap_ver_max(heap) == &num1);
    print_test("La cantidad de elementos es de 4", heap_cantidad(heap) == 4);
    print_test("Encolo devuelta al 20", heap_encolar(heap, &num3));
    print_test("El maximo es 20", heap_ver_max(heap) == &num3);
    print_test("La cantidad de elementos es de 5", heap_cantidad(heap) == 5);

    //Destrucción del heap
    heap_destruir(heap, NULL);
    print_test("Heap destruido", true);
}

void pruebas_volumen(){
    //Declaración del heap a usar
    heap_t *heap = heap_crear(funcion_comparacion_enteros);
    print_test("Heap creado", heap != NULL);

    //Inicio de Pruebas
    int tope = 100000;
    int **vector = malloc(sizeof(int*)*tope);
    bool ok = true;

    //Prueba de Encolado
    for(int i=0; i<tope; i++){
        vector[i] = malloc(sizeof(int*));
        *vector[i] = i;
        if( (!heap_encolar(heap, vector[i])) || (heap_ver_max(heap) != vector[i]) ){
            ok = false;
            break;
        }
    }

    int *valor = NULL;
    print_test("Se han incertado los elementos correctamente", ok);
    print_test("El heap no esta vacio", !heap_esta_vacio(heap));
    print_test("La cantida de elementos es correcta", heap_cantidad(heap) == tope);
    print_test("Veo el elemento mayor", heap_ver_max(heap) == vector[tope-1]);

    //Prueba de Desencolado
    for(int i=0; i<tope/2; i++){
        valor = heap_desencolar(heap);
        free(valor);
    }
    print_test("El heap no esta vacio", !heap_esta_vacio(heap));
    print_test("La cantida de elementos es correcta", heap_cantidad(heap) == tope/2);
    print_test("Veo el elemento mayor", heap_ver_max(heap) == vector[tope/2-1]);

    free(vector);

    //Destrucción del heap
    heap_destruir(heap, free);
    print_test("Heap destruido", true);
}

void pruebas_destruccion(){
    //Declaración del heap a usar
    heap_t *heap = heap_crear(funcion_comparacion_enteros);
    print_test("Heap creado", heap != NULL);

    //Inicio de pruebas
    int* num_1 = malloc(sizeof(int));
    int* num_2 = malloc(sizeof(int));
    int* num_3 = malloc(sizeof(int));
    *num_1 = 15;
    *num_2 = 100;
    *num_3 = -5;
    print_test("Encolar puntero a numero 1", heap_encolar(heap, num_1));
    print_test("Encolar puntero a numero 2", heap_encolar(heap, num_2));
    print_test("Encolar puntero a numero 3", heap_encolar(heap, num_3));
    print_test("Heap no esta vacío", !heap_esta_vacio(heap));
    print_test("El mayor es el puntero a numero 2", heap_ver_max(heap) == num_2);

    //Destrucción del heap con free
    heap_destruir(heap, free);
    print_test("Heap destruido, datos destruidos con free", true);

    //Prueba caso heap vacío
    //Declaración del heap a usar
    heap_t *heap_2 = heap_crear(funcion_comparacion_enteros);
    print_test("Heap 2 creado", heap != NULL);

    //Inicio de pruebas
    print_test("Heap 2 esta vacio", heap_esta_vacio(heap_2));

    //Destrucción del heap con free
    heap_destruir(heap_2, free);
    print_test("Heap 2 destruido, datos destruidos con free", true);
}

bool esta_ordenado(void **arreglo, size_t tope){
    for(size_t i=0; i<tope-1; i++){
        if(*(int*)arreglo[i] > *(int*)arreglo[i+1]) return false;
    }
    return true;
}

void pruebas_heapsort(){
    srand((unsigned int)time(NULL));

    int tope = 50;
    void **vector = malloc(sizeof(void*)*tope);
    for(int i=0; i<tope; i++){
        vector[i] = malloc(sizeof(void*));
        *(int*)vector[i] = rand() % 200;
    }

    heap_sort(vector, tope, funcion_comparacion_enteros);
    print_test("El arreglo esta ordenado", esta_ordenado(vector, tope));
    for(int i=0; i<tope; i++){
        free(vector[i]);
    }

    free(vector);
}

void pruebas_heap_alumno(){
    printf("\n~~~~PRUEBAS HEAP VACIO~~~~\n");
    pruebas_heap_vacio();
    printf("\n~~~~PRUEBAS BASICAS~~~~\n");
    pruebas_basicas();
    printf("\n~~~~PRUEBAS BASICAS HEAP CREADO DESDE VECTOR~~~~\n");
    pruebas_basicas_heap_arreglo();
    printf("\n~~~~PRUEBAS DE VOLUMEN~~~~\n");
    pruebas_volumen();
    printf("\n~~~~PRUEBAS DE DESTRUCCION~~~~\n");
    pruebas_destruccion();
    printf("\n~~~~PRUEBAS HEAPSORT~~~~\n");
    pruebas_heapsort();
}