#include "TempHumScreen.h"
#include "DateTimeScreen.h"

/////////////////////// VARIABLES DECLARATION ////////////////////
Screen * TempHumScreen = new Screen();

///////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

void setupTempHumScreen() {
    std::vector<Form> tempHumScreenForms;
    TempHumScreen->Init("TempHumScreen", DateTimeScreen, true, ui_TempHumNextButton, tempHumScreenForms, NULL);
}