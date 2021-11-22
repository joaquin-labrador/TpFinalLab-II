#include "diccionario.h"
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
    fwrite(&t, sizeof(termino), 1, buff);
    fclose(buff);
}

void leerTexto(int id)
{
    int i = 0;
    char *idDoc = convertirAChar(id);
    FILE *buffer = fopen(idDoc, "rb");

    free(idDoc);

    fseek(buffer, 0, SEEK_END);
    int cantLetras = ftell(buffer) / sizeof(char);
    fseek(buffer, 0, SEEK_SET);
    char *texto = (char *)calloc(sizeof(char), cantLetras);
    strcpy(texto, " ");
    if (buffer != NULL)
    {
        while (fread(&texto[i], sizeof(char), 1, buffer) > 0)
        {
            i++;
        }
        separarChar(texto, id, cantLetras);
    }
}

void separarChar(char palabra[], int id, int cantLetras)
{
    char *aux = (char *)calloc(sizeof(char), 20);
    int contador = 0;
    int pos = 0;
    int flag = 0;

    for (int i = 0; i < cantLetras; i++)
    {
        if (esCaracterValido(palabra[i]))
        {
            aux[contador++] = tolower(palabra[i]);
            flag = 1; // pq es valido
        }
        else if (flag)
        { // Si lee dos caracteres invalidos seguidos no se entra
            aux[contador] = '\0';
            escribirTermino(aux, id, pos);
            printf("%s-- %d\n", aux, contador);
            pos++;
            contador = 0;
            flag = 0;
        }
    }
    free(aux);
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
    case '\n':
    case '\r':
    case '\"':
        return 0;
    default:
        return 1;
    }
}
char *convertirAChar(int id)
{
    char texto[40];
    itoa(id, texto, 10);
    strcat(texto, ".txt\0");
    char *resultado = (char *)calloc(sizeof(char), 40);
    strcpy(resultado, texto);
    return resultado;
}
void mostrarArchivoBIN()
{
    FILE *buffer = fopen(FILE_PALABRAS, "rb");
    termino t;
    while (fread(&t, sizeof(termino), 1, buffer))
    {
        mostradorTermino(t);
    }
    fclose(buffer);
}
void mostradorTermino(termino t)
{
    printf("--------------\n");
    printf("Palabra : %s\n", t.palabra);
    printf("IdDoc : %d \n", t.idDOC);
    printf("Posicion : %d\n", t.pos);
    printf("--------------\n");
}

int Levenshtein(char *s1, char *s2)
{
    int t1, t2, i, j, *m, costo, res, ancho;

    // Calcula tamanios strings
    t1 = strlen(s1);
    t2 = strlen(s2);

    // Verifica que exista algo que comparar
    if (t1 == 0)
        return (t2);
    if (t2 == 0)
        return (t1);
    ancho = t1 + 1;

    // Reserva matriz con malloc                     m[i,j] = m[j*ancho+i] !!
    m = (int *)malloc(sizeof(int) * (t1 + 1) * (t2 + 1));
    if (m == NULL)
        return (-1); // ERROR!!

    // Rellena primera fila y primera columna
    for (i = 0; i <= t1; i++)
        m[i] = i;
    for (j = 0; j <= t2; j++)
        m[j * ancho] = j;

    // Recorremos resto de la matriz llenando pesos
    for (i = 1; i <= t1; i++)
        for (j = 1; j <= t2; j++)
        {
            if (s1[i - 1] == s2[j - 1])
                costo = 0;
            else
                costo = 1;
            m[j * ancho + i] = min(min(m[j * ancho + i - 1] + 1,
                                        m[(j - 1) * ancho + i] + 1),
                                      m[(j - 1) * ancho + i - 1] + costo);
        }

    res = m[t2 * ancho + t1];
    free(m);
    return (res);
}