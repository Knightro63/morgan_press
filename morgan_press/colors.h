/*
  This is a function that handles the batteries percentage 
  and charging. Checking the charging to 10 times to make sure it was charging
  This also only checks the percentage every 20 sec. 
*/

#ifndef COLOR_H
#define COLOR_H

#include <stdbool.h>
#include <stdint.h>

/*  r     g    b */
#define BLACK        0x0000  /*   0,   0,   0 */
#define BLUE         0x001F  /*   0,   0, 255 */
#define RED          0xF800  /* 255,   0,   0 */
#define GREEN        0x07E0  /*   0, 255,   0 */
#define CYAN         0x07FF  /*   0, 255, 255 */
#define MAGENTA      0xF81F  /* 255,   0, 255 */
#define YELLOW       0xFFE0  /* 255, 255,   0 */
#define WHITE        0xFFFF  /* 255, 255, 255 */
#define NAVY         0x000F  /*   0,   0, 128 */
#define DARKGREEN    0x03E0  /*   0, 128,   0 */
#define DARKCYAN     0x03EF  /*   0, 128, 128 */
#define MAROON       0x7800  /* 128,   0,   0 */
#define PURPLE       0x780F  /* 128,   0, 128 */
#define OLIVE        0x7BE0  /* 128, 128,   0 */
#define LIGHTGREY    0xC618  /* 192, 192, 192 */
#define DARKGREY     0x7BEF  /* 128, 128, 128 */
#define ORANGE       0xFD20  /* 255, 165,   0 */
#define GREENYELLOW  0xAFE5  /* 173, 255,  47 */
#define PINK         0xF81F  /* 255,   0, 255 */

class COLOR
{
  public:
    /*
      these three types of classes will be used for different types of battery systems
      1: if a battery charging has a power and battery on and off ability as well as a multiplexer ability
      2: on and off for battery only and multiplexer
      3: only battery on and off and no multiplexer
    */
   COLOR();
   uint16_t fromRGB(uint8_t r, uint8_t g, uint8_t b);
   uint16_t fromHEX(uint32_t hex);

  private:

};

#endif