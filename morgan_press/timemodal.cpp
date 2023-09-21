#include <stdbool.h>
#include "timemodal.h"
#include "touch.h"
#include <stdint.h>
#include <LCDWIKI_KBV.h> //Hardware-specific library
#include "colors.h"
#include <string.h>

TIMEMODAL::TIMEMODAL(LCDWIKI_KBV &lcd){
    my_lcd = &lcd;
    button_info temp[12] = {
        "0",4,WHITE,my_lcd->Color_To_565(6,167,266),EDG_X+1*BUTTON_R                   ,my_lcd->Get_Display_Height()-EDG_Y-6*BUTTON_SPACING_Y-9*BUTTON_R-1,BUTTON_R,BUTTON_R,CIRCLE,
        "1",4,WHITE,my_lcd->Color_To_565(6,167,266),EDG_X+3*BUTTON_R+1*BUTTON_SPACING_X,my_lcd->Get_Display_Height()-EDG_Y-6*BUTTON_SPACING_Y-9*BUTTON_R-1,BUTTON_R,BUTTON_R,CIRCLE,
        "2",4,WHITE,my_lcd->Color_To_565(6,167,266),EDG_X+5*BUTTON_R+2*BUTTON_SPACING_X,my_lcd->Get_Display_Height()-EDG_Y-6*BUTTON_SPACING_Y-9*BUTTON_R-1,BUTTON_R,BUTTON_R,CIRCLE,
        "3",4,WHITE,my_lcd->Color_To_565(6,167,266),EDG_X+7*BUTTON_R+3*BUTTON_SPACING_X,my_lcd->Get_Display_Height()-EDG_Y-6*BUTTON_SPACING_Y-9*BUTTON_R-1,BUTTON_R,BUTTON_R,CIRCLE,
        "4",4,WHITE,my_lcd->Color_To_565(6,167,266),EDG_X+9*BUTTON_R+4*BUTTON_SPACING_X,my_lcd->Get_Display_Height()-EDG_Y-6*BUTTON_SPACING_Y-9*BUTTON_R-1,BUTTON_R,BUTTON_R,CIRCLE,

        "5",4,WHITE,my_lcd->Color_To_565(6,167,266),EDG_X+1*BUTTON_R                   ,my_lcd->Get_Display_Height()-EDG_Y-4*BUTTON_SPACING_Y-7*BUTTON_R-1,BUTTON_R,BUTTON_R,CIRCLE,
        "6",4,WHITE,my_lcd->Color_To_565(6,167,266),EDG_X+3*BUTTON_R+1*BUTTON_SPACING_X,my_lcd->Get_Display_Height()-EDG_Y-4*BUTTON_SPACING_Y-7*BUTTON_R-1,BUTTON_R,BUTTON_R,CIRCLE,
        "7",4,WHITE,my_lcd->Color_To_565(6,167,266),EDG_X+5*BUTTON_R+2*BUTTON_SPACING_X,my_lcd->Get_Display_Height()-EDG_Y-4*BUTTON_SPACING_Y-7*BUTTON_R-1,BUTTON_R,BUTTON_R,CIRCLE,
        "8",4,WHITE,my_lcd->Color_To_565(6,167,266),EDG_X+7*BUTTON_R+3*BUTTON_SPACING_X,my_lcd->Get_Display_Height()-EDG_Y-4*BUTTON_SPACING_Y-7*BUTTON_R-1,BUTTON_R,BUTTON_R,CIRCLE,
        "9",4,WHITE,my_lcd->Color_To_565(6,167,266),EDG_X+9*BUTTON_R+4*BUTTON_SPACING_X,my_lcd->Get_Display_Height()-EDG_Y-4*BUTTON_SPACING_Y-7*BUTTON_R-1,BUTTON_R,BUTTON_R,CIRCLE,

        "DELETE",3,WHITE,RED,EDG_X+BUTTON_R*2,my_lcd->Get_Display_Width()-EDG_Y-BUTTON_R,BUTTON_R*2,BUTTON_R,R_RECTANGLE,
        "ENTER",3,WHITE,GREEN,my_lcd->Get_Display_Height()-EDG_X-BUTTON_R*2,my_lcd->Get_Display_Width()-EDG_Y-BUTTON_R,BUTTON_R*2,BUTTON_R,R_RECTANGLE,
    };
    for(int i = 0; i < 12;i++){
        phone_button[i] = temp[i];
    }

    text_x_add = 6 * phone_button[0].button_name_size;
    text_y_add = 8 * phone_button[0].button_name_size;
}

