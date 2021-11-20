// Librerias y constantes

#include <ctype.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_PALABRAS "Palabras.bin"

// Estructuras de datos
typedef struct {
    char palabra[20];
    int idDOC;
    int pos;  // incrementa palabra por palabra, y no letra por letra
} termino;
typedef struct nodoT {
    int idDOC;
    int pos;
    struct nodoT* sig;
} nodoT;
typedef struct nodoA {
    char palabra[20];
    int frecuencia;      // representa la cantidad de nodos de la lista
    nodoT* ocurrencias;  // ordenada por idDOC, luego por pos
    struct nodoA* der;
    struct nodoA* izq;
} nodoA;

// Prototipados
nodoT *crearNodoT(int pos, int idDoc);
nodoA *crearNodoA(char palabra[]);
termino crearTermino(char palabra[], int idDoc, int pos);
void escribirTermino(char palabra[], int idDoc, int pos);
void leerTexto();
int pesoArchivo();
char* convertirAChar(int id);
int esCaracterValido(char termino);
void separarChar(char palabra[], int id, int cantLetras);
void insertarArbol(nodoA **a,termino t);
void mostrarArchivoBIN();
void mostradorTermino(termino t);
