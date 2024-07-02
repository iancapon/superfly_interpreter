#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

int main(){
    tokenArray tokens=initTokenArray();
    char*text="a=(10+20)*30";
    int error=lexer(&tokens,text);
 
    if(error==0){
        for(int i=0; i< tokens.length;i++){
            printToken(tokens.list[i]);
            printf("\n");
        }
    }
    parser(&tokens);
    return 0;
}