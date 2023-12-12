import sys
import random

def procesarPalabrasEntradas(archivoEntradas):
    
    diccionarioPalabras = {}

    # Lee cada línea del archivo de entradas
    for linea in archivoEntradas.readlines():
        
        listaPalabras = linea.split()
        largoOracion = len(listaPalabras)

        # Procesa cada palabra en la línea
        for posicion in range(largoOracion):

            palabraActual = listaPalabras[posicion]
            
            # Si la palabra no está en el diccionario, se agrega
            if palabraActual not in diccionarioPalabras:
                diccionarioPalabras[palabraActual] = {"siguiente": {}, "anterior": {}}

            # Si no es la última palabra, procesa la palabra siguiente
            if posicion + 1 != largoOracion:
                palabraSiguiente = listaPalabras[posicion + 1]

                # Actualiza el contrador de la palabra siguiente
                if palabraSiguiente not in diccionarioPalabras[palabraActual]["siguiente"]:
                    diccionarioPalabras[palabraActual]["siguiente"][palabraSiguiente] = 0

                diccionarioPalabras[palabraActual]["siguiente"][palabraSiguiente] += 1

            # Si no es la primera palabra, procesa la palabra anterior
            if posicion > 0:
                palabraAnterior = listaPalabras[posicion - 1]

                # Actualiza el contrador de la palabra anterior
                if palabraAnterior not in diccionarioPalabras[palabraActual]["anterior"]:
                    diccionarioPalabras[palabraActual]["anterior"][palabraAnterior] = 0

                diccionarioPalabras[palabraActual]["anterior"][palabraAnterior] += 1

    return diccionarioPalabras  


def adivinarPalabra(diccionarioPalabra):

    listaLlaves = list(diccionarioPalabra.keys())
    palabraFinal = listaLlaves[0]

    # Encuentra la palabra más probable basándose en la que tiene más repeticiones
    for palabra in diccionarioPalabra:
        if diccionarioPalabra[palabra] > diccionarioPalabra[palabraFinal]:
            palabraFinal = palabra

    return palabraFinal



def filtrarLista(listaPalabras, largo, diccionario):

    for posicion in range(largo):
        Encontro = False

        if '_' in listaPalabras[posicion]:

            # Intenta adivinar la palabra basándose en las palabras anterior o siguiente
            if posicion > 0 and listaPalabras[posicion - 1] in diccionario:
                palabraAnterior = listaPalabras[posicion - 1]
                if diccionario[palabraAnterior]["siguiente"] != {}:
                    listaPalabras[posicion] = adivinarPalabra(diccionario[palabraAnterior]["siguiente"])
                    Encontro = True

            elif posicion + 1 < largo and listaPalabras[posicion + 1] in diccionario:
                palabraSiguiente = listaPalabras[posicion + 1]
                if diccionario[palabraSiguiente]["anterior"] != {}:
                    listaPalabras[posicion] = adivinarPalabra(diccionario[palabraSiguiente]["anterior"])
                    Encontro = True

            # Si no se pudo adivinar, elige una palabra aleatoria del diccionario
            if not Encontro:
                palabraAleatoria = random.choice(list(diccionario.keys()))
                listaPalabras[posicion] = palabraAleatoria



def completarArchivoSalida(diccionario, archivoFrases, archivoSalida):

    # Lee cada línea del archivo de frases
    for linea in archivoFrases.readlines():

        listaPalabras = linea.split()
        largo = len(listaPalabras)

        # Filtra y completa la lista de palabras
        filtrarLista(listaPalabras, largo, diccionario)

        archivoSalida.write(' '.join(listaPalabras) + '\n')

    

def main():

    if len(sys.argv) < 1:
        print("No se proporcionaron argumentos desde C.")
    
    nombreArtista = sys.argv[1]

    archivoEntradas = open("./Entradas/" + nombreArtista + ".txt", "r")
    archivoFrases = open("./Frases/" + nombreArtista + ".txt", "r")
    archivoSalidas = open("./Salidas/" + nombreArtista + ".txt", "w") 
    
    diccionarioPalabras = procesarPalabrasEntradas(archivoEntradas)
    
    completarArchivoSalida(diccionarioPalabras, archivoFrases, archivoSalidas)

    archivoEntradas.close()
    archivoFrases.close()
    archivoSalidas.close()

   

if __name__ == "__main__":
    main()