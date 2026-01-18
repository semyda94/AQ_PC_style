#ifndef _AQ_PC_STYLE_DATE_TIME_SETUP_FORM_H
#define _AQ_PC_STYLE_DATE_TIME_SETUP_FORM_H

#include <Arduino.h>
#include "../../../Form.h"

void setupDateTimeSetupForm();

extern Form * DateTimeSetupForm;

extern uint16_t yearValue;
extern uint8_t monthValue;
extern uint8_t dayValue;
extern uint8_t hourValue;
extern uint8_t minuteValue;

#endif