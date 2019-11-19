import argparse
import generador as gen
import palabras as pal

def main():
    """
    Función principal del programa. Genera e imprime el crucigrama. En caso de que el usuario
    inclusa '-s' al ejecutar el archivo, imprime también la solución.
    """
    parser = argparse.ArgumentParser(description='Generador de crucigramas')
    parser.add_argument('-s', '--solucion', action='store_true', help='imprimir la solución')
    args = parser.parse_args()
    imprimir_solucion = args.solucion # es True si el usuario incluyó la opción -s
    
    palabras_def, letras_palabras = pal.crear_dict_palabras("palabras.csv")
    horizontal = pal.palabra_horizontal_azar(letras_palabras)
    verticales = pal.palabras_vertical_azar(horizontal, letras_palabras)

    cant_abajo, cant_arriba, posiciones = gen.cant_abajo_arriba_posiciones(verticales)

    print("CRUCIGRAMA", end="\n\n")
    gen.imprimir_crucigrama(horizontal, verticales, cant_abajo, cant_arriba, posiciones)
    print(end="\n\n")
    print("DEFINICIONES", end="\n\n")
    gen.imprimir_deficiones(horizontal,verticales,palabras_def)
    if imprimir_solucion:
        print(end="\n\n")
        print("SOLUCION", end="\n\n")
        gen.imprimir_solucion_crucigrama(horizontal, verticales, cant_abajo, cant_arriba, posiciones)

main()