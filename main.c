#include "main.h"
int main()
{
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
    int creacionArchivo = 0;
    creacionArchivo = verificarIntegridad();//Funcion ubicada en diccionario.c
    if (creacionArchivo == 0)
    {
       creacionBinario();//diccionario.c // la funcion anda pero no continua compilando crea el bin y se rompe
    }

    if (consulta() == 0)
    {
        //reiniciarDic();
    }

    do
    {
        menuMain();
        printf("\n\t    -> ");
        scanf(" %d", &opcion);
        system("cls");
        switch (opcion)
        {
        case 1:
            repeticiones = busquedaEnAlgunDoc(arbolDeLista, preguntarPalabra(arbolDeLista), preguntarId(arbolDeLista));
            printf("\n\n\t\tLa palabra se repite %d vez / veces en el documento ingresado\n", repeticiones);
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
            printf("P: %s |F:  %d |ID:  %d", res.palabra, res.frecuencia, res.idDoc);
            printf("\t\t");
            system("pause");
            system("cls");
            break;
        case 6:
            do
            {
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
    } while (repeticionMenu); // Si se agregan opciones al menuMain, se aumentan los paramentros

    return 0;
}
