/**
 * -------------------------------------
 * @file  avl.c
 * file description
 * -------------------------------------
 * @author Giuseppe Akbari, 169057752, akba7752@mylaurier.ca
 *
 * @version 2025-03-08
 *
 * -------------------------------------
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "avl.h"

AVLNODE* avl_node(RECORD data) {
	AVLNODE *np = (AVLNODE*) malloc(sizeof(AVLNODE));
	if (np) {
		np->data = data;
		np->height = 1;
		np->left = NULL;
		np->right = NULL;
	}
	return np;
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

int height(AVLNODE *np) {
	// your code
	int height = 0;
	if (np != NULL) {
		height = np->height;
	}

	return height;

}

int balance_factor(AVLNODE *np) {
	// your code
	int b = 0;
	if (np != NULL) {
		b = height(np->left) - height(np->right);
	}
	return b;
}

AVLNODE* rotate_left(AVLNODE *np) {
// your code
	AVLNODE *x = np->right;
	AVLNODE *T2 = x->left;
	x->left = np;
	np->right = T2;

	if (height(np->right) >= height(np->left)) {
		np->height = height(np->right) + 1;
	} else {
		np->height = height(np->left) + 1;
	}
	if (height(x->left) >= height(x->right)) {
		x->height = height(x->left) + 1;
	} else {
		x->height = height(x->right) + 1;
	}

	return x;
}

AVLNODE* rotate_right(AVLNODE *root) {
// your code
	AVLNODE *x = root->left;
	AVLNODE *T2 = x->right;
	x->right = root;
	root->left = T2;

	if (height(root->left) >= height(root->right)) {
		root->height = height(root->left) + 1;
	} else {
		root->height = height(root->right) + 1;
	}
	if (height(x->left) >= height(x->right)) {
		x->height = height(x->left) + 1;
	} else {
		x->height = height(x->right) + 1;
	}
	return x;
}
/*
 AVLNODE* rotate_left(AVLNODE *x) {
 // your code
 }
 */
AVLNODE* extract_smallest_node(AVLNODE **rootp) {
	AVLNODE *p = *rootp, *parent = NULL;
	if (p) {
		while (p->left) {
			parent = p;
			p = p->left;
		}
		if (parent == NULL)
			*rootp = p->right;
		else
			parent->left = p->right;

		p->left = NULL;
		p->right = NULL;
	}
	return p;
}

void avl_insert(AVLNODE **rootp, RECORD data) {
	// 1. Perform the normal BST insertion
	if (*rootp == NULL) {
		AVLNODE *np = (AVLNODE*) malloc(sizeof(AVLNODE));
		if (np) {
			np->data = data;
			np->height = 1;
			np->left = NULL;
			np->right = NULL;
		}
		*rootp = np;
	} else {

		AVLNODE *root = *rootp;

		if (strcmp(data.name, root->data.name) == 0)
			return;
		else if (strcmp(data.name, root->data.name) < 0) {
			avl_insert(&root->left, data);
		} else {
			avl_insert(&root->right, data);
		}

		// 2. update height of this ancestor node
		//root->height = ???
		if (height(root->left) > height(root->right)) {
			root->height = height(root->left) + 1;
		} else {
			root->height = height(root->right) + 1;
		}

		// 3. Get the balance factor of this ancestor node to check whether this node became unbalanced
		//int balance = ???
		int balance = balance_factor(root);

		// 4. rebalance if not balanced
		//???

		if (balance > 1) {
			if (balance_factor(root->left) >= 0) {
				*rootp = rotate_right(root);
			} else {
				root->left = rotate_left(root->left);
				*rootp = rotate_right(root);
			}
		} else if (balance < -1) {
			if (balance_factor(root->right) <= 0) {
				*rootp = rotate_left(root);
			} else {
				root->right = rotate_right(root->right);
				*rootp = rotate_left(root);
			}
		}
	}
	return;
}

void avl_delete(AVLNODE **rootp, char *name) {
	AVLNODE *root = *rootp;
	AVLNODE *np;
	if (root == NULL)
		return;

	if (strcmp(name, root->data.name) == 0) {
		if (root->left == NULL && root->right == NULL) {
			free(root);
			*rootp = NULL;
		} else if (root->left != NULL && root->right == NULL) {
			np = root->left;
			free(root);
			*rootp = np;
		} else if (root->left == NULL && root->right != NULL) {
			np = root->right;
			free(root);
			*rootp = np;
		} else if (root->left != NULL && root->right != NULL) {
			np = extract_smallest_node(&root->right);
			np->left = root->left;
			np->right = root->right;
			free(root);
			*rootp = np;
		}
	} else {

		if (strcmp(name, root->data.name) < 0) {
			avl_delete(&root->left, name);
		} else {
			avl_delete(&root->right, name);
		}
	}

// If the tree had only one node then return
	if (*rootp == NULL)
		return;
	root = *rootp;

// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
//root->height = ???
	if (height(root->left) >= height(root->right)) {
		root->height = height(root->left) + 1;
	} else {
		root->height = height(root->right) + 1;
	}

// STEP 3: GET THE BALANCE FACTOR OF THIS NODE
//int balance = ???
	int balance = balance_factor(root);

// STEP 4: rebalance if not balanced
//???
	if (balance >= -1 && balance <= 1) {
		return;
	} else if (balance > 1) {
		if (balance_factor(root->left) >= 0) {
			*rootp = rotate_right(root);
		} else {
			root->left = rotate_left(root->left);
			*rootp = rotate_right(root);
		}
	} else if (balance < -1) {
		if (balance_factor(root->right) <= 0) {
			*rootp = rotate_left(root);
		} else {
			root->right = rotate_right(root->right);
			*rootp = rotate_left(root);
		}
	}

	return;
}

AVLNODE* avl_search(AVLNODE *root, char *name) {
// your code
	AVLNODE *node;
	if (root == NULL) {
		return NULL;
	} else {
		if (strcmp(name, root->data.name) == 0) {
			node = root;
			return node;
		} else if (strcmp(name, root->data.name) < 0) {		//go left
			node = avl_search(root->left, name);
		} else {		//go right
			node = avl_search(root->right, name);
		}
	}
	return node;
}

void avl_clean(AVLNODE **rootp) {
	AVLNODE *root = *rootp;
	if (root) {
		if (root->left)
			avl_clean(&root->left);
		if (root->right)
			avl_clean(&root->right);
		free(root);
	}
	*rootp = NULL;
}
