#include "arbol.h"


nodoT *crearNodoT(int pos, int idDoc)
{
    nodoT *nuevo = (nodoT *)malloc(sizeof(nodoT));
    nuevo->idDOC = idDoc;
    nuevo->pos = pos;
    nuevo->sig = NULL;
    return nuevo;
}

nodoA *crearNodoA(char palabra[])
{
    nodoA *nuevo = (nodoA *)malloc(sizeof(nodoA));
    nuevo->frecuencia = 0;
    strcpy(nuevo->palabra, palabra);
    nuevo->ocurrencias = NULL;
    nuevo->der = NULL;
    nuevo->izq = NULL;
    return nuevo;
}

void insertarOrdenado(nodoT **lista, int pos, int idDoc)
{
    nodoT *nuevo = crearNodoT(pos, idDoc);
    nodoT *act;
    nodoT *ante;
    if (*lista == NULL)
    {
        *lista = nuevo;
    }
    else
    {
        if (*lista != NULL && (*lista)->idDOC < idDoc)
        {
            nuevo->sig = *lista;
            *lista = nuevo;
        }
        else
        {
            act = (*lista)->sig;
            ante = *lista;
            while (act != NULL && act->idDOC > idDoc)
            {
                ante = act;
                act = act->sig;
            }
            ante->sig = act->sig;
            act = nuevo;
        }
    }
}
void insertarEnArbol(nodoA **a, termino t){
    if(*a == NULL){
        *a = crearNodoA(t.palabra);
        insertarOrdenado(&(*a)->ocurrencias,t.pos,t.idDOC);
        (*a)->frecuencia += 1;
    }
    else{
        if(strcmpi((*a)->palabra,t.palabra) < 0)
            insertarEnArbol(&(*a)->der,t);
        else if(strcmpi((*a)->palabra,t.palabra) > 0)
            insertarEnArbol(&(*a)->izq,t);
        else{//srtcmpi == 0
            printf("-%s-\n",t.palabra);
            insertarOrdenado(&(*a)->ocurrencias,t.pos,t.idDOC);
            (*a)->frecuencia += 1;
        } 
    }
}
void leerBin (nodoA **a){
    FILE *buffer = fopen(FILE_PALABRAS,"rb");
    termino aux;
    if(buffer){
        while (fread(&aux,sizeof(termino),1,buffer) > 0)
        {
            insertarEnArbol(a,aux);
        }
        fclose(buffer);
    }
}

//Mostadores
void inorder(nodoA *a){
    if(a != NULL){
        inorder(a->izq);
        printf("\n");
        mostrarPalabra(a);
        mostrarSubLista(a->ocurrencias);
        printf("\n");
        inorder(a->der);
    }
}

void mostrarSubLista (nodoT *lista){
    printf("-- Lista de repeticiones --\n");
    while(lista != NULL){
        mostrarOcurrencia(lista);
        lista = lista->sig;
    }
}
void mostrarOcurrencia(nodoT *lista){
    printf("-------------------------\n");
    printf("-Id doc %d\n",lista->idDOC);
    printf("-Pos %d\n",lista->pos);
    printf("-------------------------\n");
}
void mostrarPalabra(nodoA *a){
    printf("-------------------------\n");
    printf("-Palabra - %s - \n",a->palabra);
    printf("-Frecuencia %d\n",a->frecuencia);
    printf("-------------------------\n");
}
