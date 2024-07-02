#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

int main(){
    tokenArray tokens=initTokenArray();
    char*text="a=(10-1)*15";
    int error=lexer(&tokens,text);
 
    if(error==0){
        for(int i=0; i< tokens.length;i++){
            printToken(tokens.list[i]);
            printf("\n");
        }
        printf("----------------------");
        parser(&tokens);
    }

    return 0;
}