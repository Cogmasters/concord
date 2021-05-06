/*
    AVL tree implementation, source file.

    This implementation was written by Kent "ethereal" Williams-King and is
    hereby released into the public domain. Do what you wish with it.

    No guarantees as to the correctness of the implementation are provided.
*/

#include "avl.h"

/* required definitions */
#ifndef NULL
    #define NULL ((void *)0)
#endif

/* recursive destruction helper */
static void AVL_NAME(destroy_helper)(AVL_NAME(tree_t) *tree,
    AVL_NAME(tree_node_t) *node, AVL_NAME(node_visitor_t) visitor);
/* recursive insertion helper */
static void *AVL_NAME(insert_helper)(AVL_NAME(tree_t) *tree,
    AVL_NAME(tree_node_t) **node, void *key, void *data);
/* recursive removal helper, finds the appropriate node to remove */
static void *AVL_NAME(remove_helper)(AVL_NAME(tree_t) *tree,
    AVL_NAME(tree_node_t) **node, void *key);
/* recursive removal helper, updates tree depths after node swap */
static void AVL_NAME(remove_depth_helper)(AVL_NAME(tree_node_t) *ptr);

#define AVL_LEFT 0
#define AVL_RIGHT 1
/* rotates a node and its left/right child as appropriate (left=0, right=1) */
static void AVL_NAME(rotate)(AVL_NAME(tree_node_t) **ptr, int which);

/* performs rotations to appropriately rebalance a node and its children */
static void AVL_NAME(rebalance)(AVL_NAME(tree_node_t) **ptr);
/* calculates how out-of-balance a node is (>0 if left deeper) */
static int AVL_NAME(balance_factor)(AVL_NAME(tree_node_t) *ptr);
/* recalculates the depth of a node */
static void AVL_NAME(update_depth)(AVL_NAME(tree_node_t) *ptr);

void AVL_NAME(initialize)(AVL_NAME(tree_t) *tree,
    AVL_NAME(comparator_t) comparator, AVL_NAME(key_destructor_t) destructor) {
    
    tree->comparator = comparator;
    tree->destructor = destructor;
    tree->root = NULL;
}

void AVL_NAME(destroy)(AVL_NAME(tree_t) *tree,
    AVL_NAME(node_visitor_t) visitor) {

    AVL_NAME(destroy_helper)(tree, tree->root, visitor);
}

static void AVL_NAME(destroy_helper)(AVL_NAME(tree_t) *tree,
    AVL_NAME(tree_node_t) *node, AVL_NAME(node_visitor_t) visitor) {

    if(node == NULL) return;

    visitor(node->key, node->data);
    AVL_NAME(destroy_helper)(tree, node->left, visitor);
    AVL_NAME(destroy_helper)(tree, node->right, visitor);

    AVL_FREE(node);
}

void *AVL_NAME(search)(AVL_NAME(tree_t) *tree, void *key) {
    AVL_NAME(tree_node_t) *node = tree->root;
    int cmp;
    while(node) {
        cmp = tree->comparator(key, node->key);
        if(cmp == 0) return node->data;
        else if(cmp < 0) {
            node = node->left;
        }
        else /* if(cmp > 0) */ {
            node = node->right;
        }
    }
    return NULL;
}

void *AVL_NAME(insert)(AVL_NAME(tree_t) *tree, void *key, void *data) {
    return AVL_NAME(insert_helper)(tree, &tree->root, key, data);
}

static void *AVL_NAME(insert_helper)(AVL_NAME(tree_t) *tree,
    AVL_NAME(tree_node_t) **node, void *key, void *data) {

    int cmp;
    void *ret;

    /* if the search leads us to an empty location, then add the new node.
        rebalancing, if required, will be handled by the parent call in the
        recursion. */
    if(!*node) {
        AVL_ALLOC(*node, AVL_NAME(tree_node_t));
        (*node)->depth = 1;
        (*node)->key = key;
        (*node)->data = data;
        (*node)->left = (*node)->right = NULL;

        return NULL;
    }

    cmp = tree->comparator(key, (*node)->key);
    if(cmp == 0) {
        /* if we find a node with the same value, then replace the contents.
            no rebalancing is required, but will be checked by parent recursion
            call nonetheless. */
        void *old = (*node)->data;
        (*node)->data = data;
        /* we don't need the new key any more. */
        if(tree->destructor) tree->destructor(key);
        return old;
    }
    else if(cmp < 0) {
        ret = AVL_NAME(insert_helper)(tree, &(*node)->left, key, data);
    }
    else /*if(cmp > 0)*/ {
        ret = AVL_NAME(insert_helper)(tree, &(*node)->right, key, data);
    }

    /* check, and rebalance the current node, if necessary */
    AVL_NAME(rebalance)(node);
    /* ensure the depth of this node is correct */
    AVL_NAME(update_depth)(*node);

    return ret;
}

void *AVL_NAME(remove)(AVL_NAME(tree_t) *tree, void *key) {
    return AVL_NAME(remove_helper)(tree, &tree->root, key);
}

