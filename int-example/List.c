
/*
file: List.c
author: Zach Lauzon (zrl3031@rit.edu)
description: implementation for a Python-like List, implemented as a dynamic array
*/

#include "List.h"
#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////
///////////// Constructors ////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

List* makeList() {
	List* list = (List*) malloc(sizeof(List));
	if (!list) {
		fprintf(stderr, "Malloc failed in makeList\n");
		exit(EXIT_FAILURE);
	}
	list->size = 0;
	list->capacity = DEFAULTCAPACITY;
	list->data = (type*) malloc(sizeof(type*) * list->capacity);
	if (!list->data) {
		fprintf(stderr, "Malloc failed in makeList\n");
		free(list);
		exit(EXIT_FAILURE);
	}
	return list;
}

List* makeListWithCapacity(int capacity) {
	List* list = (List*) malloc(sizeof(List));
	if (!list) {
		fprintf(stderr, "Malloc failed in makeListWithCapacity\n");
		exit(EXIT_FAILURE);
	}
	list->size = 0;
	list->capacity = capacity;
	list->data = (type*) malloc(sizeof(type*) * list->capacity);
	if (!list->data) {
		fprintf(stderr, "Malloc failed in makeListWithCapacity\n");
		free(list);
		exit(EXIT_FAILURE);
	}
	return list;
}

void setCmpFun(List* list, int cmp (const void*, const void*)) {
	list->cmp = cmp;
}

void setPrintFun(List* list, char* print (const void*)) {
	list->print = print;
}

///////////////////////////////////////////////////////////////////////////////
///////////// Insertion ///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void append(List* list, type element) {
	if (list->size >= list->capacity) {
		grow(list);
	}
	list->data[list->size] = element;
	++(list->size);	
}

void appendList(List* dest, List* src) {
	for (int i = 0; i < src->size; ++i) {
		append(dest, get(src, i));
	}
}

void insert(List* list, int index, type element) {
	if (index >= 0 && index <= list->size) {
		type temp;
		for (int i = index; i < list->size; ++i) {
			temp = list->data[i];
			list->data[i] = element;
			element = temp;
		}
		append(list, element);
	}
	else {
		fprintf(stderr, "Invalid index for insert: %i for list of size %i\n",
		index, list->size);
		cleanupList(list);
		exit(EXIT_FAILURE);
	}
}

