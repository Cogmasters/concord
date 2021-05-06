/*
    AVL tree implementation, header file.

    This implementation was written by Kent "ethereal" Williams-King and is
    hereby released into the public domain. Do what you wish with it.

    No guarantees as to the correctness of the implementation are provided.
*/

#ifndef AVL_H
#define AVL_H

/* modify this macro to change the prefix */
#define AVL_NAME(name) avl_ ## name
/* memory allocation macros, change as necessary */
#define AVL_ALLOC(variable, type) variable = (type *)malloc(sizeof(type))
#define AVL_FREE(variable) free(variable)
#include <stdlib.h> /* for malloc() */

typedef int (*AVL_NAME(comparator_t))(void *key1, void *key2);
typedef void (*AVL_NAME(key_destructor_t))(void *key);
typedef void (*AVL_NAME(node_visitor_t))(void *key, void *data);

typedef struct AVL_NAME(tree_node_t) {
    struct AVL_NAME(tree_node_t) *left, *right;
    int depth;

    void *key;
    void *data;
} AVL_NAME(tree_node_t);

typedef struct {
    AVL_NAME(tree_node_t) *root;
    AVL_NAME(comparator_t) comparator;
    AVL_NAME(key_destructor_t) destructor;
} AVL_NAME(tree_t);

void AVL_NAME(initialize)(AVL_NAME(tree_t) *tree,
    AVL_NAME(comparator_t) comparator, AVL_NAME(key_destructor_t) destructor);
void AVL_NAME(destroy)(AVL_NAME(tree_t) *tree,
    AVL_NAME(node_visitor_t) visitor);

void *AVL_NAME(search)(AVL_NAME(tree_t) *tree, void *key);
void *AVL_NAME(insert)(AVL_NAME(tree_t) *tree, void *key, void *data);
void *AVL_NAME(remove)(AVL_NAME(tree_t) *tree, void *key);

int AVL_NAME(tree_depth)(AVL_NAME(tree_t) *tree);

int AVL_NAME(ptrcmp)(void *key1, void *key2);
int AVL_NAME(intcmp)(void *key1, void *key2);
int AVL_NAME(ulongcmp)(void *key1, void *key2);

void AVL_NAME(free_data)(void *key, void *data);

#endif
