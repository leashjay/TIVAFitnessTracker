/*
 * OledCustom.h
 *
 *  Created on: 6/05/2020
 *      Author: csm119
 */

#ifndef OLEDCUSTOM_H_
#define OLEDCUSTOM_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "utils/ustdlib.h"
#include "../OrbitOLED/OrbitOLEDInterface.h"
#include "../OrbitOLED/lib_OrbitOled/OrbitOled.h"
#include "../OrbitOLED/lib_OrbitOled/OrbitOledGrph.h"

void draw_distance_icon(uint8_t ox, uint8_t oy);
void draw_steps_icon(uint8_t ox, uint8_t oy);
void draw_up_arrow(uint8_t ox, uint8_t oy);
void draw_down_arrow(uint8_t ox, uint8_t oy);

void draw_line(uint8_t ox, uint8_t oy, uint8_t ex, uint8_t ey);

#endif /* OLEDCUSTOM_H_ */
