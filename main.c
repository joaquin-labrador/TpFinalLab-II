#include "main.h"
int main(){
    leerTexto(3);
    nodoA *arbolDeLista = NULL;
    leerBin(&arbolDeLista); 
    inorder(arbolDeLista);
    return 0;
}


