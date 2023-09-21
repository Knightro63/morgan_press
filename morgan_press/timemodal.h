/*
  This is a function that handles the batteries percentage 
  and charging. Checking the charging to 10 times to make sure it was charging
  This also only checks the percentage every 20 sec. 
*/

#ifndef TIMEMODAL_H
#define TIMEMODAL_H

#include <stdbool.h>
#include <stdint.h>
#include <LCDWIKI_KBV.h> //Hardware-specific library
#include "css.h"
#include "colors.h"
#include <string.h>

#define BUTTON_R 35
#define BUTTON_SPACING_X 20
#define BUTTON_SPACING_Y 10
#define EDG_Y 10
#define EDG_X 20

class TIMEMODAL
{
  public:
    uint16_t setTime = 0;

    TIMEMODAL(LCDWIKI_KBV&);
    bool loop(uint16_t px, uint16_t py);
    void reset();

  private:
    bool done = false;
    bool justOpened = true;
    uint16_t text_x = 7;
    uint16_t text_y = 10;
    uint16_t n = 0;
    button_info phone_button[12];
    uint16_t text_x_add = 0;
    uint16_t text_y_add = 0;

    LCDWIKI_KBV *my_lcd;
    COLOR Color;

    void show_input(void);
    void setup(void);
    void show_string(String str, int16_t x, int16_t y, uint8_t csize, uint16_t fc, uint16_t bc, bool mode);
};

#endif