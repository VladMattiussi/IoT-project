#include <arduino.h>

/* private */
static int privateVar;

int myfunc(int x) {
  delay(1000);
  return x + 1;
}
