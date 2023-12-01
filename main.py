import sys      
import string
import random

def procesarPalabrasEntrada(archivoEntradas):
    
    diccionario = {}

    for linea in archivoEntradas.readlines():
        listaPalabras = linea.split()
        largo = len(listaPalabras)
        for posicion in range(largo):
            palabraActual = listaPalabras[posicion]
            
            if palabraActual not in diccionario:
                diccionario[palabraActual] = {"siguiente": {}, "anterior": {}}

            if posicion + 1 != largo:
                palabraSiguiente = listaPalabras[posicion + 1]
                if palabraSiguiente not in diccionario[palabraActual]["siguiente"]:
                    diccionario[palabraActual]["siguiente"][palabraSiguiente] = 0
                diccionario[palabraActual]["siguiente"][palabraSiguiente] += 1

            if posicion > 0:
                palabraAnterior = listaPalabras[posicion - 1]
                if palabraAnterior not in diccionario[palabraActual]["anterior"]:
                    diccionario[palabraActual]["anterior"][palabraAnterior] = 0
                diccionario[palabraActual]["anterior"][palabraAnterior] += 1

    return diccionario    


def adivinarPalabra(diccionario):
    listaLlaves = list(diccionario.keys())
    palabraFinal = listaLlaves[0]

    for palabra in diccionario:
        if diccionario[palabra] > diccionario[palabraFinal]:
            palabraFinal = palabra

    return palabraFinal



def completarArchivoSalida(diccionario, archivoFrases, archivoSalida):
    for linea in archivoFrases.readlines():
        listaPalabras = linea.split()
        largo = len(listaPalabras)

        for posicion in range(largo):
            palabraActual = listaPalabras[posicion]
            if '_' in palabraActual:
                if posicion > 0 and listaPalabras[posicion - 1] in diccionario:
                    palabraAnterior = listaPalabras[posicion - 1]
                    listaPalabras[posicion] = adivinarPalabra(diccionario[palabraAnterior]["siguiente"])
                elif posicion + 1 < largo and listaPalabras[posicion + 1] in diccionario:
                    palabraSiguiente = listaPalabras[posicion   + 1]
                    listaPalabras[posicion] = adivinarPalabra(diccionario[palabraSiguiente]["anterior"])
                else:
                    palabraAleatoria = random.choice(list(diccionario.keys()))
                    listaPalabras[posicion] = palabraAleatoria

        archivoSalida.write(' '.join(listaPalabras) + '\n')

    

def main():

    if len(sys.argv) < 1:
        print("No se proporcionaron argumentos desde C.")
        

    nombreArtista = sys.argv[1]

    archivoEntradas = open("./Entradas/" + nombreArtista + ".txt", "r")

    archivoFrases = open("./Frases/" + nombreArtista + ".txt", "r")

    archivoSalidas = open("./Salidas/" + nombreArtista + ".txt", "w") 
    
    diccionarioPalabras = procesarPalabrasEntrada(archivoEntradas)
    
    completarArchivoSalida(diccionarioPalabras,archivoFrases,archivoSalidas)

    archivoEntradas.close()
    archivoFrases.close()
    archivoSalidas.close()

   

if __name__ == "__main__":
    main()