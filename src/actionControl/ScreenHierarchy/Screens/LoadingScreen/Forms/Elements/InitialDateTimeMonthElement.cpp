#include "InitialDateTimeMonthElement.h"

#include "../DateTimeSetupForm.h"
#include "../../../../../DateTimeControl/dateTimeControl.h"

//////////////////// VARIABLES DECLARATION ////////////////////
Element * InitialDateTimeMonthElement;

//////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

// Previous element (year)
void InitialDateTimeMonthElement_onButton1(void* args) {
    Serial.println("Switching focus to previous element (year)");

    DateTimeSetupForm->focusPreviousElement();
}

//Decrease month value
void InitialDateTimeMonthElement_onButton2(void* args) {
    Serial.println("Decrease month value");
    monthValue--;
    if (monthValue < 1) monthValue = 12;
    
    lv_label_set_text(ui_LoadingScreenInitialSetupMonthLabel, monthToShortName(monthValue - 1));
    return;
}

//Increase month value
void InitialDateTimeMonthElement_onButton3(void* args) {
    Serial.println("Increase month value");
    monthValue++;
    if (monthValue > 12) monthValue = 1;
    
    lv_label_set_text(ui_LoadingScreenInitialSetupMonthLabel, monthToShortName(monthValue - 1));
}

//Next element (month)
void InitialDateTimeMonthElement_onButton4(void* args) {
    Serial.println("Switching focus to next element (day)");

    DateTimeSetupForm->focusNextElement();
}

void setupInitialDateTimeMonthElement() {
    InitialDateTimeMonthElement = new Element(
        "InitialDateTimeMonthElement", //Element name
        false, //isFocused
        ui_LoadingScreenInitialSetupMonthLabel, //eventActor
        InitialDateTimeMonthElement_onButton1, //onButton1
        InitialDateTimeMonthElement_onButton2, //onButton2
        InitialDateTimeMonthElement_onButton3, //onButton3
        InitialDateTimeMonthElement_onButton4  //onButton4
    );
}