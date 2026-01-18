#include "Element.h"

//////////////////// Constructors / Destructors ////////////////////
Element::Element(
        const String& name, 
        bool isFocused,
        lv_obj_t* focusEventActor,
        ButtonCallback onButton1,
        ButtonCallback onButton2,
        ButtonCallback onButton3,
        ButtonCallback onButton4
    )
    :   name(name),
        isFocused(isFocused),
        focusEventActor(focusEventActor),
        onButton1(onButton1),
        onButton2(onButton2),
        onButton3(onButton3),
        onButton4(onButton4)
      {
      }

////////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

// Focus management
void Element::focusElement() {
    isFocused = true;

    if (onFocus != nullptr) {
        Serial.println("Executing onFocus for element: " + name);
        onFocus(nullptr);
    } else {
        Serial.println("No onFocus function defined for element: " + name);
    }

    if (focusEventActor != nullptr) {
            lv_event_send(focusEventActor, LV_EVENT_FOCUSED, NULL);
            Serial.println("Focus event sent for element: " + name);
        } else {
            Serial.println("No focusEventActor defined for element: " + name);
        }
}

void Element::defocusElement() {
    isFocused = false;

    if (onDefocus != nullptr) {
        Serial.println("Executing onDefocus for element: " + name);
        onDefocus(nullptr);
    } else {
        Serial.println("No onDefocus function defined for element: " + name);
    }

    if (focusEventActor != nullptr) {
            lv_event_send(focusEventActor, LV_EVENT_DEFOCUSED, NULL);
            Serial.println("Defocus event sent for element: " + name);
        } else {
            Serial.println("No focusEventActor defined for element: " + name);
        }
}

// Button handlers - each button has a specific purpose
void Element::handleButton1() {
    if (onButton1 != nullptr) {
        Serial.println("Executing onButton1 for element: " + name);
        onButton1(nullptr);
    } else {   
        Serial.println("No action defined for Button 1 on element: " + name);
    }
}

void Element::handleButton2() {
    if (onButton2 != nullptr) {
        Serial.println("Executing onButton2 for element: " + name);
        onButton2(nullptr);
    } else {
        Serial.println("No action defined for Button 2 on element: " + name);
    }
}

void Element::handleButton3() {
    if (onButton3 != nullptr) {
        Serial.println("Executing onButton3 for element: " + name);
        onButton3(nullptr);
    } else {
        Serial.println("No action defined for Button 3 on element: " + name);
    }
}

void Element::handleButton4() {
    if (onButton4 != nullptr) {
        Serial.println("Executing onButton4 for element: " + name);
        onButton4(nullptr);
    } else {
        Serial.println("No action defined for Button 4 on element: " + name);
    }
}