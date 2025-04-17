/**
 * -------------------------------------
 * @file  set_avl.c
 * file description
 * -------------------------------------
 * @author Giuseppe Akbari, 169057752, akba7752@mylaurier.ca
 *
 * @version 2025-03-08
 *
 * -------------------------------------
 */
#include "string.h"
#include "avl.h"
#include "set_avl.h"

int set_size(SET *s) {
// your code
	if (s) {
		return s->size;
	}
	return 0;
}

int set_contains(SET *s, char *e) {
// your code

	return (avl_search(s->root, e)) ? 1 : 0;
}

void set_add(SET *s, char *e) {
// your code
	if (set_contains(s, e) == 0) {
		RECORD r = { 0 };
		strcpy(r.name, e);
		avl_insert(&(s->root), r);
		s->size++;
	}
}

void set_remove(SET *s, char *e) {
// your code
	if (set_contains(s, e) == 1) {
		avl_delete(&(s->root), e);
		s->size--;
	}
	return;
}

void set_clean(SET *s) {
// your code
	if (s) {
		avl_clean(&(s->root));
		s->size = 0;
	}
	return;
}

