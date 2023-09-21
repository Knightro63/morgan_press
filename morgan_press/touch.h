/*
  This is a function that handles the batteries percentage 
  and charging. Checking the charging to 10 times to make sure it was charging
  This also only checks the percentage every 20 sec. 
*/

#ifndef TOUCH_H
#define TOUCH_H

#include <stdbool.h>
#include <stdint.h>

// #ifdef __cplusplus
//  extern "C" {
// #endif

extern bool is_pressed(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t px, uint16_t py);

// #ifdef __cplusplus
// }
// #endif

#endif