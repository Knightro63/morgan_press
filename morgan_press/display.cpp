#include <stdbool.h>
#include "display.h"
#include "touch.h"
#include <stdint.h>
#include <Wire.h>
#include <LCDWIKI_KBV.h> //Hardware-specific library
#include "colors.h"
#include <string.h>

#define IMMADDRESS 0x01
#define MOLDAADDRESS 0x02
#define MOLDBADDRESS 0x03
#define BARRELLADDRESS 0x04

#define BED 0x01
#define PLUNGE 0x03
#define RETRACT 0x02


/*
    imm address - 0x01,
    molda address - 0x02,
    moldb address - 0x03,
    barrell address - 0x04 //does not exist yet currently use 0x01

    imm:
        bed - 0x01
        plunge - 0x02
        retracet - 0x03

    barrell:
        barrell - 0x01
        nozzle - 0x02
*/

IMM_DISPLAY::IMM_DISPLAY(LCDWIKI_KBV &lcd){
    Wire.begin();
    my_lcd = &lcd;
    uint8_t timerLength = 35;
    uint8_t tempHeight = 15;
    uint8_t tempSpace = 1;
    button_info temp[35] = {
        "MANUAL",   2,WHITE,RED,EDG_Y+1*BUTTON_W,EDG_Y+15,BUTTON_W,15,R_RECTANGLE,

        String(actBarrelTemp),2,WHITE,BLUE,EDG_Y+60+3*timerLength+1*BUTTON_SPACING_Y,EDG_Y+tempHeight,timerLength,tempHeight,R_RECTANGLE,
        String(actNozzleTemp),2,WHITE,BLUE,EDG_Y+60+5*timerLength+2*BUTTON_SPACING_Y,EDG_Y+tempHeight,timerLength,tempHeight,R_RECTANGLE,
        String(actMoldATemp), 2,WHITE,BLUE,EDG_Y+60+7*timerLength+3*BUTTON_SPACING_Y,EDG_Y+tempHeight,timerLength,tempHeight,R_RECTANGLE,
        String(actMoldBTemp),  2,WHITE,BLUE,EDG_Y+60+9*timerLength+4*BUTTON_SPACING_Y,EDG_Y+tempHeight,timerLength,tempHeight,R_RECTANGLE,

        String(setBarrelTemp),2,WHITE,BLUE,EDG_Y+60+3*timerLength+1*BUTTON_SPACING_Y,EDG_Y+3*tempHeight-8,timerLength,tempHeight,R_RECTANGLE,
        String(setNozzleTemp),2,WHITE,BLUE,EDG_Y+60+5*timerLength+2*BUTTON_SPACING_Y,EDG_Y+3*tempHeight-8,timerLength,tempHeight,R_RECTANGLE,
        String(setMoldATemp), 2,WHITE,BLUE,EDG_Y+60+7*timerLength+3*BUTTON_SPACING_Y,EDG_Y+3*tempHeight-8,timerLength,tempHeight,R_RECTANGLE,
        String(setMoldBTemp),  2,WHITE,BLUE,EDG_Y+60+9*timerLength+4*BUTTON_SPACING_Y,EDG_Y+3*tempHeight-8,timerLength,tempHeight,R_RECTANGLE,

        "> START"         ,2,WHITE,DARKGREY,EDG_Y+60                                ,my_lcd->Get_Display_Width()-EDG_Y-2*BUTTON_H-BUTTON_SPACING_Y-20,60,20,R_RECTANGLE,
        String(raisedTime),2,WHITE,BLUE,EDG_Y+60+3*timerLength+1*BUTTON_SPACING_Y,my_lcd->Get_Display_Width()-EDG_Y-2*BUTTON_H-BUTTON_SPACING_Y-20,timerLength,20,R_RECTANGLE,
        String(injectTime),2,WHITE,BLUE,EDG_Y+60+5*timerLength+2*BUTTON_SPACING_Y,my_lcd->Get_Display_Width()-EDG_Y-2*BUTTON_H-BUTTON_SPACING_Y-20,timerLength,20,R_RECTANGLE,
        String(dwellTime), 2,WHITE,BLUE,EDG_Y+60+7*timerLength+3*BUTTON_SPACING_Y,my_lcd->Get_Display_Width()-EDG_Y-2*BUTTON_H-BUTTON_SPACING_Y-20,timerLength,20,R_RECTANGLE,
        String(restTime),  2,WHITE,BLUE,EDG_Y+60+9*timerLength+4*BUTTON_SPACING_Y,my_lcd->Get_Display_Width()-EDG_Y-2*BUTTON_H-BUTTON_SPACING_Y-20,timerLength,20,R_RECTANGLE,

        "CAGE",   2,WHITE,GREEN,EDG_Y+1*BUTTON_W+0*BUTTON_SPACING_Y,my_lcd->Get_Display_Width()-EDG_Y-BUTTON_H,BUTTON_W,BUTTON_H,R_RECTANGLE,
        "BED",    2,WHITE,RED  ,EDG_Y+3*BUTTON_W+1*BUTTON_SPACING_Y,my_lcd->Get_Display_Width()-EDG_Y-BUTTON_H,BUTTON_W,BUTTON_H,R_RECTANGLE,
        "PLUNGE", 2,WHITE,RED  ,EDG_Y+5*BUTTON_W+2*BUTTON_SPACING_Y,my_lcd->Get_Display_Width()-EDG_Y-BUTTON_H,BUTTON_W,BUTTON_H,R_RECTANGLE,
        "RETRACT",2,WHITE,RED,EDG_Y+7*BUTTON_W+3*BUTTON_SPACING_Y,my_lcd->Get_Display_Width()-EDG_Y-BUTTON_H,BUTTON_W,BUTTON_H,R_RECTANGLE,

        "",2,WHITE,WHITE,EDG_Y+60+3*timerLength+1*BUTTON_SPACING_Y,EDG_Y+2*tempHeight-4,timerLength,tempSpace,RECTANGLE,
        "",2,WHITE,WHITE,EDG_Y+60+5*timerLength+2*BUTTON_SPACING_Y,EDG_Y+2*tempHeight-4,timerLength,tempSpace,RECTANGLE,
        "",2,WHITE,WHITE,EDG_Y+60+7*timerLength+3*BUTTON_SPACING_Y,EDG_Y+2*tempHeight-4,timerLength,tempSpace,RECTANGLE,
        "",2,WHITE,WHITE,EDG_Y+60+9*timerLength+4*BUTTON_SPACING_Y,EDG_Y+2*tempHeight-4,timerLength,tempSpace,RECTANGLE,

        "",2,WHITE,DARKGREY,EDG_Y+5,my_lcd->Get_Display_Width()/2-15,10,10,RECTANGLE,

        "",2,WHITE,GREENYELLOW,EDG_Y+BUTTON_W+15,EDG_Y+35+4*tempHeight+10,45,35,TRIANGLE_90,
        "",2,WHITE,GREENYELLOW,EDG_Y+BUTTON_W+15,my_lcd->Get_Display_Width()/2-15,45,30,RECTANGLE,
        "",2,WHITE,GREENYELLOW,EDG_Y+BUTTON_W+15+115,my_lcd->Get_Display_Width()/2-15,55,30,RECTANGLE,
        "",2,WHITE,GREENYELLOW,EDG_Y+BUTTON_W+15+195,my_lcd->Get_Display_Width()/2-15,10,30,RECTANGLE,
        "",2,WHITE,GREENYELLOW,EDG_Y+BUTTON_W+15+195+30,my_lcd->Get_Display_Width()/2-15,20,30,TRIANGLE_0,

        "",2,WHITE,GREENYELLOW,EDG_Y+BUTTON_W+285,my_lcd->Get_Display_Width()/2-15,10,30,RECTANGLE,
        "",2,WHITE,GREENYELLOW,EDG_Y+BUTTON_W+305,my_lcd->Get_Display_Width()/2-15,10,20,RECTANGLE,

        "",2,WHITE,GREENYELLOW,EDG_Y+BUTTON_W+365,my_lcd->Get_Display_Width()/2-15,10,20,RECTANGLE,
        "",2,WHITE,GREENYELLOW,EDG_Y+BUTTON_W+385,my_lcd->Get_Display_Width()/2-15,10,30,RECTANGLE,

        String(currentTime),2,WHITE,BLUE,EDG_Y+60+9*timerLength+4*BUTTON_SPACING_Y,my_lcd->Get_Display_Width()-EDG_Y-2*BUTTON_H-BUTTON_SPACING_Y-57,timerLength,10,R_RECTANGLE,

        String(pressureBarrel),2,WHITE,BLUE,EDG_Y+60+3*timerLength+1*BUTTON_SPACING_Y,EDG_Y+6*tempHeight-8,timerLength,10,R_RECTANGLE,
        String(pressureBed),2,WHITE,BLUE,   EDG_Y+60+9*timerLength+1*BUTTON_SPACING_Y,EDG_Y+6*tempHeight-8,timerLength,10,R_RECTANGLE,
    };

    for(int i = 0; i < sizeof(temp)/sizeof(button_info);i++){
        phone_button[i] = temp[i];
    }
}
void IMM_DISPLAY::requestData(int address, uint8_t (&data)[8]){
  Wire.beginTransmission(address);
  Wire.requestFrom(address,sizeof(data));

  uint8_t i = 0;
  while (Wire.available()) {      //slave may send less than requested
    uint8_t r_byte = Wire.read();     //receive a byte as character
    data[i] = r_byte;             //place data incomming data in the init integer
    i++;                          //iterate for data integer
  }
  Wire.endTransmission();
}
void IMM_DISPLAY::sendData(uint8_t address, uint8_t* data){
  Wire.beginTransmission(address); // transmit to device #4
  for(int i = 0; i < sizeof(data);i++){
    Wire.write(data[i]);        // sends five bytes
  }
  Wire.endTransmission();    // stop transmitting
}

