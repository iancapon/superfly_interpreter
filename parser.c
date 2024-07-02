#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

typedef struct bpower{
    char*op;
    int val;
}bpower;
typedef struct bparr{
    bpower*list;
    int length;
} bparr;


void abpAux(bpower*x,char*op,int val){
    x->op=op;
    x->val=val;
}

void assigBindPow(bparr*array,char*op,int val){
    abpAux(array->list+array->length,op,val);
    array->list=realloc(array->list,sizeof(bpower)*(array->length+2));
    array->length+=1;
}

/*
 bPower={"+":10,"*":20,"-":10,"/":20,"\n":1,
            "null":0,"=":5,":":6,",":7,"mostrar":5,
            "mayor":50,"menor":50,"igual":50,"^":30,
            "%":20,"--":45,"(":0,")":0,"sin":40,
            "cos":40,"tan":40,"atan":40}
*/
int bindingPower(token x){
    bparr powers;
    powers.list=malloc(sizeof(bpower));
    powers.length=0;
    assigBindPow(&powers,"Null",0);
    assigBindPow(&powers,"(",0);
    assigBindPow(&powers,")",0);
    assigBindPow(&powers,";",10);
    assigBindPow(&powers,"\n",10);
    assigBindPow(&powers,"=",15);
    assigBindPow(&powers,"+",20);
    assigBindPow(&powers,"-",20);
    assigBindPow(&powers,"*",30);
    assigBindPow(&powers,"/",30);
    assigBindPow(&powers,"%",30);
    int ret=0;
    for(int i=0; i < powers.length; i++){
        if(strcmp(powers.list[i].op,x.value)==0){
            ret=powers.list[i].val;
            break;
        }
    }
    return ret;
}

token topof(tokenArray*stack){
    token ret;
    ret.type="Null";
    ret.value="Null";
    if(stack->length>0){
        ret=stack->list[stack->length-1];
    }
    return ret;
}

void push(tokenArray*stack,token x){
    appendToken(stack,x.type,x.value);
}

token pop(tokenArray*stack){
    token ret;
    if(stack->length>0){
        ret.type=stack->list[stack->length -1].type;
        ret.value=stack->list[stack->length -1].value;
        stack->list=realloc(stack->list,sizeof(token)*(stack->length));///////////// ojo acá
        stack->length-=1;
    }else{
        ret.type="Null";
        ret.value="Null";
    }
    return ret;
}

void eraseToken(token x){
    free(x.type);
    free(x.value);
}

void parser(tokenArray*input){
    tokenArray output=initTokenArray();
    tokenArray stack=initTokenArray();
    for (int i=0; i< input->length;i++){
        
        if(strcmp(input->list[i].type,"Expr")==0 || strcmp(input->list[i].type,"Number")==0 || strcmp(input->list[i].type,"String")==0){
            push(&output,input->list[i]);///////// HASTA ACÁ ESTÁ BIEN
        }
        else if(strcmp(input->list[i].type,"Bracket")==0){
            if(strcmp(input->list[i].value,"(")==0){
                push(&stack,input->list[i]);
            }
            else if(strcmp(input->list[i].value,")")==0){
                while(strcmp(topof(&stack).value,"(")!=0 && stack.length>0){
                    printToken(topof(&stack));
                    push(&output,pop(&stack));
                }
                pop(&stack);
                //eraseToken(pop(&stack));/////////////// sino va a quedar dando vueltas
                //eraseToken(input->list[i]);
            }
        }
        else if(strcmp(input->list[i].type,"InfixOperator")==0){
            if(bindingPower(topof(&stack))<= bindingPower(input->list[i])){ ////// mayor que el de arriba del stack
                push(&stack,input->list[i]);
            }
            else{
                while(bindingPower(topof(&stack))> bindingPower(input->list[i])){///// menor que el de arriba del stack
                    push(&output,pop(&stack));
                }
            }
        }
    }
    while(stack.length>0){
        push(&output,pop(&stack));
    }

    printf("\n");
    printf("\n");
    for(int i=0; i< output.length;i++){
        printToken(output.list[i]);
        printf("\n");
    }
    printf("\n");
    printf("\n");

}