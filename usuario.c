#include "usuario.h"

//Punto 1

int busquedaEnAlgunDoc(nodoA *a, char palabra[], int IdDoc)
{
    if (a != NULL)
    {
        if (strcmpi(a->palabra, palabra) == 0)
        {
            int rep = repeticiones(a->ocurrencias, IdDoc);
            return rep;
        }
        else if (strcmpi(a->palabra, palabra) < 0)
            return busquedaEnAlgunDoc(a->der, palabra, IdDoc);
        else
            return busquedaEnAlgunDoc(a->izq, palabra, IdDoc);
    }
    else
    {
        return -1; // Si la palabra no existe
    }
}

int repeticiones(nodoT *terminos, int id)
{
    int i = 0;
    while (terminos != NULL)
    {
        if (terminos->idDOC == id)
        {
            i++;
        }
        terminos = terminos->sig;
    }
    return i;
}

//Punto 2

int repiticionesTotales(nodoA *a, char palabra[])
{
    if (a != NULL)
    {
        if (strcmpi(a->palabra, palabra) == 0)
        {
            posAndId(a->ocurrencias);
            return a->frecuencia;
        }
        else if (strcmpi(a->palabra, palabra) < 0)
            return repiticionesTotales(a->der, palabra);
        else
            return repiticionesTotales(a->izq, palabra);
    }
    else
    {
        return -1; // Si la palabra no existe
    }
}
void posAndId(nodoT *a)
{
    printf("\t\t- Posicion/es y Documento/s de la palabra buscada-\n");
    while (a != NULL)
    {
        printf("-----------------\n");
        printf("\n\n\t\tPosicion %d \n", a->pos);
        printf("\n\n\t\tDocumento %d \n", a->idDOC);
        printf("-----------------\n");
        a = a->sig;
    }
}

//Punto 3

void variosTerminos(nodoA *a)
{
    int id = preguntarId();
    char s;
    char termino[30];
    int repeticiones = 0;
    do
    {
        printf("\n\n\t\tIngrese palabra a buscar en el documento %d\n", id);
        printf("\t\t->");
        fflush(stdin);
        gets(termino);
        repeticiones = busquedaEnAlgunDoc(a, termino, id);
        printf("\n\n\t\tLa palabra %s se repite %d vez / veces en el documento %d\n", termino, repeticiones, id);
        system("pause");
        system("cls");
        printf("\n\n\t\tDesea continuar buscando terminos en este documento\n");
        fflush(stdin);
        printf("\t\t->");
        scanf("%c", &s);
        towlower(s);
        system("cls");
    } while (s == 's');
}
//Punto 5

//punto 6
void distanciaLevenshtein(nodoA *a, char palabra[])
{
    if (a != NULL)
    {
        if (!existeTermino(a, palabra)){
            printf("\n\n\t\tQuisite decir\n");
            distancia(a, palabra);
        }
    }
}
int existeTermino(nodoA *a, char palabra[])
{
    if (a != NULL)
    {
        if (strcmpi(a->palabra, palabra) == 0)
        {
            return 1;
        }
        else
        {
            if (strcmpi(a->palabra, palabra) > 0)
            {
                return existeTermino(a->izq, palabra);
            }
            else
            {
                return existeTermino(a->der, palabra);
            }
        }
    }
    else
    {
        return 0;
    }
}
void distancia(nodoA *a, char palabra[])
{
    if (a != NULL)
    {
        int distanciaLev = Levenshtein(a->palabra, palabra);
        if (distanciaLev <= 3)
        {
            printf("\t\t-> %s \n", a->palabra);
        }
        distancia(a->izq, palabra);
        distancia(a->der, palabra);
    }
}

//Extras
char *preguntarPalabra(nodoA *a)
{
    char *palabra = (char *)calloc(sizeof(char), 20);
    do
    {
        
        printf("\n\n\t\tIngrese palabra a buscar\n");
        fflush(stdin);
        printf("\t\t->");
        gets(palabra);
        tolower(palabra[0]);
        if (!existeTermino(a, palabra))
        {
        
            distanciaLevenshtein(a,palabra);       
        }
    } while (!existeTermino(a, palabra));
    return palabra;
}
int preguntarId()
{
    int i = 0;
    do
    {
        printf("\n\n\t\tIngrese documento\n");
        printf("\t\t->");
        scanf("%d", &i);
        system("cls");
    } while (i > MAX_TXT && i <= 0);
    return i;
}
