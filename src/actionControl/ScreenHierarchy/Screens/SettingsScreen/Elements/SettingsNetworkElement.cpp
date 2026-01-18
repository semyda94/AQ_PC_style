#include "SettingsNetworkElement.h"

#include "../SettingsScreen.h"

//////////////////// VARIABLES DECLARATION ////////////////////
Element * SettingsNetworkElement;

//////////////////// FUNCTIONS IMPLEMENTATION ////////////////////


//Switch to previous screen (DateTimeScreen)
void SettingsNetworkElement_onButton2(void* args) {
    Serial.println("Switching to previous screen (DateTimeScreen)");
    
    SettingsScreen->switchToPrevious();
}

//Switch to next element (SettingsAppearanceElement)
void SettingsNetworkElement_onButton3(void* args) {
    Serial.println("Switching to next element (SettingsAppearanceElement)");

    SettingsScreen->focusNextElement();
}

//Open network settings form
void SettingsNetworkElement_onButton4(void* args) {
    Serial.println("Opening network settings form");

    // SettingsScreen->focusForm("NetworkSettingsForm");
}

void setupSettingsNetworkElement() {
    SettingsNetworkElement = new Element(
        "SettingsNetworkElement", //Element name
        false, //isFocused
        ui_NetworkIconContainer, //eventActor
        nullptr, //onButton1
        SettingsNetworkElement_onButton2, //onButton2
        SettingsNetworkElement_onButton3, //onButton3
        SettingsNetworkElement_onButton4  //onButton4
    );
}