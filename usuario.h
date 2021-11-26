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
void repeticionesTotales(nodoA *a, char palabra[], int id, int id2);
int verificarAnd(nodoT *lista, int id, int id2);
void posAndId(nodoT *a, int id, int id2);
// 3)
int preguntarId(nodoA *a);
void variosTerminos(nodoA *a);

// 4
int idMaximo();
int validarPosicion(nodoT *ocurrencias, char palabra[20], int id, int posiciones);
int terminoEncontrado(nodoA *a, char palabra[20], int id, int posicionesValidas);
int compararCoincidencia(nodoA *a, char matriz[][20], int posiciones[], int id, int validosFrase, int posicionValida);
int cargarPosiciones(nodoT *ocurrencias, int posiciones[], int id);
int obtenerValidos(nodoA *a, char palabra[20], int posiciones[], int id);
int validarFrase(nodoA *a, char matriz[][20], int posiciones[], int id, int validosFrase);
void buscarFrase(nodoA *a, char frase[512]);
int tokenizarFrase(char frase[512], char matriz[][20]);

// 5)
void palabraMayorFrecuencia(nodoA *a, int idDoc, PalabraFrecuente *res);
int compararOcurrencias(nodoT *ocurrencia, PalabraFrecuente *res);

// 6)
void distanciaLevenshtein(nodoA *a, char palabra[], int id);
int existeTermino(nodoA *a, char palabra[]);
void distancia(nodoA *a, char palabra[], int id);
int existePalabraDocumento(nodoA *a, char palabra[], int id);

char *preguntarPalabra(nodoA *a, int id);

int verificarIdIngresado(nodoA *a, int id);
int verificarIdEnLista(nodoT *lista, int id);
int verficadorDeOpcion(int op);
int lanzadorDeVisualizacion(nodoA *a, int op);

int consulta();
void creacionBinario();
void mostrarPalabraFrecuente(PalabraFrecuente termino);