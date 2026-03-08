#ifndef DATATYPES_H
#define DATATYPES_H

#ifdef _WIN_64

#define NULL 0

#define FALSE 0
#define TRUE 1

typedef unsigned long long SIZE_T;

typedef void* PVOID;

typedef char CHAR8;
typedef char* PCHAR8;
typedef const char* CSTRING;

typedef signed char INT8;
typedef unsigned char UINT8;

typedef short INT16;
typedef unsigned short UINT16;

typedef int INT32;
typedef unsigned int UINT32;

typedef long long INT64;
typedef unsigned long long UINT64;

typedef float FLOAT32;

typedef double FLOAT64;

#endif // _WIN_64

#endif // !DATATYPES_H
