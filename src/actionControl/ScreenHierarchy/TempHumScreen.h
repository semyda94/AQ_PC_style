#ifndef _AQ_PC_STYLE_TEMP_HUM_SCREEN_H
#define _AQ_PC_STYLE_TEMP_HUM_SCREEN_H

#include <Arduino.h>
#include <string>
#include <vector>
#include <iostream>

#include "ScreenHierarchy.h"
#include "../../ui/ui.h"


void setupTempHumScreen();

extern Screen * TempHumScreen;

#endif