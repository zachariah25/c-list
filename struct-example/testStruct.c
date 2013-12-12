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
	setPrintFun(list, printStruct);
	setCmpFun(list, ascend);
	printList(list);
	printf("made it\n");
	for (int i = 0; i < 9; ++i) {
		printf("here %d", i);
		append(list, (myStruct) {i, i * 5.0});
	}
	printf("1\n");
	append(list, (myStruct) {5, 1.5});
	printf("2\n");
	append(list, (myStruct) {8, 9.3});
	printf("3\n");
	append(list, (myStruct) {1, 3.5});
	//printList(list);
	sort(list);
	printList(list);

	return EXIT_SUCCESS;
}
