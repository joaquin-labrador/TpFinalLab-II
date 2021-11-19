#include "main.h"
int main(){
    
    return 0;
}
nodoT crearNodoT (int pos,int idDoc){
    nodoT *nuevo = (nodoT*)malloc(sizeof(nodoT));
    nuevo->idDOC = idDoc;
    nuevo->pos = pos;
    nuevo->sig = NULL;
}
nodoA crearNodoA (char palabra[],int frecuencia){
    nodoA *nuevo = (nodoA*)malloc(sizeof(nodoA));
    nuevo->frecuencia = frecuencia;
    strcpy(nuevo->palabra,palabra);
    nuevo->ocurrencias = NULL;
    nuevo->der= NULL;
    nuevo->izq = NULL;
}
termino crearTermino (char palabra[],int idDoc, int pos){
    termino m;
    m.idDOC = idDoc;
    strcpy(m.palabra,palabra),
    m.pos = pos;
    return m;
}
void crearDocumentoDePalabras(){
    FILE *buffer = fopen(FILE_PALABRAS, "ab");
    srand(time(NULL));
    int id;
    int pos = 0;
    char palabra[20];
    char s = 's';
    do{
        do{
            id = rand()% 1000 + 1;
        }while(verificarID(id) == 0);
        do{
            printf("Ingrese una palabra\n");
            fflush(stdin);
            gets(palabra);
        }while(verificadorP(palabra) == 0);
        pos = pos++;
        termino s = crearTermino(palabra,id,pos);
        fwrite(&s,sizeof(termino),1,buffer);
        printf("Continuar : ");
        fflush(stdin);
        scanf("%d",&s);
        system("cls");
    }while(s == 's');

}
int verificarID(int id){
    FILE *buffer = fopen(FILE_PALABRAS,"rb");
    termino s;
    if(buffer != NULL){
        while(fread(&s,sizeof(termino),1,buffer)>0){
            if(s.idDOC == id){
                return 0;
            }
        }
        return 1;
        fclose(buffer);
    }
}
int verificadorP(char palabra[]){
       FILE *buffer = fopen(FILE_PALABRAS,"rb");
    termino s;
    if(buffer != NULL){
        while(fread(&s,sizeof(termino),1,buffer)>0){
            if(stricmp(palabra,s.palabra)==0){
                return 0;
            }
        }
        return 1;
        fclose(buffer);
    }
}