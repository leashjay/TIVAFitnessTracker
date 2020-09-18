/*
 * fitnessTrackerDisplay.c
 *
 *  Created on: 14/03/2020
 *      Author: csm119 & dss57
 */

#include "fitnessTrackerDisplay.h"

void initDisplay(void)
{
    OLEDInitialise ();
}


float accelRawToG(float raw)
{
    return raw / 256.0;
}

float accelRawToMps(int16_t raw)
{
    return accelRawToG(raw) * 9.81;
}

void drawAccelScreen(display_mode mode, vector3_t accel, vector3_t orientation)
{
    const char* display_mode_str[] = { "RAW ", "G   ", "MS-2" };
    char string[17];  // 16 characters across the display

    // Draw Mode
    usnprintf (string, sizeof(string), "MODE: %s", display_mode_str[mode]);
    OLEDStringDraw (string, 0, 0);

    // Convert units
    float disp_accel_x, disp_accel_y, disp_accel_z = 0.0;
    switch(mode) {
        case ACCEL_RAW:
            disp_accel_x = accel.x;
            disp_accel_y = accel.y;
            disp_accel_z = accel.z;
            break;
        case ACCEL_G:
            disp_accel_x = accelRawToG(accel.x);
            disp_accel_y = accelRawToG(accel.y);
            disp_accel_z = accelRawToG(accel.z);
            break;
        case ACCEL_MPSS:
            disp_accel_x = accelRawToMps(accel.x);
            disp_accel_y = accelRawToMps(accel.y);
            disp_accel_z = accelRawToMps(accel.z);
            break;
    }


    // Draw Acceleration
    // Note(Connor): I designed this to display floats before realizing float formating
    // is not supported in usnprintf
    usnprintf (string, sizeof(string), "X %4d  OX %4d", (int)(disp_accel_x + 0.5), orientation.x);
    OLEDStringDraw (string, 0, 1);

    usnprintf (string, sizeof(string), "Y %4d  OY %4d", (int)(disp_accel_y + 0.5), orientation.y);
    OLEDStringDraw (string, 0, 2);

    usnprintf (string, sizeof(string), "Z %4d  OZ %4d", (int)(disp_accel_z + 0.5), orientation.z);
    OLEDStringDraw (string, 0, 3);
}



