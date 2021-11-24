#include "main.h"

#include <Windows.h>

int main() {
    system("title Motor de busqueda");
    /* Creacion de una archivo binario a aparitir de un archivo .txt*/
    // leerTexto(2);
    // Creacion del arbol a partir del archivo binario
    PalabraFrecuente res;
    res.frecuencia = 0;
    nodoA *arbolDeLista = NULL;
    nodoA *nodoConMayorFrecuencia = NULL;
    leerBin(&arbolDeLista);
    int repeticiones = 0;
    int opcion = 0;
    int opcionVisulizacion = 0;
    int id = 0;
    int mayor = 0;
    int repeticionMenu = 1;

    if (verificarIntegridad() == 0) {
        printf("No se ha encontrado diccionario, se cargara uno nuevo\n");
        for (int i = 1; i < MAX_TXT; i++) {
            leerTexto(i);
        }
        printf("Diccionario cargado, reinicie el programa!\n");
        system("pause");
        exit(0);
    }

    if (consulta() == 0) {
        remove(FILE_PALABRAS);
        printf("Diccionario recargado, reinicie el programa!\n");
        for (int i = 1; i < MAX_TXT; i++) {
            leerTexto(i);
        }
        system("pause");
        exit(0);
    }

    do {
        menuMain();
        printf("\n\t    -> ");
        scanf(" %d", &opcion);
        system("cls");
        switch (opcion) {
            case 1:
                repeticiones = busquedaEnAlgunDoc(arbolDeLista, preguntarPalabra(arbolDeLista), preguntarId(arbolDeLista));
                if (repeticiones == 0) {
                    printf("\n\n\t\tLa palabra no existe en el documento!\n");
                } else {
                    printf("\n\n\t\tLa palabra se repite %d %s en el documento ingresado\n", repeticiones, repeticiones == 1 ? "vez" : "veces");
                }
                printf("\t\t");
                system("pause");
                system("cls");
                break;
            case 2:
                repeticiones = repiticionesTotales(arbolDeLista, preguntarPalabra(arbolDeLista));
                printf("\n\n\t\tLa palabra ingresada se repite %d vez / veces en todos los archivos\n", repeticiones);
                printf("\t\t");
                system("pause");
                system("cls");
                break;
            case 3:
                variosTerminos(arbolDeLista);
                system("cls");
                break;
            case 4:
                printf("\n\n\t\tEstamos trabajando, funcion en desarrollo\n");
                printf("\t\t");
                system("pause");
                system("cls");
                break;
            case 5:
                palabraMayorFrecuencia(arbolDeLista, preguntarId(arbolDeLista), &res);
                // TODO: ESTITICA DE ESTE MOSTRADOR
                printf("P: %s |F:  %d |ID:  %d", res.palabra, res.frecuencia, res.idDoc);

                printf("\t\t");
                system("pause");
                system("cls");
                break;
            case 6:
                do {
                    menuVisualizacionArbol();
                    printf("\t\t");
                    scanf("%d", &opcionVisulizacion);
                    system("cls");
                } while (lanzadorDeVisualizacion(arbolDeLista, opcionVisulizacion) != 1);
                system("cls");
                break;
            case 7:
                repeticionMenu = 0;
            default:
                break;
        }
    } while (repeticionMenu);  // Si se agregan opciones al menuMain, se aumentan los paramentros

    return 0;
}
