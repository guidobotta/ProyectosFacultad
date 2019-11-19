#include "testing.h"
#include "lista.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/* ******************************************************************
 *                         PRUEBAS DE LA LISTA
 * *****************************************************************/

//Pruebas para lista vacía
void pruebas_lista_vacia(){
    printf("~~~PRUEBAS LISTA VACIA~~~\n");
    //Declaración de la lista a usar
    lista_t* lista = lista_crear();
    print_test("Lista creada", lista != NULL);

    //Inicio de pruebas
    print_test("La lista está vacía", lista_esta_vacia(lista) == true);
    print_test("La longitud de la lista es 0", lista_largo(lista) == 0);
    print_test("Lista ver primero es NULL", lista_ver_primero(lista) == NULL);
    print_test("Lista ver ultimo es NULL", lista_ver_ultimo(lista) == NULL);
    print_test("Lista borrar primero devuelve NULL", lista_borrar_primero(lista) == NULL);
    
    //Destrucción de la lista
    lista_destruir(lista, NULL);
    print_test("Lista destruída", true);

    printf("\n");
}

//Pruebas básicas para lista
void pruebas_basicas(){
    printf("~~~PRUEBAS BASICAS LISTA~~~\n");
    //Declaración de la lista a usar
    lista_t* lista = lista_crear();
    print_test("Lista creada", lista != NULL);

    //Inicio de pruebas
    //Pruebas de insertar, ver_primero, ver_ultimo, lista_largo y esta_vacia
    int num = 26;
    char letra = 'a';
    long vector[5] = {0, 18, 25, 1500, 123456};
    print_test("La lista está vacía", lista_esta_vacia(lista) == true);
    print_test("Insertar NULL primero", lista_insertar_primero(lista, NULL));
    print_test("La lista no está vacía", lista_esta_vacia(lista) == false);
    print_test("El primer elemento es NULL", lista_ver_primero(lista) == NULL);
    print_test("El ultimo elemento es NULL", lista_ver_ultimo(lista) == NULL);
    print_test("Insertar NULL al final", lista_insertar_ultimo(lista, NULL));
    print_test("Insertar primero puntero a numero 26", lista_insertar_primero(lista, &num));
    print_test("El primer elemento es el puntero a numero 26", lista_ver_primero(lista) == &num);
    print_test("El ultimo elemento es NULL", lista_ver_ultimo(lista) == NULL);
    print_test("Insertar al final puntero a letra 'a'", lista_insertar_ultimo(lista, &letra));
    print_test("El primer elemento es el puntero a numero 26", lista_ver_primero(lista) == &num);
    print_test("El ultimo elemento es el puntero a letra 'a'", lista_ver_ultimo(lista) == &letra);
    print_test("Insertar al final puntero a vector", lista_insertar_ultimo(lista, vector));
    print_test("El ultimo elemento es el puntero al vector", lista_ver_ultimo(lista) == vector);
    print_test("El largo de la lista es igual a 5", lista_largo(lista) == 5);

    // Orden: &num, NULL, NULL, &letra, vector

    //Pruebas de eliminar, ver_primero, ver_ultimo, lista_largo y esta_vacia
    print_test("Borrar el primero me devuelte puintero a numero 26", lista_borrar_primero(lista) == &num);
    print_test("Ver primero es NULL", lista_ver_primero(lista) == NULL);
    print_test("Ver ultimo es el puntero al vector", lista_ver_ultimo(lista) == vector);
    print_test("Borrar el primero me devuelve NULL", lista_borrar_primero(lista) == NULL);
    print_test("La lista no esta vacia", lista_esta_vacia(lista) == false);
    print_test("La longitud de la lista es igual a 3", lista_largo(lista) == 3);
    print_test("Borrar el primero me devuelve NULL", lista_borrar_primero(lista) == NULL);
    print_test("Borrar el primero me devuelve el puntero a la letra 'a'", lista_borrar_primero(lista) == &letra);
    print_test("Borrar el primero me devuelve el puntero al vector", lista_borrar_primero(lista) == vector);
    print_test("La lista esta vacia", lista_esta_vacia(lista) == true);
    print_test("La longitud de la lista es igual a 0", lista_largo(lista) == 0);

    //Destrucción de la lista
    lista_destruir(lista, NULL);
    print_test("Lista destruída", true);

    printf("\n");
}

