/*
file: List.h
author: Zach Lauzon (zrl3031@rit.edu)
description: header file for a Python-like List, implemented as a dynamic array
TODO: Sort, awesome documentation
*/

#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "ListConfig.h"

// The initial capacity that the list defaults to
#define DEFAULTCAPACITY 10
// The factor by which the list grows 
// (e.g. newCapacity = oldCapacity * resizeFactor)
#define RESIZEFACTOR 2

// The type of the list's data (should be able to change without effect)
#include "ListConfig.h"
typedef ListType type;

typedef struct {
	int size;		// The number of elements present in the list
	int capacity;	// The number the size can grow to without resizing
	type* data;		// A pointer to the array of data contained in the list
	int (*cmp) (const void*, const void*); // Comparison function (optional)
	char* (*print) (const void* element); // Print function (optional)
} List;

///////////////////////////////////////////////////////////////////////////////
///////////// Constructors ////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/* Initialize a list with the default capacity */
List* makeList();

/* Initialize a list with an initial capacity */
List* makeListWithCapacity();

/* Sets the comparison function */
void setCmpFun(List* list, int (const void*, const void*));

/* Sets the print function */
void setPrintFun(List* list, char* (const void*));

/* Initialize a list with values equal to their indices (only works when type
is integers */
List* sizeNList(int n);

///////////////////////////////////////////////////////////////////////////////
///////////// Insertion ///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Note: these functions should call grow() if the list becomes full

/* Appends an element to the end of the list */
void append(List* list, type element);

/* Appends the contents of source to destination */
void appendList(List* destination, List* source);

/* Inserts an element at a specific index */
void insert(List* list, int index, type element);

/* Inserts the contents of source to destination at the specified index */
void insertList(List* destination, int index, List* source);

///////////////////////////////////////////////////////////////////////////////
///////////// Deletion ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Note: these functions should call shrink() if the list becomes more than
// half empty

/* Remove an element at a specific index of the list */
void removeIndex(List* list, int index);

/* Remove the last element from the list */
void pop(List* list);

/* Remove the first instance of an element from the list, if it exists */
/* If the list contained the element, returns 1, 0 otherwise */
int removeElement(List* list, type element);

/* Remove elements between start (inclusive) to end (exclusive) 
from the list */
void removeRange(List* list, int start, int end);

/* Makes all elements of the list inaccessible, resizing if necessary */
void clear(List* list);

/* Reduces the size of the list, resizing if necessary */
void reduceSize(List* list);

///////////////////////////////////////////////////////////////////////////////
///////////// Access / Retrieval //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/* Return a single element of a list */
type get(List* list, int index);

/* Replaces the value at the specified index with the specified element 
NOTE: crash if outside capacity, but what about index > size && < capacity?*/
void set(List* list, int index, type element);

/* Swaps the element at index1 with the element at index2 */
void swap(List* list, int index1, int index2);

/* Return the first element */
type front(List* list);

/* Return the last element */
type back(List* list);

/* Copy a specific section of the source list, from start (inclusive) to end
(exclusive) and return a pointer to a List containing that data*/
List* slice(List* list, int start, int end);

/* Same as slice, but uses a step (e.g. 1 = every element, 2 = every other,
-1 every element backward, etc.). Step must not be zero. */
List* sliceWithStep(List* list, int start, int end, int step);

/* Returns the first index of a given element, or -1 if not in the list */
int indexOf(List* list, type element);

/* Returns the last index of a given element, or -1 if not in the list */
int lastIndexOf(List* list, type element);

/* Return true if the list contains the specified elmakement */
int contains(List* list, type element);

/* Returns the number of occurrences of element in the list */
int count(List* list, type element);

///////////////////////////////////////////////////////////////////////////////
///////////// Utilities ///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/* Exits and prints a debug message if the comparison function is null */
/* @param fun the name of the function that will be called afterward */
void checkCmpFun(List* list, char* fun);

/* Exits and prints a debug message if the print function is null */
void checkPrintFun(List* list);

/* Returns the number of elements in the list */
int size(List* list);

/* Returns capacity of list; internal use only */
int capacity(List* list);

/* Returns whether the list is empty */
int isEmpty(List* list);

/* Returns 1 if both lists size, capacity, and data are equivalent */
int equals(List* list1, List* list2);

/* Returns 1 if the data contained in the array given is equal to the data in
the list. Note: the array must be as large as the list's size. */
int equalsArray(List* list, type* arr);

/* Returns a string representing the list */
/* Make this also take a function pointer to the element's toString */
char* toString(List* list);

/* Returns a pointer to an array containing the data from index 0 to size of the list */
type* toArray(List* list);

/* Returns a list containing the data contained in the array */
List* arrayToList(type* arr, int nmemb);

/* Prints the contents of the list to stdout */
/* make this take a function pointer! that we we can call each element's tostring method */
void printList(List* list);

/* Sorts the list in place */
/* make this take a function pointer to a comparison function (they can control order of sorting) */
/* by using different comparison functions. this wall call qsort */
void sort(List* list);

/* Reverses the list in place */
void reverse(List* list);

///////////////////////////////////////////////////////////////////////////////
///////////// Memory management ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/* Trim the capacity of list to the current size 
Equivalent to reassigning list to copyList */
void trimToSize(List* list);

/* Ensures that the current capacity of the list is greater than or equal to 
minCapacity, resizing if necessary */
void ensureCapacity(List* list, int minCapacity);

/* Deep copy a list and return a pointer to the copy 
equivalent to copyListWithCapacity with newCapacity = old size */
List* copyList(List* list);

/* Deep copy a list using newCapacity and return a pointer to the copy 
newCapacity must be >= old list's size*/
List* copyListWithCapacity(List* list, int newCapacity);

/* Increase the capacity of the list by the resize factor; internal use only */
void grow(List* list);

/* Increase the size of the list by the resize factor; internal use only */
void capacityToFactor(List* list, float factor);

/* Decrease the capacity of the list to half its size; internal use only
Note: won't have any effect if reducing the capacity would harm the list */
void shrink(List* list);

/* Delete a list, freeing all memory allocated to it */
void cleanupList(List* list);

#ifdef POINTERS
/* Delete a list, calling the given function on each slot */
void cleanupListFun(List* list, void (*fun)(void*));
#endif

#endif
