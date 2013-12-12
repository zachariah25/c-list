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

// Function prints throws struct's data into char `
char result[99];
char* printStruct(const void* element) {
    sprintf(result, "{%d, %f}", ((myStruct*)element)->x, ((myStruct*)element)->y);
    return result;
}

type* sizeNArr(int n) {
    type* arr = (type*) malloc(sizeof(type) * n);
    for (int i = 0; i < n; ++i) {
        arr[i] = (myStruct) {i, 1.5};
    }
    return arr;
}

List* sizeNList(int n) {
	List* list = sizeNList(n);
	for (int i = 0; i < n; ++i) {
		append(list, (myStruct) {i, 1.5});
	}
	return list;
}

int t2() {
    // Create two equivalent lists, check their equality
    List* list = sizeNList(10);
    setCmpFun(list, ascend);
    List* list2 = sizeNList(10);
    setCmpFun(list2, ascend);
    int result = 
        equals(list, list2);
    cleanupList(list);
    cleanupList(list2);
    return result;
}

int t5() {
    // See if count works properly
    List* list = makeList();
    setCmpFun(list, ascend);
    append(list, (myStruct) {1, 1.5});
    append(list, (myStruct) {6, 1.5});
    append(list, (myStruct) {6, 1.5});
    int result =
        count(list, (myStruct) {6, 1.5}) == 2 &&
        count(list, (myStruct) {0, 1.5}) == 0 &&
        count(list, (myStruct) {1, 1.5}) == 1; 
    cleanupList(list);
    return result;
}

int t6() {
    // See if indexOf works properly
    List* list = makeList();
    setCmpFun(list, ascend);
    append(list, (myStruct) {0, 1.5});
    append(list, (myStruct) {1, 1.5});
    append(list, (myStruct) {2, 1.5});
    int result =
        indexOf(list, (myStruct) {0, 1.5}) == 0 && indexOf(list, (myStruct) {1, 1.5}) == 1 && indexOf(list, (myStruct) {5, 1.5}) == -1; 
    cleanupList(list);
    return result;
}

int t7() {
    // See if set works properly
    List* list = makeList();
    setCmpFun(list, ascend);
    append(list, (myStruct) {0, 1.5});
    append(list, (myStruct) {1, 1.5});
    append(list, (myStruct) {2, 1.5});
    set(list, 0, (myStruct) {15, 1.5});
    int result =
        get(list, 0).x == 15; 
    cleanupList(list);
    return result;
}

int t8() {
    // See if set works properly
    List* list = makeList();
    append(list, (myStruct) {0, 1.5});
    append(list, (myStruct) {1, 1.5});
    append(list, (myStruct) {2, 1.5});
    set(list, 0, (myStruct) {15, 1.5});
    int result =
        get(list, 0).x == 15; 
    cleanupList(list);
    return result;
}

int t9() {
    // See if makeListWithCapacity works
    List* list = makeListWithCapacity(20);
    int result =
        capacity(list) == 20; 
    cleanupList(list);
    return result;
}

int t10() {
    // See if resize works properly
    List* list = makeListWithCapacity(1);
    append(list, (myStruct) {0, 1.5});
    append(list, (myStruct) {1, 1.5});
    int result =
        capacity(list) == 1 * RESIZEFACTOR && get(list, 1).x == 1 && size(list) == 2;
    cleanupList(list);
    return result;
}

int t11() {
    // See if lastIndexOf works properly
    List* list = makeList();
    append(list, (myStruct) {0, 1.5});
    append(list, (myStruct) {1, 1.5});
    append(list, (myStruct) {0, 1.5});
    int result =
        indexOf(list, (myStruct) {0, 1.5}) == 0 && lastIndexOf(list, (myStruct) {0, 1.5}) == 2;
    cleanupList(list);
    return result;
}

int t12() {
    // See if contains works properly
    List* list = makeList();
    setCmpFun(list, ascend);
    append(list, (myStruct) {0, 1.5});
    append(list, (myStruct) {1, 1.5});
    int result =
        contains(list, (myStruct) {0, 1.5}) && 
        !contains(list, (myStruct) {-5, 1.5}) &&
        contains(list, (myStruct) {1, 1.5});
    cleanupList(list);
    return result;
}

int t16() {
    // See if removeIndex works properly
    List* list = sizeNList(5);
    removeIndex(list, 0);
    int result = 
        !contains(list, (myStruct) {0, 1.5}) && size(list) == 4;
    cleanupList(list);
    return result;
}

int t17() {
    // See if removeElement works properly
    List* list = sizeNList(5);
    setCmpFun(list, ascend);
    removeElement(list, (myStruct) {3, 1.5});
    int result =
        !contains(list, (myStruct) {3, 1.5}) && size(list) == 4;
    cleanupList(list);
    return result;
}

int t18() {
    // See if pop works properly
    List* list = sizeNList(5);
    setCmpFun(list, ascend);
    pop(list);
    int result =
        !contains(list, (myStruct) {4, 1.5}) && size(list) == 4;
    cleanupList(list);
    return result;
}

int t19() {
    // See if clear works properly
    List* list = sizeNList(5);
    clear(list);
    int result =
        size(list) == 0;
    cleanupList(list);
    return result;
}

int t20() {
    // test insertList
    List* list = sizeNList(10);
    List* newList = sizeNList(20);
    insertList(list, 5, newList);
    int result =
        get(list, 0).x == 0 && get(list, 5).x == 0 && size(list) == 30 
            && size(newList) == 20;

    cleanupList(list);
    cleanupList(newList);
    return result;
}

int t21() {
    // test removeRange
    List* list = sizeNList(10);
    removeRange(list, 3, 5);
    int result =
        get(list, 3).x == 5 && get(list, 4).x == 6 && size(list) == 8;
    cleanupList(list);
    return result;
}


void runTests() {
    puts("Running tests...");
    //printf("t2:  %i\n", t2());
    printf("t5:  %i\n", t5());
    printf("t6:  %i\n", t6());
    printf("t7:  %i\n", t7());
    printf("t8:  %i\n", t8());
    printf("t9:  %i\n", t9());
    printf("t10: %i\n", t10());
    printf("t11: %i\n", t11());
    printf("t12: %i\n", t12());
    //printf("t16: %i\n", t16());
    //printf("t17: %i\n", t17());
    //printf("t18: %i\n", t18());
    //printf("t19: %i\n", t19());
    //printf("t20: %i\n", t20());
    //printf("t21: %i\n", t21());
}

int main() {
	List* list = makeList();
	setPrintFun(list, printStruct);
	setCmpFun(list, ascend);
	for (int i = 0; i < 99; ++i) {
		append(list, (myStruct) {i, i * 5.0});
	}
	append(list, (myStruct) {5, 1.5});
	append(list, (myStruct) {8, 9.3});
	append(list, (myStruct) {1, 3.5});
	//printList(list);
	sort(list);
	printList(list);

	runTests();
	return EXIT_SUCCESS;
}