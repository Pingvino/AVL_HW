#include "ADT_AVL.h"

AVL_TREE* create_bst_tree() {
	AVL_TREE* tree = (AVL_TREE*)malloc(sizeof(AVL_TREE));
	tree->count = 0;
	tree->root = NULL;
	return tree;
}

T_NODE* find_smallest_node(T_NODE* root) {
	if(root->left == NULL)
		return root;
	else
		return find_smallest_node(root->left);
}

T_NODE* find_largest_node(T_NODE* root) {
	if(root->right == NULL)
		return root;
	else
		return find_largest_node(root->right);
}

T_NODE* search_bst(T_NODE* root, int key) {
	if(root==NULL) return NULL;
	if(key < root->data)
		return search_bst(root->left, key);
	else if(key > root->data)
		return search_bst(root->right,key);
	else
		return root;
}

T_NODE* delete_rotate(T_NODE* root, int data, bool* success, bool* shorter) {
	if(root == NULL) {
		*success = false;
		return NULL;
	}
	//traverse
	if(data < root->data)
		printf("%d < %d\n",data, root->data);
		root->left = delete_rotate(root->left, data, success, shorter);
		if(*shorter) {
			switch(root->balance) {
				case LH:
					printf("deleting (%d) node to LH parent(%d)'s left\n",
					data, root->data);
					root->balance = EH;
					printf("(%d) root balance = %s\n",
					root->data,print_balance(root->balance));
					*shorter = false;
					break;
				case EH:
					printf("deleting (%d) node to EH parent(%d)'s left\n",
					data, root->data);
					root->balance = RH;
					printf("(%d) root balance = %s\n",
					root->data,print_balance(root->balance));
					break;
				case RH:
					printf("deleting (%d) node to RH parent(%d)'s left\n",
					data, root->data);
					root = balance_right(root,shorter);
					printf("(%d) root balance = %s\n",
					root->data,print_balance(root->balance));
					break;
			}
		}
	else if(data > root->data)
		printf("%d > %d\n",data, root->data);
		root->right = delete_rotate(root->right, data, success, shorter);
			if(*shorter) {
			switch(root->balance) {
				case LH:
					printf("deleting (%d) node to LH parent(%d)'s right\n",
					data, root->data);
					root = balance_left(root,shorter);
					printf("(%d) root balance = %s\n",
					root->data,print_balance(root->balance));
					break;
				case EH:
					printf("deleting (%d) node to EH parent(%d)'s right\n",
					data, root->data);
					root->balance = LH;
					printf("(%d) root balance = %s\n",
					root->data,print_balance(root->balance));
					break;
				case RH:
					printf("deleting (%d) node to RH parent(%d)'s right\n",
					data, root->data);
					root->balance = EH;
					printf("(%d) root balance = %s\n",
					root->data,print_balance(root->balance));
					*shorter = false;
					break;
			}
		}
	else { //matched
		printf("%d = %d\n",data, root->data);
		T_NODE* deleted_node = root;//backup
		if(root->left == NULL) {
			T_NODE* newRoot = root->right;
			free(deleted_node);
			*success = true;
			return newRoot;
		} else if(root->right == NULL) {
			T_NODE* newRoot = root->left;
			free(deleted_node);
			*success = true;
			return newRoot;
		} else {
			T_NODE* search = root->left;
			while(search->right != NULL)
				search = search->right;
			root->data = search->data;
			root->left = delete_rotate(root->left, search->data, success, shorter);
		}
	*shorter = true;
	}
	return root;
}

