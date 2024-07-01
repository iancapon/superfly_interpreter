#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct token{
    char*type;
    char*value;
}token;

typedef struct tokenArray{
    token*list;
    int length;
}tokenArray;

void printToken(token x){
    printf("[%s:%s]",x.type,x.value);
}

void assignToken(token*x,char*type,char*value){
    x->type=type;
    x->value=value;
}

tokenArray initTokenArray(){
    tokenArray t;
    t.length=0;
    t.list=malloc(sizeof(token));
    return t;
}

void appendToken(tokenArray*array,char*type,char*value){
    assignToken(array->list+array->length,type,value);
    array->list=realloc(array->list,sizeof(token)*(array->length+2));
    array->length+=1;
}

int main(){
    tokenArray tokens=initTokenArray();
    appendToken(&tokens,"expr","y");
    appendToken(&tokens,"expr","z");
    for(int i=0; i< tokens.length;i++){
        printToken(tokens.list[i]);
    }
    return 0;
}