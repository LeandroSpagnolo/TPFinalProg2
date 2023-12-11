#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

void procesarTextosDelArtista(char *nombreTexto,char *nombreArtista, FILE *archivosalida){

    char ubicacionTextos[MAX_LONG_COMANDO];
    sprintf(ubicacionTextos, "./Textos/%s/%s", nombreArtista, nombreTexto);

    FILE *archivoTexto = fopen(ubicacionTextos,"r");
   
    int caracter;
    int caracterPrevio = ' ';

    while ((caracter = fgetc(archivoTexto)) != EOF) {
        caracter = tolower(caracter);

        if (isalpha(caracter) || caracter == ' ') {
            if (!(caracter == ' ' && caracterPrevio == ' ')) {
                fputc(caracter, archivosalida);
            }
        }
        
        if (caracter == '\n' && caracterPrevio != '.') {
            fputc(' ', archivosalida);
        }
        
        if (caracter == '.') {
            fputc('\n', archivosalida);
        }

        caracterPrevio = caracter;
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


int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("No se ha ingresado ningun argumento\n");
        return 1;  
    }

    if(existeCarpetaArtista(argv[1]) == 0){
        printf("No se encontro al artista en la carpeta\n");
        return 2;
    }
    
    encontrarNombreTextos(argv[1]);

    procesarArchivos(argv[1]);

    ejecutarPython(argv[1]);

    return 0;  
}
