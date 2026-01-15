#ifndef _AQ_PC_STYLE_DATETIME_CONTROL_H
#define _AQ_PC_STYLE_DATETIME_CONTROL_H

#include <Arduino.h>
#include "RTClib.h"


void setupDateTime(void);
void dateTimeControl(void* pvParameters);
void setupDateTime(DateTime &now);

const char* monthToShortName(int tm_mon);

extern RTC_DS3231 rtc;

#endif
