#include "DateTimeScreen.h"
#include "../ScreenHierarchy.h"
#include "TempHumScreen.h"

/////////////////////// VARIABLES DECLARATION ////////////////////
Screen * DateTimeScreen;

///////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

void handleButton2DateTimeScreen(void* data) {
    ActiveScreen->switchToPrevious();        
}

void handleButton3DateTimeScreen(void* data) {
    ActiveScreen->switchToNext();        
}

void setupDateTimeScreen() {
    DateTimeScreen = new Screen(
        "DateTimeScreen", //Screen name
        true, //Is screen actionable on load
        nullptr, //On load function
        ui_DateTimeScreenNextButton, //Actor to trigger switch to next screen
        ui_DateTimeScreenPreviousButton,  //Actor to trigger switch to previous screen
        nullptr, //onButton1
        handleButton2DateTimeScreen, //onButton2
        handleButton3DateTimeScreen, //onButton3
        nullptr  //onButton4
    );
}