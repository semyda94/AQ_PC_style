#include <string>

#include "ScreenHierarchy.h"
#include "../../ui/ui.h"

//Screens
#include "Screens/LoadingScreen/LoadingScreen.h"
#include "Screens/TempHumScreen.h"
#include "Screens/DateTimeScreen.h"
#include "Screens/SettingsScreen/SettingsScreen.h"

//Forms
#include "Screens/LoadingScreen/Forms/DateTimeSetupForm.h"
#include "Screens/LoadingScreen/Forms/NetworkSetupForm.h"


///////////////////// VARIABLES DECLARATION ////////////////////
Screen* ActiveScreen;

///////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

void setupScreens()
{
    //Screens should be setup in reverse order due to dependencies
    setupDateTimeScreen();
    setupTempHumScreen();
    setupLoadingScreen();
    setupSettingsScreen();

    //Setting up forms
    setupDateTimeSetupForm();
    setupNetworkSetupForm();

    //Setting up screen hierarchy
    LoadingScreen->next = TempHumScreen;
    LoadingScreen->addForm(DateTimeSetupForm);
    LoadingScreen->addForm(NetworkSetupForm);

    TempHumScreen->next = DateTimeScreen;
    DateTimeScreen->previous = TempHumScreen;
    DateTimeScreen->next = SettingsScreen;
    SettingsScreen->previous = DateTimeScreen;

    ActiveScreen = LoadingScreen;

    Serial.print("Loading first screen ");
    Serial.println(ActiveScreen->name);

    ActiveScreen->onLoadScreen();
}