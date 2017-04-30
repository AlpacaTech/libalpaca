#ifndef SENSORS_H
#define SENSORS_H
#include "main.h"

typedef struct {
  Encoder self;
  unsigned char ports[2];
  long zero;
  int8_t inverted;
  void(*reset)();
  long(*value)();
  float request;
} quad;

quad left;
quad right;

void quadInit();

#endif
