#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

tokenArray initTokenArray(){
    tokenArray t;
    t.length=0;
    t.list=malloc(sizeof(token));
    return t;
}

void printToken(token x){
    printf("[%s:%s]",x.type,x.value);
}

void assignToken(token*x,char*type,char*value){
    x->type=type;
    x->value=value;
}

void appendToken(tokenArray*array,char*type,char*value){
    assignToken(array->list+array->length,type,value);
    array->list=realloc(array->list,sizeof(token)*(array->length+2));
    array->length+=1;
}

void appendChar(char*word,char c){
    word=realloc(word,sizeof(char)*(strlen(word)+2));
    word[strlen(word)+1]='\0';
    word[strlen(word)]=c;
}
void resetString(char*word){
    word=realloc(word,sizeof(char)*2);
    word[0]='\0';
    word[1]='\0';
}

char*stringCopy(char*origen){
    char*destino=malloc(sizeof(char)*(strlen(origen)+1));
    int i=0;
    while(origen[i]!='\0'){
        destino[i]=origen[i];//appendChar(destino,origen[i]);
        i+=1;
    }
    destino[i]='\0';
    return destino;
}