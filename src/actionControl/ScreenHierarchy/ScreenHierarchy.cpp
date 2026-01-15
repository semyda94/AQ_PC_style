#include <string>

#include "ScreenHierarchy.h"
#include "../../ui/ui.h"

#include "LoadingScreen.h"
#include "TempHumScreen.h"
#include "DateTimeScreen.h"


///////////////////// VARIABLES DECLARATION ////////////////////
Screen * ActiveScreen;

///////////////////// FUNCTIONS DECLARATION ////////////////////

// void setupScreens();

///////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

void Screen::SwitchScreen() {
    Serial.println("Trying to switch screen");
    if (ActiveScreen != NULL && ActiveScreen->next != NULL) {
        Serial.println("Active screen has a next");
        
        Serial.print("Active screen ");
        Serial.println(ActiveScreen->name);

        lv_event_send(SwitchEventActor, LV_EVENT_CLICKED, NULL);
        Serial.println("switch screen event has been sent");
        
        Serial.print("New active screen ");
        ActiveScreen = ActiveScreen->next;
        Serial.println(ActiveScreen->name);

        ActiveScreen->OnLoad();
    } else {
        Serial.println("Active screen has no next");
    }
};
void Screen::OnLoad() {
    Serial.println("Trying to run onLoad for Active");
    if (ActiveScreen != NULL && ActiveScreen->onLoad != NULL){
        Serial.println("Active screen has onLoad function");
        ActiveScreen->onLoad(NULL);
    } else {
        Serial.println("Active screen doesn't have onLoad function");
    }
}


void Screen::FocusForm(int formId) {
    Serial.println("Trying to focus form");
    
    if (ActiveScreen != NULL && formId >=0 && formId < ActiveScreen->formsCount) {
        Serial.println("Form id is valid");
        if (ActiveScreen->focusedForm != NULL) {
            Serial.print("Defocus form: ");
            Serial.println(ActiveScreen->focusedForm->name);
            if (ActiveScreen->focusedForm->onDefocus != NULL) {
                ActiveScreen->focusedForm->onDefocus(NULL);
            }
        }

        ActiveScreen->focusedForm = &ActiveScreen->forms[formId];
        Serial.print("Focus form:");
        Serial.println(ActiveScreen->focusedForm->name);
        if (ActiveScreen->focusedForm->onFocus != NULL) {
            ActiveScreen->focusedForm->onFocus(NULL);
        }
    } else {
        Serial.println("Form id is not valid");
    }
}

void Screen::DefocusForm() {
    Serial.println("Trying to defocus form");
    
    if (ActiveScreen != NULL && ActiveScreen->focusedForm != NULL) {
        Serial.println("There is a focused form");

        Serial.print("Defocus form: ");
        Serial.println(ActiveScreen->focusedForm->name);
        if (ActiveScreen->focusedForm->onDefocus != NULL) {
            ActiveScreen->focusedForm->onDefocus(NULL);
        }

        ActiveScreen->focusedForm = NULL;
    } else {
        Serial.println("There is no focused form to defocus");
    }
}


void setupScreens()
{
    setupLoadingScreen();
    setupTempHumScreen();
    setupDateTimeScreen();

    ActiveScreen = LoadingScreen;
    Serial.print("Active screen ");
    Serial.println(ActiveScreen->name);
}