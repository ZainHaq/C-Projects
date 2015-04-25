#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include "bst.h"

// see bst.h documentation
struct bsttree *create_bst(void) {
	struct bsttree *tree = malloc(sizeof(struct bsttree));
	tree->root = NULL;
	return tree;
}

// destroy_tree(node) destroys node
// effects: node is deallocated along with all nodes linked to it.
// time: O(n) where n is the number of nodes linked to struct bstnode node.
void destroy_tree(struct bstnode *node) {
	if (NULL == node) {return;}
	destroy_tree(node->left);
	destroy_tree(node->right);
	free(node);
}


// see bst.h documentation
void destroy_bst(struct bsttree *t){
   assert(t);
   destroy_tree(t->root);
   free(t);
}


// see bst.h documentation
struct bstnode *make_bstnode(int val, struct bstnode *l, struct bstnode *r) {
	struct bstnode *new = malloc(sizeof(struct bstnode));
	new->item = val;
	new->left = l;
	new->right = r;
	return new;
}



// see bst.h documentation
bool is_bstempty(struct bsttree *t){
	assert(t);
	return (NULL == t->root);
}


// inorder_node(node) prints all nodes of node in order
//  (left, root, right)
// effects: node's item is printed to the screen, 
//          along with all nodes' items linked to it
// time: O(n) where n is the number of printed nodes
void inorder_node(struct bstnode *node) {
	if (NULL == node) {return;}
	inorder_node(node->left);
	printf("  %d", node->item);
	inorder_node(node->right);
}

// see bst.h documentation
void traverse_inorder(struct bsttree *t){
	assert(t);
	inorder_node(t->root);
	printf("\n");
}


// is_bst_helper(node,max,min) returns true if node is a valid BST
// bst node, meaning it is between max and min
// time: O(n) where n is the number of nodes in node
bool is_bst_helper(struct bstnode *node, int max, int min) {
    if (node == NULL) {
        return true;
    } else if (node->item > min && node->item < max) {
        return is_bst_helper(node->left, node->item, min) && 
               is_bst_helper(node->right, max, node->item);
    } else {
        return false;
    }   
}

// see bst.h documentation
bool is_bst(struct bsttree *t){
    assert(t != NULL);
    if (t->root == NULL) {
        return true;
    } else {
        return is_bst_helper(t->root, INT_MAX, INT_MIN);
    }
}

// bst_insert_helper(val, node) inserts a new node with val into 
// the given node in such a way the node remains a BST tree
// or makes no changes if val already exists
// requires: node is a valid BST node
// time: O(h) where h is the height of node
void bst_insert_helper(int val, struct bstnode **node) {
    struct bstnode *n = *node;
    if (n == NULL) {
        *node = make_bstnode(val, NULL, NULL);
    } else if (val == n->item) {
        return;
    } else if (val < n->item) {
        bst_insert_helper(val, &n->left);
    } else {
        bst_insert_helper(val, &n->right);
    }
}

//see bst.h documentation
void bst_insert(int val, struct bsttree *t) {
    assert(t);
    if (t->root == NULL) {
        t->root = make_bstnode(val, NULL,NULL);
    } else if (val == t->root->item){
        return;        
    } else if (val < t->root->item) {
        bst_insert_helper(val, &t->root->left);
        return;
    } else {
        bst_insert_helper(val, &t->root->right);
        return;
    }
}

// bst_search_helper(node, val) determines if val is an item in 
// the BST node, node, returns true if val is in node, false 
// otherwise
// requires: node is a valid BST node
// time: O(h) where h is the height of node
bool bst_search_helper(struct bstnode *node, int val) {
    if (node == NULL) {
        return false;
    } else if (val == node->item) {
        return true;
    } else if (val < node->item) {
        return bst_search_helper(node->left, val);
    } else {
        return bst_search_helper(node->right, val);
    }
}

//see bst.h documentation
bool bst_search(struct bsttree *t, int val){
    assert(t);
    if (t->root == NULL) {
        return false;
    } else {
        return bst_search_helper(t->root, val);
    }
}

// bst_height_helper(node) returns the height of BST node, node. 
//  time: O(n), where n is the number of nodes in t
int bst_height_helper(struct bstnode *node){
    if (node == NULL) {
        return 0;
    } else {
        int right_depth = bst_height_helper(node->right);
        int left_depth = bst_height_helper(node->left);
        if (right_depth > left_depth) {
            return right_depth + 1;
        } else {
            return left_depth + 1;
        }
    }
}

//see bst.h documentation
int bst_height(struct bsttree *t){
    assert(t != NULL);
    if (t->root == NULL) {
        return 0;
    } else {
        return bst_height_helper(t->root);
    }
}

// mirror(node) changes the BST node, node so that the roles of the 
// left and right pointers are swapped at every node.
// effects: modifying the pointers.
// time: O(n) where n is the number of nodes in node.
void mirror_helper(struct bstnode **node) { 
    struct bstnode *n = *node;
    if (n == NULL){
        return;
    } else {
        struct bstnode *temp = n->left;
        n->left = n->right;
        n->right = temp;
        mirror_helper(&n->left);
        mirror_helper(&n->right);
    }
}

//see bst.h documentation
void mirror(struct bsttree *t) { 
    assert(t != NULL);
    if (t->root == NULL) {
        return;
    } else {
        mirror_helper(&t->root);
    }
  
} 