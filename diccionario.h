#pragma once
#include <ctype.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_PALABRAS "Palabras.bin"
#define MAX_TXT 15
#define min(a, b) (((a) < (b)) ? (a) : (b))
// Estructuras de datos
typedef struct {
    char palabra[20];
    int idDOC;
    int pos;  // incrementa palabra por palabra, y no letra por letra
} termino;

termino crearTermino(char palabra[], int idDoc, int pos);
void escribirTermino(char palabra[], int idDoc, int pos);
void leerTexto(int id);
void separarChar(char palabra[], int id, int cantLetras);
int esCaracterValido(char termino);
char *convertirAChar(int id);
void mostrarArchivoBIN();
void mostradorTermino(termino t);
int Levenshtein(char *s1, char *s2);
int verificarIntegridad();