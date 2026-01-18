#include "DateTimeSetupForm.h"
#include "../../../ScreenHierarchy.h"
#include "../../../../DateTimeControl/dateTimeControl.h"

//Elements to include
#include "Elements/InitialDateTimeYearElement.h"
#include "Elements/InitialDateTimeMonthElement.h"
#include "Elements/InitialDateTimeDayElement.h"
#include "Elements/InitialDateTimeHoursElement.h"
#include "Elements/InitialDateTimeMinutesElement.h"

/////////////////////// VARIABLES DECLARATION ////////////////////
Form * DateTimeSetupForm;
uint16_t yearValue = 0;
uint8_t monthValue = 0;
uint8_t dayValue = 0;
uint8_t hourValue = 0;
uint8_t minuteValue = 0;

///////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

void DateTimeSetupForm_onFocus(void* args) {
    Serial.println("DateTimeSetupForm focused");
    
    Serial.println("Initial Date Time Setup onFocus called");

    DateTime now = rtc.now();
    
    yearValue = now.year();
    monthValue = now.month();
    dayValue = now.day();
    hourValue = now.hour();
    minuteValue = now.minute();

    char yearBuff[20];
    snprintf (yearBuff, sizeof(yearBuff), "%04d", now.year());
    lv_label_set_text(ui_LoadingScreenInitialSetupYearLabel, yearBuff);

    lv_label_set_text(ui_LoadingScreenInitialSetupMonthLabel, monthToShortName(now.month() - 1));

    char dayBuff[20];
    snprintf (dayBuff, sizeof(dayBuff), "%02d", now.day());
    lv_label_set_text(ui_LoadingScreenInitialSetupDayLabel, dayBuff);

    char hourBuff[20];
    snprintf (hourBuff, sizeof(hourBuff), "%02d", now.hour());
    lv_label_set_text(ui_LoadingScreenInitialSetupHoursLabel, hourBuff);

    char minuteBuff[20];
    snprintf (minuteBuff, sizeof(minuteBuff), "%02d", now.minute());
    lv_label_set_text(ui_LoadingScreenInitialSetupMinutesLabel, minuteBuff);

    lv_event_send(ui_LoadingScreenInitialDateSetupActions, LV_EVENT_FOCUSED, NULL);

    if (DateTimeSetupForm->elements.size() > 0) {
        Serial.println("Focusing first element in DateTimeSetupForm");  
        DateTimeSetupForm->focusNextElement(); //Focus first element (year)
    }
}

void DateTimeSetupForm_onDefocus(void* args) {
    Serial.println("DateTimeSetupForm defocused");

    lv_event_send(ui_LoadingScreenInitialDateSetupActions, LV_EVENT_DEFOCUSED, NULL);
    
    ActiveScreen->focusedFormId = -1;
    ActiveScreen->focusedForm = nullptr;
}


void setupDateTimeSetupForm() {
    DateTimeSetupForm = new Form(
        "DateTimeSetupForm", //Form name
        DateTimeSetupForm_onFocus, //onFocus
        DateTimeSetupForm_onDefocus, //onDefocus
        nullptr, //onButton1
        nullptr, //onButton2
        nullptr, //onButton3
        nullptr  //onButton4
    );

    //Setup elements
    setupInitialDateTimeYearElement();
    setupInitialDateTimeMonthElement();
    setupInitialDateTimeDayElement();
    setupInitialDateTimeHoursElement();
    setupInitialDateTimeMinutesElement();

    //Add elements to form
    DateTimeSetupForm->addElement(InitialDateTimeYearElement);
    DateTimeSetupForm->addElement(InitialDateTimeMonthElement);
    DateTimeSetupForm->addElement(InitialDateTimeDayElement);
    DateTimeSetupForm->addElement(InitialDateTimeHoursElement);
    DateTimeSetupForm->addElement(InitialDateTimeMinutesElement);
}