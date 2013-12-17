#ifndef CONFIG_H
#define CONFIG_H

struct ListStruct {
	int x;
	float y;
};

// Whatever type you use, make sure to typedef it to ListType
typedef struct ListStruct* ListType;

// Uncomment the next line if your List holds pointers that need to be freed
// when cleaning up memory
#define POINTERS

#endif
