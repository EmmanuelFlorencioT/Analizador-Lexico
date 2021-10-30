#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    FILE *f;
    char input[1000];
    int t, i=0;
    
    f=fopen("input.txt", "r");
    fseek(f, 0, SEEK_END);
    t=ftell(f);

    fseek(f,0,SEEK_SET);

    while(!feof(f)){
        fscanf(f, "%c", &input[i]);
        i++;
    }
    input[i-1]='\0';

    printf("%s", input);
}

