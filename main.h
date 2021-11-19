//Librerias y constantes

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#define FILE_PALABRAS "Palabras.bin"
//Estructuras de datos
typedef struct {
  char palabra[20];
  int idDOC;
  int pos; //incrementa palabra por palabra, y no letra por letra
}termino;
typedef struct nodoT
{
    int idDOC;
    int pos;
    struct nodoT* sig;
}nodoT;
typedef struct nodoA
{
   char palabra[20];
   int frecuencia; //representa la cantidad de nodos de la lista
   nodoT* ocurrencias; //ordenada por idDOC, luego por pos
   struct nodoA* der;
   struct nodoA* izq;
}nodoA;

//Prototipados
nodoT crearNodoT (int pos,int idDoc);
nodoA crearNodoA (char palabra[],int frecuencia);   
void crearDocumentoDePalabras();
termino crearTermino (char palabra[],int idDoc, int pos);
int verificarID(int id);
int verificadorP(char palabra[]);
