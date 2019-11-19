#define _GNU_SOURCE //Sino falla getline
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "strutil.h"
#include "pila.h"

//Asignación de números
void asignar_num(pila_t* pila_num, char* op, long long int* num1, long long int* num2, long long int* num3, bool* exito){
    *num1 = *(long long int*) pila_desapilar(pila_num);

    if (!strcmp(op, "sqrt")) return;
    if (pila_esta_vacia(pila_num)){
        *exito = false;
        return;
    }
    *num2 = *(long long int*) pila_desapilar(pila_num);

    if (!strcmp(op, "?")){
        if (pila_esta_vacia(pila_num)){
            *exito = false;
            return;
        }
        *num3 = *(long long int*) pila_desapilar(pila_num);
    }
}

//Calculo de suma

void calcular_suma(pila_t* pila_num, long long int* resultado, bool* exito){
    long long int num1;
    long long int num2;
    asignar_num(pila_num, "+", &num1, &num2, NULL, exito);
    if(!*exito) return;
    *resultado = num1 + num2;
}

//Calculo de resta

void calcular_resta(pila_t* pila_num, long long int* resultado, bool* exito){
    long long int num1;
    long long int num2;
    asignar_num(pila_num, "-", &num1, &num2, NULL, exito);
    if(!*exito) return;
    *resultado = num1 - num2;
}

//Calculo de multiplicacion

void calcular_multiplo(pila_t* pila_num, long long int* resultado, bool* exito){
    long long int num1;
    long long int num2;
    asignar_num(pila_num, "*", &num1, &num2, NULL, exito);
    if(!*exito) return;
    *resultado = num1 * num2;
}

//Calculo de division

void calcular_division(pila_t* pila_num, long long int* resultado, bool* exito){
    long long int num1;
    long long int num2;
    asignar_num(pila_num, "/", &num1, &num2, NULL, exito);
    if(!*exito) return;
    if(num2 == 0){
        *exito = false;
        return;
    }
    *resultado = num1 / num2;
}

//Calculo de logaritmo

long long int _calc_log(long long int base, long long int arg, long long int contador){
    if(arg < base) return contador;
    contador++;
    return _calc_log(base, arg/base, contador);
}

void calcular_logaritmo(pila_t* pila_num, long long int* resultado, bool* exito){
    long long int arg;
    long long int base;
    asignar_num(pila_num, "log", &arg, &base, NULL, exito);
    if(!*exito) return;

    if (base <= 1 || arg<1){
        *exito = false;
        return;
    }else if (arg == base){
    *resultado = 1;
    return;
    }
    long long int contador = 0;
    *resultado = _calc_log(base, arg, contador);
}

//Calculo de raiz

long long int _calc_raiz(long long int num, long long int inicio, long long int fin){
    if (num == 1) return 1;
    long long int medio = (fin+inicio)/2;
    if (medio*medio <= num){
        if (((medio+1)*(medio+1)) > num) return medio;
        return _calc_raiz(num, medio, fin);
    }
    return _calc_raiz(num, inicio, medio);
}

void calcular_raiz(pila_t* pila_num, long long int* resultado, bool* exito){
    long long int num;
    asignar_num(pila_num, "sqrt", &num, NULL, NULL, exito);
    if (num<0){
        *exito = false;
        return;
    }
    long long int inicio = 0;

    *resultado = _calc_raiz(num, inicio, num);
}

//Calculo de potencia

long long int _calc_pot(long long int num, long long int exponente/*, long long int resultado*/){
    if (exponente == 0) return 1;
    else if (exponente == 1) return num;

    long long int resultado;
    resultado = _calc_pot(num, exponente/2);

    if ((exponente%2) == 1){
        return resultado*resultado*num;
    }
    else{
        return resultado*resultado;
    }
}

void calcular_potencia(pila_t* pila_num, long long int* resultado, bool* exito){
    long long int num;
    long long int exponente;
    asignar_num(pila_num, "^", &num, &exponente, NULL, exito);
    if(!*exito) return;

    if (exponente < 0){
        *exito = false;
        return;
    }

    *resultado = _calc_pot(num, exponente);
}

//Operador Ternario

void operador_ternario(pila_t* pila_num, long long int* resultado, bool* exito){
    long long int op;
    long long int num2;
    long long int num1;
    asignar_num(pila_num, "?", &op, &num2, &num1, exito);

    if(!*exito) return;

    if (op == 0) *resultado = num1;
    else *resultado = num2;
}

//Operador de la calculadora

bool operar(pila_t* pila_num, char* op, long long int* resultado){
    if (pila_esta_vacia(pila_num)){
        return false;
    }
    bool exito = true;
    if (!strcmp(op, "+")) calcular_suma(pila_num, resultado, &exito);
    else if (!strcmp(op, "-")) calcular_resta(pila_num, resultado, &exito);
    else if (!strcmp(op, "*")) calcular_multiplo(pila_num, resultado, &exito);
    else if (!strcmp(op, "/")) calcular_division(pila_num, resultado, &exito);
    else if (!strcmp(op, "log")) calcular_logaritmo(pila_num, resultado, &exito);
    else if (!strcmp(op, "sqrt")) calcular_raiz(pila_num, resultado, &exito);
    else if (!strcmp(op, "^")) calcular_potencia(pila_num, resultado, &exito);
    else if (!strcmp(op, "?")) operador_ternario(pila_num, resultado, &exito);
    pila_apilar(pila_num, resultado);
    return exito;
}

bool es_numero(char* str){
    size_t lon = strlen(str);
    for(long long int i=0; i<lon; i++){
        if (lon > 1 && str[0] == '-') continue;
        if (!isdigit(str[i])) return false;
    }
    return true;
}

//Cuerpo principal de la calculadora

void _error(char** lista_elementos, pila_t* pila_num){
    printf("ERROR\n");
    free_strv(lista_elementos);
    pila_destruir(pila_num);
}

void calculadora(char* linea){
    char** lista_elementos = split(linea, ' ');
    long long int cantidad = 0;
    while(lista_elementos[cantidad]!=NULL){
        cantidad++;
    }
    long long int numeros[cantidad];
    pila_t* pila_num = pila_crear();
    long long int pos = 0;
    long long int it = 0;
    long long int resultado;

    while (lista_elementos[it] != NULL){
        if (lista_elementos[it][0] == '\0'){
            it++;
            continue;
        }
        if (es_numero(lista_elementos[it])){
            numeros[pos] = (long long int)atol(lista_elementos[it]);
            pila_apilar(pila_num, &numeros[pos]);
            pos++;
        }else{
            bool exito = operar(pila_num, lista_elementos[it], pila_ver_tope(pila_num));
            if (!exito) {
                _error(lista_elementos, pila_num);
                return;
            } 
        }
        it++;
    }
    resultado = *(long long int*) pila_desapilar(pila_num);
    if (!pila_esta_vacia(pila_num)){
        _error(lista_elementos, pila_num);
        return;
    } 
    //Operacion exitosa, imprimo resultado
    free_strv(lista_elementos);
    pila_destruir(pila_num);
    printf("%lld\n", resultado);
}

//Ejecucion del programa

int main(){
    size_t tam = 0;
    char* linea = NULL;
    while (getline(&linea, &tam, stdin) != -1){
        linea[strlen(linea)-1] = '\0';
        calculadora(linea);
    }
    free(linea);
    return 0;
}