static void *AVL_NAME(remove_helper)(AVL_NAME(tree_t) *tree,
    AVL_NAME(tree_node_t) **node, void *key) {

    int cmp;
    void *ret;

    /* if we didn't find the node, then, well . . . */
    if(!*node) return NULL;

    cmp = tree->comparator(key, (*node)->key);

    if(cmp < 0) ret = AVL_NAME(remove_helper)(tree, &(*node)->left, key);
    else if(cmp > 0) ret = AVL_NAME(remove_helper)(tree, &(*node)->right, key);
    else /* if(cmp == 0) */ {
        /* node found. */
        AVL_NAME(tree_node_t) **y, *p = NULL;

        ret = (*node)->data;
        if(tree->destructor) tree->destructor((*node)->key);

        /* complicated case */
        if((*node)->left && (*node)->right) {
            /* use maximum node in left subtree as the replacement */
            y = &(*node)->left;
            while((*y)->right) y = &(*y)->right;

            /* copy contents out */
            (*node)->key = (*y)->key;
            (*node)->data = (*y)->data;

            /* replace the found node with its left child: if there is no left
                child, this will replace it with NULL */
            p = (*y)->left;
            AVL_FREE(*y);
            *y = p;

            /* ensure all the depths in the left subtree are correct. */
            AVL_NAME(remove_depth_helper)((*node)->left);
        }
        else if((*node)->left) {
            /* no right subtree, so replace this node with the left subtree */
            p = (*node)->left;
            AVL_FREE(*node);
            *node = p;
        }
        else if((*node)->right) {
            /* no left subtree, so replace this node with the right subtree */
            p = (*node)->right;
            AVL_FREE(*node);
            *node = p;
        }
        else {
            /* no children at all, i.e. a leaf */
            AVL_FREE(*node);
            *node = NULL;
        }
    }

    /* if the node was replaced, ensure the depth is correct and that
        everything is balanced */
    if(*node) {
        AVL_NAME(update_depth)(*node);
        AVL_NAME(rebalance)(node);
    }

    return ret;
}

static void AVL_NAME(remove_depth_helper)(AVL_NAME(tree_node_t) *ptr) {
    if(ptr) {
        AVL_NAME(remove_depth_helper)(ptr->right);
        AVL_NAME(update_depth)(ptr);
    }
}

static void AVL_NAME(rebalance)(AVL_NAME(tree_node_t) **node) {
    int delta = AVL_NAME(balance_factor)(*node);

    /* two rotation directions */
    if(delta == 2) {
        if(AVL_NAME(balance_factor((*node)->left) < 0)) {
            AVL_NAME(rotate)(&(*node)->left, AVL_LEFT);
        }
        AVL_NAME(rotate)(node, AVL_RIGHT);
    }
    else if(delta == -2) {
        if(AVL_NAME(balance_factor((*node)->right) > 0)) {
            AVL_NAME(rotate)(&(*node)->right, AVL_RIGHT);
        }
        AVL_NAME(rotate)(node, AVL_LEFT);
    }
}

static void AVL_NAME(rotate)(AVL_NAME(tree_node_t) **node, int dir) {
    AVL_NAME(tree_node_t) *ch;
    
    /* standard tree rotations */
    if(dir == 0) {
        ch = (*node)->right;
        
        (*node)->right = (*node)->right->left;
        ch->left = *node;
        AVL_NAME(update_depth)(*node);
        *node = ch;
    }
    else {
        ch = (*node)->left;
        
        (*node)->left = (*node)->left->right;
        ch->right = *node;
        AVL_NAME(update_depth)(*node);
        *node = ch;
    }
    AVL_NAME(update_depth)(*node);
}

static int AVL_NAME(balance_factor)(AVL_NAME(tree_node_t) *ptr) {
    int delta = 0;
    if(ptr->left) delta = ptr->left->depth;
    if(ptr->right) delta -= ptr->right->depth;
    return delta;
}

static void AVL_NAME(update_depth)(AVL_NAME(tree_node_t) *ptr) {
    ptr->depth = 0;
    if(ptr->left) ptr->depth = ptr->left->depth;
    if(ptr->right && ptr->depth < ptr->right->depth) {
        ptr->depth = ptr->right->depth;
    }
    ptr->depth ++;
}

int AVL_NAME(tree_depth)(AVL_NAME(tree_t) *tree) {
    if(tree->root) return tree->root->depth;
    return 0;
}

int AVL_NAME(ptrcmp)(void *key1, void *key2) {
    if(key1 < key2) return -1;
    else if(key1 > key2) return 1;
    else return 0;
}

int AVL_NAME(intcmp)(void *key1, void *key2) {
    int val1 = *(int *)key1;
    int val2 = *(int *)key2;
    if(val1 < val2) return -1;
    else if(val1 > val2) return 1;
    else return 0;
}

int AVL_NAME(ulongcmp)(void *key1, void *key2) {
    unsigned long val1 = *(int *)key1;
    unsigned long val2 = *(int *)key2;
    if(val1 < val2) return -1;
    else if(val1 > val2) return 1;
    else return 0;
}

void AVL_NAME(free_data)(void *key, void *data) {
    AVL_FREE(key);
    AVL_FREE(data);
}
