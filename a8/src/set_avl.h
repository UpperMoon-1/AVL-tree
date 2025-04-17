/**
 * -------------------------------------
 * @file  set_avl.h
 * file description
 * -------------------------------------
 * @author Giuseppe Akbari, 169057752, akba7752@mylaurier.ca
 *
 * @version 2025-03-08
 *
 * -------------------------------------
 */
#ifndef SET_AVL_H
#define SET_AVL_H

typedef struct {
	AVLNODE *root;
	int size;
} SET;

int set_size(SET *s);
int set_contains(SET *s, char *e);
void set_add(SET *s, char *e);
void set_remove(SET *s, char *e);
void set_clean(SET *s);

#endif
