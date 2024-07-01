#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

int main(){
    tokenArray tokens=initTokenArray();
    char*text="10+20*30 #comentario tonto\n";
    int error=lexer(&tokens,text);
 
    if(error==0){
        for(int i=0; i< tokens.length;i++){
            printToken(tokens.list[i]);
            printf("\n");
        }
    }

    return 0;
}