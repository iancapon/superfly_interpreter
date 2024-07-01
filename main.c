#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

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
int typeofC(char c){
    int ret=-1;//// INVALID CHARACTER
    if(strrchr("abcdefghijklmnñopqrstuvwxyz_ABCDEFGHIJKLMNÑOPQRSTUVWXYZ",c)){
        ret= 0;//"Letter";
    }
    if(strrchr(";\n",c)){
        ret= 1;//"Line";
    }
    if(strrchr(".0123456789",c)){
        ret= 2;//"Number";
    }
    if(strrchr("()",c)){
        ret= 3;//"Bracket";
    }
    if(strrchr("+-*/=",c)){
        ret= 4;//"InfixOperator";
    }
    if(strrchr(" ",c)){
        ret= 5;//"Space";
    }
    if(c=='"'){
        ret= 6;//"Double Commas";
    }
    return ret;
}
char*typeofT(char*value){
    char*ret;
    if(typeofC(value[0])==0){
        ret="Expr";
    }
    else if(typeofC(value[0])==1){
        ret="Line";
    }
    else if(typeofC(value[0])==2){
        ret="Number";
    }
    else if(typeofC(value[0])==3){
        ret="Bracket";
    }
    else if(typeofC(value[0])==4){
        ret="InfixOperator";
    }
    else if(typeofC(value[0])==5){
        ret="Space";
    }
    else if(typeofC(value[0])==6){
        ret="String";
    }
    else{
        ret="Null";
    }
    return ret;
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
char*assembleString(char*text,int*i,int*errorFlag){
    char*word=malloc(sizeof(char)*2);
    word[0]=text[*i-1];
    word[1]='\0';
    while(text[*i]!='"' && text[*i]!='\0'){
        appendChar(word,text[*i]);
        *i+=1;
    }
    if(text[*i]!='"'){
        *errorFlag=10;
        printf("\nError, upper commas missing\n");
    }
    appendChar(word,text[*i]);
    *i+=1;
    
    return word;
}

int lexer(tokenArray*tokens,char*text){
    int errorFlag=0;
    char*word=malloc(sizeof(char)*2);
    word[0]=text[0];
    word[1]='\0';
    int i=1;
    while (text[i]!='\0'){
        if(typeofC(text[i-1])!=6){
            if(typeofC(text[i-1])==typeofC(text[i]) && typeofC(text[i-1])!=3){
                appendChar(word,text[i]);
            }else{
                if(typeofC(word[0])!=5){
                    char*value=stringCopy(word);
                    appendToken(tokens,typeofT(value),value);
                }
                resetString(word);
                word[0]=text[i];
            }
        }
        else{
            word=assembleString(text,&i, &errorFlag);
            char*value=stringCopy(word);
            appendToken(tokens,typeofT(value),value);
            resetString(word);
            word[0]=text[i];
        }
        i+=1;
    }
    if(typeofC(word[0])!=5){
        char*value=stringCopy(word);
        appendToken(tokens,typeofT(value),value);
    }
    resetString(word);
    word[0]=text[i];
    free(word);

    return errorFlag;
}


int main(){
    tokenArray tokens=initTokenArray();
    char*text="xyz=\"hola mundo\"";
    int error=lexer(&tokens,text);
 
    if(error==0){
        for(int i=0; i< tokens.length;i++){
            printToken(tokens.list[i]);
            printf("\n");
        }
    }

    return 0;
}