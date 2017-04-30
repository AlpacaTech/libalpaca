#include "main.h"

void driveSet(int l, int r) {
  motorSet(TLEFT, l * left.inverted);
  motorSet(BLEFT, l * left.inverted);
  motorSet(TRIGHT, r * right.inverted);
  motorSet(BRIGHT, r * right.inverted);
}

void leftSet(int l) {
  motorSet(TLEFT, l * left.inverted);
  motorSet(BLEFT, l * left.inverted);
}

void rightSet(int r) {
  motorSet(TRIGHT, r * right.inverted);
  motorSet(BRIGHT, r * right.inverted);
}
