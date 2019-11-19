from random import choice
from random import randint
from csv import reader

def crear_dict_palabras(archivo):
    """ 
    Recibe un archivo csv que contengan palabras y sus respectivas definiciones,
    delimitadas por un "|".
    Abre el archivo, crea dos diccionarios, y lo cierra.
    
    El primer diccionario contiene las palabras como claves y las definiciones como valores.
    El segundo contiene las letras del abecedario como claves y una lista de las palabras que
    contienen la letra como valores.
    """
    with open(archivo, encoding="utf8") as palabras:

        #Diccionario que contiene {"Palabra":"Defición"}
        dic_palabras_def = dict(reader(palabras, delimiter="|"))

        #Diccionario que contiene {"Letra":"Palabras"}
        dic_letras_pal = {}
        for pal in dic_palabras_def:
            for letra in pal:
                if not letra in dic_letras_pal:
                    dic_letras_pal[letra] = [pal]
                elif pal in dic_letras_pal[letra]:
                    continue
                else:
                    dic_letras_pal[letra] += [pal]

        return dic_palabras_def, dic_letras_pal

def palabra_horizontal_azar(dic_letras_pal):
    """
    Recibe un diccionario que contiene letras(str) como claves y palabras(str) como valores.
    Devuelve una palabra al azar de más de ocho letras.
    """
    lista_palabras = list(dic_letras_pal.keys())
    while True:
        letra_azar = choice(lista_palabras)
        palabra_azar = choice(dic_letras_pal[letra_azar])
        if len(palabra_azar) < 8:
            continue
        return palabra_azar

def palabras_vertical_azar(pal_horizontal, dic_letras_pal):
    """
    Recibe la palabra horizontal(str) y un diccionario que contiene letras como claves y 
    palabras como valores.

    Devuelve una lista de tuplas de la forma [(palabra, posición, índice de la letra, len(palabra)]. 
    La lista estará ordenada por posición de menor a mayor.
    """
    vertical = []
    pos_vertical = randint(0,2) #Numero al azar que dara el indice de la letra

    for posicion in range(len(pal_horizontal)):
        while posicion == pos_vertical:
            letra = pal_horizontal[posicion]
            palabra = choice(dic_letras_pal[letra])
            if palabra in vertical or palabra == pal_horizontal:
                continue
            vertical.append((palabra, posicion, palabra.index(letra), len(palabra)))
            pos_vertical += randint (2,3) #Le suma entre 2(min) y 3(max) posiciones a la siguiente palabra
    return vertical