#include "dictionary.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Programmer: Zain Haq

struct bstnode {
    void *key;
    void *val;
    struct bstnode *left;
    struct bstnode *right;
};


struct dictionary {
    struct bstnode *root;
    CompareFunction comp_k;
    FreeFunction free_k;
    FreeFunction free_v;
};

// see "dictionary.h" for more detail
Dictionary create_Dictionary(CompareFunction comp_k, FreeFunction
                             free_k, FreeFunction free_v) {
    assert(comp_k && free_k && free_v);
    Dictionary new = malloc(sizeof(struct dictionary));
    new->root = NULL;
    new->comp_k = comp_k;
    new->free_k = free_k;
    new->free_v = free_v;
    return new;
}

// destroy_node(dict,node) consumes a dictionary and a node and 
// frees memory allocated for the given node
// requires: dict != NULL and is a dictionary
// time: O(n * f), where n is the number of items in Dictionary, 
//       f is time to free key & value
void destroy_node(Dictionary dict, struct bstnode *node) {
    assert(dict);
    if (node == NULL) {
        return;
    } else {
        destroy_node(dict,node->left);
        destroy_node(dict, node->right);
        dict->free_k(node->key);
        dict->free_v(node->val);
        free(node);
    }    
}

// see "dictionary.h" for more detail
void destroy_Dictionary(Dictionary dict) {
    assert(dict);
    destroy_node(dict, dict->root);
    free(dict);
}

// make_node(k,v,l,r) creates a new bstnode with k  as the key and 
// as the value of the node, and l and r as the left and right node
// respectively
// effects: allocates memory from heap for the node
//          user must free
// requires: k != NULL && v != NULL
// time: O(1)
struct bstnode *make_bstnode(void *k, void *v, struct bstnode *l, 
                             struct bstnode *r) {
    assert(k && v);
	struct bstnode *new = malloc(sizeof(struct bstnode));
	new->key = k;
	new->val = v;
	new->left = NULL;
    new->right = NULL;
	return new;
}

// bst_insert(dict, k, v) inserts a new node with the given k and v
// into the dictionary dict
// effects: allocates memory on heap for the new node
//          user must free
// requires: k != NULL && v != NULL && dict != NULL
//   time: O(h * c + f), where h is height of underlying BST, 
//         c is time to compare two keys,
//         and f is the time to free the previous value (if      
//         necessary)
void bst_insert(Dictionary dict, void *k, void *v, 
                       struct bstnode **node) {
    assert(k && v && dict);
    struct bstnode *n = *node;
    if (n == NULL) {
        *node = make_bstnode(k, v, NULL, NULL);
    } else if (dict->comp_k(k, n->key) == 0) {
        void *temp = n->val;
        n->val = v;
        free(temp);
        return;
    } else if (dict->comp_k(k, n->key) == -1) {
        bst_insert(dict, k, v, &n->left);
    } else {
        bst_insert(dict,k,v, &n->right);
    }
}

// see "dictionary.h" for more detail
void insert(Dictionary dict, void *k, void *v) {
    assert(dict && k && v);
    bst_insert(dict, k, v, &dict->root);
};

// bst_search(node, k , dict) searches dict for a node asscociated 
// with key k
// requires: k != NULL and dict != NULL
//   time: O(h * c), where h is height of underlying BST, 
//         c is time to compare two keys
void *bst_search(struct bstnode *node, void *k, Dictionary dict) {
    assert(k && dict);
    if (node == NULL) {
        return NULL;
    } else if (dict->comp_k(k, node->key) == 0) {
        return node->val;
    } else if (dict->comp_k(k, node->key) == -1) {
        return bst_search(node->left, k, dict);
    } else {
        return bst_search(node->right, k, dict);
    }
}

// see "dictionary.h" for more detail
void *lookup(Dictionary dict, void *k) {
    assert(dict && k);
    return bst_search(dict->root, k, dict);
}