/*
Namn: BinSearchTree.c
Beskrivning: Implementering av BinSearchTree.h
*/

#include <stdlib.h>
#include "BinSearchTree.h"


typedef struct node_{

    void *data;
    TreeNode left;
    TreeNode right;
} Node;

typedef struct tree_{

    int size;
    TreeNode root;
    int (*cmp)(const void *key1, const void *key2);
    void (*destroy)(const void *data);
} Tree;

static int addNode(Binsearchtree, TreeNode, const void *data);
static void inorder_traverse(Binsearchtree, TreeNode, void (*func)(void *data));
static void preorder_traverse(Binsearchtree, TreeNode, void (*func)(void *data));
static void postorder_traverse(Binsearchtree, TreeNode, void (*func)(void *data));


Binsearchtree inittree(int (*cmp)(const void *key1, const void *key2), void (*destroy)(const void *data)){

    Binsearchtree bintree = malloc(sizeof(Tree));
    bintree->size = 0;
    bintree->root = NULL;
    bintree->cmp = cmp;
    bintree->destroy = destroy;
    return bintree;
}

static int addNode(Binsearchtree tree, TreeNode position, const void *data){

    int code;
    TreeNode *tmp;

    code = (tree->cmp(data, position->data));
    if(code > 0){
	tmp = &position->right;
	position = position->right;
    }
    else if(code < 0){
	tmp = &position->left;
	position = position->left;
    }
    else if(code == 0){
	return 1;
    }
    if(position){
	return addNode(tree, position, data);
    }
    else{
	TreeNode node = malloc(sizeof(Node));
	if(node == NULL){
	    return -1;
	}
	*tmp = node;
	node->data = (void *)data;
	node->left = NULL;
	node->right = NULL;
	return 0;
    }
}

int insert(Binsearchtree tree, const void *data){
    
    TreeNode node;
    int code;

    if((tree->size < 1)){
	node = malloc(sizeof(Node));
	node->data = (void *)data;
	node->left = NULL;
	node->right = NULL;
	tree->root = node;
	tree->size++;
	code = 0;
    }
    else{
	node = tree->root;
	code = addNode(tree, node, data);
	if(code == 0){
	    tree->size++;
	    return 0;
	}
	
    }
    return code;
}

static void inorder_traverse(Binsearchtree tree, TreeNode position, void (*func)(void *data)){

    /*Från lösningsförslag. Inorder traversering.*/
    if(position){
	inorder_traverse(tree, position->left, func);
	func(position->data);
	inorder_traverse(tree, position->right, func);
    }
}

void doforall(Binsearchtree tree, void (*func)(void *data)){
    
    TreeNode node = tree->root;
    inorder_traverse(tree, node, func);
}

static void preorder_traverse(Binsearchtree tree, TreeNode position, void (*func)(void *data)){

    if(position){
	func(position->data);
	preorder_traverse(tree, position->left, func);
	preorder_traverse(tree, position->right, func);
    }
}

void preorder(Binsearchtree tree, void (*func)(void *data)){

    TreeNode node = tree->root;
    preorder_traverse(tree, node, func);
}

static void postorder_traverse(Binsearchtree tree, TreeNode position, void (*func)(void *data)){

    if(position){
	postorder_traverse(tree, position->left, func);
	postorder_traverse(tree, position->right, func);
	func(position->data);
    }
}

void postorder(Binsearchtree tree, void (*func)(void *data)){

    TreeNode node = tree->root;
    postorder_traverse(tree, node, func);
}

void *find(Binsearchtree tree, const void *data){
    
    TreeNode position = tree->root;
    int code;
    
    while(position){
	if((code = (tree->cmp(data, position->data))) == 0){
	    return position->data;
	}
	else if(code == -1){
	    position = position->left;
	}
	else if(code == 1){
	    position = position->right;
	}
	else{
	    return NULL;
	}
    }
    return NULL;
}
