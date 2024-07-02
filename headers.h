// mi_libreria.h
#ifndef MI_LIBRERIA_H
#define MI_LIBRERIA_H

typedef struct token{
    char*type;
    char*value;
}token;

typedef struct tokenArray{
    token*list;
    int length;
}tokenArray;

tokenArray initTokenArray();

void printToken(token x);
void assignToken(token*x,char*type,char*value);
void appendToken(tokenArray*array,char*type,char*value);


void appendChar(char*word,char c);
void resetString(char*word);
char*stringCopy(char*origen);

int lexer(tokenArray*tokens,char*text);
void parser(tokenArray*input);
#endif
