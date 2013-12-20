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

// This file contains the type of the data the list will store (as ListType)
#include "ListConfig.h"
typedef ListType type;

typedef struct {
    int size;       // The number of elements present in the list
    int capacity;   // The number the size can grow to without resizing
    type* data;     // A pointer to the array of data contained in the list
    int (*cmp) (const void*, const void*); // Comparison function (optional)
    char* (*print) (const void* element); // Print function (optional)
} List;

///////////////////////////////////////////////////////////////////////////////
///////////// Constructors ////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/** Initialize a list with the default capacity.
  * 
  * @return a pointer to the newly allocated List
  */
List* makeList();

/** Initialize a list with the specified capacity.
  * 
  * @param capacity the capacity for the list to begin with
  * @return a pointer to the newly allocated List
  */
List* makeListWithCapacity(int capacity);

/** Sets the comparison function that the list will use. Only necessary if 
  * functions like sort, count, indexOf, etc. will be called.
  * 
  * @param int (const void*, const void*) - the comparison function that will
  *     be used to compare elements in the list. It should return -1, 0, 1, if
  *     the the first element is less than, equal to, or greater than the 
  *     second, respectively.
  */
void setCmpFun(List* list, int (const void*, const void*));

/** Sets the comparison function that the list will use. Only necessary if
  * printList will be called.
  * 
  * @param char* (const void*) - the function that will called on each element
  *      contained within the list, which should return a C string
  *      representation of that element.
  */
void setPrintFun(List* list, char* (const void*));

/** Initialize a list with values equal to their indices (only works when type
  * is int).
  * 
  * @param n the size of the list to create
  * @return a pointer to the newly allocated list
  */
List* sizeNList(int n);

///////////////////////////////////////////////////////////////////////////////
///////////// Insertion ///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/// All insertion routines will cause a realloc if the list's size meets its
/// capacity, multiplying the capacity by RESIZEFACTOR.

/** Appends an element to the end of the list.
  * 
  * @param list the list to append to
  * @param element the element to append
  */
void append(List* list, type element);

/** Appends each element of the source list to the destination list.
  * 
  * @param destination the list to append to
  * @param source the list to retrieve elements from
  */
void appendList(List* destination, List* source);

/** Inserts an element at the specified index.
  * 
  * @param list the list to insert into
  * @param index the index to insert at
  * @param element the element to insert
  * @pre 0 <= index <= size(list)
  */
void insert(List* list, int index, type element);

/** Inserts each element of the source list into the destination list at the 
  * specified index.
  * 
  * @param destination the list to insert into
  * @param index the index to insert at
  * @param source the list to retrieve elements from
  * @pre 0 <= index <= size(list)
  */
void insertList(List* destination, int index, List* source);

///////////////////////////////////////////////////////////////////////////////
///////////// Deletion ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/// For all deletion functions, if the POINTERS flag in ListConfig.h is set,
/// the element(s) being deleted will be freed prior to their removal.
/// They will also cause a realloc if less than (1 / RESIZEFACTOR) of the
/// list's capacity is occupied, such that (1 / RESIZEFACTOR) is occupied.

/** Remove the element at the specified index of the list.
  * 
  * @param list the list to remove an element from
  * @param index the index to remove
  * @pre 0 <= index < size(list)
  */
void removeIndex(List* list, int index);

/** Remove the last element from the list.
  * 
  * @param list the list to pop from
  */
void pop(List* list);

/** Removes the first instance of an element from the list, if it exists.
  * 
  * @param list the list to remove the element from
  * @param element the element to remove 
  * @return 1 on success, 0 on failure (the element was not found)
  */
int removeElement(List* list, type element);

/** Removes all elements between start (inclusive) to end (exclusive).
  * 
  * @param list the list to remove elements from
  * @param start the beginning of the range to remove (inclusive)
  * @param end the end of the range to remove (exclusive)
  */
void removeRange(List* list, int start, int end);

/** Removes all of the elements from the list.
  *
  * @param list the list to remove every element from
  */
void clear(List* list);

/** Reduces the size of the list by one, causing a realloc if necessary.
  * (internal use only)
  *
  * @param list the list whose size shall be reduced
  */
void reduceSize(List* list);

///////////////////////////////////////////////////////////////////////////////
///////////// Access / Retrieval //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/** Return the element at the specified index of the list.
  *
  * @param list the list to retrieve an element from
  * @param index the index to return
  * @return the element at the given index
  * @pre 0 <= index < size(list)
  */
type get(List* list, int index);

/** Replaces the value at the specified index with the given element.
  * TODO: should this free the element that was replaced if POINTERS is set?
  *
  * @param list the list to modify 
  * @param index the index to change
  * @param element the element to set the index to
  * @pre 0 <= index < size(list)
  */
void set(List* list, int index, type element);

/** Swaps the element at index1 with the element at index2.
  *
  * @param list the list to modify 
  * @param index1 the first index to change
  * @param index2 the second index to change
  * @pre 0 <= index1 < size(list)
  * @pre 0 <= index2 < size(list)
  */
void swap(List* list, int index1, int index2);

/** Return the first element of the list (at the 0th index).
  *
  * @param list the list to retrieve an element from
  * @return the element at the 0th index of the list
  * @pre size(list) > 0
  */
type front(List* list);

/** Return the last element of the list (at the size(list) - 1th index).
  *
  * @param list the list to retrieve an element from
  * @return the element at the last index of the list
  * @pre size(list) > 0
  */
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
