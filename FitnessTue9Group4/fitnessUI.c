/*
 * fitnessUI.c
 *
 *  Created on: 6/05/2020
 *      Author: dss57
 */

#include "fitnessUI.h"

// Defines
#define MILES_PER_KM 0.62
#define TEST_STEPS_UP 100
#define TEST_STEPS_DOWN 500
#define STEPS_TO_KM 0.0009

// ========
// UI Types
// ========

const char* DISTANCE_UNITS_STR[] = { "KM", "MI"};
typedef enum {
    DISTANCE_KM,
    DISTANCE_MI
} UI_DistanceUnits_t;

typedef enum {
    SCREEN_STEPS,
    SCREEN_DISTANCE
} UI_ScreenState_t;


// ============
// UI Variables
// ============

uint32_t UI_totalSteps = 0;
float UI_totalDistance = 0; // Distance in km
uint32_t UI_stepsAtReset = 0;
float UI_distanceAtReset = 0; // Distance in km

UI_DistanceUnits_t UI_distUnits = DISTANCE_KM;
UI_ScreenState_t UI_scrState = SCREEN_STEPS;

bool testFlag = false;
bool staticRedraw = true;

// =================
// Private Functions
// =================


// Utility Functions
// -----------------

int32_t getCurrentSteps(void) {
    return UI_totalSteps - UI_stepsAtReset;
}

float getCurrentDistance(void) {
    float distance = UI_totalDistance - UI_distanceAtReset;

    if (UI_distUnits == DISTANCE_MI) {
        distance *= MILES_PER_KM;
    }

    return distance;
}

void resetSteps(void) {
    UI_stepsAtReset = UI_totalSteps;
}

void resetDistance(void) {
    UI_distanceAtReset = UI_totalDistance;
}

// Switches between distance units
void toggleDistanceUnits(void)
{
   if (UI_distUnits == DISTANCE_KM) {
       UI_distUnits = DISTANCE_MI;
   } else if (UI_distUnits == DISTANCE_MI) {
      UI_distUnits = DISTANCE_KM;
  }
}

void formatFloatToStr(char* buffer, int length, float number) {
    int dp_factor = 1000;

    int integer = (int)number;
    int decimal = (number - integer) * dp_factor;

    usnprintf(buffer, length, "%d.%03d", integer, decimal);
}


// Screen Functions
// ----------------

void setScreen(UI_ScreenState_t state) {
    UI_scrState = state;
    staticRedraw = true;
}

void pollTestUpdate() {
    if (checkButton(DOWN) == PUSHED) {
        UI_stepsAtReset += TEST_STEPS_DOWN;
        UI_distanceAtReset += TEST_STEPS_DOWN * STEPS_TO_KM;
    }
    if (checkButton(UP) == PUSHED) {
        UI_stepsAtReset -= TEST_STEPS_UP;
        UI_distanceAtReset -= TEST_STEPS_UP * STEPS_TO_KM;
    }

    if(getCurrentSteps() < 0) UI_stepsAtReset = UI_totalSteps;
    if(getCurrentDistance() < 0) UI_distanceAtReset = UI_totalDistance;
}

void pollStepScreen(void)
{
    updateButtons();

    // Switch to distance screen
    if (checkButton(LEFT) == PUSHED || checkButton(RIGHT) == PUSHED) {
         setScreen(SCREEN_DISTANCE);
    }

    if (testFlag) {
        pollTestUpdate();
    } else {
        // Reset the step count
        if (checkTimedButton(DOWN, 1000) == PUSHED) {
            resetSteps();
        }
    }
}

void pollDistanceScreen(void)
{
    updateButtons();

    // Switch to steps screen
    if (checkButton(LEFT) == PUSHED || checkButton(RIGHT) == PUSHED) {
        setScreen(SCREEN_STEPS);
    }

    if (testFlag) {
       pollTestUpdate();
    } else {
        // Switch distance units
        if (checkButton(UP) == PUSHED) {
            toggleDistanceUnits();
        }

        // Reset the distance
        if (checkTimedButton(DOWN, 1000) == PUSHED) {
            resetDistance();
        }
    }
}

void drawStaticTestIcons(void) {
    draw_up_arrow(120, 9);
    OLEDStringDraw("T", 15, 2);
    draw_down_arrow(120, 25);
}

void drawStaticStepsScreen(void)
{
    OrbitOledClear();

    char str_steps[17]=" ";
    usnprintf (str_steps, sizeof(str_steps), "%d", getCurrentSteps());

    OLEDStringDraw("STEPS", 3 , 0);


    OLEDStringDraw("''", 0, 2);

    draw_line(0,8,128, 8);
    draw_steps_icon(3, 15);

    if(testFlag) drawStaticTestIcons();

    staticRedraw = false;
}


void drawStaticDistanceScreen(void)
{
    OrbitOledClear();

    OLEDStringDraw("DISTANCE", 3 , 0);

    draw_line(0,8,128, 8);
    draw_distance_icon(2, 15);

    if(testFlag) drawStaticTestIcons();

    staticRedraw = false;
}

void drawStepsScreen(void)
{
    if(staticRedraw) drawStaticStepsScreen();

    char str_steps[17]=" ";
    usnprintf (str_steps, sizeof(str_steps), "%d    ", getCurrentSteps());
    OLEDStringDraw(str_steps, 3, 2);
}


void drawDistanceScreen(void)
{
    if(staticRedraw) drawStaticDistanceScreen();

    char str_dist[17]=" ";
    formatFloatToStr(str_dist, sizeof(str_dist), getCurrentDistance());
    OLEDStringDraw(" ", 8, 2);
    OLEDStringDraw(str_dist, 3, 2);
    OLEDStringDraw(DISTANCE_UNITS_STR[UI_distUnits], 9, 2);
}

// ===================
// Interface Functions
// ===================


// Sets total number of steps for UI
void setTotalSteps(uint32_t steps)
{
    UI_totalSteps = steps;
}

// Sets total distance for UI
void setTotalDistance(float distance)
{
    UI_totalDistance = distance;
}

// Polls user input for UI
void pollUI(void)
{
    updateSwitches();
    bool oldTestFlag = testFlag;
    testFlag = (checkSwitch(SW1) == SWITCH_UP);
    if(oldTestFlag != testFlag) staticRedraw = true;

    switch(UI_scrState) {
    case SCREEN_STEPS:
        pollStepScreen();
        break;
    case SCREEN_DISTANCE:
        pollDistanceScreen();
        break;
    }

}

// Draws current screen for UI
void drawUI(void)
{
    switch(UI_scrState) {
    case SCREEN_STEPS:
        drawStepsScreen();
        break;
    case SCREEN_DISTANCE:
        drawDistanceScreen();
        break;
    }
}

void initUI(void) {
    initTimedButton();
    initButtons();
    OLEDInitialise ();
    initSwitches();
}


