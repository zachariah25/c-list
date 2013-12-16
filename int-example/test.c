/*
file: test.c
author: Zach Lauzon (zrl3031@rit.edu)
description: test harness for List.c. prints all '1's if successful
*/

#include "List.h"
#include <stdio.h>

// Comparison function for integers sorted in ascending order
int ascend( const void *a, const void *b ) {
    return (*(int*)a - *(int*)b); 
}

// Comparison function for integers sorted in descending order
int descend( const void *a, const void *b ) {
    return (*(int*)b -  *(int*)a); 
}

char result[11];

char* printInt(const void* element) {
    sprintf(result, "%d", *(int*)element);
    return result;
}

List* sizeNList(int n) {
    List* list = makeListWithCapacity(n);
    for (int i = 0; i < n; ++i) {
    	append(list, i);
    }
    return list;
}

type* sizeNArr(int n) {
    type* arr = (type*) malloc(sizeof(type) * n);
    for (int i = 0; i < n; ++i) {
        arr[i] = i;
    }
    return arr;
}

int t1() {
    // Create a list and an equivalent array, check their equality
    List* list = sizeNList(10);
    type* arr  = sizeNArr(10);
    setCmpFun(list, ascend);
    int result = 
        equalsArray(list, arr);
    cleanupList(list);
    free(arr);
    return result;
}

int t2() {
    // Create two equivalent lists, check their equality
    List* list = sizeNList(10);
    List* list2 = sizeNList(10);
    setCmpFun(list, ascend);
    int result = 
        equals(list, list2);
    cleanupList(list);
    cleanupList(list2);
    return result;
}

int t3() {
    // Make a list with three elements, ensure they're correct using array comparison
    type arr[] = {8, 6, 7};
    List* list = makeList();
    setCmpFun(list, ascend);
    append(list, 8);
    append(list, 6);
    append(list, 7);
    int result = 
        equalsArray(list, arr);
    cleanupList(list);
    return result;
}

int t4() {
    // Make a list with three elements, ensure they're correct using the get method
    type arr[] = {8, 6, 7};
    List* list = makeList();
    setCmpFun(list, ascend);
    append(list, 8);
    append(list, 6);
    append(list, 7);
    int result = 
        get(list, 0) == arr[0] && get(list, 1) == arr[1] && get(list, 2) == arr[2];
    cleanupList(list);
    return result;
}

int t5() {
    // See if count works properly
    List* list = makeList();
    setCmpFun(list, ascend);
    append(list, 1);
    append(list, 6);
    append(list, 6);
    int result =
        count(list, 6) == 2 && count(list, 0) == 0 && count(list, 1) == 1; 
    cleanupList(list);
    return result;
}

int t6() {
    // See if indexOf works properly
    List* list = makeList();
    setCmpFun(list, ascend);
    append(list, 0);
    append(list, 1);
    append(list, 2);
    int result =
        indexOf(list, 0) == 0 && indexOf(list, 1) == 1 && indexOf(list, 5) == -1; 
    cleanupList(list);
    return result;
}

int t7() {
    // See if set works properly
    List* list = makeList();
    append(list, 0);
    append(list, 1);
    append(list, 2);
    set(list, 0, 15);
    int result =
        get(list, 0) == 15; 
    cleanupList(list);
    return result;
}

int t8() {
    // See if set works properly
    List* list = makeList();
    append(list, 0);
    append(list, 1);
    append(list, 2);
    set(list, 0, 15);
    int result =
        get(list, 0) == 15; 
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
    append(list, 0);
    append(list, 1);
    int result =
        capacity(list) == 1 * RESIZEFACTOR && get(list, 1) == 1 && size(list) == 2;
    cleanupList(list);
    return result;
}

int t11() {
    // See if lastIndexOf works properly
    List* list = makeList();
    setCmpFun(list, ascend);
    append(list, 0);
    append(list, 1);
    append(list, 0);
    int result =
        indexOf(list, 0) == 0 && lastIndexOf(list, 0) == 2;
    cleanupList(list);
    return result;
}

int t12() {
    // See if contains works properly
    List* list = makeList();
    setCmpFun(list, ascend);
    append(list, 0);
    append(list, 1);
    int result =
        contains(list, 0) && !contains(list, -5) && contains(list, 1);
    cleanupList(list);
    return result;
}

int t13() {
    // See if front and back work properly
    List* list = makeList();
    setCmpFun(list, ascend);
    append(list, 0);
    append(list, 1);
    append(list, 2);
    int result =
        front(list) == 0 && back(list) == 2;
    cleanupList(list);
    return result;
}

