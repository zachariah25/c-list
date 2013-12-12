/*
file: List.c
author: Zach Lauzon (zrl3031@rit.edu)
description: live interpreter to execute list commands
to run: make and run ./interp, and type "help" for a list of commands
*/

#include "ListConfig.h"
#include "List.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Comparison function for integers sorted in ascending order
int cmp_int_ascend( const void *a, const void *b ) {
    return (*(int*)a - *(int*)b); 
}

// Comparison function for integers sorted in descending order
int cmp_int_descend( const void *a, const void *b ) {
    return (*(int*)b -  *(int*)a); 
}

char result[11];

char* printInt(const void* element) {
    sprintf(result, "%d", *(int*)element);
    return result;
}

int main() {
    List* list1 = makeList();
    List* list2 = makeList();
    setCmpFun(list1, cmp_int_ascend);
    setPrintFun(list1, printInt);
    setPrintFun(list2, printInt);
    int max = 20;
    int arg1;
    int arg2;
    int arg3;
    char cmd[max];

    // Comparison function
    //int(*compar)(const void *, const void *);
    //compar = &compareInts;

    puts("Entering live interpreter");
    puts("CTRL+D to exit, \"help\" for a list of commands");

    while (!feof(stdin)) {
        printf("\n>>> "); fgets(cmd, max, stdin);
        cmd[strlen(cmd) - 1] = '\0'; // remove newline

        if (!strcmp(cmd, "help")) {
            puts("Available commands:");
            puts("--------CREATION----------");
            puts("note: the list starts as an empty list and may be modified");
            puts("sizeNList:        create a list of size N");
            puts("10:               shortcut for creating a size 10 list");
            puts("--------INSERTION---------");
            puts("append:           append an element to the end");
            puts("insert:           insert an element at a given index");
            puts("--------MODIFICATION---------");
            puts("swap:             switch the elements at two indicies");
            puts("sort:             sort the elements in place ###TO BE IMPLEMENTED");
            puts("reverse:          reverse the list in place");
            puts("--------DELETION----------");
            puts("removeIndex:      remove an element with a given index");
            puts("pop:              remove the last element");
            puts("removeElement:    remove an element with a given index");
            puts("removeRange:      remove elements in a range of indices (inclusive, exclusive)");
            puts("clear:            remove all elements");
            puts("--------RETRIEVAL----------");
            puts("get:              retrieve an element with a given index");
            puts("front:            get the element at the 0th index");
            puts("back:             get the element at the last index");
            puts("slice:            get the element in a range of indices (inclusive, exclusive)");
            puts("sliceWithStep:    get the element in a range of indices, with a step size (+/-)");
            puts("--------UTILITIES----------");
            puts("indexOf:          get the first index of a given element; -1 if not present");
            puts("lastIndexOf:      get the last index of a given element; -1 if not present");
            puts("contains:         1 if the list contains the given element");
            puts("count:            get the number of occurrences of a given element");
            puts("size:             get the total number of elements");
            puts("capacity:         get the total number of spaces available without resizing");
            puts("isEmpty:          1 if the list is empty, 0 otherwise");
            puts("printList:        prints the list's contents, size, and capacity to stdout");
            puts("--------MEMORY MANAGEMENT--");
            puts("trimToSize:       reduce the capacity to the size of the list");
            puts("ensureCapacity:   force the list's size to be >= a given capacity");
            puts("grow:             increases the capacity by the resize factor");
            puts("shrink:           makes the capacity equal to size * resize factor");
        }
        //else if (!strcmp(cmd, "sizeNList")) {
        //    printf("Size of list: "); scanf("%d", &arg1);
        //    cleanupList(list1);
        //    list1 = sizeNList(arg1);
        //    printList(list1);
        //}
        //else if (!strcmp(cmd, "10")) {
        //    cleanupList(list1);
        //    list1 = sizeNList(10);
        //    printList(list1);
        //}
        else if (!strcmp(cmd, "append")) {
            printf("Element: "); scanf("%d", &arg1);
            append(list1, arg1);
            printList(list1);
        }
        else if (!strcmp(cmd, "insert")) {
            printf("Index: ");   scanf("%d", &arg1);
            printf("Element: "); scanf("%d", &arg2);
            insert(list1, arg1, arg2);
            printList(list1);
        }
        else if (!strcmp(cmd, "removeIndex")) {
            printf("Index: "); scanf("%d", &arg1);
            removeIndex(list1, arg1);
            printList(list1);
        }
        else if (!strcmp(cmd, "pop")) {
            pop(list1);
            printList(list1);
        }
        else if (!strcmp(cmd, "removeElement")) {
            printf("Element: "); scanf("%d", &arg1);    
            removeElement(list1, arg1);
            printList(list1);
        }
        else if (!strcmp(cmd, "removeRange")) {
            printf("Start: "); scanf("%d", &arg1);
            printf("End: ");   scanf("%d", &arg2);
            removeRange(list1, arg1, arg2);
            printList(list1);
        }
        else if (!strcmp(cmd, "clear")) {
            clear(list1);
            printList(list1);
        }
        else if (!strcmp(cmd, "get")) {
            printf("Index: "); scanf("%d", &arg1);
            printf("%d", get(list1, arg1));
        }
        else if (!strcmp(cmd, "set")) {
            printf("Index: ");   scanf("%d", &arg1);
            printf("Element: "); scanf("%d", &arg2);
            set(list1, arg1, arg2);
            printList(list1);
        }
        else if (!strcmp(cmd, "swap")) {
            printf("Index1: "); scanf("%d", &arg1);
            printf("Index2: "); scanf("%d", &arg2);
            swap(list1, arg1, arg2);
            printList(list1);
        }
        else if (!strcmp(cmd, "front")) {
            printf("%d", front(list1));
        }
        else if (!strcmp(cmd, "back")) {
            printf("%d", back(list1));
        }
        else if (!strcmp(cmd, "slice")) {
            printf("Start: "); scanf("%d", &arg1);
            printf("End: ");   scanf("%d", &arg2);
            cleanupList(list2);
            list2 = slice(list1, arg1, arg2);
            printList(list2);
        }
        else if (!strcmp(cmd, "sliceWithStep")) {
            printf("Start: "); scanf("%d", &arg1);
            printf(  "End: "); scanf("%d", &arg2);
            printf( "Step: "); scanf("%d", &arg3);
            cleanupList(list2);
            list2 = sliceWithStep(list1, arg1, arg2, arg3);
            printList(list2);
        }
        else if (!strcmp(cmd, "indexOf")) {
            printf("Element: "); scanf("%d", &arg1);
            printf("%d", indexOf(list1, arg1));
        }
        else if (!strcmp(cmd, "lastIndexOf")) {
            printf("Element: "); scanf("%d", &arg1);
            printf("%d", lastIndexOf(list1, arg1));
        }
        else if (!strcmp(cmd, "contains")) {
            printf("Element: "); scanf("%d", &arg1);
            printf("%d", contains(list1, arg1));
        }
        else if (!strcmp(cmd, "count")) {
            printf("Element: "); scanf("%d", &arg1);
            printf("%d", count(list1, arg1));
        }
        else if (!strcmp(cmd, "size")) {
            printf("%d", size(list1));
        }
        else if (!strcmp(cmd, "capacity")) {
            printf("%d", capacity(list1));  
        }
        else if (!strcmp(cmd, "isEmpty")) {
            printf("%d", isEmpty(list1));
        }
        else if (!strcmp(cmd, "printList") || !strcmp(cmd, "print")) {
            // Print isn't a routine, just added for convenience
            printList(list1);
        }
        else if (!strcmp(cmd, "reverse")) {
            reverse(list1);
            printList(list1);
        }
        else if (!strcmp(cmd, "trimToSize")) {
            trimToSize(list1);
            printList(list1);
        }
        else if (!strcmp(cmd, "ensureCapacity")) {
            printf("Capacity: "); scanf("%d", &arg1);
            ensureCapacity(list1, arg1);
            printList(list1);
        }
        else if (!strcmp(cmd, "grow")) {
            grow(list1);
            printList(list1);
        }
        else if (!strcmp(cmd, "shrink")) {
            shrink(list1);
            printList(list1);
        }
        else if (!strcmp(cmd, "sort")) {
            //int(*compar)(const void *, const void *);
            //compar = &compareInts;
            sort(list1);
            printList(list1);
        }
    }

    cleanupList(list1);
    cleanupList(list2);
    return EXIT_SUCCESS;
}
