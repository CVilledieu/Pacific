#ifndef __UTIL_ERR_H__
#define __UTIL_ERR_H__

typedef enum {
    E_NONE = 0,
    E_FILE_NOT_FOUND,
    E_OUT_OF_MEMORY,
} ErrCode;

// typedef enum {
//     ELVL_LOW,
//     ELVL_HIGH,
//     ELVL_CRIT,
// } ErrLevel;

typedef struct Err_t{
    char msg[256];
    ErrCode eType;
    void* rtnData;
} Err_t;

void logErr(Err_t* err,  const char* msg);

void printErrLog(void);

#endif