#include "main.h"

void driveSet(unsigned int l, unsigned int r) {
  motorSet(TLEFT, l * left.inverted);
  motorSet(BLEFT, l * left.inverted);
  motorSet(TRIGHT, r * right.inverted);
  motorSet(BRIGHT, r * right.inverted);
}
