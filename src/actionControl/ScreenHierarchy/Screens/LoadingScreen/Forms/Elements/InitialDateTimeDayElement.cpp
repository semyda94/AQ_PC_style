#include "InitialDateTimeDayElement.h"

#include "../DateTimeSetupForm.h"

//////////////////// VARIABLES DECLARATION ////////////////////
Element * InitialDateTimeDayElement;

//////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

// Previous element (month)
void InitialDateTimeDayElement_onButton1(void* args) {
    Serial.println("Switching focus to previous element (month)");

    DateTimeSetupForm->focusPreviousElement();
}

//Decrease day value
void InitialDateTimeDayElement_onButton2(void* args) {
    Serial.println("Decrease day value");
    
    dayValue--;
    if (dayValue < 1) dayValue = 31;
        
    char dayBuff[20];
    snprintf (dayBuff, sizeof(dayBuff), "%02d", dayValue);
    lv_label_set_text(ui_LoadingScreenInitialSetupDayLabel, dayBuff);
}

//Increase day value
void InitialDateTimeDayElement_onButton3(void* args) {
    Serial.println("Increase day value");
    dayValue++;
    if (dayValue > 31) dayValue = 1;
    
    char dayBuff[20];
    snprintf (dayBuff, sizeof(dayBuff), "%02d", dayValue);
    lv_label_set_text(ui_LoadingScreenInitialSetupDayLabel, dayBuff);
}

//Next element (hours)
void InitialDateTimeDayElement_onButton4(void* args) {
    Serial.println("Switching focus to next element (hours)");

    DateTimeSetupForm->focusNextElement();
}

void setupInitialDateTimeDayElement() {
    InitialDateTimeDayElement = new Element(
        "InitialDateTimeDayElement", //Element name
        false, //isFocused
        ui_LoadingScreenInitialSetupDayLabel, //eventActor
        InitialDateTimeDayElement_onButton1, //onButton1
        InitialDateTimeDayElement_onButton2, //onButton2
        InitialDateTimeDayElement_onButton3, //onButton3
        InitialDateTimeDayElement_onButton4  //onButton4
    );
}