#include "InitialDateTimeHoursElement.h"

#include "../DateTimeSetupForm.h"

//////////////////// VARIABLES DECLARATION ////////////////////
Element * InitialDateTimeHoursElement;

//////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

// Previous element (day)
void InitialDateTimeHoursElement_onButton1(void* args) {
    Serial.println("Switching focus to day element");

    DateTimeSetupForm->focusPreviousElement();
}

//Decrease hours value
void InitialDateTimeHoursElement_onButton2(void* args) {
    Serial.println("Decrease hour value");
    if (hourValue == 0) hourValue = 23; else hourValue--;
    
    char hourBuff[20];
    snprintf (hourBuff, sizeof(hourBuff), "%02d", hourValue);
    lv_label_set_text(ui_LoadingScreenInitialSetupHoursLabel, hourBuff);
}

//Increase hours value
void InitialDateTimeHoursElement_onButton3(void* args) {
    Serial.println("Increase hour value");
    
    hourValue++;
    if (hourValue > 23) hourValue = 0;
    
    char hourBuff[20];
    snprintf (hourBuff, sizeof(hourBuff), "%02d", hourValue);
    lv_label_set_text(ui_LoadingScreenInitialSetupHoursLabel, hourBuff);
}

//Next element (minutes)
void InitialDateTimeHoursElement_onButton4(void* args) {
    Serial.println("Switching focus to minutes element");

    DateTimeSetupForm->focusNextElement();
}

void setupInitialDateTimeHoursElement() {
    InitialDateTimeHoursElement = new Element(
        "InitialDateTimeHoursElement", //Element name
        false, //isFocused
        ui_LoadingScreenInitialSetupHoursLabel, //eventActor
        InitialDateTimeHoursElement_onButton1, //onButton1
        InitialDateTimeHoursElement_onButton2, //onButton2
        InitialDateTimeHoursElement_onButton3, //onButton3
        InitialDateTimeHoursElement_onButton4  //onButton4
    );
}