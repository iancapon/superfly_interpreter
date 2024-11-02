#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

void calculadoraSimple(tokenArray*input){///// ESTO SE VA DESPUES, SOLO SIRVE PARA CALC SIMPLE
    char*answer;
        for(int i=0; i< input->length;i++){
            if(strcmp(input->list[i].type,"InfixOperator")==0){
                if(strcmp(input->list[i].value,"+")==0)
                    sprintf(input->list[i].value, "%.4f", (atof(input->list[i-2].value)+atof(input->list[i-1].value)));
                else if(strcmp(input->list[i].value,"*")==0)
                    sprintf(input->list[i].value, "%.4f", (atof(input->list[i-2].value)*atof(input->list[i-1].value)));
                else if(strcmp(input->list[i].value,"-")==0)
                    sprintf(input->list[i].value, "%.4f", (atof(input->list[i-2].value)-atof(input->list[i-1].value)));
                else if(strcmp(input->list[i].value,"/")==0)
                    sprintf(input->list[i].value, "%.4f", (atof(input->list[i-2].value)/atof(input->list[i-1].value)));
                answer=input->list[i].value;
            }
        }
    printf("\n\nANSWER: %s",answer);
}   

int main(){
    tokenArray tokens=initTokenArray();
    char*text="5+(10.0-20.0)*3.0";
    int error=lexer(&tokens,text);
    
    if(error==0){
        parser(&tokens);
        for(int i=0; i< tokens.length;i++){
            printf("\n");
            printToken(tokens.list[i]);
        }
        calculadoraSimple(&tokens);
    }
    
    return 0;
}