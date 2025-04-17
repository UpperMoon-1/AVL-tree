/**
 * -------------------------------------
 * @file  myrecord_avl.c
 * file description
 * -------------------------------------
 * @author Giuseppe Akbari, 169057752, akba7752@mylaurier.ca
 *
 * @version 2025-03-08
 *
 * -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "avl.h"
#include "myrecord_avl.h"

void avl_merge(AVLNODE **dest_rootp, AVLNODE **source_rootp) {
	// your code
	if ((*source_rootp) != NULL) {
		if (avl_search(*dest_rootp, (*source_rootp)->data.name) == NULL) {
			RECORD r = { 0 };
			strcpy(r.name, (*source_rootp)->data.name);
			r.score = (*source_rootp)->data.score;
			avl_insert(dest_rootp, r);
			avl_merge(dest_rootp, &((*source_rootp)->left));
			avl_merge(dest_rootp, &((*source_rootp)->right));
		}
	}
	return;

}

void avlds_merge(AVLDS *dest, AVLDS *source) {
	// your code
	avl_merge(&(dest->root), &(source->root));
	int count = dest->count + source->count;
	float mean = ((dest->mean) * (dest->count)
			+ (source->mean) * (source->count)) / (float) count;

	float s1 = (dest->stddev) * (dest->stddev);
	float s2 = (source->stddev) * (source->stddev);

	float ns = ((dest->count * (s1 + dest->mean * dest->mean))
			+ (source->count * (s2 + source->mean * source->mean)));
	float newStddev = ns / (float) count - (mean * mean);
	newStddev = sqrt(newStddev);

	dest->count = count;
	dest->mean = mean;
	dest->stddev = newStddev;
	avlds_clean(source);

	return;
}

void avlds_clean(AVLDS *ds) {
	avl_clean(&ds->root);
	ds->count = 0;
	ds->mean = 0;
	ds->stddev = 0;
}

// the following functions are adapted from a7q3
void add_record(AVLDS *tree, RECORD data) {
	if (avl_search(tree->root, data.name) == NULL) {
		avl_insert(&(tree->root), data);
		int count = tree->count;
		float mean = tree->mean;
		float stddev = tree->stddev;
		tree->count = count + 1;
		tree->mean = (mean * count + data.score) / (count + 1.0);
		tree->stddev = sqrt(
				data.score * data.score / (count + 1.0)
						+ (stddev * stddev + mean * mean)
								* (count / (count + 1.0))
						- tree->mean * tree->mean);
	} else {
		printf("record exits");
	}
}

void remove_record(AVLDS *tree, char *name) {
	AVLNODE *np = NULL;
	if ((np = avl_search(tree->root, name)) != NULL) {
		float score = np->data.score;
		avl_delete(&(tree->root), name);
		float count = tree->count;
		float mean = tree->mean;
		float stddev = tree->stddev;
		tree->count = count - 1;
		if (count >= 3) {
			tree->mean = (mean * count - score) / (count - 1.0);
			tree->stddev = sqrt(
					(stddev * stddev + mean * mean) * (count / (count - 1.0))
							- score * score / (count - 1.0)
							- tree->mean * tree->mean);
		} else if (count == 2) {
			tree->mean = mean * count - score;
			tree->stddev = 0;
		} else {
			tree->mean = 0;
			tree->stddev = 0;
		}
	} else {
		printf("record does not exit");
	}
}