void IMM_DISPLAY::setup(void){
  my_lcd->Fill_Screen(33,33,33);
  show_display();
  justOpened = false;
  setBarrel(17);
}
void IMM_DISPLAY::reset(uint16_t newValue){
  justOpened = true;
  openModal = false;

  switch (selected){
    case raised_time:
        raisedTime = newValue;
        
        break;
    case inject_time:
        injectTime = newValue;
        break;
    case dwell_time:
        dwellTime = newValue;
        break;
    case rest_time:
        restTime = newValue;
        break;
    case barrel_temp_set:
        setBarrelTemp = newValue;
        uint8_t tempBar[2];
        memcpy(tempBar,&newValue,sizeof(tempBar));
        uint8_t temp1Bar[3];
        temp1Bar[0] = 0x01;
        temp1Bar[1] = tempBar[0];
        temp1Bar[2] = tempBar[1];
        sendData(BARRELLADDRESS,temp1Bar);
        break;
    case nozzle_temp_set:
        setNozzleTemp = newValue;
        uint8_t tempNoz[2];
        memcpy(tempNoz,&newValue,sizeof(tempNoz));
        uint8_t temp1Noz[3];
        temp1Noz[0] = 0x02;
        temp1Noz[1] = tempNoz[0];
        temp1Noz[2] = tempNoz[1];
        sendData(BARRELLADDRESS,temp1Noz);
        break;
    case moldA_temp_set:
        setMoldATemp = newValue;
        uint8_t tempA[2];
        memcpy(tempA,&newValue,sizeof(tempA));
        sendData(MOLDAADDRESS,tempA);
        break;
    case moldB_temp_set:
        setMoldBTemp = newValue;
        uint8_t tempB[2];
        memcpy(tempB,&newValue,sizeof(tempB));
        sendData(MOLDBADDRESS,tempB);
        break;
    default:
        break;
  }

    phone_button[selected].button_name =  String(newValue);
    setButton(selected);
}

