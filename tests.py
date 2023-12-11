import pytest
from io import StringIO

import main

def test_procesarPalabrasEntradas():
    datosEntrada = "hola mundo mundo mundo mundo esto es una prueba esto es un ejemplo mundo mundo de prueba para muchas palabras"
    archivoEntrada = StringIO(datosEntrada)

    resultado = main.procesarPalabrasEntradas(archivoEntrada)

    assert resultado["hola"]["siguiente"]["mundo"] == 1
    assert resultado["mundo"]["anterior"]["hola"] == 1
    assert resultado["mundo"]["siguiente"]["mundo"] == 4
    assert resultado["mundo"]["siguiente"]["esto"] == 1
    assert resultado["esto"]["anterior"]["mundo"] == 1
    assert resultado["es"]["siguiente"]["una"] == 1
    assert resultado["una"]["anterior"]["es"] == 1

    
def test_adivinarPalabra():
    diccionario_prueba_1 = {'hola': 3, 'mundo': 2, 'python': 5, 'ejemplo': 1}
    resultado = main.adivinarPalabra(diccionario_prueba_1)
    assert resultado == 'python'

    diccionario_prueba_2 = {'hola': 4, 'mundo': 4, 'python': 4, 'ejemplo': 4}
    resultado = main.adivinarPalabra(diccionario_prueba_2)
    assert resultado == 'hola'

    diccionario_prueba_3 = {'unicapalabra': 10}
    resultado = main.adivinarPalabra(diccionario_prueba_3)
    assert resultado == 'unicapalabra'


def test_filtrarLista():

    lista = ["hola","_","esto","es","un","ejemplo"]
    diccionarioPrueba = {
        'hola': {"siguiente": {'mundo': 3, 'python': 2}, "anterior": {'ejemplo': 1}},
        'mundo': {"siguiente": {'hola': 2, 'python': 1}, "anterior": {'ejemplo': 1}},
        'python': {"siguiente": {'hola': 1, 'mundo': 1}, "anterior": {'ejemplo': 1}},
        'ejemplo': {"siguiente": {'hola': 1, 'mundo': 1, 'python': 1}, "anterior": {}}
    }

    largoLista = len(lista)

    main.filtrarLista(lista,largoLista,diccionarioPrueba)

    assert lista == ["hola","mundo","esto","es","un","ejemplo"]
