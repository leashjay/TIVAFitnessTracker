/*
 * fitnessUI.h
 *
 *  Created on: 6/05/2020
 *      Author: csm119 & dss57
 */

#ifndef FITNESSUI_H_
#define FITNESSUI_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "utils/ustdlib.h"
#include "../OrbitOLED/OrbitOLEDInterface.h"
#include "../OrbitOLED/lib_OrbitOled/OrbitOled.h"
#include "../OrbitOLED/lib_OrbitOled/OrbitOledGrph.h"
#include "buttons4.h"
#include "timedButton.h"
#include "switches.h"
#include "OledCustom.h"
#include "serialCom.h"

// Set UI displayed total steps
void setTotalSteps(uint32_t steps);

// Sets UI displayed total distance
void setTotalDistance(float distance);

// Checks user input for updates to UI
void pollUI(void);

// Renders current UI menu
void drawUI(void);

// Initalise UI
void initUI(void);


#endif /* FITNESSUI_H_ */