int t14() {
    // See if slice works properly
    List* list = makeListWithCapacity(5);
    setCmpFun(list, ascend);
    List* list2 = makeListWithCapacity(3);
    setCmpFun(list2, ascend);
    List* list3 = makeListWithCapacity(1);
    setCmpFun(list3, ascend);

    append(list, 0);
    append(list, 1); append(list2, 1);
    append(list, 2); append(list2, 2);
    append(list, 3); append(list2, 3);
    append(list, 4);
    append(list3, 0);

    List* list4 = slice(list, 0, size(list));   // Equivalent to list
    List* list5 = slice(list, 1, 4);            // Equivalent to list2
    List* list6 = slice(list, 0, 1);            // Equivalent to list3

    int result1 = equals(list, list4);
    int result2 = equals(list2, list5);
    int result3 = equals(list3, list6);

    cleanupList(list);
    cleanupList(list2);
    cleanupList(list3);
    cleanupList(list4);
    cleanupList(list5);
    cleanupList(list6);
    return result1 && result2 && result3;
}

int t15() {
    // See if sliceWithStep works properly
    List* list = sizeNList(5);
    setCmpFun(list, ascend);
    List* reverseList = copyList(list);
    setCmpFun(reverseList, ascend);
    reverse(reverseList); 
    List* reverseSlice = sliceWithStep(list, size(list) - 1, -1, -1);
    int result1 = 
        equals(reverseList, reverseSlice);
    /*
    puts("list");
    print(list);
    puts("reverseList");
    print(reverseList);
    puts("reverseSlice");
    print(reverseSlice);
    */

    List* slice = sliceWithStep(list, 0, size(list), 1);
    int result2 = 
        equals(list, slice);

    List* step2List = makeListWithCapacity(3);
    setCmpFun(step2List, ascend);
    append(step2List, 0);
    append(step2List, 2);
    append(step2List, 4);
    List* step2Slice = sliceWithStep(list, 0, size(list), 2);
    int result3 = 
        equals(step2List, step2Slice);
    /*
    print(step2List);
    print(step2Slice);
    */

    cleanupList(list);
    cleanupList(reverseList);
    cleanupList(slice);
    cleanupList(reverseSlice);
    cleanupList(step2List);
    cleanupList(step2Slice);
    /*
    printf("result1 %i\n", result1);
    printf("result2 %i\n", result2);
    printf("result3 %i\n", result3);
    */
    return result1 && result2 && result3;
}

int t16() {
    // See if removeIndex works properly
    List* list = sizeNList(5);
    setCmpFun(list, ascend);
    removeIndex(list, 0);
    int result = 
        !contains(list, 0) && size(list) == 4;
    cleanupList(list);
    return result;
}

int t17() {
    // See if removeElement works properly
    List* list = sizeNList(5);
    setCmpFun(list, ascend);
    removeElement(list, 3);
    int result =
        !contains(list, 3) && size(list) == 4;
    cleanupList(list);
    return result;
}

int t18() {
    // See if pop works properly
    List* list = sizeNList(5);
    setCmpFun(list, ascend);
    pop(list);
    int result =
        !contains(list, 4) && size(list) == 4;
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
        get(list, 0) == 0 && get(list, 5) == 0 && size(list) == 30 
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
        get(list, 3) == 5 && get(list, 4) == 6 && size(list) == 8;
    cleanupList(list);
    return result;
}

int t22() {
    // test toArray
    List* list = sizeNList(10);
    setCmpFun(list, ascend);
    type* arr = toArray(list);
    int result =
        equalsArray(list, arr);
    cleanupList(list);
    free(arr);
    return result;
}

void runTests() {
    puts("Running tests...");
    printf("t1:  %i\n", t1());
    printf("t2:  %i\n", t2());
    printf("t3:  %i\n", t3());
    printf("t4:  %i\n", t4());
    printf("t5:  %i\n", t5());
    printf("t6:  %i\n", t6());
    printf("t7:  %i\n", t7());
    printf("t8:  %i\n", t8());
    printf("t9:  %i\n", t9());
    printf("t10: %i\n", t10());
    printf("t11: %i\n", t11());
    printf("t12: %i\n", t12());
    printf("t13: %i\n", t13());
    printf("t14: %i\n", t14());
    printf("t15: %i\n", t15());
    printf("t16: %i\n", t16());
    printf("t17: %i\n", t17());
    printf("t18: %i\n", t18());
    printf("t19: %i\n", t19());
    printf("t20: %i\n", t20());
    printf("t21: %i\n", t21());
    printf("t22: %i\n", t22());
}

int main() {
    runTests();
}
