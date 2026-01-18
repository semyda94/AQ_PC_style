#include "SettingsScreen.h"
#include "../ScreenHierarchy.h"
#include "DateTimeScreen.h"

/////////////////////// VARIABLES DECLARATION ////////////////////
Screen * SettingsScreen;

///////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

void handleButton2SettingsScreen(void* data) {
    ActiveScreen->switchToPrevious();        
}

void setupSettingsScreen() {
    SettingsScreen = new Screen(
        "SettingsScreen", //Screen name
        true, //Is screen actionable on load
        nullptr, //On load function
        nullptr, //Actor to trigger switch to next screen
        ui_SettingsScreenPreviousButton,  //Actor to trigger switch to previous screen
        nullptr, //onButton1
        handleButton2SettingsScreen, //onButton2
        nullptr, //onButton3
        nullptr  //onButton4
    );
}