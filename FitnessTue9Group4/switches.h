/*
 * switches.h
 *
 *  Created on: 6/05/2020
 *      Author: dss57
 */

#ifndef SWITCHES_H_
#define SWITCHES_H_

#include <stdint.h>
#include <stdbool.h>
#include "buttons4.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"

#define SWITCH1_PIN GPIO_PIN_7
#define SWITCH2_PIN GPIO_PIN_6

enum switchNames {SW1 = 0, SW2, NUM_SWITCHES};
enum switchStates {SWITCH_DOWN = 0, SWITCH_UP};

void initSwitches(void);

void updateSwitches(void);

uint8_t checkSwitch(uint8_t switchNames);

#endif /* SWITCHES_H_ */
