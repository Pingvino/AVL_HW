#ifndef ADT_AVL
#define ADT_AVL
#include <stdio.h>
#include <stdlib.h>
#define LH 1
#define EH 0
#define RH -1

// AVL Tree Node
typedef struct node {
	int data;
	struct node* left;
	struct node* right;
	int balance;
} T_NODE;

// AVL TREE
typedef struct {
	int count;
	T_NODE* root;
} AVL_TREE;

// Operations;
AVL_TREE* create_bst_tree();//ok
T_NODE* find_smallest_node(T_NODE* root);//ok
T_NODE* find_largest_node(T_NODE* root);//ok
T_NODE* search_bst(T_NODE* root, int key);//ok
T_NODE* delete_bst(T_NODE* root, int data, bool* success);

T_NODE* insert_rotate(T_NODE root, T_NODE* new_node, bool* taller);
T_NODE* balance_left(T_NODE* root, bool* taller);
T_NODE* balance_right(T_NODE* root, bool* taller);
T_NODE* rotate_left(T_NODE* root);
T_NODE* rotate_right(T_NODE* root);

void traverse_preorder(T_NODE* root);
void traverse_inorder(T_NODE* root);
void traverse_postorder(T_NODE* root);

bool AVL_insert(AVL_TREE* tree, int data);
bool AVL_delete(AVL_TREE* tree, int data);
void AVL_print(AVL_TREE* tree, int method);//ok
void AVL_diagram(T_NODE* root);
char const* print_balance(int balance);
bool AVL_destroy(AVL_TREE* tree);

#endif
