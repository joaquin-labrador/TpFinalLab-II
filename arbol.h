// Librerias y constantes

#include "diccionario.h"

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
void mostradorTermino(termino t);
nodoA *existePalabraArbol(nodoA *a, char p[]);
void inorder(nodoA *a);
void insertarEnArbol(nodoA **a, termino t);
void leerBin (nodoA **a);
void mostrarSubLista (nodoT *lista);
void mostrarOcurrencia(nodoT *lista);
void mostrarPalabra(nodoA *a);