//Pruebas de volumen para lista
void pruebas_volumen(){
    printf("~~~PRUEBAS VOLUMEN LISTA~~~\n");
    //Declaración de la lista a usar
    lista_t* lista = lista_crear();
    print_test("Lista creada", lista != NULL);

    //Inicio de pruebas
    size_t tam;
    bool verdad;

    //Prueba con cien mil enteros

    //Prueba de insertado en primer lugar
    tam = 100000; //Prueba realizada con 1 millon exitosa
    verdad = true;
    int* vector_prueba = malloc(tam * sizeof(int));
    for (int i=0; i<tam; i++){
        vector_prueba[i] = i;
        lista_insertar_primero(lista, &vector_prueba[i]);
        if (lista_ver_primero(lista) != &vector_prueba[i] || lista_ver_ultimo(lista) != &vector_prueba[0]){
            verdad = false;
            break;
        }
    }
    print_test("Prueba de insertado en primer lugar", verdad);
    print_test("La lista no está vacía", lista_esta_vacia(lista) == false);
    print_test("La longitud de la lista es de 100.000", lista_largo(lista) == 100000);

    //Prueba de eliminado
    verdad = true;
    for (int i=0; i<tam; i++){
        if(lista_borrar_primero(lista) != &vector_prueba[99999-i]){
            verdad = false;
            break;
        }
    }
    print_test("Prueba de eliminado", verdad);
    print_test("La lista está vacía", lista_esta_vacia(lista) == true);

    //Prueba de insertado en ultimo lugar
    verdad = true;
    for (int i=0; i<tam; i++){
        lista_insertar_ultimo(lista, &vector_prueba[i]);
        if (lista_ver_ultimo(lista) != &vector_prueba[i] || lista_ver_primero(lista) != &vector_prueba[0]){
            verdad = false;
            break;
        }
    }
    print_test("Prueba de insertado en ultimo lugar", verdad);
    print_test("La lista no está vacía", lista_esta_vacia(lista) == false);
    print_test("La longitud de la lista es de 100.000", lista_largo(lista) == 100000);

    //Prueba de eliminado
    verdad = true;
    for (int i=0; i<tam; i++){
        if(lista_borrar_primero(lista) != &vector_prueba[i]){
            verdad = false;
            break;
        }
    }
    print_test("Prueba de eliminado", verdad);
    print_test("La lista está vacía", lista_esta_vacia(lista) == true);

    //Liberar vector utilizado
    free(vector_prueba);

    //Destrucción de la lista
    lista_destruir(lista, NULL);
    print_test("Lista destruída", true);

    printf("\n");
}

//Pruebas de memoria dinamica para lista
void pruebas_memoria_dinamica(){
    printf("~~~PRUEBAS DE MEMORIA DINAMICA~~~\n");
    //Destruir lista 1 teniendo dentro a lista 2
    //Declaración de las listas a usar
    lista_t* lista_1 = lista_crear();
    print_test("Lista 1 creada", lista_1 != NULL);
    lista_t* lista_2 = lista_crear();
    print_test("Lista 2 creada", lista_2 != NULL);

    //Inicio de pruebas
    print_test("Insertar lista 2 en lista 1", lista_insertar_primero(lista_1, lista_2));
    print_test("Lista 1 no está vacía", lista_esta_vacia(lista_1) == false);
    print_test("Lista 2 está vacía", lista_esta_vacia(lista_2) == true);
    print_test("El primero elemento de lista 1 es lista 2", lista_ver_primero(lista_1) == lista_2);
    print_test("El ultimo elemento de la lista 1 es lista 2", lista_ver_ultimo(lista_1) == lista_2);
    lista_destruir(lista_1, NULL);
    print_test("Lista 1 destruída", true);
    print_test("Lista 2 está vacía", lista_esta_vacia(lista_2) == true);
    lista_destruir(lista_2, NULL);
    print_test("Lista 2 destruída", true);

    //Destuir lista 4 estando dentro de lista 3
    //Declaración de las listas a usar
    lista_t* lista_3 = lista_crear();
    print_test("Lista 3 creada", lista_3 != NULL);
    lista_t* lista_4 = lista_crear();
    print_test("Lista 4 creada", lista_4 != NULL);

    //Inicio de pruebas
    print_test("Insertar lista 4 en lista 3", lista_insertar_ultimo(lista_3, lista_4));
    print_test("Lista 3 no está vacía", lista_esta_vacia(lista_3) == false);
    print_test("Lista 4 esta vacía", lista_esta_vacia(lista_4) == true);
    print_test("El primer elemento de lista 3 es lista 4", lista_ver_primero(lista_3) == lista_4);
    lista_destruir(lista_4, NULL);
    print_test("Lista 4 destruída", true);
    print_test("Lista 3 no está vacía", lista_esta_vacia(lista_3) == false);
    lista_destruir(lista_3, NULL);
    print_test("Lista 3 destruída", true);

    //Insertar lista 5 en lista 6 y lista 6 en lista 5
    //Declaración de las listas a usar
    lista_t* lista_5 = lista_crear();
    print_test("Lista 5 creada", lista_5 != NULL);
    lista_t* lista_6 = lista_crear();
    print_test("Lista 6 creada", lista_6 != NULL);

    //Inicio de pruebas
    print_test("Insertar lista 5 en lista 6", lista_insertar_primero(lista_5, lista_6));
    print_test("Insertar lista 6 en lista 5", lista_insertar_ultimo(lista_6, lista_5));
    print_test("El primero de lista 5 es lista 6", lista_ver_primero(lista_5) == lista_6);
    print_test("El ultimo de la lista 6 es lista 5", lista_ver_ultimo(lista_6) == lista_5);
    lista_destruir(lista_5, NULL);
    print_test("Lista 5 destruída", true);
    lista_destruir(lista_6, NULL);
    print_test("Lista 6 destruída", true);

    printf("\n");
}

