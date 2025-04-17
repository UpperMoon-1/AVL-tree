/**
 * -------------------------------------
 * @file  myrecord_avl.h
 * file description
 * -------------------------------------
 * @author Giuseppe Akbari, 169057752, akba7752@mylaurier.ca
 *
 * @version 2025-03-08
 *
 * -------------------------------------
 */
#ifndef MYRECORD_AVL_H_
#define MYRECORD_AVL_H_

typedef struct {
	AVLNODE *root;
	int count;
	float mean;
	float stddev;
} AVLDS;

void avl_merge(AVLNODE **dest_rootp, AVLNODE **source_rootp);

void avlds_merge(AVLDS *dest, AVLDS *source);

void avlds_clean(AVLDS *ds);

void add_record(AVLDS *ds, RECORD data);

void remove_record(AVLDS *ds, char *name);

#endif
