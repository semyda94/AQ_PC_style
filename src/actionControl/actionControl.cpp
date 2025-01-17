#include "actionControl.h"
#include "../ui/ui.h"

#include "ScreenHierarchy/ScreenHierarchy.h"

///////////////////// VARIABLES DECLARATION ////////////////////

//Button
int Button1Pin = 7;
int Button2Pin = 2;
int Button3Pin = 0;
int Button4Pin = 1;

// Variables will change:
int lastState1 = HIGH; // the previous state from the input pin
int currentState1;     // the current reading from the input pin
int lastState2 = HIGH; // the previous state from the input pin
int currentState2;     // the current reading from the input pin
int lastState3 = HIGH; // the previous state from the input pin
int currentState3;     // the current reading from the input pin
int lastState4 = HIGH; // the previous state from the input pin
int currentState4;     // the current reading from the input pin

///////////////////// FUNCTIONS DECLARATION ////////////////////

// void setupActionButtons(void);
// void actionControl(void* pvParameters);

///////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

void setupActionButtons(void)
{
    setupScreens();
    
    //Switch button
    pinMode(Button1Pin, INPUT_PULLUP);
    pinMode(Button2Pin, INPUT_PULLUP);
    pinMode(Button3Pin, INPUT_PULLUP);
    pinMode(Button4Pin, INPUT_PULLUP);
}

void actionControl(void* pvParameters) 
{
  while (1) {

    currentState1 = digitalRead(Button1Pin);
    currentState2 = digitalRead(Button2Pin);
    currentState3 = digitalRead(Button3Pin);
    currentState4 = digitalRead(Button4Pin);

    if(lastState1 == LOW && currentState1 == HIGH)
        Serial.println("Button 1 Released");
    if (lastState1 == HIGH && currentState1 == LOW) {
        Serial.println("Button 1 presed");
        ActiveScreen->SwitchScreen();
        // lv_event_send(ui_Button3, LV_EVENT_CLICKED, NULL);
        // HideAqi_Animation(ui_Wallpaper, 0);
    }

    if(lastState2 == LOW && currentState2 == HIGH)
        Serial.println("Button 2 Released");
    if (lastState2 == HIGH && currentState2 == LOW) {
        Serial.println("Button 2 presed");
        ActiveScreen->focusedElement->MoveToPrevious();
        // lv_event_send(ui_NetworkConnectionsButton, LV_EVENT_FOCUSED, NULL);
        // ShowAqi_Animation(ui_Wallpaper, 0);
    }

    if(lastState3 == LOW && currentState3 == HIGH)
        Serial.println("Button 3 Released");
    if (lastState3 == HIGH && currentState3 == LOW) {
        Serial.println("Button 3 presed");
        ActiveScreen->focusedElement->MoveToNext();
        // lv_event_send(ui_NetworkConnectionsButton, LV_EVENT_DEFOCUSED, NULL);
    }

    if(lastState4 == LOW && currentState4 == HIGH)
        Serial.println("Button 4 Released");
    if (lastState4 == HIGH && currentState4 == LOW) {
        Serial.println("Button 4 presed");
        ActiveScreen->focusedElement->Select();
        // lv_event_send(ui_Button1, LV_EVENT_CLICKED, NULL);
    }

    // save the last state
    lastState1 = currentState1;
    lastState2 = currentState2;
    lastState3 = currentState3;
    lastState4 = currentState4;
    
    delay(10);
  }
}
