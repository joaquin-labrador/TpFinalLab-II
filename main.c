#include "main.h"
int main(){
    /* Creacion de una archivo binario a aparitir de un archivo .txt*/
    //leerTexto(2);
    //Creacion del arbol a partir del archivo binario
    nodoA *arbolDeLista = NULL;
    nodoA *nodoConMayorFrecuencia = NULL;
    leerBin(&arbolDeLista); 
    int repeticiones = 0;
    int opcion = 0;
    int id = 0;
    int mayor = 0;
    bool repeticionMenu = true;
    do
    {
       
        menuMain();
        printf("\n\t    -> ");
        scanf(" %d",&opcion);
        system("cls");
        switch (opcion)
        {
        case 1:
            repeticiones = busquedaEnAlgunDoc(arbolDeLista,preguntarPalabra(arbolDeLista),preguntarId());
            printf("\n\n\t\tLa palabra se repite %d vez / veces en el documento ingresado\n",repeticiones);
            system("pause");
            system("cls");
            break;
        case 2:
            repeticiones = repiticionesTotales(arbolDeLista,preguntarPalabra(arbolDeLista));
            printf("\n\n\t\tLa palabra ingresada se repite %d vez / veces en todos los archivos\n",repeticiones);
            system("pause");
            system("cls");
            break;
        case 3:
            variosTerminos(arbolDeLista);
            system("cls");
            break;
        case 4:
            printf("\n\n\t\tEstamos trabajando, funcion en desarrollo\n");
            system("pause");
            system("cls");
            break;
        case 5:
            printf("\n\n\t\tEstamos trabajando, funcion en desarrollo\n");
            system("pause");
            system("cls");
            break;
        case 6: 
            menuVisualizacionArbol();

            break;
        case 7:
            repeticionMenu = false;
        default:
            break;
        }
    } while (repeticionMenu);//Si se agregan opciones al menuMain, se aumentan los paramentros
    
    return 0;
   
}


