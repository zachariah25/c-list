/*
file: testString.c
author: Zach Lauzon (zrl3031@rit.edu)
description: example of storing strings in List structure
*/

#include "List.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Comparison function for strings sorted in ascending order
int ascend( const void *a, const void *b ) {
    return strcmp((char*) a, (char*) b); 
}

// Comparison function for strings sorted in descending order
int descend( const void *a, const void *b ) {
    return -1 * strcmp((char*) a, (char*) b); 
}

char* printString(const void* element) {
    return *(char**) element;
}

int main() {
	List* list = makeList();
	// Set a print function so that we may call printList
	setPrintFun(list, printString);
	printList(list);

	// Add ten elements
	for (int i = 0; i < 9; ++i) {
		append(list, "hello");
	}

	// Force a resize
	append(list, "aaa");
	append(list, "zzz");
	append(list, "lists!");

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
