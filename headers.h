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

#endif
