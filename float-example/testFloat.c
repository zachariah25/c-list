/*
file: testFloat.c
author: Zach Lauzon (zrl3031@rit.edu)
description: example of storing floats in List structure
*/

#include "List.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Comparison function for integers sorted in ascending order
int ascend( const void *a, const void *b ) {
    return (*(float*)a - *(float*)b); 
}

// Comparison function for integers sorted in descending order
int descend( const void *a, const void *b ) {
    return (*(float*)b -  *(float*)a); 
}

char result[12];

char* printFloat(const void* element) {
    sprintf(result, "%lf", *(float*)element);
    return result;
}

int main() {
	List* list = makeList();
	// Set a print function so that we may call printList
	setPrintFun(list, printFloat);
	printList(list);

	// Add ten elements
	for (int i = 0; i < 9; ++i) {
		append(list, 5.0);
	}

	// Force a resize
	append(list, 1.5);
	append(list, 9.3);
	append(list, 3.5);
	
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
