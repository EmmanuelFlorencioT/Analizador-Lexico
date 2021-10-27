/*
    Analizador Léxico
    Nombre: Emmanuel Florencio Trujillo.
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
int comparaCaracter(char car, LST cab);
int comparaCadena(char *cad, LST cab);
int comparaNum(char *num, LST lstNum);
void compruebaClasif(char *cad, TOKENS t);
void analisisLexico(char input[], TOKENS t);

void recorre(LST cab){
    while(cab){
        printf("Nombre del token: %s\n", cab->nomToken);
        cab=cab->liga;
    }
}

/*FUNCION AUXILIAR PARA LA PRUEBA DE LA FUNCION*/


/*      Ahora probando:
    int comparaCadena(char *cad, TOKENS t);   */
int main(){
    TOKENS tok;
    char ejemplo[40], token[40];
    /*VARIABLES AUXILIARES PARA LA PRUEBA DE LA FUNCION*/
    int res;
    char actual;

    iniTokens(&tok);
    setTokens(&tok);
    /* recorre(tok.palabraReser);
    recorre(tok.simbolos);
    recorre(tok.simbolosIgnorados);
    recorre(tok.numeros); */
    dameCad(ejemplo);
    printf("%s", ejemplo);
    analisisLexico(ejemplo, tok);

    /* strcpy(ejemplo, "9");
    strcpy(token, ejemplo);
    res=comparaCadena(token, tok.palabraReser);
    printf("El res de comparaCadena: %d", res);
    compruebaClasif(token, tok); */
}


/*Para guardar el input en una variable*/
void dameCad(char instruc[]){
    printf("Cadena a analizar: ");
    gets(instruc);
}

/*Inicializamos las listas para guardar nuestras clasifiaciones de tokens*/
void iniLista(LST *cab){
    *cab=NULL;
}

void iniTokens(TOKENS *t){
    iniLista(&t->palabraReser);
    iniLista(&t->simbolos);
    iniLista(&t->simbolosIgnorados);
    iniLista(&t->numeros);
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

/*Establecemos las palabras reservadas*/
void setPalRes(LST *pRes){
    insIni(pRes, "int");
    insIni(pRes, "float");
    insIni(pRes, "void");
    insIni(pRes, "if");
    insIni(pRes, "while");
    insIni(pRes, "for");
}

/*Establecemos los simbolos*/
void setSimbol(LST *smb){
    insIni(smb, "(");
    insIni(smb, ")");
    insIni(smb, ",");
    insIni(smb, "+");
    insIni(smb, "-");
    insIni(smb, ";");
    insIni(smb, "=");
    insIni(smb, "&");
    insIni(smb, "==");
    insIni(smb, ">=");
    insIni(smb, "<=");
    insIni(smb, "&&");
    insIni(smb, "||");
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

int comparaCaracter(char car, LST cab){ /*Funciona Correctamente*/
    int res=1;

    while(cab){
        if(car==cab->nomToken[0]){
            res=0;
            break;
        }
        else
            cab=cab->liga;
    }

    return(res);
    /*Retornamos un 0 si hubo coincidencia y un 1 si NO hubo coincidencia*/
}

/*NECESITAMOS otra función que compare las palabras*/
int comparaCadena(char *cad, LST cab){ /*Funciona Correctamente*/
    int res=1;

    while(cab){
        res=strcmp(cad, cab->nomToken);
        if(res==0)
            break;
        else
            cab=cab->liga;
    }

    return(res);
    /*Retornamos un 0 si hubo coincidencia*/
}

void compruebaClasif(char *cad, TOKENS t){ /*Funciona Correctamente*/
    if(comparaCadena(cad, t.palabraReser)==0)
        printf("\tPalabra reservada\n");
    else
        if(comparaNum(cad, t.numeros)==0)
            printf("\tNumero\n");
        else
            if(comparaNum(cad, t.numeros)==-1)
                printf("\tNo valido\n");
            else
                printf("\tIdentificador\n");
}

int comparaNum(char *num, LST lstNum){ /*Funciona Correctamente*/
    int len, i, res;

    len=strlen(num);
    for(i=0;i<len;i++){
        res=comparaCaracter(num[i], lstNum);
        if(res)
            break;
    }
    if(res && comparaCaracter(num[0], lstNum)==0)
        res=-1;

    return(res);
    /*Retorna 0 si es un numero*/
    /*Retorna 1 si no es un numero*/
    /*Retorna -1 si es una cadena que comienza con numero pero no es un numero*/
}

void concatena(char *cad, char caract){
    int len;
    len=strlen(cad);
    cad[len]=caract;
    cad[len+1]='\0'; /*Terminador de cadena*/
}

void analisisLexico(char input[], TOKENS t){
    char actual, token[30];
    int cadLon, i=0; /*La 'i' será para ubicarse dentro de la cadena input*/

    strcpy(token, "");
    actual=input[i];
    cadLon=strlen(input);
    for(i;i<cadLon;i++){
        actual=input[i];
        if(comparaCaracter(actual, t.simbolosIgnorados)!=0 && comparaCaracter(actual, t.simbolos)!=0){
            concatena(token, actual);
            printf("Token al momento: %s\n", token);
        }
        else
            if(comparaCaracter(actual, t.simbolosIgnorados)==0){
                
            }
    }
}