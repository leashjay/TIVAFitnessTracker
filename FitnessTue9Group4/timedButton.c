/*
 * timedButton.c
 *
 *  Created on: 6/05/2020
 *      Author: dss57 && csm119
 */
#include "timedButton.h"

// Variables
uint32_t button_timestamp[NUM_BUTS];
bool     button_pressed[NUM_BUTS];


// Private
uint32_t getClockTimestamp() {
    return TimerValueGet(TIMER0_BASE, TIMER_A);
}

uint32_t getTimeDifference(uint32_t start, uint32_t end) {
    if(end > start) {
        return end - start;
    } else {
        return end + (UINT32_MAX - start); // Assume overflow
    }
}

uint32_t toMilliseconds(uint32_t value) {
    return value / (SysCtlClockGet() / 1000);
}

// Interfaces
void initTimedButton(void) {
    initButtons();

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerDisable(TIMER0_BASE, TIMER_BOTH);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC_UP);
    TimerEnable(TIMER0_BASE, TIMER_BOTH);
}

int checkTimedButton(int button, int period_ms) {
    uint8_t current_state = checkButton(button);

    switch(current_state) {
        case PUSHED:
            button_timestamp[button] = getClockTimestamp();
            button_pressed[button] = true;
            break;
        case RELEASED:
            button_pressed[button] = false;
            return RELEASED;
            break;
        case NO_CHANGE:
            if (button_pressed[button]) {
                uint32_t difference = getTimeDifference(button_timestamp[button], getClockTimestamp());
                if(toMilliseconds(difference) > period_ms) {
                    return PUSHED;
                }
            }
            break;
    }

    return NO_CHANGE;
}
