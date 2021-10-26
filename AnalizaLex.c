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
int comparaCaracter(char *cad, LST cab);
void compruebaClasif(char *cad, TOKENS t);
void analisisLexico(char input[], TOKENS t);

int main(){
    TOKENS tok;
    char ejemplo[40];

    iniTokens(&tok);
    setTokens(&tok);
    dameCad(ejemplo);
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
    iniLista(t->palabraReser);
    iniLista(t->simbolos);
    iniLista(t->simbolosIgnorados);
    iniLista(t->numeros);
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

int comparaCaracter(char *cad, LST cab){
    int res=1;

    while(cab){
        res=strcmp(cad, cab->nomToken);
        if(res==0)
            break;
        else
            cab=cab->liga;
    }

    return(res);
    /*Retornamos un 0 si hubo coincidencia y un 1 si NO hubo coincidencia*/
}

void compruebaClasif(char *cad, TOKENS t){
    if(comparaCaracter(cad, t.palabraReser)==0)
        printf("\tPalabra reservada\n");
    else
        if(comparaCaracter(cad[0], t.numeros)==0)
            printf("\tNumero\n");
        else
            printf("\tIdentificador\n");
}

void analisisLexico(char input[], TOKENS t){
    char actual, token[30];
    int cadLon, i=0; /*La 'i' será para ubicarse dentro de la cadena input*/
    int cont=0; /*El contador para sabe cuantos espacios avencé por el token*/

    strcpy(token, "");
    cadLon=strlen(input);
    while(i<cadLon){
        actual=input[i];
        i++;
        cont++;
        if(comparaCaracter(actual, t.simbolosIgnorados)!=0 && comparaCaracter(actual, t.simbolos)!=0){
            strcat(token, actual);
        }
        else
            if(comparaCaracter(actual, t.simbolosIgnorados)==0){
                if(strcmp(token, "")!=0){
                    printf("%s", token);
                    compruebaClasif(token, t);
                }
                strcpy(token, "");
            }
            else
                if(comparaCaracter(actual, t.simbolos)==0){
                    if(strcmp(token, "")!=0){
                        printf("%s", token);
                        compruebaClasif(token, t);
                    }
                    /*Aquí debería revisar si se trata de un símbolo o de dos*/
                    if(comparaCaracter(input[i], t.simbolos)==0){ /*Para ese momento a 'i' ya se le sumó 1*/
                        strcpy(token, actual);
                        strcat(token, input[i]);
                        if(comparaCaracter(token, t.simbolos)==0)
                            printf("%s\tSimbolo\n", token);
                        else
                            printf("%s\tCombinacion invalida\n", token);
                    }
                    else
                        printf("%c\tSimbolo\n", actual);
                    strcpy(token, "");
                }
    }
}