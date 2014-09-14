/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#ifndef __STRING_H
#define __STRING_H

#ifndef NULL
#define NULL 0
#endif

#ifndef __SIZE_T_DEF
#define __SIZE_T_DEF
typedef unsigned size_t;
#endif

void* memset(void*, int, size_t);
void* memcpy(void*, void*, size_t);
void* memmove(void*, void*, size_t);
char* memchr(char*, int, size_t);
int memcmp(void*, void*, size_t);

char* strcpy(char*, char*);
char* strncpy(char*, char*, size_t);
size_t strxfrm(char*, char*, size_t);
char* strcat(char*, char*);
char* strncat(char*, char*, size_t);
size_t strlen(char*);
char* strchr(char*, int);
char* strrchr(char*, int);
char* strstr(char*, char*);
size_t strspn(char*, char*);
size_t strcspn(char*, char*);
char* strpbrk(char*, char*);
char* strtok(char*, char*);
int strcmp(char*, char*);
int strncmp(char*, char*, size_t);
int strcoll(char*, char*);

char* strerror(int);
#endif
