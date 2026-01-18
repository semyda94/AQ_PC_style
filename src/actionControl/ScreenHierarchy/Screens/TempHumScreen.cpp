#include "TempHumScreen.h"
#include "DateTimeScreen.h"
#include "../ScreenHierarchy.h"

/////////////////////// VARIABLES DECLARATION ////////////////////
Screen * TempHumScreen;

/////////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

void handleButton3TempHumScreen(void* data) {
    ActiveScreen->switchToNext();        
}

void setupTempHumScreen() {
    TempHumScreen = new Screen(
        "TempHumScreen", //Screen name
        true, //Is screen actionable on load
        nullptr, //On load function
        ui_TempHumNextButton, //Actor to trigger switch to next screen,
        nullptr,  //Actor to trigger switch to previous screen
        nullptr, //onButton1
        nullptr, //onButton2
        handleButton3TempHumScreen, //onButton3
        nullptr  //onButton4
    );
}