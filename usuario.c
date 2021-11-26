#include "usuario.h"

// Punto 1

int busquedaEnAlgunDoc(nodoA *a, char palabra[], int IdDoc) {
    if (a != NULL) {
        if (strcmpi(a->palabra, palabra) == 0) {
            int rep = repeticiones(a->ocurrencias, IdDoc);
            return rep;
        } else if (strcmpi(a->palabra, palabra) < 0)
            return busquedaEnAlgunDoc(a->der, palabra, IdDoc);
        else
            return busquedaEnAlgunDoc(a->izq, palabra, IdDoc);
    } else {
        return -1;  // Si la palabra no existe
    }
}

int repeticiones(nodoT *terminos, int id) {
    int i = 0;
    while (terminos != NULL) {
        if (terminos->idDOC == id) {
            i++;
        }
        terminos = terminos->sig;
    }
    return i;
}

// Punto 2

int repiticionesTotales(nodoA *a, char palabra[]) {
    if (a != NULL) {
        if (strcmpi(a->palabra, palabra) == 0) {
            posAndId(a->ocurrencias);
            return a->frecuencia;
        } else if (strcmpi(a->palabra, palabra) < 0)
            return repiticionesTotales(a->der, palabra);
        else
            return repiticionesTotales(a->izq, palabra);
    } else {
        return -1;  // Si la palabra no existe
    }
}
void posAndId(nodoT *a) {
    printf("\t\t- Posicion/es y Documento/s de la palabra buscada-\n");
    while (a != NULL) {
        printf("\t\t-----------------\n");
        printf("\t\tPosicion %d \n", a->pos);
        printf("\t\tDocumento %d \n", a->idDOC);
        printf("\t\t-----------------\n");
        a = a->sig;
    }
}

// Punto 3

