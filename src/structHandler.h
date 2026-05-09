#ifndef STRUCTHANDLER_H
#define STRUCTHANDLER_H


extern const char* STRUCT_STRING;

extern const int MULTILINE_STRUCT;
extern const int ENDED_STRUCT;

int checkStruct(char*, char*, int, int);
int singleLineStruct(char*, char*, int, const char*, const char*);


#endif

