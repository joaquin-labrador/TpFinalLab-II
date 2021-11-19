#include "main.h"

int main() {
    leerTexto(1);
    return 0;
}

nodoT crearNodoT(int pos, int idDoc) {
    nodoT *nuevo = (nodoT *)malloc(sizeof(nodoT));
    nuevo->idDOC = idDoc;
    nuevo->pos = pos;
    nuevo->sig = NULL;
}

nodoA crearNodoA(char palabra[], int frecuencia) {
    nodoA *nuevo = (nodoA *)malloc(sizeof(nodoA));
    nuevo->frecuencia = frecuencia;
    strcpy(nuevo->palabra, palabra);
    nuevo->ocurrencias = NULL;
    nuevo->der = NULL;
    nuevo->izq = NULL;
}

termino crearTermino(char palabra[], int idDoc, int pos) {
    termino m;
    m.idDOC = idDoc;
    strcpy(m.palabra, palabra);
    m.pos = pos;
    return m;
}

void escribirTermino(char palabra[], int idDoc, int pos) {
    FILE *buff = fopen(FILE_PALABRAS, "ab");
    termino t = crearTermino(palabra, idDoc, pos);
    // printf("BONDIOLA CASERA: %s -- %d\n", t.palabra, t.pos);
    fwrite(&t, sizeof(termino), 1, buff);
    fclose(buff);
}

void leerTexto(int id) {
    int i = 0;
    char *idDoc = convertirAChar(id);
    FILE *buffer = fopen(idDoc, "rb");

    free(idDoc);  // xDDDDD

    fseek(buffer, 0, SEEK_END);
    int cantLetras = ftell(buffer) / sizeof(char);
    fseek(buffer, 0, SEEK_SET);
    char *texto = (char *)calloc(sizeof(char), cantLetras);
    strcpy(texto, " ");
    if (buffer != NULL) {
        while (fread(&texto[i], sizeof(char), 1, buffer) > 0) {
            i++;
        }
        separarChar(texto, id, cantLetras);
    }
}

void separarChar(char palabra[], int id, int cantLetras) {
    printf("%s | %d\n", palabra, strlen(palabra));
    char *aux = (char *)calloc(sizeof(char), 20);
    int contador = 0;
    int pos = 0;
    int flag = 0;

    for (int i = 0; i < cantLetras; i++) {
        if (esCaracterValido(palabra[i])) {
            aux[contador++] = tolower(palabra[i]);
            flag = 1;       // pq es valido
        } else if (flag) {  // Si lee dos caracteres invalidos seguidos no se entra
            aux[contador] = '\0';
            // escribirTermino(aux, id, pos);
            printf("%s-- %d\n", aux, contador);
            pos++;
            contador = 0;
            flag = 0;
        }
    }
    free(aux);
}

int esCaracterValido(char termino) {
    switch (termino) {
        case ',':
        case '.':
        case ':':
        case ';':
        case ' ':
        case '\0':
        case '/':
        case '(':
        case ')':
        case '{':
        case '}':
        case '[':
        case ']':
        case '<':
        case '>':
        case '\'':
        case '\n':
        case '\r':
        case '\"':
            return 0;
        default:
            return 1;
    }
}
char *convertirAChar(int id) {
    char texto[40];
    itoa(id, texto, 10);
    strcat(texto, ".txt\0");
    char *resultado = (char *)calloc(sizeof(char), 40);
    strcpy(resultado, texto);
    return resultado;
}
