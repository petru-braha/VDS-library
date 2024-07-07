#pragma once
#include <stdio.h>
#include <stdlib.h>

#define ERROR_CODE -1

#define fatal_error(msg){perror(msg); exit(EXIT_FAILURE);}
#define  hard_error(msg){perror(msg); throw(ERROR_CODE);}
#define  eazy_error(msg){perror(msg);}

enum
{
	bubble_sort,
	selection_sort,
	insertion_sort,

	merge_sort,
	heap_sort,
	quick_sort
};

#define FOR(n) for(size_t i = 0; i < n; i++)

// to be considered as global header