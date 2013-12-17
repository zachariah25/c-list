/*
file: testStruct.c
author: Zach Lauzon (zrl3031@rit.edu)
description: example of storing structs in List structure
*/

#include "ListConfig.h"
#include "List.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct ListStruct myStruct;


// Comparison function for integers sorted in ascending order
int ascend( const void *a, const void *b ) {
    //return (*((myStruct*)a)->x - *((myStruct*)b)->x); 
    int p = ((myStruct*) (*(myStruct**) a))->x;
    int q = ((myStruct*) (*(myStruct**) b))->x;
    //int q = ((myStruct*) b)->x;
    return p - q;
}

// Comparison function for integers sorted in descending order
int descend( const void *a, const void *b ) {
    return ((*(myStruct**)b)->x - (*(myStruct**)a)->x); 
}

// Function prints throws struct's data into char *
char result[99];
char* printStruct(const void* element) {
    sprintf(result, "{%d, %f}", (*(myStruct**)element)->x, (*(myStruct**)element)->y);
    return result;
}

myStruct* mkMyStruct(int x, float y) {
	myStruct* el = malloc(sizeof(myStruct));
	el->x = x;
	el->y = y;
	return el;
}

int main() {
	List* list = makeList();
	// Set a comparison function so that we may call printList
	setPrintFun(list, printStruct);
	printList(list);

	// Add ten elements
	for (int i = 0; i < 100; ++i) {
		myStruct* el = mkMyStruct(i, i * 5.0);
		append(list, el);
	}

	// Force a resize
	myStruct* a = mkMyStruct(5, 1.5);
	myStruct* b = mkMyStruct(8, 9.3);
	myStruct* c = mkMyStruct(1, 3.5);
	append(list, a);
	append(list, b);
	append(list, c);
	
	// Print the list in its current state
	printList(list);

	// Sort the list, using the comparison function we set
	setCmpFun(list, ascend);
	sort(list);
	printList(list);

	// It's the caller's responsibility to call this
	// Note that we callend the pointer version so we free each element
	cleanupList(list);
	return EXIT_SUCCESS;
}
