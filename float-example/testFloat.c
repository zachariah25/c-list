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
	int arr[] = {1,3,2};
	//List* list = arrayToList(arr, 3);
	List* list = sizeNList(10);
	printList(list, printFloat);
	sort(list, ascend);

	return EXIT_SUCCESS;
}