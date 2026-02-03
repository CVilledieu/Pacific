#ifndef __UTIL_ERROR_H__
#define __UTIL_ERROR_H__

typedef enum {
    E_SUCCESS = 0,
    E_FILE_NOT_FOUND,
    E_OUT_OF_MEMORY,
    ERROR_TYPE_COUNT,
} Err;

typedef struct Err_t{
    char msg[256];
    Err eType;
} Err_t;

// DevNote: Possible better option for type format
// type would use an id to prevent the log array from being filed with the same error.
// This would still allow me to keep track of the number of times the error occured. 
// ALt option 1.
// typedef struct Error_t {
//     int id;
//     int count;
//     char msg[256];
//     Err eType;
// } Error_t;

// Alt option 2.
// Enables only desired errors to be printed. 
// Hopefully faster search time if attempting to reduce logging duplicate Errs
// typedef struct ErrNode_t{
//     char msg[256];
//     char src[256];
//     int count;
//     ErrNode_t* nextNode;
// } ErrNode_t;

// typedef struct ErrorLog_t{
//     int count;
//     ErrNode_t arrayOfNodes[ERROR_TYPE_COUNT-1]; // enum index 0 = no error
// } ErrorLog_t;

void checkZeroValue(float value);

void logErr(Err err,  const char* msg);

void printErrLog(void);

#endif