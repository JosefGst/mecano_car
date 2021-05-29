#include "my_functions.h"

int limit (int value){ //limits value in range of -255 to +255
  if (value >= 255) return 255;
  else if (value <= -255) return -255;
  else return value;  
}
