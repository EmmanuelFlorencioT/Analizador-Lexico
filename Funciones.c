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
//void compruebaClasif(char *cad, TOKENS t);
//void analisisLexico(char input[], TOKENS t);

void recorre(LST cab){
    while(cab){
        printf("Nombre del token: %s\n", cab->nomToken);
        cab=cab->liga;
    }
}

/*FUNCION AUXILIAR PARA LA PRUEBA DE LA FUNCION*/
void func(char input[], TOKENS t){
    int res;
    char actual;

    actual=input[0];
    res=comparaCaracter(actual, t.simbolos);
    printf("Resu de comparaCaracter: %d", res);
    printf("Caracter actual: %c", actual);
}

/*      Ahora probando:
    int comparaCaracter(char *cadn TOKENS t);   */
int main(){
    TOKENS tok;
    char ejemplo[40];
    /*VARIABLES AUXILIARES PARA LA PRUEBA DE LA FUNCION*/
    int res;
    char actual;

    iniTokens(&tok);
    setTokens(&tok);
    /* recorre(tok.palabraReser);
    recorre(tok.simbolos);
    recorre(tok.simbolosIgnorados);
    recorre(tok.numeros);
    dameCad(ejemplo);
    analisisLexico(ejemplo, tok); */

    strcpy(ejemplo, ",Hola)");
    actual=ejemplo[0];
    res=comparaCaracter(actual, tok.simbolos);
    printf("Resultado: %d\n", res);
    printf("Caracter: %c\n", actual);
    printf("----------------------------\n");
    func(ejemplo, tok);
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
