#include "actionControl.h"
#include "../ui/ui.h"
#include "../actionControl/wifiControl/wifiControl.h"

#include "ScreenHierarchy/ScreenHierarchy.h"

///////////////////// VARIABLES DECLARATION ////////////////////

//Button
int Button1Pin = 7;
int Button2Pin = 6;
int Button3Pin = 5;
int Button4Pin = 4;

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
    Serial.println("========== BEGIN ACTION BUTTONS SETUP ==========");

    //Switch button
    pinMode(Button1Pin, INPUT_PULLUP);
    pinMode(Button2Pin, INPUT_PULLUP);
    pinMode(Button3Pin, INPUT_PULLUP);
    pinMode(Button4Pin, INPUT_PULLUP);

    Serial.println("========== END ACTION BUTTONS SETUP ==========");
}

void actionControl(void* pvParameters) 
{
    
    Serial.println("========== BEGIN ACTION CONTROL CYCLE ==========");
    while (1) {

        currentState1 = digitalRead(Button1Pin);
        currentState2 = digitalRead(Button2Pin);
        currentState3 = digitalRead(Button3Pin);
        currentState4 = digitalRead(Button4Pin);

        if (ActiveScreen == nullptr) {
            Serial.println("Warning: ActiveScreen is null, no action will be processed");
            delay(10);
            continue;
        }

        if(lastState1 == LOW && currentState1 == HIGH) {
            Serial.println("Button 1 presed");

            if (ActiveScreen->focusedForm != nullptr) {
                if (ActiveScreen->focusedForm->focusedElement != nullptr) {
                    Serial.println("Screen " + String(ActiveScreen->name) + " has focused form " + String(ActiveScreen->focusedForm->name) + " and focused element" + String(ActiveScreen->focusedForm->focusedElement->name) + ", executing its handleButton1()");
                    ActiveScreen->focusedForm->focusedElement->handleButton1();
                } else {
                    Serial.println("Screen " + String(ActiveScreen->name) + " has focused form " + String(ActiveScreen->focusedForm->name) + " executing its handleButton1()");
                    ActiveScreen->focusedForm->handleButton1();
                }
            } else {
                if (ActiveScreen->focusedElement != nullptr) {
                    Serial.println("Screen " + String(ActiveScreen->name) + " has focused element " + String(ActiveScreen->focusedElement->name) + ", executing its handleButton1()");
                    ActiveScreen->focusedElement->handleButton1();
                } else {
                    Serial.println("Screen " + String(ActiveScreen->name) + " has no focused form or element, executing its handleButton1()");
                    ActiveScreen->handleButton1();
                }
            }

        // if (ActiveScreen->isActionable) {
        //     //Do thin for actionable screen
        //     Serial.println("Screen is actionable");
        //     ActiveScreen->handleButton1();
        // } else {
        //     Serial.println("Screen is not actionable, checking focused element");

        //     if (ActiveScreen != nullptr && 
        //         ActiveScreen->focusedForm != nullptr && 
        //         ActiveScreen->focusedForm->onButton1 != nullptr
        //     ) {
        //         Serial.println("Focused form has onButton1 function");
        //         ActiveScreen->focusedForm->onButton1(nullptr);
        //     } else {
        //         Serial.println("Focused form doesn't have onButton1 function checking focused element");

        //         if (ActiveScreen != nullptr && 
        //             ActiveScreen->focusedForm != nullptr && 
        //             ActiveScreen->focusedForm->focusedElement != nullptr &&
        //             ActiveScreen->focusedForm->focusedElement->onButton1 != nullptr
        //         ) {
        //             Serial.println("Focused element has onButton1 function");
        //             ActiveScreen->focusedForm->focusedElement->onButton1(nullptr);
        //         } else {
        //             Serial.println("Focused element doesn't have onButton1 function");
        //         }
        //     }
        // }
        }

        if(lastState2 == LOW && currentState2 == HIGH) {
            Serial.println("Button 2 presed");

            if (ActiveScreen->focusedForm != nullptr) {
                if (ActiveScreen->focusedForm->focusedElement != nullptr) {
                    Serial.println("Screen " + String(ActiveScreen->name) + " has focused form " + String(ActiveScreen->focusedForm->name) + " and focused element" + String(ActiveScreen->focusedForm->focusedElement->name) + ", executing its handleButton2()");
                    ActiveScreen->focusedForm->focusedElement->handleButton2();
                } else {
                    Serial.println("Screen " + String(ActiveScreen->name) + " has focused form " + String(ActiveScreen->focusedForm->name) + " executing its handleButton2()");
                    ActiveScreen->focusedForm->handleButton2();
                }
            } else {
                if (ActiveScreen->focusedElement != nullptr) {
                    Serial.println("Screen " + String(ActiveScreen->name) + " has focused element " + String(ActiveScreen->focusedElement->name) + ", executing its handleButton2()");
                    ActiveScreen->focusedElement->handleButton2();
                } else {
                    Serial.println("Screen " + String(ActiveScreen->name) + " has no focused form or element, executing its handleButton2()");
                    ActiveScreen->handleButton2();
                }
            }

        // if (ActiveScreen->isActionable) {
        //     //Do thin for actionable screen
        //     Serial.println("Screen is actionable");
        //     ActiveScreen->handleButton2();
        // } else {
        //     Serial.println("Screen is not actionable, checking focused element");

        //     if (ActiveScreen != NULL && 
        //         ActiveScreen->focusedForm != NULL && 
        //         ActiveScreen->focusedForm->onButton2 != NULL
        //     ) {
        //         Serial.println("Focused form has onButton2 function");
        //         ActiveScreen->focusedForm->onButton2(NULL);
        //     } else {
        //         Serial.println("Focused form doesn't have onButton2 function checking focused element");

        //         if (ActiveScreen != nullptr &&
        //             ActiveScreen->focusedForm != nullptr &&
        //             ActiveScreen->focusedForm->focusedElement != nullptr &&
        //             ActiveScreen->focusedForm->focusedElement->onButton2 != nullptr
        //         ) {
        //             Serial.println("Focused element has onButton2 function");
        //             ActiveScreen->focusedForm->focusedElement->onButton2(nullptr);
        //         } else {
        //             Serial.println("Focused element doesn't have onButton2 function");
        //         }
        //     }
        // }
        }

        if(lastState3 == LOW && currentState3 == HIGH) {
            Serial.println("Button 3 presed");

            if (ActiveScreen->focusedForm != nullptr) {
                if (ActiveScreen->focusedForm->focusedElement != nullptr) {
                    Serial.println("Screen " + String(ActiveScreen->name) + " has focused form " + String(ActiveScreen->focusedForm->name) + " and focused element" + String(ActiveScreen->focusedForm->focusedElement->name) + ", executing its handleButton3()");
                    ActiveScreen->focusedForm->focusedElement->handleButton3();
                } else {
                    Serial.println("Screen " + String(ActiveScreen->name) + " has focused form " + String(ActiveScreen->focusedForm->name) + " executing its handleButton3()");
                    ActiveScreen->focusedForm->handleButton3();
                }
            } else {
                if (ActiveScreen->focusedElement != nullptr) {
                    Serial.println("Screen " + String(ActiveScreen->name) + " has focused element " + String(ActiveScreen->focusedElement->name) + ", executing its handleButton3()");
                    ActiveScreen->focusedElement->handleButton3();
                } else {
                    Serial.println("Screen " + String(ActiveScreen->name) + " has no focused form or element, executing its handleButton3()");
                    ActiveScreen->handleButton3();
                }
            }

        // if (ActiveScreen->isActionable) {
        //     //Do thin for actionable screen
        //     Serial.println("Screen is actionable");
        //     ActiveScreen->handleButton3();
        // } else {
        //     Serial.println("Screen is not actionable, checking focused element");

        //     if (ActiveScreen != NULL && 
        //         ActiveScreen->focusedForm != NULL && 
        //         ActiveScreen->focusedForm->onButton3 != NULL
        //     ) {
        //         Serial.println("Focused form has onButton3 function");
        //         ActiveScreen->focusedForm->onButton3(NULL);
        //     } else {
        //         Serial.println("Focused form doesn't have onButton3 function checking focused element");

        //         if (ActiveScreen != nullptr &&
        //             ActiveScreen->focusedForm != nullptr &&
        //             ActiveScreen->focusedForm->focusedElement != nullptr &&
        //             ActiveScreen->focusedForm->focusedElement->onButton3 != nullptr
        //         ) {
        //             Serial.println("Focused element has onButton3 function");
        //             ActiveScreen->focusedForm->focusedElement->onButton3(nullptr);
        //         } else {
        //             Serial.println("Focused element doesn't have onButton3 function");
        //         }
        //     }
        // }
        }


        if(lastState4 == LOW && currentState4 == HIGH) {
            Serial.println("Button 4 presed");

            if (ActiveScreen->focusedForm != nullptr) {
                if (ActiveScreen->focusedForm->focusedElement != nullptr) {
                    Serial.println("Screen " + String(ActiveScreen->name) + " has focused form " + String(ActiveScreen->focusedForm->name) + " and focused element" + String(ActiveScreen->focusedForm->focusedElement->name) + ", executing its handleButton4()");
                    ActiveScreen->focusedForm->focusedElement->handleButton4();
                } else {
                    Serial.println("Screen " + String(ActiveScreen->name) + " has focused form " + String(ActiveScreen->focusedForm->name) + " executing its handleButton4()");
                    ActiveScreen->focusedForm->handleButton4();
                }
            } else {
                if (ActiveScreen->focusedElement != nullptr) {
                    Serial.println("Screen " + String(ActiveScreen->name) + " has focused element " + String(ActiveScreen->focusedElement->name) + ", executing its handleButton4()");
                    ActiveScreen->focusedElement->handleButton4();
                } else {
                    Serial.println("Screen " + String(ActiveScreen->name) + " has no focused form or element, executing its handleButton4()");
                    ActiveScreen->handleButton4();
                }
            }
            
        // if (ActiveScreen->isActionable) {
        //     //Do thin for actionable screen
        //     Serial.println("Screen is actionable");
        //     ActiveScreen->handleButton4();
        // } else {
        //     Serial.println("Screen is not actionable, checking focused element");

        //     if (ActiveScreen != NULL && 
        //         ActiveScreen->focusedForm != NULL && 
        //         ActiveScreen->focusedForm->onButton4 != NULL
        //     ) {
        //         Serial.println("Focused form has onButton4 function");
        //         ActiveScreen->focusedForm->onButton4(NULL);
        //     } else {
        //         Serial.println("Focused form doesn't have onButton4 function checking focused element");

        //         if (ActiveScreen != NULL && 
        //             ActiveScreen->focusedForm != NULL &&
        //             ActiveScreen->focusedForm->focusedElement != NULL &&
        //             ActiveScreen->focusedForm->focusedElement->onButton4 != NULL
        //         ) {
        //             Serial.println("Focused element has onButton4 function");
        //             ActiveScreen->focusedForm->focusedElement->onButton4(NULL);
        //         } else {
        //             Serial.println("Focused element doesn't have onButton4 function");
        //         }
        //     }
        // }
        }

        // save the last state
        lastState1 = currentState1;
        lastState2 = currentState2;
        lastState3 = currentState3;
        lastState4 = currentState4;

        tickWifiPortal();
    
        delay(10);
    }

    Serial.println("========== END ACTION CONTROL CYCLE ==========");
}
