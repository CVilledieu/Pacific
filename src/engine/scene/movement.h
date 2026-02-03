#ifndef __MOVEMENT_H__
#define __MOVEMENT_H__

void moveEntities(void);
void setXVelocity(int id, float force);
void setYVelocity(int id, float force);
void stopMovement(int id);
#endif