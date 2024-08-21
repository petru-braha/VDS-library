#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <ostream>

#define SZT_ERROR ULLONG_MAX
#define ERROR_CODE -1

std::ofstream log_file("stderr log.txt");
#define print_error(msg) { log_file << msg << '\n'; }

#define fatal_error(msg) { print_error(msg); exit(ERROR_CODE); }
#define  hard_error(msg) { print_error(msg); throw(ERROR_CODE); }
#define  eazy_error(msg) { print_error(msg); }

#define FOR(n) for(size_t i = 0; i < n; i++)

typedef const size_t& szt;
typedef signed char bit;
typedef const char* text;
typedef signed long long loong;
