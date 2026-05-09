#ifndef ENUMHANDLER_H
#define ENUMHANDLER_H

extern const char* ENUM_STRING;

extern const int MULTILINE_ENUM;
extern const int ENDED_ENUM;

int checkEnum(char*, char*, int, int);
int singleLineEnum(char*, char*, int);
int multiLineEnum(char*, char*, int);
char* getEnumName(char*);

#endif