//Pruebas de la funcion destruccion para lista
void pruebas_destruccion(){
    printf("~~~PRUEBAS DE DESTRUCCION~~~\n");
    //Declaración de la lista a usar
    lista_t* lista = lista_crear();
    print_test("Lista creada", lista != NULL);

    //Inicio de pruebas
    int* num = malloc(sizeof(int));
    num[0] = 100;
    long* lon = malloc(sizeof(long));
    lon[0] = 1256312;
    char* letra = malloc(sizeof(char));
    letra[0] = 'a';
    print_test("Insertar puntero a numero", lista_insertar_primero(lista, num));   
    print_test("Insertar puntero a lon", lista_insertar_primero(lista, lon));
    print_test("Insertar puntero a letra", lista_insertar_primero(lista, letra));
    print_test("La lista no está vacía", lista_esta_vacia(lista) == false);
    print_test("El primero de la lista es puntero a letra", lista_ver_primero(lista) == letra);
    print_test("El ultimo de la lista es puntero a numero", lista_ver_ultimo(lista) == num);

    //Destruccion de la lista con funcion free
    lista_destruir(lista, free);
    print_test("Lista destruida, datos destruidos con free", true);

    //Prueba caso borde lista vacía
    lista_t* lista_2 = lista_crear();
    print_test("Lista 2 creada", lista_2 != NULL);

    //Inicio de pruebas
    print_test("Lista 2 está vacía", lista_esta_vacia(lista_2) == true);

    //Destruccion de la lista con funcion free
    lista_destruir(lista_2, free);
    print_test("Lista destruida, datos destruidos con free", true);

    printf("\n");
}

/* ******************************************************************
 *                       PRUEBAS DE ITERADORES
 * *****************************************************************/

bool sumar_todos(void* dato, void* extra){
    *(int*) extra += *(int*) dato;
    return true;
}

bool sumar_10_primeros(void* dato, void* extra){
    if (*(int*)extra == 55) return false;
    *(int*) extra += *(int*) dato;
    return true;
}

//Pruebas para iterador interno
void pruebas_iterador_interno(){
    printf("~~~PRUEBAS ITERADOR INTERNO~~~\n");
    //Declaracion de lista a usar
    lista_t* lista = lista_crear();
    print_test("Lista creada", lista != NULL);

    //Prueba con lista vacía
    int suma = 0;
    int resultado = 0;
    lista_iterar(lista, sumar_todos, &suma);
    print_test("La suma de todos los numeros con lista vacia es 0", suma == resultado);

    //Construcción de la lista
    int tam = 1001;
    int* vector_prueba = malloc(tam * sizeof(int));
    for (int i=0; i<tam; i++){
        vector_prueba[i] = i;
        if (!lista_insertar_ultimo(lista, &vector_prueba[i])) return;
    }

    //Inicio de pruebas sin corte
    suma = 0;
    resultado = 500500;
    lista_iterar(lista, sumar_todos, &suma);
    print_test("La suma de todos los numeros con lista del 0 al 1000 es 500500", suma == resultado);

    //Inicio de pruebas con corte
    suma = 0;
    resultado = 55;
    lista_iterar(lista, sumar_10_primeros, &suma);
    print_test("La suma de los numeros del 0 al 10 es 55", suma == resultado);

    //Liberar vector utilizado
    free(vector_prueba);

    //Destrucción de la lista
    lista_destruir(lista, NULL);
    print_test("Lista destruída",true);

    printf("\n");
}