void variosTerminos(nodoA *a) {
    int id = preguntarId(a);
    char s;
    char termino[30];
    int repeticiones = 0;
    do {
        printf("\n\n\t\tIngrese palabra a buscar en el documento %d\n", id);
        printf("\t\t->");
        fflush(stdin);
        gets(termino);
        repeticiones = busquedaEnAlgunDoc(a, termino, id);
        if (repeticiones == -1) {
            printf("\n\n\t\tLa palabra no existe en el documento\n");
        } else {
            printf("\n\n\t\tLa palabra %s se repite %d vez / veces en el documento %d\n", termino, repeticiones, id);
        }
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

// Punto 5
void palabraMayorFrecuencia(nodoA *a, int idDoc, PalabraFrecuente *res) {
    res->idDoc = idDoc;
    char *aux = (char *)calloc(sizeof(char), 21);
    if (a != NULL) {
        palabraMayorFrecuencia(a->izq, idDoc, res);
        palabraMayorFrecuencia(a->der, idDoc, res);
        strcpy(aux, a->palabra);
        if (compararOcurrencias(a->ocurrencias, res)) {
            strcpy(res->palabra, aux);
        }
    }
    free(aux);
}

/*
    Retorna 1 si la palabra es mas frecuente que la del valor del parametro, además modifica la estructura.
    Retorna 0 si la palabra es menos frecuente que la del valor del parametro. No se ve alterada la estructura.
*/
int compararOcurrencias(nodoT *ocurrencia, PalabraFrecuente *res) {
    int contadorAuxiliar = 0;
    while (ocurrencia != NULL) {
        if (ocurrencia->idDOC == res->idDoc) {
            contadorAuxiliar++;
        }
        ocurrencia = ocurrencia->sig;
    }
    if (res->frecuencia < contadorAuxiliar) {
        res->frecuencia = contadorAuxiliar;
        return 1;
    }
    return 0;
}

// punto 6
// Recibe arbol, palabra e id, si la id es -1 no filtra levenshtein por id del doc
void distanciaLevenshtein(nodoA *a, char palabra[], int id) {
    if (a != NULL) {
        if (!existeTermino(a, palabra)) {
            printf("\n\n\t\tQuisite decir\n");
            distancia(a, palabra, id);
        }
    }
}
// Verifica si una palabra existe en algun documento, recibe la palabra, el arbol y la id del documento.
int existePalabraDocumento(nodoA *a, char palabra[], int id) {
    if (a != NULL) {
        if (id != -1) {
            if (strcmpi(a->palabra, palabra) == 0) {
                return verificarIdEnLista(a->ocurrencias, id);
            }
            if (strcmpi(a->palabra, palabra) > 0) {
                return existePalabraDocumento(a->izq, palabra, id);
            } else {
                return existePalabraDocumento(a->der, palabra, id);
            }
        } else {
            return -1;
        }
    }
}

int existeTermino(nodoA *a, char palabra[]) {
    if (a != NULL) {
        if (strcmpi(a->palabra, palabra) == 0) {
            return 1;
        } else {
            if (strcmpi(a->palabra, palabra) > 0) {
                return existeTermino(a->izq, palabra);
            } else {
                return existeTermino(a->der, palabra);
            }
        }
    } else {
        return 0;
    }
}
// Recibe id del doc, si la id es -1 no filtra levenshtein por documento
void distancia(nodoA *a, char palabra[], int id) {
    if (a != NULL) {
        int distanciaLev = Levenshtein(a->palabra, palabra);
        if (id != -1) {
            if (distanciaLev <= 3 && existePalabraDocumento(a, a->palabra, id)) {
                printf("\t\t-> %s \n", a->palabra);
            }
        } else {
            if (distanciaLev <= 3) {
                printf("\t\t-> %s \n", a->palabra);
            }
        }
        distancia(a->izq, palabra, id);
        distancia(a->der, palabra, id);
    }
}
// Extras
/*
    Recibe el arbol y una id, si la id es -1 hara que levenshtein no filtre por misma id doc
    Si recibe una id distinta a -1, o sea se pasa una id valida de doc, hara que haga sugerencias >= a 3 con palabras del mismo documento
*/
char *preguntarPalabra(nodoA *a, int id) {
    char *palabra = (char *)calloc(sizeof(char), 20);
    do {
        printf("\n\n\t\tIngrese palabra a buscar\n");
        fflush(stdin);
        printf("\t\t->");
        gets(palabra);
        tolower(palabra[0]);
        if (!existeTermino(a, palabra)) {
            distanciaLevenshtein(a, palabra, id);
        }
    } while (!existeTermino(a, palabra));
    return palabra;
}
int preguntarId(nodoA *a) {
    int scanValido;
    int i = 0;
    do {
        printf("\n\n\t\tIngrese documento\n");
        printf("\t\t->");
        fflush(stdin);
        if (!scanf("%d", &i) || (i > MAX_TXT || i < 1) || verificarIdIngresado(a, i) != 1) {
            i = 0;  // forzamos la entrada al dowhile
            printf("\t\tIngrese un ID de documento valido\n");
            printf("\t\t");
            system("pause");
        }
        system("cls");
    } while (i > MAX_TXT || i < 1);
    return i;
}
int verificarIdIngresado(nodoA *a, int id) {
    if (a != NULL) {
        return verificarIdEnLista(a->ocurrencias, id) ? 1 : verificarIdIngresado(a->izq, id) || verificarIdIngresado(a->der, id);
    } else {
        return 0;
    }
}

int verificarIdEnLista(nodoT *lista, int id) {
    while (lista != NULL) {
        if (lista->idDOC == id) {
            return 1;
        }
        lista = lista->sig;
    }
    return 0;
}
int lanzadorDeVisualizacion(nodoA *a, int op) {
    if (op <= 0 || op > 4) op = verficadorDeOpcion(op);

    switch (op) {
        case 1:
            preorder(a);
            printf("\t\t");
            system("pause");
            system("cls");
            return 0;
            break;
        case 2:
            inorder(a);
            printf("\t\t");
            system("pause");
            system("cls");
            return 0;
            break;
        case 3:
            postorder(a);
            printf("\t\t");
            system("pause");
            system("cls");
            return 0;
        case 4:
            return 1;
        default:
            break;
    }
}
int verficadorDeOpcion(int op) {
    do {
        system("cls");
        printf("\n\n\t\tOpcion incorrecta, ingrese nuevamente\n");
        menuVisualizacionArbol();
        printf("\t\t->");
        scanf("%d", &op);
        system("cls");
    } while (op <= 0 || op > 4);
    return op;
}

/// Funcion de consulta, si desea seguir utilizando el archivo ya crea o

int consulta() {
    char s;
    printf("\n\n\t\t--------------------------\n");
    printf("\t\tDesea utilizar el Diccionario actual ?[S / N]\n");
    printf("\t\t--------------------------\n");
    printf("\t\t->");
    fflush(stdin);
    scanf("%c", &s);
    s = tolower(s);
    system("cls");
    switch (s) {
        case 's':
            return 1;
            break;
        case 'n':
            return 0;
            break;
        default:
            printf("\n\n\t\tOpcion invalida\n");
            return consulta();
            break;
    }
}

// PUNTO 4
// Separa en una matriz de strings una frase
int tokenizarFrase(char frase[256], char matriz[][20]) {
    char *token = strtok(frase, "{}[]<> ,.:;/()");
    int validos = 0;
    while (token != 0) {
        strcpy(matriz[validos++], token);
        token = strtok(NULL, "{}[]<> ,.:;/()");
    }
    return validos;
}

void buscarFrase(nodoA *a, char frase[256]) {
    int res;
    char matriz[50][20];
    int posiciones[50];
    int validosFrase = 0;
    validosFrase = tokenizarFrase(frase, matriz);

    if (validosFrase <= 1) {
        printf("\n-> Ingrese mas de una palabra\n\n");
    } else {
        for (int i = 1; i < idMaximo() + 1; i++) {
            res = validarFrase(a, matriz, posiciones, i, validosFrase);
            if (res) {
                return;
            }
        }
        printf("La frase no existe\n");
    }
}

int validarFrase(nodoA *a, char matriz[][20], int posiciones[], int id, int validosFrase) {
    int arrayValidospos = 0;
    arrayValidospos = obtenerValidos(a, matriz[0], posiciones, id);
    for (int i = 0; i < arrayValidospos; i++) {
        if (compararCoincidencia(a, matriz, posiciones, id, validosFrase, i)) {
            printf("\nFrase encontrada en el documento con id %d\n", id);
            return 1;
        }
    }
    return 0;
}

int obtenerValidos(nodoA *a, char palabra[20], int posiciones[], int id) {
    int posicionesValidas = 0;
    if (a) {
        if (strcmpi(palabra, a->palabra) == 0) {
            posicionesValidas = cargarPosiciones(a->ocurrencias, posiciones, id);
        } else {
            return (strcmpi(a->palabra, palabra) > 0) ? obtenerValidos(a->izq, palabra, posiciones, id) : obtenerValidos(a->der, palabra, posiciones, id);
        }
    }
    return posicionesValidas;
}

// carga arreglo de posiciones de la palabra
int cargarPosiciones(nodoT *ocurrencias, int posiciones[], int id) {
    nodoT *aux;
    aux = ocurrencias;
    int validos = 0;

    while (aux != NULL) {
        if (aux->idDOC == id) {
            posiciones[validos] = ocurrencias->pos;
            validos++;
        }
        aux = aux->sig;
    }
    return validos;
}

// Retorna 1 si encuentra los terminos
int compararCoincidencia(nodoA *a, char matriz[][20], int posiciones[], int id, int validosFrase, int posicionValida) {
    int res = 1;
    int j = 1;
    int aux = posiciones[posicionValida] + 1;

    while (j < validosFrase && res == 1) {
        res = terminoEncontrado(a, matriz[j++], id, aux++);
    }
    return res;
}

int terminoEncontrado(nodoA *a, char palabra[20], int id, int posicionesValidas) {
    int flag = 0;
    if (a) {
        if (strcmpi(palabra, a->palabra) == 0 && (a->ocurrencias->idDOC == id)) {
            flag = validarPosicion(a->ocurrencias, a->palabra, id, a->ocurrencias->pos);
        } else {
            if (strcmpi(a->palabra, palabra) > 0) {
                return terminoEncontrado(a->izq, palabra, id, posicionesValidas);
            } else {
                return terminoEncontrado(a->der, palabra, id, posicionesValidas);
            }
        }
    } else {
        flag = 0;
    }
    return flag;
}

int validarPosicion(nodoT *ocurrencias, char palabra[20], int id, int posiciones) {
    while (ocurrencias != NULL) {
        if (ocurrencias->idDOC == id) {
            if (posiciones == ocurrencias->pos) {
                return 1;
            }
        }
        ocurrencias = ocurrencias->sig;
    }
    return 0;
}

// Retorna el idMaximo encontrado de los terminos cargados
int idMaximo() {
    FILE *buffer = fopen(FILE_PALABRAS, "rb");
    termino t;
    int id;
    int flag = 1;
    while (fread(&t, sizeof(termino), 1, buffer) > 0) {
        if (flag) {
            id = t.idDOC;
            flag = 0;
        }
        if (id < t.idDOC) {
            id = t.idDOC;
        }
    }
    fclose(buffer);
    return id;
}
