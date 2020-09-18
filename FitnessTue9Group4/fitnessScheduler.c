/*
 * fitnessScheduler.c
 *
 *  Created on: 26/05/2020
 *      Author: csm119
 */
#include "fitnessScheduler.h"



// Variables
uint32_t lastTaskTrigger[MAX_TASKCOUNT] = {0};

// Private
static uint32_t getClockTimestamp() {
    return TimerValueGet(TIMER1_BASE, TIMER_A);
}

static uint32_t getTimeDifference(uint32_t start, uint32_t end) {
    if(end > start) {
        return end - start;
    } else {
        return end + (UINT32_MAX - start); // Assume overflow
    }
}

static uint32_t toMicroSeconds(uint32_t value) {
    return value / (SysCtlClockGet());
}

static uint32_t frequencyToPeriod(uint32_t frequency) {
    return SysCtlClockGet() / frequency;
}


// Public
void initScheduler(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    TimerDisable(TIMER1_BASE, TIMER_BOTH);
    TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC_UP);
    TimerEnable(TIMER1_BASE, TIMER_BOTH);
}

bool scheduleFrequency(uint8_t taskID, uint32_t frequency)
{
    uint32_t timeSinceLastTrigger = getTimeDifference(lastTaskTrigger[taskID], getClockTimestamp());
    uint32_t triggerPeriod = frequencyToPeriod(frequency);

    // Trigger update
    if(timeSinceLastTrigger >= triggerPeriod) {
        lastTaskTrigger[taskID] = getClockTimestamp();
        return true;
    }

    return false;
}