//Pruebas para iterador externo con lista vacia
void pruebas_iterador_externo_lista_vacia(){
    printf("~~~PRUEBAS ITERADOR EXTERNO CON LISTA VACIA~~~\n");
    //Declaracion de lista e iterador a usar
    lista_t* lista = lista_crear();
    lista_iter_t* iter = lista_iter_crear(lista);
    print_test("Lista creada", lista != NULL);
    print_test("Iterador creado", iter != NULL);

    //Inicio de pruebas
    print_test("La lista esta vacia", lista_esta_vacia(lista) == true);
    print_test("El iterador se encuentra al final de la lista", lista_iter_al_final(iter) == true);
    print_test("Avanzar devuelve false", lista_iter_avanzar(iter) == false);
    print_test("Ver actual es NULL", lista_iter_ver_actual(iter) == NULL);
    print_test("Borrar es NULL", lista_iter_borrar(iter) == NULL);
    int num = 5;
    print_test("Insertar puntero a numero 5", lista_iter_insertar(iter, &num) == true);
    print_test("La lista no está vacía", lista_esta_vacia(lista) == false);
    print_test("El primero y el ultimo de la lista es puntero a numero 5", 
    lista_ver_primero(lista) == &num && lista_ver_ultimo(lista) == &num);
    print_test("El iterador no se encuentra al final de la lista", lista_iter_al_final(iter) == false);
    print_test("Avanzo con el iterador", lista_iter_avanzar(iter));
    print_test("El iterador se encuentra al final de la lista", lista_iter_al_final(iter) == true);
    print_test("Avanzar devuelve false", lista_iter_avanzar(iter) == false);
    char letra = 'a';
    print_test("Agrego un puntero a letra 'a'", lista_iter_insertar(iter, &letra));
    print_test("El iterador no se encuentra al final de la lista", lista_iter_al_final(iter) == false);
    print_test("Ver actual devuelve el puntero a letra 'a'", lista_iter_ver_actual(iter) == &letra);
    long vector[5] = {1,2,123,321,50};
    print_test("Agrego un puntero a vector", lista_iter_insertar(iter, vector));
    print_test("Ver actual devuelve el puntero al vector", lista_iter_ver_actual(iter) == vector);
    
    //Compruebo primero y ultimo de la lista
    //Orden = &num, vector, &letra
    print_test("El primero de la lista es puntero a numero 5", lista_ver_primero(lista) == &num);
    print_test("El ultimo de la lista es puntero a letra 'a'", lista_ver_ultimo(lista) == &letra);
    print_test("El largo de la lista es 3", lista_largo(lista) == 3);

    //Crear otro iterador
    printf("Creo otro iterador\n");
    lista_iter_t* iter_2 = lista_iter_crear(lista);
    print_test("Iterador 2 creado", iter != NULL);
    
    //Testeo con iterador 2
    print_test("Iterador no esta al final", lista_iter_al_final(iter_2) == false);
    print_test("Ver actual en iterador 2 es puntero a numero 5", lista_iter_ver_actual(iter_2) == &num);
    print_test("Avanzo con iterador 2", lista_iter_avanzar(iter_2));
    print_test("Iterador no esta al final", lista_iter_al_final(iter_2) == false);
    print_test("Ver actual en iterador 2 es puntero a vector", lista_iter_ver_actual(iter_2) == vector);
    print_test("Avanzo con iterador 2", lista_iter_avanzar(iter_2));
    print_test("Iterador no esta al final", lista_iter_al_final(iter_2) == false);
    print_test("Ver actual en iterador 2 es puntero a letra 'a'", lista_iter_ver_actual(iter_2) == &letra);
    print_test("Borro el actual con iterador 2", lista_iter_borrar(iter_2) == &letra);
    print_test("Iterador esta al final", lista_iter_al_final(iter_2) == true);

    //Compruebo primero y ultimo de la lista
    print_test("El primero de la lista es puntero a numero 5", lista_ver_primero(lista) == &num);
    print_test("El ultimo de la lista es puntero a vector", lista_ver_ultimo(lista) == vector);
    print_test("El largo de la lista es 2", lista_largo(lista) == 2);

    //Destrucción de lista e iterador
    lista_destruir(lista, NULL);
    print_test("La lista fue destruída", true);
    lista_iter_destruir(iter);
    print_test("El iterador fue destruído", true);
    lista_iter_destruir(iter_2);
    print_test("El iterador 2 fue destruído", true);

    printf("\n");
}

