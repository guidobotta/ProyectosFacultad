#include "cola.h"
#include <stdlib.h>
#include <stdio.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct nodo{
    void* dato;
    struct nodo* proximo;
}nodo_t;

struct cola{
    nodo_t* primero;
    nodo_t* ultimo;
};

/* ******************************************************************
 *                    PRIMITIVAS DEL NODO
 * *****************************************************************/

// Crea un nodo.
// Post: devuelve el nodo con su valor asignado.
nodo_t* crear_nodo(void* valor){
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if (!nodo) return NULL;

    nodo->dato = valor;
    nodo->proximo = NULL;
    return nodo;
}

// Asigna nodo_2 como proximo al nodo_1. Puede recibir NULL.
// Pre: los nodos fueron creados.
// Post: el proximo al nodo_1 es nodo_2.
void asignar_siguiente_nodo(nodo_t *nodo_1, nodo_t *nodo_2){
    nodo_1->proximo = nodo_2;
}

// Devuelve el siguiente nodo asignado
// Pre: el nodo fue creado.
// Post: se devolvio el proximo nodo.
nodo_t* ver_proximo(nodo_t* nodo){
    return nodo->proximo;
}

// Devuelve el dato asignado al nodo.
// Pre: el nodo fue creado.
// Post: se devolvio el valor guardado en el nodo.
void* ver_dato(nodo_t *nodo){
    return nodo->dato;
}

/* ******************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/

cola_t* cola_crear(void){
    cola_t* cola = malloc(sizeof(cola_t));
    if (!cola) return NULL;

    cola->primero = NULL;
    cola->ultimo = NULL;
    return cola;
}

void cola_destruir(cola_t *cola, void destruir_dato(void*)){
    while (!cola_esta_vacia(cola)){
        //Libero nodos
        void* dato = cola_desencolar(cola);
        //Aplico destruir_dato (si es distinto de NULL) a cada dato
        if (destruir_dato) destruir_dato(dato);
    }
    free(cola);
}

bool cola_esta_vacia(const cola_t *cola){
    return !cola->primero;
}

void* cola_ver_primero(const cola_t *cola){
    if (cola_esta_vacia(cola)) return NULL;
    return ver_dato(cola->primero);
}

bool cola_encolar(cola_t *cola, void* valor){
    nodo_t* nodo = crear_nodo(valor);
    if (!nodo) return false;

    if (cola_esta_vacia(cola)) {
        cola->primero = nodo;
    } else{
        asignar_siguiente_nodo(cola->ultimo, nodo); //Asigno el proximo del nodo
    }
    cola->ultimo = nodo;

    return true;
}

void* cola_desencolar(cola_t *cola){
    if (cola_esta_vacia(cola)) return NULL;

    nodo_t* nodo = cola->primero;
    void* dato = ver_dato(nodo);

    if (!ver_proximo(nodo)){ //Chequeo si hay un solo elemento en la cola
        cola->ultimo = NULL;
    }
    cola->primero = ver_proximo(nodo);
    free(nodo);

    return dato;
}