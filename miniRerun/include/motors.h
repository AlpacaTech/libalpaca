#ifndef MOTORS_H
#define MOTORS_H

#define TLEFT 2
#define BLEFT 3
#define TRIGHT 4
#define BRIGHT 5

void driveSet(unsigned int l, unsigned int r);
void leftSet(unsigned int l);
void rightSet(unsigned int r);

#endif
