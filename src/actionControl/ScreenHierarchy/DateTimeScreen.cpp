#include "DateTimeScreen.h"

/////////////////////// VARIABLES DECLARATION ////////////////////
Screen * DateTimeScreen = new Screen();

///////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

void setupDateTimeScreen() {
    std::vector<Form> dateTimeScreenForms;
    DateTimeScreen->Init("DateTimeScreen", NULL, true, NULL, dateTimeScreenForms, NULL);
}