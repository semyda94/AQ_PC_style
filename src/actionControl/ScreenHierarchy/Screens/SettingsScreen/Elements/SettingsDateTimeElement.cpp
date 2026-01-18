#include "SettingsDateTimeElement.h"

#include "../SettingsScreen.h"

//////////////////// VARIABLES DECLARATION ////////////////////
Element * SettingsDateTimeElement;

//////////////////// FUNCTIONS IMPLEMENTATION ////////////////////


//Switch to previous element (SettingsAppearanceElement)
void SettingsDateTimeElement_onButton2(void* args) {
    Serial.println("Switching to previous element (SettingsAppearanceElement)");
    
    SettingsScreen->focusPreviousElement();
}

//Open date and time settings form
void SettingsDateTimeElement_onButton4(void* args) {
    Serial.println("Opening date and time settings form");

    // SettingsScreen->focusForm("DateTimeSettingsForm");
}

void setupSettingsDateTimeElement() {
    SettingsDateTimeElement = new Element(
        "SettingsDateTimeElement", //Element name
        false, //isFocused
        ui_DateTimeIconContainer, //eventActor
        nullptr, //onButton1
        SettingsDateTimeElement_onButton2, //onButton2
        nullptr, //onButton3
        SettingsDateTimeElement_onButton4  //onButton4
    );
}