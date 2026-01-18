#include <string>

#include "ScreenHierarchy.h"
#include "../../ui/ui.h"

//Screens
#include "Screens/LoadingScreen/LoadingScreen.h"
#include "Screens/TempHumScreen.h"
#include "Screens/DateTimeScreen.h"
#include "Screens/SettingsScreen.h"

//Forms
#include "Screens/LoadingScreen/Forms/DateTimeSetupForm.h"
#include "Screens/LoadingScreen/Forms/NetworkSetupForm.h"


///////////////////// VARIABLES DECLARATION ////////////////////
Screen* ActiveScreen;

///////////////////// FUNCTIONS DECLARATION ////////////////////

///////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

// void Screen::SwitchScreen() {
//     Serial.println("Trying to switch screen");
//     if (ActiveScreen != NULL && ActiveScreen->next != NULL) {
//         Serial.println("Active screen has a next");
        
//         Serial.print("Active screen ");
//         Serial.println(ActiveScreen->name);

//         lv_event_send(SwitchEventActor, LV_EVENT_CLICKED, NULL);
//         Serial.println("switch screen event has been sent");
        
//         Serial.print("New active screen ");
//         ActiveScreen = ActiveScreen->next;
//         Serial.println(ActiveScreen->name);

//         ActiveScreen->OnLoad();
//     } else {
//         Serial.println("Active screen has no next");
//     }
// };
// void Screen::OnLoad() {
//     Serial.println("Trying to run onLoad for Active");
//     if (ActiveScreen != NULL && ActiveScreen->onLoad != NULL){
//         Serial.println("Active screen has onLoad function");
//         ActiveScreen->onLoad(NULL);
//     } else {
//         Serial.println("Active screen doesn't have onLoad function");
//     }
// }


// void Screen::FocusForm(int formId) {
//     Serial.println("Trying to focus form");
    
//     if (ActiveScreen != NULL && formId >=0 && formId < ActiveScreen->formsCount) {
//         Serial.println("Form id is valid");
//         if (ActiveScreen->focusedForm != NULL) {
//             Serial.print("Defocus form: ");
//             Serial.println(ActiveScreen->focusedForm->name);
//             if (ActiveScreen->focusedForm->onDefocus != NULL) {
//                 ActiveScreen->focusedForm->onDefocus(NULL);
//             }
//         }

//         ActiveScreen->focusedForm = &ActiveScreen->forms[formId];
//         Serial.print("Focus form:");
//         Serial.println(ActiveScreen->focusedForm->name);
//         if (ActiveScreen->focusedForm->onFocus != NULL) {
//             ActiveScreen->focusedForm->onFocus(NULL);
//         }
//     } else {
//         Serial.println("Form id is not valid");
//     }
// }

// void Screen::DefocusForm() {
//     Serial.println("Trying to defocus form");
    
//     if (ActiveScreen != NULL && ActiveScreen->focusedForm != NULL) {
//         Serial.println("There is a focused form");

//         Serial.print("Defocus form: ");
//         Serial.println(ActiveScreen->focusedForm->name);
//         if (ActiveScreen->focusedForm->onDefocus != NULL) {
//             ActiveScreen->focusedForm->onDefocus(NULL);
//         }

//         ActiveScreen->focusedForm = NULL;
//     } else {
//         Serial.println("There is no focused form to defocus");
//     }
// }


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