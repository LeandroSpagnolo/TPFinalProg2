#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define MAX_LONG_COMANDO 300

// Función para verificar si existe una carpeta para un artista dado
int existeCarpetaArtista(char *nombreArtista){

    // Ejecuta el comando para listar archivos en la carpeta Textos y guarda los nombres en el archivo nombresArtistas.txt
    system("cd Textos/ && ls > ../nombresArtistas.txt");

    FILE *archivoNombreArtistas = fopen("./nombresArtistas.txt","r");

    char linea[100];

    int encontroArtista = 0;

    // Lee cada línea del archivo de nombres de artistas
    while (fscanf(archivoNombreArtistas, "%s", linea) == 1 && encontroArtista == 0) {
        // Compara el nombre del artista con la línea actual
        if(strcmp(linea, nombreArtista) == 0){
            encontroArtista = 1; 
        }
    }

    fclose(archivoNombreArtistas); 

    return encontroArtista; // Devuelve 1 si se encontró al artista, 0 si no
}

// Función para obtener los nombres de los textos de un artista y guardarlos en un archivo
void encontrarNombreTextos(char *nombreArtista){

    char comando[MAX_LONG_COMANDO]; 
    
    // Construye el comando para cambiar al directorio de Textos del artista y listar archivos
    sprintf(comando, "cd Textos/%s && ls > ../../nombresTextos.txt", nombreArtista);

    // Ejecuta el comando
    system(comando);
}

// Función para procesar un solo carácter en un archivo de salida
void procesarCaracter(FILE *archivosalida, char caracter, char *caracterPrevio) {
    caracter = tolower(caracter); // Convierte el carácter a minúscula

    if (isalpha(caracter) || caracter == ' ') {
        if (!(caracter == ' ' && *caracterPrevio == ' ') && *caracterPrevio != '.') {
            fputc(caracter, archivosalida);
        }
    }

    if (caracter == '\n' && isalpha(*caracterPrevio)) {
        fputc(' ', archivosalida);
    }

    // Si es un punto, se agrega un salto de línea para dividir las oraciones
    if (caracter == '.') {
        fputc('\n', archivosalida);
    }

    *caracterPrevio = caracter; 
}

// Función para procesar los textos de un artista y escribir el resultado en un archivo de salida
void procesarTextosDelArtista(char *nombreTexto, char *nombreArtista, FILE *archivosalida) {
    char ubicacionTextos[MAX_LONG_COMANDO];
    sprintf(ubicacionTextos, "./Textos/%s/%s", nombreArtista, nombreTexto);

    FILE *archivoTexto = fopen(ubicacionTextos, "r");

    char caracter;
    char caracterPrevio = ' ';

    // Lee cada carácter del archivo de texto y lo procesa
    while ((caracter = fgetc(archivoTexto)) != EOF) {
        procesarCaracter(archivosalida, caracter, &caracterPrevio);
    }

    fclose(archivoTexto); 
}

// Función para procesar todos los archivos de texto de un artista y escribir el resultado en un archivo de salida
void procesarArchivos(char *nombreArtista){

    FILE *archivoNombresTextos = fopen("./nombresTextos.txt","r");

    char ubicacionEntradasArtista[MAX_LONG_COMANDO];
    sprintf(ubicacionEntradasArtista, "./Entradas/%s.txt", nombreArtista);
    
    FILE *archivoEntradasArtista = fopen(ubicacionEntradasArtista,"w");

    char linea[100];

    // Lee cada nombre de texto y procesa los archivos correspondientes
    while (fscanf(archivoNombresTextos, "%s", linea) == 1) {
       procesarTextosDelArtista(linea, nombreArtista, archivoEntradasArtista);
    }

    fclose(archivoNombresTextos); 
    fclose(archivoEntradasArtista); 
}

// Función para ejecutar un script de Python con el nombre del artista como argumento
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

// Funciones para manejar los test
void manejarTest(){

    testExisteCarpetaArtista();

    testProcesarCaracter();

    printf("Los Test se han ejecutado correctamente\n");
}

void verificarExistenciaCarpetas(){

    if (system("test -d Textos") != 0) {
        printf("No se encontro la carpeta Textos\n");
        exit(1);
    }

    if (system("test -d Frases") != 0) {
        printf("No se encontro la carpeta Frases\n");
        exit(1);
    }

    if (system("test -d Salidas") != 0) {
        if (system("mkdir Salidas") != 0) {
            perror("Error al crear la carpeta Salidas");
            exit(1);
        }
    } 
    
    if (system("test -d Entradas") != 0) {
        if (system("mkdir Entradas") != 0) {
            perror("Error al crear la carpeta Entradas");
            exit(1);
        }
    }

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

    verificarExistenciaCarpetas();

    if(existeCarpetaArtista(argv[1]) == 0){
        printf("No se encontro al artista en la carpeta\n");
        exit(1);
    }

    encontrarNombreTextos(argv[1]);

    procesarArchivos(argv[1]);

    ejecutarPython(argv[1]);

    return 0;  
}
