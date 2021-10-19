
def cadenaMasLarga(lista_cadena):
    indice_cadena_mas_larga = 0
    longitud_anterior = 0
    indice = 0
    if len(lista_cadena) == 0:
        return -1
    for cadena in lista_cadena:
        if len(cadena) > longitud_anterior:
            indice_cadena_mas_larga = indice
        longitud_anterior = len(cadena)
        indice += 1
    return indice_cadena_mas_larga

lista = ["ho", "golas", "portisfeb", "ñovrkm rieñgo vñrog", "h"]

if __name__ == '__main__':
    indice = cadenaMasLarga(lista)
    print("El indice de la cadena más larga es: ",indice)
    print("La cadena es:",lista[indice])
    