void insertList(List* dest, int index, List* src) {
	if (dest >= 0 && index <= dest->size) {
		int tempIndex = index;
		//fprintf(stderr, "entering insertList index = %i\n", index);
		ensureCapacity(dest, dest->size + src->size);
		// temp array will hold overwritten values from dest array 
		type temp[dest->size + 1];
		// as we copy values from src to dest, save temp values
		// runs to end of dest to get all data
		int i = 0;
		for ( ; index <= dest->size; ++index) {
			//fprintf(stderr, "in first for loop,  i = %i, index = %i\n", i, index);
			temp[i] = dest->data[index];
			if (i < src->size) {
				//fprintf(stderr, "copying value %i from src to dest\n",src->data[i]);
				dest->data[index] = src->data[i];
			}
			++i;
		} 

		// for the case that we reached the end of the dest array prematurely,
		// we must copy the rest of the source data over
		if ( i != dest->size) {
			for ( ; i < src->size; ++i) {
				dest->data[index] = src->data[i];
				++index;
			}
		}

		// reset index to where we start to copy over temporary values
		index = tempIndex + src->size;
		// fill in remainder of array using temporary values
		i = 0;
		for ( ; index < dest->size + src->size; ++index) {
			//fprintf(stderr, "in second for loop, i = %i, index = %i\n", i, index);
			dest->data[index] = temp[i];
			++i;
		}
		// increment the number of values we added
		dest->size += src->size;
	}
	else {
		//fprintf(stderr, "Invalid index for insertList for size %i list: %i\n",
		//	index, dest->size);
		cleanupList(dest);
		cleanupList(src);
		exit(EXIT_FAILURE);
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////// Deletion ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void removeIndex(List* list, int index) {
	if (index >= 0 && index < list->size) {
		for ( ; index < list->size - 1; ++index) {
			list->data[index] = list->data[index + 1];
		}
		reduceSize(list);
	}
	else {
		fprintf(stderr, "Invalid index for removeIndex for size %i list: %i\n", 
			list->size, index);
		cleanupList(list);
		exit(EXIT_FAILURE);
	}
}

void pop(List* list) {
	if (list->size > 0) {
		reduceSize(list);
	}
	else {
		fprintf(stderr, "Pop from empty list\n");
		cleanupList(list);
		exit(EXIT_FAILURE);
	}
}

int removeElement(List* list, type element) {
	int index = indexOf(list, element);
	if (index >= 0) {
		removeIndex(list, index);
		// Check if realloc is in order
		if (list->size * RESIZEFACTOR < list->capacity) {
			capacityToFactor(list, (float) RESIZEFACTOR);
		}
		return 1;
	}
	else {
		return 0;
	}
}

void removeRange(List* list, int start, int end) {
	if (start >= 0 && end <= list->size && end >= start) {
		// Copy over data into now invalid spots
		for (int i = 0; end + i < list->size; ++i) {
			list->data[start + i] = list->data[end + i];
		}
		// Reduce list's size accordingly
		list->size -= end - start;
		// Check if realloc is in order
		if (list->size * RESIZEFACTOR < list->capacity) {
			capacityToFactor(list, (float) RESIZEFACTOR);
		}
	}
	else {
		fprintf(stderr, "Invalid indicies for removeRange: %i and %i\n", start, end);
		cleanupList(list);
		exit(EXIT_FAILURE);
	}
}

void clear(List* list) {
	list->size = 0;
	trimToSize(list);
}

inline void reduceSize(List* list) {
	--(list->size);
	if (list->size * RESIZEFACTOR < list->capacity) {
		capacityToFactor(list, (float) RESIZEFACTOR);
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////// Access / Retrieval //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

type get(List* list, int index) {
	if (index >= 0 && index < list->size) {
		return list->data[index];
	}
	else {
		fprintf(stderr, "Invalid index for get: %i for list of size %i\n",
			index, list->size);
		cleanupList(list);
		exit(EXIT_FAILURE);
	}
}

void set(List* list, int index, type element) {
	if (index >= 0 && index < list->size) {
		list->data[index] = element;
	}
	else {
		fprintf(stderr, "Invalid index for set: %i for list of size %i\n",
			index, list->size);
		cleanupList(list);
		exit(EXIT_FAILURE);
	}
}

void swap(List* list, int index1, int index2) {
	if (index1 >= 0 && index2 >= 0 && 
	index1 < list->size && index2 < list-> size) {
		type temp = list->data[index1];
		list->data[index1] = list->data[index2];
		list->data[index2] = temp;
	}
	else {
		fprintf(stderr, "Invalid indices for swap: %i, %i for list of size %i\n",
			index1, index2, list->size);
		cleanupList(list);
		exit(EXIT_FAILURE);
	}
}

type front(List* list) {
	if (list->size > 0) {
		return list->data[0];
	}
	else {
		fprintf(stderr, "Front of empty list\n");
		cleanupList(list);
		exit(EXIT_FAILURE);
	}
}


type back(List* list) {
	if (list->size > 0) {
		return list->data[list->size - 1];
	}
	else {
		fprintf(stderr, "Back of empty list\n");
		cleanupList(list);
		exit(EXIT_FAILURE);
	}
}


List* slice(List* list, int start, int end) {
	if (end >= start && start >= 0 && end <= list->size) {
		List* newList = makeListWithCapacity(end - start);
		for ( ; start < end; ++start) {
			newList->data[newList->size] = list->data[start];
			++(newList->size);	
		}
		return newList;
	}
	else {
		return makeListWithCapacity(0);
	}
}

List* sliceWithStep(List* list, int start, int end, int step) {
	if (step) {
		if (start >= 0 && end >= -1 && 
		end <= list->size && start < list->size &&
		((step > 0 && start <= end) || (step < 0 && start >= end))) {
			List* newList;
			
			// Backwards or forwards? 
			if (step > 0) {
				// Round to nearest capacity
				float modifier = (step - 0.5);
				newList = makeListWithCapacity((int) ((modifier + end - start) / step));
				for ( ; start < end; start+=step) {
					newList->data[newList->size] = 
						list->data[start];
					++(newList->size);	
				}
			}
			else {
				// Round to nearest capacity (and we mustn't forget that step is negative)
				float modifier = (step + 0.5);
				if (modifier < 0) {
					modifier *= -1;
				}
				newList = makeListWithCapacity((int) (((modifier + start - end) / step)) * -1);
				for ( ; start > end; start+=step) {
					newList->data[newList->size] = 
						list->data[start]; 
					++(newList->size);	
				}
			}
			return newList;
		}
		else {
			return makeListWithCapacity(0);
		}
	}
	else {
		fprintf(stderr, "Slice step cannot be zero");
		cleanupList(list);
		exit(EXIT_FAILURE);
	}
}

int indexOf(List* list, type element) {
	if (list->cmp == NULL) {
		fprintf(stderr, "Cannot get indexOf: comparison function not defined\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < list->size; ++i) {
		if (list->cmp((const void*) &list->data[i], (const void*) &element) == 0) {
			return i;
		}
	}
	return -1;
}

int lastIndexOf(List* list, type element) {
	for (int i = list->size - 1; i >= 0; --i) {
		if (list->cmp((const void*) &list->data[i], (const void*) &element) == 0) {
			return i;
		}
	}
	return -1;
}

int contains(List* list, type element) {
	for (int i = 0; i < list->size; ++i) {
		if (list->cmp((const void*) &list->data[i], (const void*) &element) == 0) {
			return 1;
		}
	}
	return 0;
}

int count(List* list, type element) {
	int count = 0;
	for (int i = 0; i < list->size; ++i) {
		if (list->cmp((const void*) &list->data[i], (const void*) &element) == 0) {
			++count;
		}
	}
	return count;
}

///////////////////////////////////////////////////////////////////////////////
///////////// Utilities ///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int size(List* list) {
	return list->size;
}

int capacity(List* list) {
	return list->capacity;
}

int isEmpty(List* list) {
	return list->size == 0;
}

int equals(List* list1, List* list2) {
	if (list1->size != list2->size || list1->capacity != list2->capacity) {
		return 0;
	}
	for (int i = 0; i < list1->size; ++i) {
		if (list1->cmp((const void*) &list1->data[i],
		               (const void*) &list2->data[i]) != 0) {
			return 0;
		}
	}
	return 1;
}

int equalsArray(List* list, type* arr) {
	for (int i = 0; i < list->size; ++i) {
		if (list->cmp((const void*) &list->data[i], 
			          (const void*) &arr[i]) != 0) {
			return 0;
		}
	}
	return 1;
}

type* toArray(List* list) {
	type* arr = malloc(sizeof(type) * list->size);
	for (int i = 0; i < list->size; ++i) {
		arr[i] = list->data[i];
	}
	return arr;
}

List* arrayToList(type* arr, int nmemb) {
	List* list = makeListWithCapacity(nmemb);
	for (int i = 0; i < nmemb; ++i) {
		list->data[i] = arr[i];
	}
	list->size = nmemb;
	return list;
}

void printList(List* list) {
	if (list->print == NULL) {
		fprintf(stderr, "Cannot print without print function (use setPrintFun)\n");
		cleanupList(list);
		exit(EXIT_FAILURE);
	}

	printf("[");
	for (int i = 0; i < list->size; ++i) {
		if (i == list->size - 1) {
			printf("%s",   list->print((void*) &list->data[i]));
		}
		else {
			printf("%s, ", list->print((void*) &list->data[i])); 
		}
	}
	printf("]\nsize: %i\ncapacity: %i\n", list->size, list->capacity);
}

void sort(List* list) {
	if (list->cmp == NULL) {
		fprintf(stderr, "Cannot sort without comparison function (use setCmpFun)\n");
		cleanupList(list);
		exit(EXIT_FAILURE);
	}
	qsort(list->data, (size_t) list->size,
 	(size_t) sizeof(list->data[0]), list->cmp);
	
}

void reverse(List* list) {
	for (int i = 0; i < (int) (list->size / 2); ++i) {
		type temp = list->data[i];
		list->data[i] = list->data[list->size - 1 - i];
		list->data[list->size - 1 - i] = temp;
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////// Memory management ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void trimToSize(List* list) {
	// Avoid pointless reallocs
	if (list->size == list->capacity) {
		return;
	}
	type* newData;
	if (list->size > 0) {
		newData = (type*) realloc(list->data, sizeof(type) * list->size);
	}
	else {
		// If size is 0, realloc to capacity of 1
		newData = (type*) realloc(list->data, sizeof(type));
	}

	if (newData != NULL) {
		list->data = newData;
		if (list->size > 0) {
			list->capacity = list->size;
		}
		else {
			list->capacity = 1;
		}
	}
	else {
		//Realloc failed (not enough mem) - must deal with error here!
		fprintf(stderr, "System ran out of memory for realloc, exiting.");
		cleanupList(list);
		exit(EXIT_FAILURE);
	}
}
void ensureCapacity(List* list, int minCapacity) {
	if (list->capacity < minCapacity) {
		type* newData = (type*) realloc(list->data,
		sizeof(type) * minCapacity);

		if (newData != NULL) {
			list->data = newData;
			list->capacity = minCapacity;
		}
		else {
			//Realloc failed (not enough mem) - must deal with error here!
			fprintf(stderr, "System ran out of memory for realloc, exiting.");
			cleanupList(list);
			exit(EXIT_FAILURE);
		}
	}
}

List* copyList(List* list) {
	List* newList = makeListWithCapacity(list->size);
	for ( ; newList->size < list->size; ++(newList->size)) {
		newList->data[newList->size] = list->data[newList->size];
	}
	return newList;
}

List* copyListWithCapacity(List* list, int newCapacity) {
	if (newCapacity >= list->size) {
		List* newList = makeListWithCapacity(newCapacity);
		for ( ; newList->size < list->size; ++(newList->size)) {
			newList->data[newList->size] = list->data[newList->size];
		}
		return newList;
	}
	else {
		fprintf(stderr, "Invalid capacity %i for copy of size %i list", 
			newCapacity, list->size);
		cleanupList(list);
		exit(EXIT_FAILURE);
	}
}

void grow(List* list) {
	type* newData = (type*) realloc(list->data,
		sizeof(type) * list->capacity * RESIZEFACTOR );

	if (newData != NULL) {
		list->data = newData;
		list->capacity = list->capacity * RESIZEFACTOR;
	}
	else {
		//Realloc failed (not enough mem) - must deal with error here!
		fprintf(stderr, "System ran out of memory for realloc, exiting.");
		cleanupList(list);
		exit(EXIT_FAILURE);
	}
}

// Reallocs such that capacity is some factor >= 1 of size (e.g. factor of
// 2 indicates that the capacity is 2*size)
void capacityToFactor(List* list, float factor) {
	type* newData;
	if (list->size > 0) {
		// Round up just in case floating point multiplication screwed us over
		newData = (type*) realloc(list->data, 
			sizeof(type) * (int)(list->size * factor + 0.5));
	}
	else {
		// If size = 0, realloc to hold one element
		newData = (type*) realloc(list->data, 
			sizeof(type) * (int)(factor + 0.5));
	}
	


	if (newData != NULL) {
		list->data = newData;

		if (list->size > 0) {
			list->capacity = (int) (list->size * factor + 0.5);	
		}
		else {
			list->capacity = (int) (factor + 0.5);
		}
	}
	else {
		//Realloc failed (not enough mem) - must deal with error here!
		fprintf(stderr, "System ran out of memory for realloc, exiting.");
		cleanupList(list);
		exit(EXIT_FAILURE);
	}
}

void shrink(List* list) {
	type* newData;
	if (list->size > 0) {
		newData = (type*) realloc(list->data,
			sizeof(type) * list->size * RESIZEFACTOR );
	}
	else {
		newData = (type*) realloc(list->data,
			sizeof(type) * RESIZEFACTOR );
	}

	if (newData != NULL) {
		list->data = newData;

		if (list->size > 0) {
			list->capacity = list->size * RESIZEFACTOR;
		}
		else {
			list->capacity = RESIZEFACTOR;
		}
	}
	else {
		//Realloc failed (not enough mem) - must deal with error here!
		fprintf(stderr, "System ran out of memory for realloc, exiting.");
		cleanupList(list);
		exit(EXIT_FAILURE);
	}
}

void cleanupList(List* list) {
	free(list->data);
	free(list);
}
