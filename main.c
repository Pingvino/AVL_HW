//ADT list
#include <stdio.h>
#include "ADT_AVL.h"

int main() {
	int i;
	T_NODE* search;

	//Create
	AVL_TREE* tree = create_bst_tree();

	//Insertion Test
	if(!AVL_insert(tree,10))
		printf("tree insertion error\n");
	if(!AVL_insert(tree,9))
		printf("tree insertion error\n");
	if(!AVL_insert(tree,8))
		printf("tree insertion error\n");
	if(!AVL_insert(tree,7))
		printf("tree insertion error\n");
	if(!AVL_insert(tree,6))
		printf("tree insertion error\n");
	if(!AVL_insert(tree,5))
		printf("tree insertion error\n");
	if(!AVL_insert(tree,11))
		printf("tree insertion error\n");
	if(!AVL_insert(tree,12))
		printf("tree insertion error\n");
	if(!AVL_insert(tree,13))
		printf("tree insertion error\n");
	if(!AVL_insert(tree,14))
		printf("tree insertion error\n");
	if(!AVL_insert(tree,15))
		printf("tree insertion error\n");
	if(!AVL_insert(tree,20))
		printf("tree insertion error\n");
	if(!AVL_insert(tree,19))
		printf("tree insertion error\n");
	if(!AVL_insert(tree,17))
		printf("tree insertion error\n");
	if(!AVL_insert(tree,16))
		printf("tree insertion error\n");
	if(!AVL_insert(tree,18))
		printf("tree insertion error\n");
	if(!AVL_insert(tree,0))
		printf("tree insertion error\n");
	if(!AVL_insert(tree,2))
		printf("tree insertion error\n");
	if(!AVL_insert(tree,4))
		printf("tree insertion error\n");
	if(!AVL_insert(tree,1))
		printf("tree insertion error\n");

	printf("\n");
	AVL_diagram(tree->root);
	printf("\n");
	
	if(!AVL_delete(tree,1))
		printf("tree deletion error\n");
	if(!AVL_delete(tree,4))
		printf("tree deletion error\n");
	if(!AVL_delete(tree,10))
		printf("tree deletion error\n");
	if(!AVL_delete(tree,15))
		printf("tree deletion error\n");
	if(!AVL_delete(tree,8))
		printf("tree deletion error\n");

	AVL_destroy(tree);
	return 0;
}
