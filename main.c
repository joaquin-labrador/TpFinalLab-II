#include "main.h"
int main(){
    
    return 0;
}
nodoT crearNodoT (int pos,int idDoc){
    nodoT *nuevo = (nodoT*)malloc(sizeof(nodoT));
    nuevo->idDOC = idDoc;
    nuevo->pos = pos;
    nuevo->sig = NULL;
}
nodoA crearNodoA (char palabra[],int frecuencia){
    nodoA *nuevo = (nodoA*)malloc(sizeof(nodoA));
    nuevo->frecuencia = frecuencia;
    strcpy(nuevo->palabra,palabra);
    nuevo->ocurrencias = NULL;
    nuevo->der= NULL;
    nuevo->izq = NULL;
}
