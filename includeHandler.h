#ifndef INCLUDEHANDLER_H
#define INCLUDEHANDLER_H
#include <stdio.h>

extern const char *INCLUDE_STRING;
extern const char *INCLUDE_TYPES[];



void import(char*, FILE*);
char *getImportName(char*);


#endif
