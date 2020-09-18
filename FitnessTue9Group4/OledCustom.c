/*
 * OledCustom.c
 *
 *  Created on: 6/05/2020
 *      Author: dss57
 */

#include "OledCustom.h"

//  L
//D   U
//  R
char distance_icon_UL[] = {
    0b01111100,
    0b11111110,
    0b11000111,
    0b10000011,
    0b10000011,
    0b10000011,
    0b11000111,
    0b11111110
};

char distance_icon_UR[] = {
    0b01111100,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
};

char distance_icon_BL[] = {
    0b00000000,
    0b00000001,
    0b00000111,
    0b00011111,
    0b01111111,
    0b00011111,
    0b00000111,
    0b00000001,
};

void draw_distance_icon(uint8_t ox, uint8_t oy) {
    OrbitOledMoveTo(ox, oy);
    OrbitOledPutBmp(8,8, distance_icon_UL);
    OrbitOledMoveTo(ox + 8, oy);
    OrbitOledPutBmp(8,8, distance_icon_UR);
    OrbitOledMoveTo(ox, oy + 8);
    OrbitOledPutBmp(8,8, distance_icon_BL);
}

char steps_icon_UL[] = {
    0b11110000,
    0b11111000,
    0b11111000,
    0b11110000,
    0b00000000,
    0b00000000,
    0b00111110,
    0b01111111,
};

char steps_icon_UR[] = {
    0b01111111,
    0b01111110,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
};

char steps_icon_BL[] = {
    0b00111011,
    0b01111011,
    0b01111011,
    0b00110001,
    0b00000000,
    0b00000000,
    0b00000110,
    0b00001111,
};

char steps_icon_BR[] = {
    0b00001111,
    0b00000111,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
};

void draw_steps_icon(uint8_t ox, uint8_t oy) {
    OrbitOledMoveTo(ox, oy);
    OrbitOledPutBmp(8,8, steps_icon_UL);
    OrbitOledMoveTo(ox + 8, oy);
    OrbitOledPutBmp(8,8, steps_icon_UR);
    OrbitOledMoveTo(ox, oy + 8);
    OrbitOledPutBmp(8,8, steps_icon_BL);
    OrbitOledMoveTo(ox + 8, oy + 8);
    OrbitOledPutBmp(8,8, steps_icon_BR);
}

char arrow_icon_up[] = {
    0b00100000,
    0b00110000,
    0b00111100,
    0b00111110,
    0b00111100,
    0b00110000,
    0b00100000,
    0b00000000,
};

char arrow_icon_down[] = {
    0b00000001,
    0b00000011,
    0b00001111,
    0b00011111,
    0b00001111,
    0b00000011,
    0b00000001,
    0b00000000,
};

void draw_up_arrow(uint8_t ox, uint8_t oy) {
    OrbitOledMoveTo(ox, oy);
    OrbitOledPutBmp(8,8, arrow_icon_up);
}

void draw_down_arrow(uint8_t ox, uint8_t oy) {
    OrbitOledMoveTo(ox, oy);
    OrbitOledPutBmp(8,8, arrow_icon_down);
}


void draw_line(uint8_t ox, uint8_t oy, uint8_t ex, uint8_t ey)
{
    OrbitOledMoveTo(ox, oy);
    OrbitOledLineTo(ex, ey);
}
