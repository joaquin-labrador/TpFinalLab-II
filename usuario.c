#include "usuario.h"


//Punto 1

int busquedaEnAlgunDoc (nodoA *a, char palabra[], int IdDoc){
   if(a != NULL){
       if(strcmpi(a->palabra,palabra) == 0){
            int rep = repeticiones(a->ocurrencias,IdDoc);
            return rep;
       }
       else if (strcmpi(a->palabra,palabra) < 0)
            return busquedaEnAlgunDoc(a->der,palabra,IdDoc);
        else
            return busquedaEnAlgunDoc(a->izq,palabra,IdDoc);
   }
   else{
       return -1;// Si la palabra no existe
   }
}

int repeticiones(nodoT *terminos, int id){
    int i = 0;
    while(terminos != NULL){
        if(terminos->idDOC == id){
            if(i == 0)
                printf("La palabra ingresada se encuentra en la/s posicion/es del documento %d: ",id);
            printf("-%d-",terminos->pos);
            i++;
        }
        terminos = terminos->sig;
    }
    return i;
}

//Punto 2

int repiticionesTotales(nodoA *a, char palabra[]){
       if(a != NULL){
       if(strcmpi(a->palabra,palabra) == 0){
            posAndId(a->ocurrencias);
            return a->frecuencia;
       }
       else if (strcmpi(a->palabra,palabra) < 0)
            return repiticionesTotales(a->der,palabra);
        else
            return repiticionesTotales(a->izq,palabra);
   }
   else{
       return -1;// Si la palabra no existe
   }
}
void posAndId(nodoT *a){
    printf("- Posicion/es y Documento/s de la palabra buscada-\n");
    while(a != NULL){
        printf("-----------------\n");
        printf("Posicion %d \n",a->pos);
        printf("Documento %d \n",a->idDOC);
        printf("-----------------\n");
        a = a->sig;
    }
}

//Punto 3
int preguntarId(){
    int i = 0;
    do{
    printf("De que documento desea buscar varios terminos\n");
    scanf("%d",&i);
    system("cls");
    }while(i > MAX_TXT && i <= 0);
    return i;
}
void variosTerminos(nodoA *a){
    int id = preguntarId();
    char s;
    char termino[30];
    printf("Ingrese palabra a buscar en el documento %d\n",&id);
    do{
        printf("-: ");
        fflush(stdin);
        gets(termino);
        busquedaEnAlgunDoc(a,termino,id);
        system("pause");
        system("cls");
        
        printf("Desea continuar buscando terminos en este documento\n");
        fflush(stdin);
        scanf("%c",&s);
        towlower(s);
        system("cls");
    }while(s == 's');
    
}