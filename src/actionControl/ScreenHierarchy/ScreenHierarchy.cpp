#include "ScreenHierarchy.h"
#include "../../ui/ui.h"
#include "../wifiControl/wifiControl.h"

#include <string>


///////////////////// VARIABLES DECLARATION ////////////////////
Screen * LoadingScreen = new Screen();

Screen * TempHumScreen = new Screen();

Screen * DateTimeScreen = new Screen();

Screen * SettingsScreen = new Screen();
Element * NetworkConnectionsElement = new Element();
Element * AppearanceElement = new Element();
Element * DateAndTimeElement = new Element();

Screen * NetworkConnectionsScreen = new Screen();

Screen * ActiveScreen = LoadingScreen;

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

void Element::MoveToNext() {
    Serial.println("Trying to switch focused element");

    if (ActiveScreen != NULL && ActiveScreen->focusedElement != NULL && ActiveScreen->focusedElement->next) {
        Serial.println("Active screen focused element has a next element"); 

        Serial.print("Defocus element:");
        Serial.println(ActiveScreen->focusedElement->name);
        lv_event_send(ActiveScreen->focusedElement->eventActor, LV_EVENT_DEFOCUSED, NULL);

        ActiveScreen->focusedElement = ActiveScreen->focusedElement->next;

        Serial.print("Focus next element");
        Serial.println(ActiveScreen->focusedElement->name);
        lv_event_send(ActiveScreen->focusedElement->eventActor, LV_EVENT_FOCUSED, NULL);
    } else {
        Serial.println("Active screen focused element doesn't have a next element"); 
    }
}

void Element::MoveToPrevious() {
    Serial.println("Trying to switch focused element");

    if (ActiveScreen != NULL && ActiveScreen->focusedElement != NULL && ActiveScreen->focusedElement->previous) {
        Serial.println("Active screen focused element has a previous element"); 

        Serial.print("Defocus element:");
        Serial.println(ActiveScreen->focusedElement->name);
        lv_event_send(ActiveScreen->focusedElement->eventActor, LV_EVENT_DEFOCUSED, NULL);

        ActiveScreen->focusedElement = ActiveScreen->focusedElement->previous;

        Serial.print("Focus next element");
        Serial.println(ActiveScreen->focusedElement->name);
        lv_event_send(ActiveScreen->focusedElement->eventActor, LV_EVENT_FOCUSED, NULL);
    } else {
        Serial.println("Active screen focused element doesn't have a previous element"); 
    }
}

void Element::Select() {
    Serial.println("Trying to select element");

    if (ActiveScreen != NULL && ActiveScreen->focusedElement != NULL && ActiveScreen->focusedElement->ChildScreen) {
        Serial.println("Active screen focused element has a child screen"); 

        Serial.print("Active screen:");
        Serial.println(ActiveScreen->name);

        lv_event_send(ActiveScreen->focusedElement->eventActor, LV_EVENT_CLICKED, NULL);
        Serial.println("switch screen event has been sent");
        
        Serial.print("New active screen ");
        ActiveScreen = ActiveScreen->focusedElement->ChildScreen;
        Serial.println(ActiveScreen->name);
        
        ActiveScreen->OnLoad();
    } else {
        Serial.println("Active screen focused element doesn't have a child screen"); 
    }
}


void setupScreens()
{
    LoadingScreen->Init("LoadingScreen", TempHumScreen, ui_LoadingScreenSwitchToTempHumScreen, NULL);

    // DataScreen->Init("DataScreen", SettingsScreen, ui_Button1, NULL);

    TempHumScreen->Init("TempHumScreen", TempHumScreen, ui_TempHumNextButton, NULL);

    DateTimeScreen->Init("DateTimeScreen", NULL, NULL, NULL);
    //Frome Above

    // SettingsScreen->Init("SettingsScreen", DataScreen, ui_Button3, NetworkConnectionsElement);
    // NetworkConnectionsElement->Init(SettingsScreen, NetworkConnectionsScreen, "NetworkConnections", AppearanceElement, DateAndTimeElement, ui_NetworkConnectionsButton);
    // AppearanceElement->Init(SettingsScreen, NULL, "Appearance", DateAndTimeElement, NetworkConnectionsElement, ui_AppearenceButton);
    // DateAndTimeElement->Init(SettingsScreen, NULL, "DateAndTime", NetworkConnectionsElement, AppearanceElement, ui_DateAndTimeButton);

    // NetworkConnectionsScreen->Init("NetworkConnections", SettingsScreen, ui_BackFormnetworkConnections, NULL, &scan);

    Serial.print("Active screen ");
    Serial.println(ActiveScreen->name);
}