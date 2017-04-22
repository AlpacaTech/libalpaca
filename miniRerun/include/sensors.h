#include "main.h"

typedef struct {
  Encoder self;
  unsigned char ports[2];
  long zero;
  bool inverted;
  void(*reset)();
  long(*value)();
} quad;

quad left;
quad right;

void quadInit();
