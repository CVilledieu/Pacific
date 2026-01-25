#include "err.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



// Err_t* errLog[1024];
// static int errCount = 0;

// void critErrClose(void);
// void printErrLog(void);

// Error* newError(ErrCode type, const char* msg){
    
// }

// Err_t* newErr_t(ErrCode type, ErrLevel lvl, const char* msg){
//     if(type == E_NONE) return 0;

//     Err_t* err = malloc(sizeof(Err_t));
//     err->eType = type;
//     err->severity = lvl;

//     int index= 0;
//     while (*msg != '\0') {
//         err->msg[index] = *msg;
//         index++;
//         msg++;
//     }
//     errLog[errCount] = &err;

//     if(lvl == ELVL_CRIT){
//         critErrClose();
//     }
//     return &err;
// }


// void critErrClose(void){
//     printErrLog();
//     exit(1);
// }


// const char* CodeStrings[] = {
//     "NONE",
//     "FILE_NOT_FOUND",
//     "OUT_OF_MEMORY",
// };

// void printErrLog(void){
//     for (int i = 0; i < errCount; i++){
//         Err_t* err = &errLog[i];
//         fprintf("Err type: %s, Err severity: %d,\n Err msg: %s \n", CodeStrings[err->eType], err->severity, err->msg);
//     }
// }