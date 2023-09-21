/*
  This is a function that handles the batteries percentage 
  and charging. Checking the charging to 10 times to make sure it was charging
  This also only checks the percentage every 20 sec. 
*/

#ifndef CSS_H
#define CSS_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

enum object_types{
  CIRCLE,
  RECTANGLE,
  R_RECTANGLE,
  TRIANGLE_0,
  TRIANGLE_90
};

typedef struct _button_info{
  String button_name;
  uint8_t button_name_size;
  uint16_t button_name_colour;
  uint16_t button_colour;
  uint16_t button_x;
  uint16_t button_y;
  uint16_t width;
  uint16_t height;
  object_types type;
}button_info;

class CSS
{
  public:

  private:

};

#endif