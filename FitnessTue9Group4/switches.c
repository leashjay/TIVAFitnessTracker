/*
 * switches.c
 *
 *  Created on: 6/05/2020
 *      Author: dss57
 */

#include "switches.h"

uint8_t currentSwitchStates[NUM_SWITCHES] = {0, 0};

void initSwitches(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // Switch 1
    GPIOPinTypeGPIOInput (GPIO_PORTA_BASE, SWITCH1_PIN);
    GPIOPadConfigSet (GPIO_PORTA_BASE, SWITCH1_PIN, GPIO_STRENGTH_2MA,
    GPIO_PIN_TYPE_STD_WPD);

    // Switch 2
    GPIOPinTypeGPIOInput (GPIO_PORTA_BASE, SWITCH2_PIN);
    GPIOPadConfigSet (GPIO_PORTA_BASE, SWITCH2_PIN, GPIO_STRENGTH_2MA,
    GPIO_PIN_TYPE_STD_WPD);
}

void updateSwitches(void)
{
    currentSwitchStates[SW1] = GPIOPinRead(GPIO_PORTA_BASE, SWITCH1_PIN) > 0;
    currentSwitchStates[SW2] = GPIOPinRead(GPIO_PORTA_BASE, SWITCH2_PIN) > 0;
}

uint8_t checkSwitch(uint8_t switchNames)
{
    return currentSwitchStates[switchNames];
}