void TIMEMODAL::setup(void){
  my_lcd->Fill_Screen(33,33,33);
  show_input();
  setTime = 0;
  justOpened = false;
}
void TIMEMODAL::reset(void){
  done = false;
  n = 0;
  text_x = 7;
  justOpened = true;
}
bool TIMEMODAL::loop(uint16_t px, uint16_t py){
  if(justOpened){
    setup();
  }
  uint16_t i;
  for(i=0;i<sizeof(phone_button)/sizeof(button_info);i++){
    if(is_pressed(
        phone_button[i].button_x-phone_button[i].width,
        phone_button[i].button_y-phone_button[i].height,
        phone_button[i].button_x+phone_button[i].width,
        phone_button[i].button_y+phone_button[i].height,
        px,
        py
    )){
      my_lcd->Set_Draw_color(DARKGREY);
      if(phone_button[i].type == CIRCLE)
        my_lcd->Fill_Circle(phone_button[i].button_x, phone_button[i].button_y, phone_button[i].width);
      else if(phone_button[i].type == R_RECTANGLE)
        my_lcd->Fill_Round_Rectangle(
            phone_button[i].button_x-phone_button[i].width, 
            phone_button[i].button_y-phone_button[i].height, 
            phone_button[i].button_x+phone_button[i].width, 
            phone_button[i].button_y+phone_button[i].height,
            10
        );

      show_string(
        phone_button[i].button_name,
        phone_button[i].button_x-phone_button[i].button_name.length()*phone_button[i].button_name_size*6/2+phone_button[i].button_name_size/2+1,
        phone_button[i].button_y-phone_button[i].button_name_size*8/2+phone_button[i].button_name_size/2+1,
        phone_button[i].button_name_size,
        WHITE,
        BLACK,
        1
      );
      delay(100);
      my_lcd->Set_Draw_color(phone_button[i].button_colour);

      if(phone_button[i].type == CIRCLE)
        my_lcd->Fill_Circle(phone_button[i].button_x,phone_button[i].button_y,phone_button[i].width);
      else if(phone_button[i].type == R_RECTANGLE)
        my_lcd->Fill_Round_Rectangle(
            phone_button[i].button_x-phone_button[i].width, 
            phone_button[i].button_y-phone_button[i].height, 
            phone_button[i].button_x+phone_button[i].width, 
            phone_button[i].button_y+phone_button[i].height,
            10
        );
    
      show_string(phone_button[i].button_name,phone_button[i].button_x-phone_button[i].button_name.length()*phone_button[i].button_name_size*6/2+phone_button[i].button_name_size/2+1,phone_button[i].button_y-phone_button[i].button_name_size*8/2+phone_button[i].button_name_size/2+1,phone_button[i].button_name_size,phone_button[i].button_name_colour,BLACK,1);
      if(i < 10 && n < 13 && (setTime < 6553 || (setTime == 6553 && (i+1) < 6))){
        show_string(phone_button[i].button_name,text_x,text_y,phone_button[i].button_name_size,GREENYELLOW, BLACK,1);
        setTime = i+setTime*10;
        text_x += text_x_add-1;
        n++;
      }
      else if(11 == i){
        done = true;
      }
      else if(10 == i){
        if(n > 0){
          setTime = setTime/10;
          my_lcd->Set_Draw_color(Color.fromRGB(33,33,33));
          text_x -= (text_x_add-1);
          my_lcd->Fill_Rectangle(text_x, text_y, text_x+text_x_add-1, text_y+text_y_add-2);
          n--;
        }
        else{
          setTime = 0;
        }
      }
    }
  }
  return done;
}

void TIMEMODAL::show_string(String str, int16_t x, int16_t y, uint8_t csize, uint16_t fc, uint16_t bc, bool mode){
  my_lcd->Set_Text_Mode(mode);
  my_lcd->Set_Text_Size(csize);
  my_lcd->Set_Text_colour(fc);
  my_lcd->Set_Text_Back_colour(bc);
  my_lcd->Print_String(str, x, y);
}
void TIMEMODAL::show_input(void){
  uint16_t i;
  for(i = 0;i < sizeof(phone_button)/sizeof(button_info);i++){
    my_lcd->Set_Draw_color(phone_button[i].button_colour);
    if(phone_button[i].type == CIRCLE)
      my_lcd->Fill_Circle(phone_button[i].button_x, phone_button[i].button_y, phone_button[i].width);
    else if(phone_button[i].type == R_RECTANGLE)
      my_lcd->Fill_Round_Rectangle(
        phone_button[i].button_x-phone_button[i].width, 
        phone_button[i].button_y-phone_button[i].height, 
        phone_button[i].button_x+phone_button[i].width, 
        phone_button[i].button_y+phone_button[i].height,
        10
      );
    show_string(phone_button[i].button_name,phone_button[i].button_x-phone_button[i].button_name.length()*phone_button[i].button_name_size*6/2+phone_button[i].button_name_size/2+1,phone_button[i].button_y-phone_button[i].button_name_size*8/2+phone_button[i].button_name_size/2+1,phone_button[i].button_name_size,phone_button[i].button_name_colour,BLACK,1);
  }
  my_lcd->Set_Draw_color(DARKGREY);
  my_lcd->Fill_Rectangle(1, 1, my_lcd->Get_Display_Width()-2, 3);
  my_lcd->Fill_Rectangle(1, 45, my_lcd->Get_Display_Width()-2, 47);
  my_lcd->Fill_Rectangle(1, 1, 3, 47);
  my_lcd->Fill_Rectangle(my_lcd->Get_Display_Width()-4, 1, my_lcd->Get_Display_Width()-2, 47);
}

