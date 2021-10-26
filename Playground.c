/*
Voy a tener que definir algunas listas con las cuales se compararán
los tokens que tenga la instrucción que quiero analizar.
--->Lista de palabras reservadas
--->Lista de símbolos
--->Lista de numeros
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct nodo{
    char nomToken[10];
    struct nodo *liga;
} *LST;

void iniLista();
int creaNodo(LST *nvo, char *cadena);
void insIni(LST *cab, char *cadena);
void setPalRes(LST *pRes);
void recorre(LST cab);

int main(){
    LST palRsv;
    char actual, test[10];
    int res;

/*
    iniLista(&palRsv);
    setPalRes(&palRsv);
    recorre(palRsv);
*/
/*
    strcpy(test,"Hola");
    actual=test[0];
    printf("El caracter fue: %c", actual);
*/
/*
    res=strcmp("a", "alonso");
    printf("La respuesta es= %d", res);
*/

    strcpy(test, "");
    strcat(test, " ");
    //strcat(test, "o");
    //strcat(test, "l");
    //strcat(test, "a");
    res=strcmp(test, " ");
    printf("La respuesta es= %d", res); /*res fue igual a 0*/
}

void iniLista(LST *cab){
    *cab=NULL;
}

/*Necesitamos añadir las palabras reservadas, simbolos, etc. en nodos*/
int creaNodo(LST *nvo, char *cadena){
    int res=0;

    *nvo=(LST)malloc(sizeof(struct nodo));
    if(*nvo){
        strcpy((*nvo)->nomToken, cadena);
        (*nvo)->liga=NULL;
        res=1;
    }
    return(res);
}

/*Necesitamos una manera para insertar los nodos*/
void insIni(LST *cab, char *cadena){
    int res;
    LST auxNvo;

    res=creaNodo(&auxNvo, cadena);
    if(res){
        auxNvo->liga=*cab;
        *cab=auxNvo;
    }
}

/*Vamos a establecer las palabras reservadas*/
void setPalRes(LST *pRes){
    insIni(pRes, "int");
    insIni(pRes, "float");
    insIni(pRes, "void");
    insIni(pRes, "if");
    insIni(pRes, "while");
    insIni(pRes, "for");
}

void recorre(LST cab){
    while(cab){
        printf("%s\n", cab->nomToken);
        cab=cab->liga;
    }
}
