/*
 * fitnessTrackerDisplay.h
 * Original fitness display code for demo 1
 *  Created on: 14/03/2020
 *      Author: csm119
 */

#ifndef FITNESSTRACKERDISPLAY_H_
#define FITNESSTRACKERDISPLAY_H_
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "utils/ustdlib.h"
#include "../OrbitOLED/OrbitOLEDInterface.h"
#include "acc.h"

// Display modes for accelerometer units
typedef enum {ACCEL_RAW, ACCEL_G, ACCEL_MPSS, DISPLAY_MODE_COUNT} display_mode;


// Initialise display module
void initDisplay(void);

// Draw simple accelerometer screen to display
void drawAccelScreen(display_mode mode, vector3_t accel, vector3_t orientation);


#endif /* FITNESSTRACKERDISPLAY_H_ */
