#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define MAX_LONG_COMANDO 300

int existeCarpetaArtista(char *nombreArtista){

    system("cd Textos/ && ls > ../nombresArtistas.txt");

    FILE *archivoNombreArtistas = fopen("./nombresArtistas.txt","r");

    char linea[100];

    int encontroArtista = 0;

    while (fscanf(archivoNombreArtistas, "%s", linea) == 1&& encontroArtista == 0) {
        if(strcmp(linea,nombreArtista) == 0){
            encontroArtista = 1;
        }
    }

    fclose(archivoNombreArtistas);

    return encontroArtista;

}

void encontrarNombreTextos(char *nombreArtista){

    char comando[MAX_LONG_COMANDO]; 
    
    sprintf(comando, "cd Textos/%s && ls > ../../nombresTextos.txt", nombreArtista);

    system(comando);

}

void procesarCaracter(FILE *archivosalida, char caracter, char *caracterPrevio) {
    caracter = tolower(caracter);

    if (isalpha(caracter) || caracter == ' ') {
        if (!(caracter == ' ' && *caracterPrevio == ' ') && *caracterPrevio != '.') {
            fputc(caracter, archivosalida);
        }
    }

    if (caracter == '\n' && isalpha(*caracterPrevio)) {
        fputc(' ', archivosalida);
    }

    if (caracter == '.') {
        fputc('\n', archivosalida);
    }

    *caracterPrevio = caracter;
}

void procesarTextosDelArtista(char *nombreTexto, char *nombreArtista, FILE *archivosalida) {
    char ubicacionTextos[MAX_LONG_COMANDO];
    sprintf(ubicacionTextos, "./Textos/%s/%s", nombreArtista, nombreTexto);

    FILE *archivoTexto = fopen(ubicacionTextos, "r");

    char caracter;
    char caracterPrevio = ' ';

    while ((caracter = fgetc(archivoTexto)) != EOF) {
        procesarCaracter(archivosalida, caracter, &caracterPrevio);
    }

    fclose(archivoTexto);
}

void procesarArchivos(char *nombreArtista){

    FILE *archivoNombresTextos = fopen("./nombresTextos.txt","r");

    char ubicacionEntradasArtista[MAX_LONG_COMANDO];
    sprintf(ubicacionEntradasArtista, "./Entradas/%s.txt", nombreArtista);
    
    FILE *archivoEntradasArtista = fopen(ubicacionEntradasArtista,"w");

    char linea[100];

    while (fscanf(archivoNombresTextos, "%s", linea) == 1) {
       procesarTextosDelArtista(linea,nombreArtista,archivoEntradasArtista);
    }

    fclose(archivoNombresTextos);
    fclose(archivoEntradasArtista);

}

void ejecutarPython(char *nombreArtista){

    char comando[MAX_LONG_COMANDO];
    
    sprintf(comando, "python3 main.py %s", nombreArtista);

    system(comando);
}

void testExisteCarpetaArtista() {
    assert(existeCarpetaArtista("Fito_Paez") == 1);
    assert(existeCarpetaArtista("NombreArtistaNoExistente") == 0);
}

void testProcesarCaracter(){

    FILE *archivosalida = fopen("salida.txt", "w+");

    char caracterPrevio = ' ';

    procesarCaracter(archivosalida, 'A', &caracterPrevio);
    procesarCaracter(archivosalida, 'B', &caracterPrevio);
    procesarCaracter(archivosalida, ' ', &caracterPrevio);
    procesarCaracter(archivosalida, 'C', &caracterPrevio);
    
    fseek(archivosalida, 0, SEEK_SET);
    
    assert(fgetc(archivosalida) == 'a');
    assert(fgetc(archivosalida) == 'b');
    assert(fgetc(archivosalida) == ' ');
    assert(fgetc(archivosalida) == 'c');

    fclose(archivosalida);

    remove("salida.txt");


}

void manejarTest(){

    testExisteCarpetaArtista();

    testProcesarCaracter();

    printf("Los Test se han ejecutado correctamente\n");

}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("No se ha ingresado ningun argumento\n");
        exit(1);  
    }

    if(strcmp(argv[1],"test") == 0){
        manejarTest();
        return 0;
    }

    if(existeCarpetaArtista(argv[1]) == 0){
        printf("No se encontro al artista en la carpeta\n");
        exit(1);
    }
    
    encontrarNombreTextos(argv[1]);

    procesarArchivos(argv[1]);

    ejecutarPython(argv[1]);

    return 0;  
}
