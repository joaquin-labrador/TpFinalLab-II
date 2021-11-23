#include "arbol.h"
//Prototipados
//1)
int busquedaEnAlgunDoc (nodoA *a, char palabra[], int IdDoc);
int repeticiones(nodoT *terminos, int id);
//2)
int repiticionesTotales(nodoA *a, char palabra[]);
void posAndId(nodoT *a);
//3)
int preguntarId();
void variosTerminos(nodoA *a);
//6)
void distanciaLevenshtein(nodoA *a,char palabra[]);
int existeTermino(nodoA *a, char palabra[]);
void distancia(nodoA *a, char palabra[]);

char *preguntarPalabra();