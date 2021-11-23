#include "main.h"
int main(){
    /* Creacion de una archivo binario a aparitir de un archivo .txt
    leerTexto();*/ 
    //Creacion del arbol a partir del archivo binario
    nodoA *arbolDeLista = NULL;
    leerBin(&arbolDeLista); 
    int repeticiones = 0;
    int opcion = 0;
    
    do
    {
        menuMain();
        scanf("%d",&opcion);
        system("cls");
        switch (opcion)
        {
        case 1:
            repeticiones = busquedaEnAlgunDoc(arbolDeLista,preguntarPalabra(),preguntarId());
            printf("La palabra se repite %d vez / veces en el documento ingresado\n",repeticiones);
            system("pause");
            system("cls");
            break;
        case 2:
            repeticiones = repiticionesTotales(arbolDeLista,preguntarPalabra());
            printf("La palabra ingresada se repite %d vez / veces en todos los archivos\n",repeticiones);
            system("pause");
            system("cls");
            break;
        case 3:
            variosTerminos(arbolDeLista);
            system("pause");
            system("cls");
            break;
        case 4:
            printf("Estamos trabajando, funcion en desarrollo\n");
            system("pause");
            system("cls");
            break;
        case 5:
            printf("Estamos trabajando, funcion en desarrollo\n");
            system("pause");
            system("cls");
            break;
        case 6: 
            distanciaLevenshtein(arbolDeLista,preguntarPalabra());
            system("pause");
            system("cls");
            break;
        case 7: 
            menuVisualizacionArbol();
            break;
        case 8:
            exit(0);
        default:
            break;
        }
    } while (opcion >= 0 || opcion < 7);//Si se agregan opciones al menuMain, se aumentan los paramentros
    
    return 0;
   
}