T_NODE* insert_rotate(T_NODE* root, T_NODE* new_node, bool* taller) {
	if(root == NULL) {
		root = new_node;
		*taller = true;
		return root;
	}
	if((new_node->data) < (root->data)) {
//		printf("%d < %d\n", new_node->data,root->data);//loging
		root->left = insert_rotate(root->left, new_node, taller);
		if(*taller) {
			switch(root->balance) {
				case LH:
//					printf("inserting (%d) node to LH parent(%d)'s left\n",
//					new_node->data, root->data);
					root = balance_left(root,taller);
//					printf("(%d) root balance = %s\n",
//					root->data,print_balance(root->balance));
					break;
				case EH:
//					printf("inserting (%d) node to EH parent(%d)'s left\n",
//					new_node->data, root->data);
					root->balance = LH;
//					printf("(%d) root balance = %s\n",
//					root->data,print_balance(root->balance));
					break;
				case RH:
//					printf("inserting (%d) node to RH parent(%d)'s left\n",
//					new_node->data, root->data);
					root->balance = EH;
//					printf("(%d) root balance = %s\n",
//					root->data,print_balance(root->balance));
					*taller = false;
					break;
			}
		}
		return root;
	} else {
//		printf("%d >= %d\n", new_node->data,root->data);//loging
		root->right = insert_rotate(root->right, new_node, taller);
		if(*taller) {
			switch(root->balance) {
				case LH:
//					printf("inserting (%d) node to LH parent(%d)'s right\n",
//					new_node->data, root->data);
					root->balance = EH;
//					printf("(%d) root balance = %s\n",
//					root->data,print_balance(root->balance));
					*taller = false;
					break;
				case EH:
//					printf("inserting (%d) node to EH parent(%d)'s right\n",
//					new_node->data, root->data);
					root->balance = RH;
//					printf("(%d) root balance = %s\n",
//					root->data,print_balance(root->balance));
					break;
				case RH:
//					printf("inserting (%d) node to RH parent(%d)'s right\n",
//					new_node->data, root->data);
					root = balance_right(root, taller);
//					printf("(%d) root balance = %s\n",
//					root->data,print_balance(root->balance));
					break;
			}
		}
		return root;
	}
	return root;
}

T_NODE* balance_left(T_NODE* root, bool* taller) {
	printf("\ninitializing balance_left...\n");
	T_NODE* right_tree;
	T_NODE* left_tree;
	left_tree = root->left;
	switch(left_tree->balance) {
		case LH:
			printf("LH case\n");
			root->balance = EH;
			left_tree->balance = EH;
			root = rotate_right(root);
			*taller = false;
			*shorter = false;
			break;
		case EH:
			exit(0);
		case RH: //right of left
			printf("RH case\n");
			right_tree = left_tree->right;
			switch(right_tree->balance) {
				case LH:
					root->balance = RH;
					left_tree->balance = EH;
					break;
				case EH:
					root->balance = EH;
					left_tree->balance = LH;
					break;
				case RH:
					root->balance = EH;
					left_tree->balance = LH;
					break;
			}
			right_tree->balance = EH;
			root->left = rotate_left(left_tree);
			root = rotate_right(root);
			*taller = false;
			*shorter = false;
	} //end of switch
	printf("after balance_left, balance of root(%d) = %s\n\n",
	root->data, print_balance(root->balance));
	return root;
}

T_NODE* balance_right(T_NODE* root, bool* taller) {
	printf("\ninitializing balance_right...\n");
	T_NODE* right_tree;
	T_NODE* left_tree;
	right_tree = root->right;
	switch(right_tree->balance) {
		case RH:
			printf("RH case\n");
			root->balance = EH;
			right_tree->balance = EH;
			root = rotate_left(root);
			*taller = false;
			*shorter = false;
			break;
		case EH: exit(0);
		case LH: //left of right
			printf("LH case\n");
			left_tree = right_tree->left;
			switch(left_tree->balance) {
				case LH:
					root->balance = RH;
					right_tree->balance = EH;
					break;
				case EH:
					root->balance = EH;
					right_tree->balance = LH;
					break;
				case RH:
					root->balance = EH;
					right_tree->balance = LH;
					break;
			}
			left_tree->balance = EH;
			root->right = rotate_right(right_tree);
			root = rotate_left(root);
			*taller = false;
			*shorter = false;
	} //end of switch
	printf("after balance_right, balance of root(%d) = %s\n\n",
	root->data, print_balance(root->balance));
	return root;
}

