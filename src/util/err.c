#include "err.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



static Err_t* errLog[1024];
static int errCount = 0;



void logErr(Err_t* err,  const char* msg){
    if (errCount >= 1024){
        return;
    }

    errLog[errCount] = malloc(sizeof(Err_t));
    errLog[errCount]->eType = err->eType;
    strcpy(errLog[errCount]->msg, msg);
}


const char* CodeStrings[] = {
    "NONE",
    "FILE_NOT_FOUND",
    "OUT_OF_MEMORY",
};

void printErrLog(void){
    for (int i = 0; i < errCount; i++){
        Err_t* err = errLog[i];
        printf("Err type: %s\n Err msg: %s \n", CodeStrings[err->eType], err->msg);
    }
}