def cant_abajo_arriba_posiciones (pal_verticales):
    """
    Recibe una lista de tuplas de palabras de la forma [(palabra,posicion, indice, longitud)].
    Devuelve la cantidad de letras que hay debajo de la palabra horizontal, la cantidad de letras que hay
    encima de la palabra horizontal, y una lista con las posiciones de las palabras.

    La cantidad que hay debajo se cuenta a partir de la palabra horizontal inclusive.
    Si no hay letras hacia arriba ni hacia abajo de la palabra horizontal, la cantidad arriba será 0
    y la cantidad abajo será 1.
    """
    cant_arriba = 0
    cant_abajo = 1
    posiciones = []
    for pal in pal_verticales:
        posicion = pal[1]
        posiciones.append(posicion)
        indice = pal[2]
        if indice > cant_arriba:
            cant_arriba = indice
        longitud = pal[3]
        if longitud-indice > cant_abajo:
            cant_abajo = longitud-indice
    return cant_abajo,cant_arriba, posiciones

def imprimir_solucion_crucigrama(pal_horizontal, pal_verticales, cant_abajo, cant_arriba, posiciones):
    """
    Recibe la palabra horizontal(str), una lista de tuplas de palabras de la forma
    [(palabra,posicion, indice, longitud)], la cantidad de letras que hay abajo(int), la cantidad de 
    letras que hay arriba de la palabra horizontal(int) y una lista con las posiciones de las palabras.
    
    Imprime la solución crucigrama.
    """
    #Va de 0 hasta la ultima letra a imprimir, la fila 0 son los números.
    for fila in range(cant_abajo+cant_arriba+1): 
        pos = 0 #Da la posición de la tupla que se utilizara
        num = 1 #Contador para imprimir el número de la palabra vertical
        if fila == cant_arriba+1:
            print ("H", end="  ")
        else:
            print(end="   ")
        #La letra H no es una columna, empieza desde la primer letra.
        #Va de 0 hasta la longitud de la palabra horizontal
        for columna in range(len(pal_horizontal)):
            if fila == 0:
                if columna in posiciones:
                    print(num, end=" ")
                    num += 1
                else:
                    print(end="  ")
            elif fila == cant_arriba+1: #Imprime la palabra horizontal
                print(pal_horizontal[columna], end=" ")
            elif columna in posiciones:
                tupla_palabra = pal_verticales[pos]
                pos += 1
                indice = tupla_palabra[2]
                longitud = tupla_palabra[3]
                if indice+fila > cant_arriba and (fila-cant_arriba <= longitud-indice):
                    print(tupla_palabra[0][indice+(fila-cant_arriba-1)], end=" ")
                else:
                    print(end="  ")    
            else:
                print(end="  ")
        print()

def imprimir_crucigrama(pal_horizontal, pal_verticales, cant_abajo, cant_arriba, posiciones):
    """
    Recibe la palabra horizontal(str), una lista de tuplas de palabras de la forma
    [(palabra,posicion, indice, longitud)], la cantidad de letras que hay abajo(int), la cantidad de 
    letras que hay arriba de la palabra horizontal(int) y una lista con las posiciones de las palabras.

    Imprime el crucigrama.
    """
    palabra_hor = "."*len(pal_horizontal)
    lista_pal_ver = []
    for tupla in pal_verticales:
        lista_pal_ver.append(("."*len(tupla[0]),tupla[1],tupla[2],tupla[3]))
    #Se utiliza la funcion previamente definida para imprimir el crucigrama
    imprimir_solucion_crucigrama(palabra_hor,lista_pal_ver,cant_abajo, cant_arriba, posiciones)

def imprimir_deficiones(pal_horizontal, pal_verticales, dic_pal_def):
    """
    Recibe la palabra horizontal(str), una lista de tuplas de palabras de la forma 
    [(palabra,posicion, indice, longitud)] y un diccionario que contiene las palabras 
    como claves y las definiciones como valores.

    Imprime la definición de cada palabra incluida en el crucigrama.
    """
    pos = 0
    print ("H. {}".format(dic_pal_def[pal_horizontal]))
    for tupla in pal_verticales:
        pos += 1
        print ("{}. {}".format(pos, dic_pal_def[tupla[0]]))