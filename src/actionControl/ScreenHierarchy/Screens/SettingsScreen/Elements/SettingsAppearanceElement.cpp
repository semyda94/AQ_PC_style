#include "SettingsAppearanceElement.h"

#include "../SettingsScreen.h"

//////////////////// VARIABLES DECLARATION ////////////////////
Element * SettingsAppearanceElement;

//////////////////// FUNCTIONS IMPLEMENTATION ////////////////////


//Switch to previous element (SettingsNetworkElement)
void SettingsAppearanceElement_onButton2(void* args) {
    Serial.println("Switching to previous element (SettingsNetworkElement)");
    
    SettingsScreen->focusPreviousElement();
}

//Switch to next element (SettingsDateTimeElement)
void SettingsAppearanceElement_onButton3(void* args) {
    Serial.println("Switching to next element (SettingsDateTimeElement)");

    SettingsScreen->focusNextElement();
}

//Open appearance settings form
void SettingsAppearanceElement_onButton4(void* args) {
    Serial.println("Opening appearance settings form");

    // SettingsScreen->focusForm("AppearanceSettingsForm");
}

void setupSettingsAppearanceElement() {
    SettingsAppearanceElement = new Element(
        "SettingsAppearanceElement", //Element name
        false, //isFocused
        ui_AppearanceIconContainer, //eventActor
        nullptr, //onButton1
        SettingsAppearanceElement_onButton2, //onButton2
        SettingsAppearanceElement_onButton3, //onButton3
        SettingsAppearanceElement_onButton4  //onButton4
    );
}