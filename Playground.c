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

typedef struct{
    LST palabraReser;
    LST simbolos;
    LST simbolosIgnorados;
    LST numeros;
} TOKENS;

void dameCad(char instruc[]);
void iniLista(LST *cab);
void iniTokens(TOKENS *t);
int creaNodo(LST *nvo, char *cadena);
void insIni(LST *cab, char *cadena);
void setPalRes(LST *pRes);
void setSimbol(LST *smb);
void setNums(LST *num);
void setSimbolIgnorar(LST *ignora);
void setTokens(TOKENS *t);
int comparaCaracter(char *a, LST cab);
void analisisLexico(char input[], TOKENS t);

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

    dameCad(test);
    printf("\n%s", test);
}

void dameCad(char instruc[]){
    printf("Cadena a analizar: ");
    gets(instruc);
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
 /*
void recorre(LST cab){
    while(cab){
        printf("%s\n", cab->nomToken);
        cab=cab->liga;
    }
}
*/

/*Establecemos los simbolos*/
void setSimbol(LST *smb){
    insIni(smb, "(");
    insIni(smb, ")");
    insIni(smb, ",");
    insIni(smb, "+");
    insIni(smb, "-");
    insIni(smb, ";");
    insIni(smb, "=");
}

/*Establecemos los numeros*/
void setNums(LST *num){
    insIni(num, "0");
    insIni(num, "1");
    insIni(num, "2");
    insIni(num, "3");
    insIni(num, "4");
    insIni(num, "5");
    insIni(num, "6");
    insIni(num, "7");
    insIni(num, "8");
    insIni(num, "9");
}

/*Establecemos los simbolos a ignorar*/
void setSimbolIgnorar(LST *ignora){
    insIni(ignora, " ");
    insIni(ignora, "\n");
    insIni(ignora, "\t");
}

void setTokens(TOKENS *t){
    setPalRes(&t->palabraReser);
    setSimbol(&t->simbolos);
    setSimbolIgnorar(&t->simbolosIgnorados);
    setNums(&t->numeros);
}

int comparaCaracter(char *a, LST cab){ /*Esta funcion si compila*/
    int res=1;

    while(cab){
        res=strcmp(a, cab->nomToken);
        if(res==0)
            break;
        else
            cab=cab->liga;
    }

    return(res);
    /*Retornamos un 0 si hubo coincidencia y un 1 si NO hubo coincidencia*/
}