import sys
import random

def procesarPalabrasEntradas(archivoEntradas):
    
    diccionarioPalabras = {}

    for linea in archivoEntradas.readlines():
        
        listaPalabras = linea.split()
        largoOracion = len(listaPalabras)

        for posicion in range(largoOracion):

            palabraActual = listaPalabras[posicion]
            
            if palabraActual not in diccionarioPalabras:

                diccionarioPalabras[palabraActual] = {"siguiente": {}, "anterior": {}}

            if posicion + 1 != largoOracion:

                palabraSiguiente = listaPalabras[posicion + 1]

                if palabraSiguiente not in diccionarioPalabras[palabraActual]["siguiente"]:
                    diccionarioPalabras[palabraActual]["siguiente"][palabraSiguiente] = 0

                diccionarioPalabras[palabraActual]["siguiente"][palabraSiguiente] += 1

            if posicion > 0:

                palabraAnterior = listaPalabras[posicion - 1]

                if palabraAnterior not in diccionarioPalabras[palabraActual]["anterior"]:
                    diccionarioPalabras[palabraActual]["anterior"][palabraAnterior] = 0

                diccionarioPalabras[palabraActual]["anterior"][palabraAnterior] += 1

    return diccionarioPalabras   


def adivinarPalabra(diccionarioPalabra):

    listaLlaves = list(diccionarioPalabra.keys())
    palabraFinal = listaLlaves[0]

    for palabra in diccionarioPalabra:
        if diccionarioPalabra[palabra] > diccionarioPalabra[palabraFinal]:
            palabraFinal = palabra

    return palabraFinal



def filtrarLista(listaPalabras,largo,diccionario):

    for posicion in range(largo):

            if '_' in listaPalabras[posicion]:

                if posicion > 0 and listaPalabras[posicion - 1] in diccionario:

                    palabraAnterior = listaPalabras[posicion - 1]
                    listaPalabras[posicion] = adivinarPalabra(diccionario[palabraAnterior]["siguiente"])

                elif posicion + 1 < largo and listaPalabras[posicion + 1] in diccionario:

                    palabraSiguiente = listaPalabras[posicion + 1]
                    listaPalabras[posicion] = adivinarPalabra(diccionario[palabraSiguiente]["anterior"])
                    
                else:
                    palabraAleatoria = random.choice(list(diccionario.keys()))
                    listaPalabras[posicion] = palabraAleatoria



def completarArchivoSalida(diccionario, archivoFrases, archivoSalida):

    for linea in archivoFrases.readlines():

        listaPalabras = linea.split()
        largo = len(listaPalabras)

        filtrarLista(listaPalabras,largo,diccionario)

        archivoSalida.write(' '.join(listaPalabras) + '\n')

    

def main():

    if len(sys.argv) < 1:
        print("No se proporcionaron argumentos desde C.")
        

    nombreArtista = sys.argv[1]

    archivoEntradas = open("./Entradas/" + nombreArtista + ".txt", "r")

    archivoFrases = open("./Frases/" + nombreArtista + ".txt", "r")

    archivoSalidas = open("./Salidas/" + nombreArtista + ".txt", "w") 
    
    diccionarioPalabras = procesarPalabrasEntradas(archivoEntradas)
    
    completarArchivoSalida(diccionarioPalabras,archivoFrases,archivoSalidas)

    archivoEntradas.close()
    archivoFrases.close()
    archivoSalidas.close()

   

if __name__ == "__main__":
    main()