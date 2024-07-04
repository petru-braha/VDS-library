#pragma once
#include <stdio.h>
#include <stdlib.h>

#define ERROR_CODE -1

#define fatal_error(msg){printf("error: %s.\n", msg); exit(EXIT_FAILURE);}
#define strng_error(msg){printf("error: %s.\n", msg); throw(ERROR_CODE);}
#define error(msg){printf("error: %s.\n", msg);}