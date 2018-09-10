#ifndef HASH_H
#define HASH_H
#define TABLE_HASH 128;
    typedef void *Hash;
Hash createHash(int TABLE_HASH);
/*Cria uma tabela de espalhamento de tamanho TABLE_HASh*/
int functionHash(char *str);
/*função que define aonde vai determinado dado*/
void *searchHash(Hash ha, char *id);
/*função de busca da Hash por id*/
void deleteHash(Hash ha, char *id);
/*função de delição da hash por id*/
#endif