//Pruebas basicas para iterador externo
void pruebas_iterador_externo_lista_basica(){
    printf("~~~PRUEBAS ITERADOR EXTERNO CON LISTA BASICA~~~\n");
    //Declaracion de lista a usar
    lista_t* lista = lista_crear();
    print_test("Lista creada", lista != NULL);

    //Construcción de la lista
    size_t tam = 10000;
    int* vector_prueba = malloc(tam * sizeof(int));
    for (int i=0; i<tam; i++){
        vector_prueba[i] = i;
        if (!lista_insertar_ultimo(lista, &vector_prueba[i])) return;
    }
    print_test("La lista no está vacía", lista_esta_vacia(lista) == false);
    print_test("El primero de la lista es el puntero al numero 0", lista_ver_primero(lista) == &vector_prueba[0]);

    //Declaracion del iterador a usar
    lista_iter_t* iter = lista_iter_crear(lista);
    print_test("Iterador creado", iter != NULL);

    //Inicio de pruebas
    print_test("El iterador no se encuentra al final", lista_iter_al_final(iter) == false);
    print_test("Ver actual devuelve el puntero al numero 0", lista_iter_ver_actual(iter) == &vector_prueba[0]);
    //Insertar y borrar estando sobre el primer elemento de la lista
    int num = 5;
    print_test("Insertar puntero a numero 5", lista_iter_insertar(iter, &num));
    print_test("El primero de la lista es puntero a numero 5", lista_ver_primero(lista) == &num);
    print_test("Borrar elemento devuelve el puntero a numero 5", lista_iter_borrar(iter) == &num);
    print_test("El primero de la lista es puntero a numero 0", lista_ver_primero(lista) == &vector_prueba[0]);

    //Avanzar hasta el ultimo elemento con iterador 1
    bool verdad = true;
    for (int i=0; i<tam-1; i++){
        if ((lista_iter_ver_actual(iter) != &vector_prueba[i]) || !lista_iter_avanzar(iter)){
            verdad = false;
            break;
        }
    }
    print_test("Se avanzó correctamente hasta el último elemento", verdad);
    print_test("El iterador no se encuentra al final", lista_iter_al_final(iter) == false);
    print_test("Ver actual devuelve el puntero al numero 9999", lista_iter_ver_actual(iter) == &vector_prueba[9999]);

    //Borrar e insertar estando sobre el último elemento de la lista
    print_test("Borrar elemento devuelve el puntero a numero 9999", lista_iter_borrar(iter) == &vector_prueba[9999]);
    print_test("El iterador se encuentra al final", lista_iter_al_final(iter) == true);
    print_test("Ver actual devuelve NULL", lista_iter_ver_actual(iter) == NULL);
    print_test("Insertar puntero a numero 5", lista_iter_insertar(iter, &num));
    print_test("Ver actual devuelve el puntero al numero 5", lista_iter_ver_actual(iter) == &num);
    print_test("El iterador no se encuentra al final", lista_iter_al_final(iter) == false);

    //Liberar vector utilizado
    free(vector_prueba);

    //Destrucción de lista e iterador
    lista_destruir(lista, NULL);
    print_test("La lista fue destruída", true);
    lista_iter_destruir(iter);
    print_test("El iterador fue destruído", true);

    printf("\n");
}

//Ejecuta las pruebas
void pruebas_lista_alumno(){
    
    //Pruebas para la lista
    pruebas_lista_vacia();
    pruebas_basicas();
    pruebas_volumen();
    pruebas_memoria_dinamica();    
    pruebas_destruccion();

    //Pruebas para iterador
    pruebas_iterador_interno();
    pruebas_iterador_externo_lista_vacia();
    pruebas_iterador_externo_lista_basica();
}