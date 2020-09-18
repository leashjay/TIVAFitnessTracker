/*
 * timedButton.h
 *
 *  Created on: 6/05/2020
 *      Author: dss57 & csm119
 */

#ifndef TIMEDBUTTON_H_
#define TIMEDBUTTON_H_

#include <stdint.h>
#include <stdbool.h>
#include "buttons4.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "inc/hw_memmap.h"


void initTimedButton(void);

// Checks a polled button is held for a duration before
// returning pushed
int checkTimedButton(int button, int milliseconds);


#endif /* TIMEDBUTTON_H_ */
