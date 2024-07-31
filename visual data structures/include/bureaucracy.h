#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <ostream>

#define SZT_ERROR ULLONG_MAX
#define ERROR_CODE -1

#define fatal_error(msg){perror(msg); exit(ERROR_CODE);}
#define  hard_error(msg){perror(msg); throw(ERROR_CODE);}
#define  eazy_error(msg){perror(msg);}

#define FOR(n) for(size_t i = 0; i < n; i++)

typedef const size_t& szt;
typedef signed char bit;
typedef const char* text;
typedef signed long long loong;
