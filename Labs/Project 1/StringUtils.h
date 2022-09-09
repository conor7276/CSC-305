#ifdef STRING_UTILS_H
#define STRING_UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const char NULL_CHAR = '\0';
int compareString(const char* OneStr, const char* OtherStr);
int find_length(const char* s);
int max_length(const char* OneStr, const char* OtherStr);
void concatenateString(char * destStr, const char* sourceStr);
void copyString(char * destStr, const char* sourceStr);
#endif
