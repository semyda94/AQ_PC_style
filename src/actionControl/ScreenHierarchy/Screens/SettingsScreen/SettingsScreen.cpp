#include "SettingsScreen.h"
#include "../../ScreenHierarchy.h"
#include "../DateTimeScreen.h"

//Elements
#include "Elements/SettingsNetworkElement.h"
#include "Elements/SettingsAppearanceElement.h"
#include "Elements/SettingsDateTimeElement.h"

/////////////////////// VARIABLES DECLARATION ////////////////////
Screen * SettingsScreen;

///////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

void SettingsScreen_onLoad(void* args) {
    Serial.println("SettingsScreen loaded");

    if (SettingsScreen->focusedForm != nullptr) {
        Serial.println("Focusing first form in SettingsScreen");
        SettingsScreen->focusedForm->defocusForm(); //Focus first form if any
        SettingsScreen->focusedForm = nullptr;
        SettingsScreen->focusedFormId = -1;
    }

    //Focus first element (SettingsNetworkElement)
    if (SettingsScreen->elements.size() > 0) {
        Serial.println("Focusing first element in SettingsScreen");  
        SettingsScreen->focusNextElement();
    }
}

void setupSettingsScreen() {
    SettingsScreen = new Screen(
        "SettingsScreen", //Screen name
        true, //Is screen actionable on load
        SettingsScreen_onLoad, //On load function
        nullptr, //Actor to trigger switch to next screen
        ui_SettingsScreenPreviousButton,  //Actor to trigger switch to previous screen
        nullptr, //onButton1
        nullptr, //onButton2
        nullptr, //onButton3
        nullptr  //onButton4
    );

    //Setup Elements
    setupSettingsNetworkElement();
    setupSettingsAppearanceElement();
    setupSettingsDateTimeElement();

    //Add Elements to SettingsScreen
    SettingsScreen->addElement(SettingsNetworkElement);
    SettingsScreen->addElement(SettingsAppearanceElement);
    SettingsScreen->addElement(SettingsDateTimeElement);
}