bool IMM_DISPLAY::loop(uint16_t px, uint16_t py){
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
        if(i > 4 && i != 9 && i < 14 && !play){
            selected = i;
            setButton(i,DARKGREY);
            show_string(phone_button[i].button_name,phone_button[i].button_x-phone_button[i].button_name.length()*phone_button[i].button_name_size*6/2+phone_button[i].button_name_size/2+1,phone_button[i].button_y-phone_button[i].button_name_size*8/2+phone_button[i].button_name_size/2+1,phone_button[i].button_name_size,WHITE,BLACK,1);
            openModal = true;
        }
        else if(i >= 1 && i < 5){
            selected = i+4;
            setButton(selected,DARKGREY);
            show_string(phone_button[selected].button_name,phone_button[selected].button_x-phone_button[selected].button_name.length()*phone_button[selected].button_name_size*6/2+phone_button[selected].button_name_size/2+1,phone_button[selected].button_y-phone_button[selected].button_name_size*8/2+phone_button[selected].button_name_size/2+1,phone_button[selected].button_name_size,WHITE,BLACK,1);
            openModal = true;
        }
        else if(i == 9 && isAutomatic){
            if(!play){
                play = true;
                if(isRetracted){
                    setBarrel(17);
                    currentTime = millis()+retractTime;
                }
                else{
                    currentTime = millis();
                }
                phone_button[i].button_name = "> STOP";
                setButton(i,RED);
            }
            else{
                play = false;
                phone_button[i].button_name = "> START";
                setButton(i,GREEN);
                resetAutomatic();
            }
        }
        else if(i == 0){
            if(!isAutomatic){
                isAutomatic = true;
                phone_button[i].button_name = "AUTO";
                setButton(i,GREEN);

                phone_button[9].button_name = "> START";
                setButton(9,GREEN);
            }
            else{
                resetAutomatic();
                isAutomatic = false;
                phone_button[i].button_name = "MANUAL";
                setButton(i,RED);

                phone_button[9].button_name = "> START";
                setButton(9,DARKGREY);
            }
        }
        else if(i == 14 && !play){
            setButton(i,!cageClosed?GREEN:RED);
            cageClosed = !cageClosed;
        }
        else if(i == 15 && !play){
            setBed();
        }
        else if((i == 16 || i == 17) && !play){
            setBarrel(i);
        }
        delay(100);
    }
  }

  if(!isRetracted && millis() >= currentRetractTime+retractTime){
    isRetracted = true;
    setBarrel(17, isRetracted);
  }

  startAutomatic();

  getTempData();

  return openModal;
}
uint16_t IMM_DISPLAY::convertTemp(uint16_t rawtemp){
  float average;
  average = (1023/(float)rawtemp) - 1;
  average = 4700 / average;
  float steinhart;
  steinhart = log(average / 100000)/3950;// ln(R/Ro)/B
  steinhart += 1.0 / (25 + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;                         // convert absolute temp to C
  return steinhart < 0?0:lrintf(steinhart);
}
void IMM_DISPLAY::getTempData(){
  if(millis() >= updateDisplay+1000){
    //get temperatures and pressures of the imm
    uint8_t incomming[8] = {0,0,0,0,0,0,0,0};
    requestData(IMMADDRESS, incomming);

    uint16_t abt = convertTemp(incomming[1]*256+incomming[0]);
    uint16_t ant = convertTemp(incomming[3]*256+incomming[2]);
    uint16_t pBed = incomming[5]*256+incomming[4];
    uint16_t pBarrel = incomming[7]*256+incomming[6];

    if(actBarrelTemp != abt){
      actBarrelTemp = abt;
      phone_button[1].button_name = String(actBarrelTemp);
      setButton(1);
      setButton(18);
    }
    if(actNozzleTemp != ant){
      actNozzleTemp = ant;
      phone_button[2].button_name = String(actNozzleTemp);
      setButton(2);
      setButton(19);
    }
    if(pressureBarrel != pBarrel){
      pressureBarrel = pBarrel;
      phone_button[33].button_name = String(pressureBarrel);
      setButton(33);
    }
    if(pressureBed != pBed){
      pressureBed = pBed;
      phone_button[34].button_name = String(pressureBed);
      setButton(34);
    }

    //get temperatures of mold a
    uint8_t incomming2[8] = {0,0,0,0,0,0,0,0};
    requestData(MOLDAADDRESS, incomming2);
    uint16_t amat = 0;
    for(uint8_t i = 0; i < 4; i++){
      amat += convertTemp(incomming2[i*2+1]*256+incomming2[i*2]);
    }
    amat /= 4;
    if(actMoldATemp != amat){
      actMoldATemp = amat;
      phone_button[3].button_name = String(actMoldATemp);
      setButton(3);
      setButton(20);
    }

    //get temperatures of mold b
    uint8_t incomming3[8] = {0,0,0,0,0,0,0,0};
    requestData(MOLDBADDRESS, incomming3);
    uint16_t ambt = 0;
    for(uint8_t i = 0; i < 4; i++){
      ambt += convertTemp(incomming3[i*2+1]*256+incomming3[i*2]);
    }
    ambt /= 4;
    if(actMoldBTemp != ambt){
      actMoldBTemp = ambt;
      phone_button[4].button_name = String(actMoldBTemp);
      setButton(4);
      setButton(21);
    }

    updateDisplay = millis();
  }
}
void IMM_DISPLAY::resetAutomatic(){
    if(bedClosed){
        setBed();
    }
    if(phone_button[16].button_colour == GREEN){
        setBarrel(16);
    }
    if(!barrelUp){
        setBarrel(17);
    }

    step = 0;
}
void IMM_DISPLAY::startAutomatic(){
  if(play){
    if(millis() >= currentTime+static_cast<unsigned long>(raisedTime+injectTime+dwellTime+restTime)*1000 && step == 4){
        currentTime = millis();
        step = 0;
    }
    else if(millis() >= currentTime+static_cast<unsigned long>(raisedTime+injectTime+dwellTime)*1000 && step == 3){
        setBed();
        setBarrel(17);
        step++;
    }
    else if(millis() >= currentTime+static_cast<unsigned long>(raisedTime+injectTime)*1000 && step == 2){
        setBarrel(16);
        step++;
    }
    else if(millis() >= currentTime+static_cast<unsigned long>(raisedTime)*1000 && step == 1){
        setBarrel(16);
        step++;
    }
    else if(millis() >= currentTime && step == 0){
        setBed();
        step++;
    }

    if(millis() >= updateTime+1000 && currentTime < millis()){
        phone_button[32].button_name = String((millis()-currentTime)/1000);
        setButton(32);
        updateTime = millis();
    }
  }
}
void IMM_DISPLAY::setBed(){
    if(barrelUp && !bedClosed && cageClosed){
        setButton(15,GREEN);
        bedClosed = true;
        uint8_t temp[2] = {BED,0x01};
        sendData(IMMADDRESS,temp);

        setButton(28,33,33,33);
        setButton(29,33,33,33);
        setButton(30,33,33,33);
        setButton(31,33,33,33);

        phone_button[28].button_x = phone_button[28].button_x-20;
        phone_button[29].button_x = phone_button[29].button_x-20;
        setButton(28,GREENYELLOW);
        setButton(29,GREENYELLOW);

        phone_button[30].button_x = phone_button[30].button_x-60;
        phone_button[31].button_x = phone_button[31].button_x-60;
        setButton(30,GREENYELLOW);
        setButton(31,GREENYELLOW);
    }
    else if(bedClosed){
        setButton(15,RED);
        bedClosed = false;
        uint8_t temp[2] = {BED,0x00};
        sendData(IMMADDRESS,temp);

        setButton(28,33,33,33);
        setButton(29,33,33,33);
        setButton(30,33,33,33);
        setButton(31,33,33,33);

        phone_button[28].button_x = phone_button[28].button_x+20;
        phone_button[29].button_x = phone_button[29].button_x+20;
        setButton(28,GREENYELLOW);
        setButton(29,GREENYELLOW);


        phone_button[30].button_x = phone_button[30].button_x+60;
        phone_button[31].button_x = phone_button[31].button_x+60;
        setButton(30,GREENYELLOW);
        setButton(31,GREENYELLOW);
    }
}
void IMM_DISPLAY::setBarrel(uint8_t toSet){
    setBarrel(toSet, false);
}
void IMM_DISPLAY::setBarrel(uint8_t toSet, bool retracted){
    if(toSet == 17){
        setButton(22,33,33,33);
        phone_button[22].button_x = EDG_Y+5;
        phone_button[22].width = 10;

        setButton(22);
        for(int i = 23; i < 28; i++){
            setButton(i);
        }

        if(phone_button[toSet].button_colour == GREEN){
            phone_button[toSet].button_colour = RED;
            setButton(toSet);
            uint8_t temp[2] = {RETRACT,0x00};
            sendData(IMMADDRESS,temp);
        }
        else{
            phone_button[toSet].button_colour = GREEN;
            setButton(toSet);
            uint8_t temp[2] = {RETRACT,0x01};
            sendData(IMMADDRESS,temp);
        }
            
        setButton(16,RED);
        barrelUp = true;
        isRetracted = retracted;
        currentRetractTime = millis();
    }
    else if(toSet == 16){
        setButton(22,33,33,33);

        phone_button[22].button_x = 155;
        phone_button[22].width = 150;
        setButton(22);
        for(int i = 23; i < 28; i++){
            setButton(i);
        }
        if(phone_button[toSet].button_colour == GREEN){
            phone_button[toSet].button_colour = RED;
            setButton(toSet);
            uint8_t temp[2] = {PLUNGE,0x00};
            sendData(IMMADDRESS,temp);
        }
        else{
            phone_button[toSet].button_colour = GREEN;
            setButton(toSet);
            uint8_t temp[2] = {PLUNGE,0x01};
            sendData(IMMADDRESS,temp);
        }
        setButton(17,RED);
        barrelUp = false;
    }
}
void IMM_DISPLAY::setButton(uint8_t selection){
    setButton(selection,phone_button[selection].button_colour);
}
void IMM_DISPLAY::setButton(uint8_t selection, uint8_t r, uint8_t g, uint8_t b){
    setButton(selection,my_lcd->Color_To_565(r,g,b));
}
void IMM_DISPLAY::setButton(uint8_t selection,uint16_t color){
    my_lcd->Set_Draw_color(color);
    if(phone_button[selection].type == CIRCLE){
        my_lcd->Fill_Circle(phone_button[selection].button_x, phone_button[selection].button_y, phone_button[selection].width);
    }
    else if(phone_button[selection].type == R_RECTANGLE){
        my_lcd->Fill_Round_Rectangle(
            phone_button[selection].button_x-phone_button[selection].width, 
            phone_button[selection].button_y-phone_button[selection].height, 
            phone_button[selection].button_x+phone_button[selection].width, 
            phone_button[selection].button_y+phone_button[selection].height,
            10
        );
    }
    else if(phone_button[selection].type == RECTANGLE){
        my_lcd->Fill_Rectangle(
            phone_button[selection].button_x-phone_button[selection].width, 
            phone_button[selection].button_y-phone_button[selection].height, 
            phone_button[selection].button_x+phone_button[selection].width, 
            phone_button[selection].button_y+phone_button[selection].height
        );
    }
    else if(phone_button[selection].type == TRIANGLE_0){
        my_lcd->Fill_Triangle(
            phone_button[selection].button_x-phone_button[selection].width, 
            phone_button[selection].button_y-phone_button[selection].height,
            phone_button[selection].button_x+phone_button[selection].width,
            phone_button[selection].button_y,
            phone_button[selection].button_x-phone_button[selection].width, 
            phone_button[selection].button_y+phone_button[selection].height
        );
    }
    else if(phone_button[selection].type == TRIANGLE_90){
        my_lcd->Fill_Triangle(
            phone_button[selection].button_x-phone_button[selection].width, 
            phone_button[selection].button_y-phone_button[selection].height,
            phone_button[selection].button_x+phone_button[selection].width,
            phone_button[selection].button_y-phone_button[selection].height,
            phone_button[selection].button_x, 
            phone_button[selection].button_y+phone_button[selection].height
        );
    }
    show_string(phone_button[selection].button_name,phone_button[selection].button_x-phone_button[selection].button_name.length()*phone_button[selection].button_name_size*6/2+phone_button[selection].button_name_size/2+1,phone_button[selection].button_y-phone_button[selection].button_name_size*8/2+phone_button[selection].button_name_size/2+1,phone_button[selection].button_name_size,WHITE,BLACK,1);
}
void IMM_DISPLAY::show_string(String str, int16_t x, int16_t y, uint8_t csize, uint16_t fc, uint16_t bc, bool mode){
  my_lcd->Set_Text_Mode(mode);
  my_lcd->Set_Text_Size(csize);
  my_lcd->Set_Text_colour(fc);
  my_lcd->Set_Text_Back_colour(bc);
  my_lcd->Print_String(str, x, y);
}
void IMM_DISPLAY::show_display(void){
  uint16_t i;
  for(i = 0;i < sizeof(phone_button)/sizeof(button_info);i++){
    setButton(i);
  }
}