T_NODE* rotate_left(T_NODE* root) {
	printf("rotating left... root is now (%d)\n",root->data);
	T_NODE* new_root;
	new_root = root->right;
	root->right = new_root->left;
	new_root->left = root;
	printf("rotated left... root is now (%d)\n\n",new_root->data);
	return new_root;
	}

T_NODE* rotate_right(T_NODE* root) {
	printf("rotating right... root is now (%d)\n",root->data);
	T_NODE* new_root;
	new_root = root->left;
	root->left = new_root->right;
	new_root->right = root;
	printf("rotated right... root is now (%d)\n\n",new_root->data);
	return new_root;
	}

bool AVL_insert(AVL_TREE* tree, int data) {
//	printf("inserting %d...\n",data);
	T_NODE* new_node;
	bool taller;
	new_node = (T_NODE*)malloc(sizeof(T_NODE));
	if(!new_node) return false;
	new_node->balance = EH;
	new_node->right = NULL;
	new_node->left = NULL;
	new_node->data = data;

	tree->root = insert_rotate(tree->root, new_node, &taller);
//	printf("After insert, root is (%d), balance = %s\n\n",
//	tree->root->data, print_balance(tree->root->balance));
	(tree->count)++;
	return true;
}

bool AVL_delete(AVL_TREE* tree, int data) {
	printf("deleting %d...\n",data);
	bool success;
	bool shorter;
	T_NODE* newRoot;
	newRoot = delete_rotate(tree->root, data, &success, &shorter);
	if(success) {
		tree->root = newRoot;
		(tree->count)--;
		if(tree->count == 0)
			tree->root = NULL;
	}
	printf("After delet, root is (%d), balance = %s\n\n",
	tree->root->data, print_balance(tree->root->balance));
	return success;
}

void traverse_preorder(T_NODE* root) {
	if(root) {
		printf("%d,",root->data);
		traverse_preorder(root->left);
		traverse_preorder(root->right);
	}
	return;
}

void traverse_postorder(T_NODE* root) {
	if(root) {
		traverse_postorder(root->left);
		traverse_postorder(root->right);
		printf("%d,",root->data);
	}
	return;
}

void traverse_inorder(T_NODE* root) {
	if(root) {
		if(root->left != NULL)
			traverse_inorder(root->left);
		printf("%d,",root->data);
		if(root->right != NULL)
			traverse_inorder(root->right);
	}
	return;
}

void AVL_print(AVL_TREE* tree, int method) {
	printf("AVL_TREE:\n");
	printf(" size : %d\n", tree->count);
	printf(" data : ");

	if(method == 0)
		traverse_preorder(tree->root);
	else if(method == 1)
		traverse_inorder(tree->root);
	else if(method ==2)
		traverse_postorder(tree->root);
	else
		printf("type error");

	printf("\n");
}

void AVL_diagram(T_NODE* root){
	if(root) {
		printf("root : %d,",root->data);
		if(root->left)
			printf(" left : %d,",root->left->data);
		else
			printf(" left : NULL,");
		if(root->right)
			printf(" right : %d,", root->right->data);
		else
			printf(" right : NULL,");
		printf(" balance : %s\n",
		print_balance(root->balance));
		AVL_diagram(root->left);
		AVL_diagram(root->right);
	}
	return;
}

char const* print_balance(int balance) {
		switch(balance) {
			case EH:
				return "EH";
			case RH:
				return "RH";
			case LH:
				return "LH";
		}
}
bool AVL_destroy(AVL_TREE* tree) {
	while(tree->count !=0) {
	int min = (find_smallest_node(tree->root))->data;
	if(!AVL_delete(tree,min))
		printf("failed on deleting min.node : %d\n",min);
	//printf("deleted node: %d\n", min);
	//printf("current nodes in tree : %d\n",tree->count);
	}
	free(tree);

}
