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
    word[strlen(word)]=c;
    word=realloc(word,sizeof(char)*(strlen(word)+2));
    word[strlen(word)]='\0';
}
void resetString(char*word){
    word=word=realloc(word,sizeof(char)*2);
    word[1]='\0';
}

char*stringCopy(char*origen){
    char*destino=malloc(sizeof(char)*2);
    destino[0]=origen[0];
    destino[1]='\0';
    int i=1;
    while(origen[i]!='\0'){
        appendChar(destino,origen[i]);
        i+=1;
    }
    return destino;
}