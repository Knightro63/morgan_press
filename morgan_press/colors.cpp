#include <stdbool.h>
#include "colors.h"
#include <stdint.h>

COLOR::COLOR(){}

uint16_t COLOR::fromRGB(uint8_t r, uint8_t g, uint8_t b){
    return ((r & 0b11111000) << 8) | ((g & 0b11111100) << 3) | (b >> 3);
    //return ((r / 8) << 11) | ((g / 4) << 5) | (b / 8);
}
uint16_t COLOR::fromHEX(uint32_t hex){
    return (hex << 8) | (hex << 5) | (hex << 3) | 0x0000;
}