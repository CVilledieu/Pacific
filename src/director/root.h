#ifndef __DIRECTOR_ROOT_H__
#define __DIRECTOR_ROOT_H__

typedef struct Director_t {
    unsigned int PID;
    unsigned int VAO;
} Director_t;

void initDirector(void);
#endif