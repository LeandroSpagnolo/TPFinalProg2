#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int existeCarpetaArtista(char *nombreArtista){

    system("cd Textos/ && ls > ../nombresArtistas.txt");

    FILE *archivo = fopen("./nombresArtistas.txt","r");

    char linea[100];

    int encontro = 0;

    while (fscanf(archivo, "%s", linea) == 1&& encontro == 0) {
        if(strcmp(linea,nombreArtista) == 0){
            encontro = 1;
        }
    }

    fclose(archivo);

    return encontro;

}

void encontrarNombreTextos(char *nombreArtista){

    char comando[200]; 
    
    sprintf(comando, "cd Textos/%s && ls > ../../nombresTextos.txt", nombreArtista);

    system(comando);

}

void procesarTextos(char *nombreTexto,char *nombreArtista, FILE *archivosalida){

    char ubicacionTextos[100] = "./Textos/";
    strcat(ubicacionTextos,nombreArtista);
    strcat(ubicacionTextos,"/");
    strcat(ubicacionTextos,nombreTexto);

    FILE *archivoTexto = fopen(ubicacionTextos,"r");
   
    int caracter;
    int caracterPrevio = ' ';

    while ((caracter = fgetc(archivoTexto)) != EOF) {
        caracter = tolower(caracter);

        if (isalnum(caracter) || caracter == ' ') {
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

    char ubicacionEntradas[100] = "./Entradas/";
    strcat(ubicacionEntradas,nombreArtista);
    strcat(ubicacionEntradas,".txt");
    
    FILE *archivoEntradas = fopen(ubicacionEntradas,"w");

    char linea[100];

    

    while (fscanf(archivoNombresTextos, "%s", linea) == 1) {
       procesarTextos(linea,nombreArtista,archivoEntradas);
    }

    fclose(archivoNombresTextos);
    fclose(archivoEntradas);

}

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("No se ha ingresado ningun argumento\n");
        return 1;  
    }

    if(existeCarpetaArtista(argv[1]) == 0){
        printf("No se encontro al artista en la carpeta\n");
        return 1;
    }
    
    encontrarNombreTextos(argv[1]);

    procesarArchivos(argv[1]);

    char comando[100];
    
    sprintf(comando, "python3 main.py %s", argv[1]);

    system(comando);

    return 0;  
}
