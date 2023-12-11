#ifndef MAIN_H
#define MAIN_H

int existeCarpetaArtista(char *nombreArtista);

void encontrarNombreTextos(char *nombreArtista);

void procesarTextosDelArtista(char *nombreTexto,char *nombreArtista, FILE *archivosalida);

void procesarArchivos(char *nombreArtista);

void ejecutarPython(char *nombreArtista);

#endif