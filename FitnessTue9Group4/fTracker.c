//********************************************************
//
// Fitness Tracker Main file
// (copied from ADCdemo.c) with files removed
//
// Link with modules:  buttons2, OrbitOLEDInterface
//
// Author:  A.D.C. Tuesday 9 Group 4
// Last modified:	12.03.2020
//

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_i2c.h"
#include "driverlib/pin_map.h" //Needed for pin float accelRawToG(float raw)configure
#include "driverlib/systick.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/timer.h"
#include "../OrbitOLED/OrbitOLEDInterface.h"
#include "i2c_driver.h"
#include "utils/ustdlib.h"
#include "driverlib/adc.h"
#include "driverlib/pwm.h"
#include "driverlib/interrupt.h"
#include "driverlib/debug.h"
#include "serialCom.h"
#include "circBufT.h"
#include "buttons4.h"
#include "fitnessTrackerDisplay.h"
#include "acc.h"
#include "fitnessUI.h"
#include "OledCustom.h"
#include "fitnessScheduler.h"

//*****************************************************************************
// Constants
//*****************************************************************************
#define BUF_SIZE 10
#define SAMPLE_RATE_HZ 75
#define SCREEN_RATE_HZ 200
#define STEP_THRESHOLD 1.5
#define DISTANCE_MULTIPLIER 0.0009

//*****************************************************************************
// Global variables
//*****************************************************************************
vector3_t   g_newAccelData = {0};
bool        g_newAccelFlag = false;

circBuf_t g_inXBuffer;   // Buffer of size BUF_SIZE integers (sample values)
circBuf_t g_inYBuffer;
circBuf_t g_inZBuffer;

volatile vector3_t meanXYZ;
volatile uint16_t g_meanMag;

bool g_isStepping = false;
volatile uint32_t g_iStepCount;
volatile float g_fDistanceTracker;

//*****************************************************************************
//static bool
// The interrupt handler for the for SysTick interrupt.
//
//*****************************************************************************
void
SysTickIntHandler(void)
{
    // Get data using mailbox prototype
    // Read data from accelerometer using I2C
    g_newAccelData = getAcclData();
    g_newAccelFlag = true;
}

//*****************************************************************************
// Initialisation functions for the clock (incl. SysTick), ADC, display
//*****************************************************************************
void
initClock(void)
{
    // Set the clock rate to 20 MHz
    /* divider of 10, phase lock loop */
    SysCtlClockSet(SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
    SYSCTL_XTAL_16MHZ);
    //
    // Set up the period for the SysTick timer.  The SysTick timer period is
    // set as a function of the system clock.
    SysTickPeriodSet(SysCtlClockGet() / SAMPLE_RATE_HZ);

    // Register the interrupt handler
    SysTickIntRegister(SysTickIntHandler);
    //
    // Enable interrupt and device
    SysTickIntEnable();
    SysTickEnable();
}

//******************************************************************************
/*
 * Function to initialise all three buffers for accelerometer data collection *
 */
//*****************************************************************************
void
initXYZBuffers()
{
    initCircBuf(&g_inXBuffer, BUF_SIZE);
    initCircBuf(&g_inYBuffer, BUF_SIZE);
    initCircBuf(&g_inZBuffer, BUF_SIZE);
}

// Updates buffer contents if data is available
void updateXYZBuffers()
{
    if(g_newAccelFlag)
    {
        IntMasterDisable();
        writeCircBuf(&g_inXBuffer, g_newAccelData.x);
        writeCircBuf(&g_inYBuffer, g_newAccelData.y);
        writeCircBuf(&g_inZBuffer, g_newAccelData.z);
        g_newAccelFlag = false;
        IntMasterEnable();
    }
}

//******************************************************************************
/*
 * Function to calculate mean of data set in buffer
 * Background task: calculate the (approximate) mean of the values in the
 * circular buffcalculateDistanceer
 */
//*****************************************************************************
vector3_t
calculateMean(void)
{
    uint16_t i;
    int32_t sumX;
    int32_t sumY;
    int32_t sumZ;
    float sumMag;

    i = 0;
    sumX = sumY = sumZ = sumMag = 0;
    meanXYZ.mag = 0.0;

    //LOOP all 3 simultaneous
    for (i = 0; i < BUF_SIZE; i++)
    {
        sumX = sumX + readCircBuf(&g_inXBuffer);
        sumY = sumY + readCircBuf(&g_inYBuffer);
        sumZ = sumZ + readCircBuf(&g_inZBuffer);
    }

    // Calculate and store the rounded mean of the buffer contents
    vector3_t meanXYZ;     // Vector object to store mean of x,y,z values
    meanXYZ.x = (2 * sumX + BUF_SIZE) / 2 / BUF_SIZE;
    meanXYZ.y = (2 * sumY + BUF_SIZE) / 2 / BUF_SIZE;
    meanXYZ.z = (2 * sumZ + BUF_SIZE) / 2 / BUF_SIZE;

    //include the magnitude in the struct
    sumMag = sqrt(
            (meanXYZ.x * meanXYZ.x) + (meanXYZ.x * meanXYZ.x)
                    + (meanXYZ.z * meanXYZ.z));
    meanXYZ.mag = sumMag / 256.0;

    return meanXYZ;
}

//******************************************************************************
/*
 * Translate steps into a distance measurement.
 * Assignment requirements recommend 0.9m multiplier
 */
//******************************************************************************
void
cacluateDistance(void)
{
    g_fDistanceTracker += DISTANCE_MULTIPLIER;
}

//******************************************************************************
/*
 * Calculate steps, if value is greater than the step threshold value
 * (1.5 provided in assignment requirements) and the we are currently stepping
 *  increments global  step counter.
 */
//******************************************************************************
void
checkSampleStep(float magnitude)
{

    if (magnitude >= STEP_THRESHOLD)
    {
        if (!g_isStepping)
        {
            g_isStepping = true;
            g_iStepCount++;
            cacluateDistance();
        }
    }
    else
    {
        g_isStepping = false;
    }
}

// Main Entry point
int
main(void)
{
    initAccl();
    initClock();
    initDisplay();
    initButtons();
    initXYZBuffers();
    initUI();
    initScheduler();

    g_iStepCount = 0;
    g_fDistanceTracker = 0.0;


    // Enable interrupts to the processor.
    IntMasterEnable();

    // Kernel Loop
    vector3_t orientation = getAcclData();

    while (1)
    {
        // Update accelerometer buffers
        if(scheduleFrequency(0, SAMPLE_RATE_HZ)) updateXYZBuffers();

        // Calculate if a step has been taken
        if(scheduleFrequency(1, SAMPLE_RATE_HZ)) checkSampleStep(calculateMean().mag);

        // Update UI shown values
        if(scheduleFrequency(2, 10)) setTotalSteps(g_iStepCount);
        if(scheduleFrequency(3, 10)) setTotalDistance(g_fDistanceTracker);

        // Update UI based on user input
        if(scheduleFrequency(4, 30)) pollUI();

        // Draw UI updates
        if(scheduleFrequency(5, 15)) drawUI();
    }

}

