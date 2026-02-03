#ifndef __DIRECTOR_H__
#define __DIRECTOR_H__

#include "types.h"

extern Entities_t creatures;
extern Entities_t constructs;

void initDirector(GLFWwindow* window);

void update(void);

#endif