/*
  This is a function that handles the batteries percentage 
  and charging. Checking the charging to 10 times to make sure it was charging
  This also only checks the percentage every 20 sec. 
*/

#ifndef IMM_DISPLAY_H
#define IMM_DISPLAY_H

#include <stdbool.h>
#include <stdint.h>
#include <LCDWIKI_KBV.h> //Hardware-specific library
#include "css.h"
#include "colors.h"
#include "timemodal.h"
#include <string.h>

#define BUTTON_W 54
#define BUTTON_H 25
#define BUTTON_SPACING_X 20
#define BUTTON_SPACING_Y 10
#define EDG_Y 10
#define EDG_X 20

enum selected_tab{
  auto_manual,
  barrel_temp_act,
  nozzle_temp_act,
  moldA_temp_act,
  moldB_temp_act,
  barrel_temp_set,
  nozzle_temp_set,
  moldA_temp_set,
  moldB_temp_set,
  start_stop,
  raised_time,
  inject_time,
  dwell_time,
  rest_time,
  cage,
  bed,
  plunge,
  retract,
};

class IMM_DISPLAY{
  public:
    selected_tab selected = raised_time;
    IMM_DISPLAY(LCDWIKI_KBV&);
    bool loop(uint16_t px, uint16_t py);
    void reset(uint16_t newValue);

  private:
    uint16_t setNozzleTemp = 220;
    uint16_t setBarrelTemp = 200;
    uint16_t setMoldATemp = 100;
    uint16_t setMoldBTemp = 100;

    uint16_t actNozzleTemp = 0;
    uint16_t actBarrelTemp = 0;
    uint16_t actMoldATemp = 0;
    uint16_t actMoldBTemp = 0;

    uint16_t pressureBed = 0;
    uint16_t pressureBarrel = 0;

    uint16_t retractTime = 5000;
    uint16_t raisedTime = 10;
    uint16_t injectTime = 20;
    uint16_t dwellTime = 30;
    uint16_t restTime = 10;

    uint8_t step = 0;

    unsigned long currentRetractTime;
    unsigned long currentTime;
    unsigned long updateTime;
    unsigned long updateDisplay;

    bool cageClosed = true;
    bool bedClosed = false;
    bool barrelUp = true;

    bool isRetracted = false;

    bool play = false;
    bool isAutomatic = false;

    bool justOpened = true;
    bool openModal = false;

    button_info phone_button[35];
    LCDWIKI_KBV *my_lcd;
    COLOR Color;

    void show_display(void);
    void setButton(uint8_t, uint16_t);
    void setButton(uint8_t, uint8_t r, uint8_t g, uint8_t b);
    void setButton(uint8_t);
    void setBed(void);
    void startAutomatic(void);
    void resetAutomatic(void);
    void setBarrel(uint8_t);
    void setBarrel(uint8_t,bool);
    void getTempData(void);
    uint16_t convertTemp(uint16_t val);
    void requestData(int address, uint8_t (&data)[8]);
    void sendData(uint8_t address, uint8_t* data);
    void setup(void);
    void show_string(String str, int16_t x, int16_t y, uint8_t csize, uint16_t fc, uint16_t bc, bool mode);
};

#endif