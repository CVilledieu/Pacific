#include "error.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static Err_t errLog[1024];
static int errCount = 0;



void logErr(Err err,  const char* msg){
    if (errCount >= 1024){
        return;
    }

    errLog[errCount].eType = err;
    strcpy(errLog[errCount].msg, msg);
}


const char* CodeStrings[] = {
    "NONE",
    "FILE_NOT_FOUND",
    "OUT_OF_MEMORY",
};

void printErrLog(void){
    for (int i = 0; i < errCount; i++){
        printf("Err type: %s\n Err msg: %s \n", CodeStrings[errLog[i].eType], errLog[i].msg);
    }
}

void checkZeroValue(float value){
    if (value == 0){
        printf("Zero Value");
    }
}