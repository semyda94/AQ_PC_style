#include "InitialDateTimeYearElement.h"

#include "../DateTimeSetupForm.h"

//////////////////// VARIABLES DECLARATION ////////////////////
Element * InitialDateTimeYearElement;

//////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

//Decrease year value
void InitialDateTimeYearElement_onButton2(void* args) {
    Serial.println("Decrease year value");
    yearValue--;
    char yearBuff[20];
    snprintf (yearBuff, sizeof(yearBuff), "%04d", yearValue);
    lv_label_set_text(ui_LoadingScreenInitialSetupYearLabel, yearBuff);
}

//Increase year value
void InitialDateTimeYearElement_onButton3(void* args) {
    Serial.println("Increase year value");
    yearValue++;

    char yearBuff[20];
    snprintf (yearBuff, sizeof(yearBuff), "%04d", yearValue);
    lv_label_set_text(ui_LoadingScreenInitialSetupYearLabel, yearBuff);
}

//Next element (month)
void InitialDateTimeYearElement_onButton4(void* args) {
    Serial.println("Switching focus to next element (month)");

    DateTimeSetupForm->focusNextElement();
}

void setupInitialDateTimeYearElement() {
    InitialDateTimeYearElement = new Element(
        "InitialDateTimeYearElement", //Element name
        false, //isFocused
        ui_LoadingScreenInitialSetupYearLabel, //eventActor
        nullptr, //onButton1
        InitialDateTimeYearElement_onButton2, //onButton2
        InitialDateTimeYearElement_onButton3, //onButton3
        InitialDateTimeYearElement_onButton4  //onButton4
    );
}