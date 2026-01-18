#include "InitialDateTimeMinutesElement.h"

#include "../DateTimeSetupForm.h"
#include "../../../../../DateTimeControl/dateTimeControl.h"

//////////////////// VARIABLES DECLARATION ////////////////////
Element * InitialDateTimeMinutesElement;

//////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

// Previous element (ho)
void InitialDateTimeMinutesElement_onButton1(void* args) {
    Serial.println("Switching focus to previous element (hours)");

    DateTimeSetupForm->focusPreviousElement();
}

//Decrease minutes value
void InitialDateTimeMinutesElement_onButton2(void* args) {
    Serial.println("Decrease minute value");
    
    if (minuteValue == 0) minuteValue = 59; else minuteValue--;
        
    char minuteBuff[20];
    snprintf (minuteBuff, sizeof(minuteBuff), "%02d", minuteValue);
    lv_label_set_text(ui_LoadingScreenInitialSetupMinutesLabel, minuteBuff);
}

//Increase minutes value
void InitialDateTimeMinutesElement_onButton3(void* args) {
    Serial.println("Increase minute value");
    
    minuteValue++;
    if (minuteValue > 59) minuteValue = 0;
    
    char minuteBuff[20];
    snprintf (minuteBuff, sizeof(minuteBuff), "%02d", minuteValue);
    lv_label_set_text(ui_LoadingScreenInitialSetupMinutesLabel, minuteBuff);
}

//Save values into RTC and defocus form
void InitialDateTimeMinutesElement_onButton4(void* args) {
    Serial.println("Saving date time to RTC and defocusing form");
    DateTime newDateTime(yearValue, monthValue, dayValue, hourValue, minuteValue, 0);
    setupDateTime(newDateTime);

    Serial.println("Defocusing DateTimeSetupForm");
    DateTimeSetupForm->defocusForm();
}

void setupInitialDateTimeMinutesElement() {
    InitialDateTimeMinutesElement = new Element(
        "InitialDateTimeMinutesElement", //Element name
        false, //isFocused
        ui_LoadingScreenInitialSetupMinutesLabel, //eventActor
        InitialDateTimeMinutesElement_onButton1, //onButton1
        InitialDateTimeMinutesElement_onButton2, //onButton2
        InitialDateTimeMinutesElement_onButton3, //onButton3
        InitialDateTimeMinutesElement_onButton4  //onButton4
    );
}