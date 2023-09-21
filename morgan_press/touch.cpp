#include <stdbool.h>
#include "touch.h"
#include <stdint.h>

bool is_pressed(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t px, uint16_t py){
  if ((px > x1 && px < x2) && (py > y1 && py < y2)){
    return true;
  }
  else{
    return false;
  }
}