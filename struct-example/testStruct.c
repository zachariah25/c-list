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
    return (((myStruct*)a)->x - ((myStruct*)b)->x); 
}

// Comparison function for integers sorted in descending order
int descend( const void *a, const void *b ) {
    return (((myStruct*)b)->x - ((myStruct*)a)->x); 
}

// Function prints throws struct's data into char *
char result[99];
char* printStruct(const void* element) {
    sprintf(result, "{%d, %f}", ((myStruct*)element)->x, ((myStruct*)element)->y);
    return result;
}

int main() {
	List* list = makeList();
	// Set a comparison function so that we may call printList
	setPrintFun(list, printStruct);
	printList(list);

	// Add ten elements
	for (int i = 0; i < 9; ++i) {
		append(list, (myStruct) {i, i * 5.0});
	}

	// Force a resize
	append(list, (myStruct) {5, 1.5});
	append(list, (myStruct) {8, 9.3});
	append(list, (myStruct) {1, 3.5});
	
	// Print the list in its current state
	printList(list);

	// Sort the list, using the comparison function we set
	setCmpFun(list, ascend);
	sort(list);
	printList(list);

	// It's the caller's responsibility to call this
	cleanupList(list);
	return EXIT_SUCCESS;
}
