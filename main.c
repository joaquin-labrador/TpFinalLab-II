#include "main.h"
int main()
{
    leerTexto(1);
    return 0;
}
nodoT crearNodoT(int pos, int idDoc)
{
    nodoT *nuevo = (nodoT *)malloc(sizeof(nodoT));
    nuevo->idDOC = idDoc;
    nuevo->pos = pos;
    nuevo->sig = NULL;
}
nodoA crearNodoA(char palabra[], int frecuencia)
{
    nodoA *nuevo = (nodoA *)malloc(sizeof(nodoA));
    nuevo->frecuencia = frecuencia;
    strcpy(nuevo->palabra, palabra);
    nuevo->ocurrencias = NULL;
    nuevo->der = NULL;
    nuevo->izq = NULL;
}
termino crearTermino(char palabra[], int idDoc, int pos)
{
    termino m;
    m.idDOC = idDoc;
    strcpy(m.palabra, palabra);
    m.pos = pos;
    return m;
}
void escribirTermino(char palabra[], int idDoc, int pos)
{
    FILE *buff = fopen(FILE_PALABRAS, "ab");
    termino t = crearTermino(palabra, idDoc, pos);
    fread(&t, sizeof(termino), 1, buff);
    fclose(buff);
}

void leerTexto(int id)
{
    int i = 0;
    char *idDoc = convertirAChar(id);
    FILE *buffer = fopen(idDoc, "r");
    int peso = pesoArchivo(id);
    char *texto = (char *)calloc(sizeof(char) , peso);
    strcpy(texto, " ");
    if (buffer != NULL)
    {
        while(fread(&texto[i], sizeof(char) , 1, buffer) > 0){
            i++;   
        }
        separarChar(texto, id);     
    }
}
void separarChar(char palabra[], int id)
{
    printf("%s\n",palabra);

    char *aux = NULL;
    int contador = 0;
    int pos = 0;
    int flag = 0;
    for (int i = 0; i < pesoArchivo(id); i++)
    {
        if (aux != NULL)
        {
            if (esCaracterValido(palabra[i]))
            {
                aux[contador++] = palabra[i];
                flag = 1; //pq es valido
            }
            else if (flag)
            { //Si lee dos caracteres invalidos seguidos no se entra
                escribirTermino(aux, id, pos);
                printf("%s\n", aux);
                pos++;
                contador = 0;
                flag = 0;
                free(aux);
            }
        }
        else{
            aux = (char *)calloc(sizeof(char), 20);
            strcpy(aux, " ");
            i--;

        }
    }
}
int esCaracterValido(char termino)
{
    switch (termino)
    {
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
    case '\"':
        return 0;
    default:
        return 1;
        break;
    }
    return 0;
}
int pesoArchivo(int id)
{
    char *idDoc = convertirAChar(id);
    FILE *buffer = fopen(idDoc, "r");
    if (buffer != NULL)
    {
        fseek(buffer, 0, SEEK_END);
        int cant = ftell(buffer) / sizeof(char);
        fclose(buffer);
        return cant;
    }
}
char *convertirAChar(int id)
{
    char *texto = (char *)malloc(sizeof(char) * 20);
    sprintf(texto, "%d.txt", id);
    return texto;
}
