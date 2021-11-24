#include "arbol.h"

nodoT *crearNodoT(int pos, int idDoc) {
    nodoT *nuevo = (nodoT *)malloc(sizeof(nodoT));
    nuevo->idDOC = idDoc;
    nuevo->pos = pos;
    nuevo->sig = NULL;
    return nuevo;
}

nodoA *crearNodoA(char palabra[]) {
    nodoA *nuevo = (nodoA *)malloc(sizeof(nodoA));
    nuevo->frecuencia = 0;
    strcpy(nuevo->palabra, palabra);
    nuevo->ocurrencias = NULL;
    nuevo->der = NULL;
    nuevo->izq = NULL;
    return nuevo;
}
void insertarPorPos(nodoT **lista, nodoT *nuevo) {
    nodoT *act;
    nodoT *ante;
    if (*lista == NULL || (*lista)->pos > nuevo->pos) {
        nuevo->sig = *lista;
        *lista = nuevo;
    } else {
        act = (*lista)->sig;
        ante = *lista;
        while (act != NULL && act->pos < nuevo->pos) {
            ante = act;
            act = act->sig;
        }
        ante->sig = nuevo;
        nuevo->sig = act;
    }
}

void insertarOrdenado(nodoT **lista, int pos, int idDoc) {
    nodoT *nuevo = crearNodoT(pos, idDoc);
    nodoT *act;
    nodoT *ante;
    if (*lista == NULL || (*lista)->idDOC > idDoc) {
        nuevo->sig = *lista;
        *lista = nuevo;
    }

    else {
        act = (*lista)->sig;
        ante = *lista;
        while (act != NULL && act->idDOC < idDoc && act->idDOC != idDoc) {
            ante = act;
            act = act->sig;
        }
        if ((*lista)->idDOC == nuevo->idDOC) {
            insertarPorPos(lista, nuevo);
        } else {
            ante->sig = nuevo;
            nuevo->sig = act;
        }
    }
}
int insertarEnArbol(nodoA **a, termino t) {
    if (*a == NULL) {
        nodoA *aux;
        aux = crearNodoA(t.palabra);
        *a = aux;  // aca se inserta
        insertarOrdenado(&(*a)->ocurrencias, t.pos, t.idDOC);
        (*a)->frecuencia++;
    } else {
        if (strcmpi((*a)->palabra, t.palabra) < 0)
            return insertarEnArbol(&(*a)->der, t);
        else if (strcmpi((*a)->palabra, t.palabra) > 0)
            return insertarEnArbol(&(*a)->izq, t);
        else {  // srtcmpi == 0

            insertarOrdenado(&(*a)->ocurrencias, t.pos, t.idDOC);
            (*a)->frecuencia++;
            return -1;
        }
    }
}
void leerBin(nodoA **a) {
    FILE *buffer = fopen(FILE_PALABRAS, "rb");
    termino aux;
    if (buffer) {
        while (fread(&aux, sizeof(termino), 1, buffer) > 0) {
            insertarEnArbol(a, aux);
        }
        fclose(buffer);
    }
}

// Mostadores
void inorder(nodoA *a) {
    if (a != NULL) {
        inorder(a->izq);
        printf("\n");
        mostrarPalabra(a);
        mostrarSubLista(a->ocurrencias);
        printf("\n");
        inorder(a->der);
    }
}
void preorder(nodoA  *a){
    if(a != NULL){
        mostrarPalabra(a);
        mostrarSubLista(a->ocurrencias);
        preorder(a->izq);
        preorder(a->der);
    }
}
void postorder(nodoA *a){
    if(a != NULL){
      
        postorder(a->izq);
        postorder(a->der);
        mostrarPalabra(a);
        mostrarSubLista(a->ocurrencias);
    }
}
void mostrarSubLista(nodoT *lista) {
    printf("\n\t\t-- Lista de repeticiones --\n");
    while (lista != NULL) {
        mostrarOcurrencia(lista);
        lista = lista->sig;
    }
}
void mostrarOcurrencia(nodoT *lista) {
    printf("\t\t-------------------------\n");
    printf("\t\t-Id doc %d\n", lista->idDOC);
    printf("\t\t-Pos %d\n", lista->pos);
    printf("\t\t-------------------------\n");
}
void mostrarPalabra(nodoA *a) {
    printf("\n\t\t-------------------------\n");
    printf("\t\t-Palabra - %s - \n", a->palabra);
    printf("\t\t-Frecuencia %d\n", a->frecuencia);
    printf("\t\t-------------------------\n");
}
