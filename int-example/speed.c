/*
file: List.c
author: Zach Lauzon (zrl3031@rit.edu)
description: speed test
*/

#include "List.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	List* list = makeList();

	for (int i = 0; i < 100000; ++i) {
		append(list, i);
	}

	cleanupList(list);

	return EXIT_SUCCESS;
}