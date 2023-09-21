/***********************************************************************************
  This program is a demo of display phonecall UI
  This demo was made for LCD modules with 8bit data port.
  This program requires the the LCDKIWI library.

  File                : display_phonecall.ino
  Hardware Environment: Arduino Mega2560
  Build Environment   : Arduino

  Set the pins to the correct ones for your development shield or breakout board.
  This demo use the BREAKOUT BOARD only and use these 16 data lines to the LCD,
  //pin usage as follow:
  //             CS  CD  WR  RD  RST  D0  D1  D2  D3  D4  D5  D6  D7  D8  D9  D10  D11  D12  D13  D14  D15
  //Arduino Mega 40  38  39  43  41   37  36  35  34  33  32  31  30  22  23  24   25   26   27   28   29
  //             TP_IRQ  MOSI  MISO  TP_CS  EX_CLK
  //Arduino Mega   44    51     50    53      52

  //when using the BREAKOUT BOARD only and using these 8 data lines to the LCD,
  //pin usage as follow:
  //             CS  CD  WR  RD  RST  D0  D1  D2  D3  D4  D5  D6  D7  D8  D9  D10  D11  D12  D13  D14  D15
  //Arduino Mega 40  38  39  43  41   37  36  35  34  33  32  31  30  /   /    /    /    /    /    /    /
  //             TP_IRQ  MOSI  MISO  TP_CS  EX_CLK
  //Arduino Mega   44    51     50    53      52
  Remember to set the pins to suit your display module!

  @attention

  THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**********************************************************************************/
//#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_KBV.h> //Hardware-specific library
#include <LCDWIKI_TOUCH.h> //touch screen library
#include "timemodal.h"
#include "display.h"

LCDWIKI_KBV lcd(ILI9488, 40, 38, 39, 43, 41); //model,cs,cd,wr,rd,reset
LCDWIKI_TOUCH touch(53, 52, 50, 51, 44); //tcs,tclk,tdout,tdin,tirq
TIMEMODAL timemodal(lcd);
IMM_DISPLAY mainDisplay(lcd);

bool openModal = false;

void setup(void){
  lcd.Init_LCD();
  lcd.Set_Rotation(1);
  touch.TP_Set_Rotation(3);
  touch.TP_Init(lcd.Get_Rotation(), lcd.Get_Display_Width(), lcd.Get_Display_Height());
  Serial.begin(9600);
}

void loop(void){
  uint16_t px = 0;
  uint16_t py = 0;
  touch.TP_Scan(0);
  if (touch.TP_Get_State()&TP_PRES_DOWN){
    px = touch.x;
    py = touch.y;
  }

  if(openModal){
    bool done = timemodal.loop(px,py);
    if(done){
      Serial.println(timemodal.setTime);
      timemodal.reset();
      mainDisplay.reset(timemodal.setTime);
      openModal = false;
    }
  }
  else{
    openModal = mainDisplay.loop(px,py);
  }
}



