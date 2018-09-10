#ifndef KDTREE_H
#define KDTREE_H
    typedef void *kdTree;
kdTree createKdTree();
/*Esta função cria uma arvore kd, retornando o ponteiro para ela*/
void addkdTree(kdTree tree, void *thing);
/*Esta função insere um elemento na árvore*/
void deletekdTree(kdTree tree, char *id);
/*Esta função exclui um elemento da a partir do id*/
void *searchkdTree(kdTree tree, char *id);
#endif