#include "main.h"

#include <Windows.h>

#include "arbol.h"

int main() {
    char frase[256];
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
                id = preguntarId(arbolDeLista);
                do {
                    repeticiones = busquedaEnAlgunDoc(arbolDeLista, preguntarPalabra(arbolDeLista, id), id);
                    if (repeticiones == -1) {
                        printf("\n\n\t\tLa palabra no existe en el documento!\n");
                    }
                } while (repeticiones == 0);

                printf("\n\n\t\tLa palabra se repite %d %s en el documento ingresado\n", repeticiones, repeticiones == 1 ? "vez" : "veces");
                printf("\t\t");
                system("pause");
                system("cls");
                break;
            case 2:
                repeticiones = repiticionesTotales(arbolDeLista, preguntarPalabra(arbolDeLista, -1));
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
                fflush(stdin);
                //TODO: que si te equivocas puede volver a ingresar una frase
                printf("\n\n\t\t  Ingrese una frase \n");
                printf("\t\t ->");
                gets(frase);
                buscarFrase(arbolDeLista, frase);
                printf("\t\t");
                system("pause");
                system("cls");
                break;
            case 5:
                palabraMayorFrecuencia(arbolDeLista, preguntarId(arbolDeLista), &res);
                mostrarPalabraFrecuente(res);
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
                printf("\n\n\t\tUsted no a ingresado un numero, se cortara el proceso\n");
                system("pause");
                system("cls");
                repeticionMenu = 0;
                break;
        }
    } while (repeticionMenu);  // Si se agregan opciones al menuMain, se aumentan los paramentros

    return 0;
}

