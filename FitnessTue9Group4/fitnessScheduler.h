/*
 * fitnessScheduler.h
 *
 *  Created on: 26/05/2020
 *      Author: csm119
 */

#ifndef FITNESSSCHEDULER_H_
#define FITNESSSCHEDULER_H_

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "inc/hw_memmap.h"

// This scheduler does not use dynamic memory allocation
// For now it instead has a max count that can be adjusted
#define MAX_TASKCOUNT 20


void initScheduler(void);

// Returns true if task should be run
// Should return true at input frequency
bool scheduleFrequency(uint8_t taskID, uint32_t frequency);


#endif /* FITNESSSCHEDULER_H_ */
