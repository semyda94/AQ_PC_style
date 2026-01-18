#include "LoadingScreen.h"
#include "../../Screen.h"
#include "../TempHumScreen.h"

// #include "../DateTimeControl/dateTimeControl.h"

// /////////////////////// VARIABLES DECLARATION ////////////////////
Screen * LoadingScreen;



// ///////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

void setupLoadingScreen() {
    LoadingScreen = new Screen(
        "LoadingScreen", //Screen name
        false, //Is screen actionable on load
        nullptr, //On load function
        ui_LoadingScreenSwitchToTempHumScreen, //Actor to trigger switch to next screen
        nullptr, //Actor to trigger switch to previous screen
        nullptr, //onButton1
        nullptr, //onButton2
        nullptr, //onButton3
        nullptr  //onButton4
    );
}