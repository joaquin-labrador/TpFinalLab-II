#pragma once
#include "arbol.h"
#include "menus.h"
typedef struct PalabraFrecuente {
    char palabra[20];
    int frecuencia;
    int idDoc;
} PalabraFrecuente;
// Prototipados
// 1)
int busquedaEnAlgunDoc(nodoA *a, char palabra[], int IdDoc);
int repeticiones(nodoT *terminos, int id);
// 2)
int repiticionesTotales(nodoA *a, char palabra[]);
void posAndId(nodoT *a);
// 3)
int preguntarId();
void variosTerminos(nodoA *a);

// 5)
void palabraMayorFrecuencia(nodoA *a, int idDoc, PalabraFrecuente *res);
int compararOcurrencias(nodoT *ocurrencia, PalabraFrecuente *res);

// 6)
void distanciaLevenshtein(nodoA *a, char palabra[]);
int existeTermino(nodoA *a, char palabra[]);
void distancia(nodoA *a, char palabra[]);

char *preguntarPalabra();


int verificarIdIngresado(nodoA *a, int id);
int verificarIdEnLista(nodoT *lista, int id);
int verficadorDeOpcion(int op);
int lanzadorDeVisualizacion(nodoA *a, int op);

int consulta();
void creacionBinario();