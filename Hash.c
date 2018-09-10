#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Hash.h"

typedef struct {
    int size;
    int qtd;
    void **vet;
}hash;

Hash createHash(int TABLE_SIZE){
    hash *newHash;
    newHash = (hash*)malloc(sizeof(hash));
    newHash.size = TABLE_SIZE;
    newHash.qtd = 0;
    newHash.vet = (void**)calloc(TABLE_SIZE, sizeof(void*));
    
}