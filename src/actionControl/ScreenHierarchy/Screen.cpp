#include "Screen.h"
#include "ScreenHierarchy.h"

//////////////////// Constructors / Destructors ////////////////////
Screen::Screen(
        const String& name, //Screen name
        bool isActionable, //Is screen actionable on load
        LoadCallback onLoadFunc, //On load function
        lv_obj_t* nextScreenSwitchEventActor, //Actor to trigger switch to next screen
        lv_obj_t* previousScreenSwitchEventActor, //Actor to trigger switch to previous screen
        ButtonCallback onButton1,
        ButtonCallback onButton2,
        ButtonCallback onButton3,
        ButtonCallback onButton4
        )
    : name(name),
      isActionable(isActionable),
      onLoad(onLoadFunc),
      nextScreenSwitchEventActor(nextScreenSwitchEventActor),
      previousScreenSwitchEventActor(previousScreenSwitchEventActor),
      onButton1(onButton1),
      onButton2(onButton2),
      onButton3(onButton3),
      onButton4(onButton4)
      {
        
      }

////////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

// Navigation methods
void Screen::switchToNext() {
    if (next != nullptr) {
        Serial.println("Switching to next screen: " + next->name);
        
        lv_event_send(nextScreenSwitchEventActor, LV_EVENT_CLICKED, NULL);
        Serial.println("Switch event sent for next screen");
        ActiveScreen = next;
        ActiveScreen->onLoadScreen();
    } else {
        Serial.println("No next screen to switch to from screen: " + name);
    }
}
void Screen::switchToPrevious() {
    if (previous != nullptr) {
        Serial.println("Switching to previous screen: " + previous->name);
        
        lv_event_send(previousScreenSwitchEventActor, LV_EVENT_CLICKED, NULL);
        Serial.println("Switch event sent for previous screen");
        ActiveScreen = previous;
        ActiveScreen->onLoadScreen();
    } else {
        Serial.println("No previous screen to switch to from screen: " + name);
    }
}

// Form management
// void focusNextForm();
// void focusPreviousForm();
// void focusForm(int formId);
// void defocusCurrentForm();

// Button handlers - each button has a specific purpose
void Screen::handleButton1() {
    if (onButton1 != nullptr) {
        Serial.println("Executing onButton1 for screen: " + name);
        onButton1(nullptr);
    } else {
        Serial.println("No action defined for Button 1 on screen: " + name);
    }
} 

void Screen::handleButton2(){
    if (onButton2 != nullptr) {
        Serial.println("Executing onButton2 for screen: " + name);
        onButton2(nullptr);
    } else {
        Serial.println("No action defined for Button 2 on screen: " + name);
    }
}

void Screen::handleButton3() {
    if (onButton3 != nullptr) {
        Serial.println("Executing onButton3 for screen: " + name);
        onButton3(nullptr);
    } else {
        Serial.println("No action defined for Button 3 on screen: " + name);
    }
}

void Screen::handleButton4() {
    if (onButton4 != nullptr) {
        Serial.println("Executing onButton4 for screen: " + name);
        onButton4(nullptr);
    } else {
        Serial.println("No action defined for Button 4 on screen: " + name);
    }
}

void Screen::onLoadScreen() {
    if (onLoad != nullptr) {
        Serial.println("Executing onLoad for screen: " + name);
        onLoad(nullptr);
    } else {
        Serial.println("No onLoad function defined for screen: " + name);
    }
}

//Forms navigation methods
void Screen::addForm(Form* form) {
    if (form != nullptr) {
        forms.push_back(form);
        Serial.println("Added form '" + form->name + "' to screen '" + name + "'. Total forms count: " + String(forms.size()));
    } else {
        Serial.println("Warning: Attempted to add null form to screen '" + name + "'");
    }
}

void Screen::focusForm(String name) {
    Serial.println("Attempting to focus form '" + name + "' on screen '" + this->name + "'");
    for (int i = 0; i < forms.size(); ++i) {
        if (forms[i]->name == name) {
            Serial.println("Found form '" + name + "' on screen '" + this->name + "'. Focusing it now.");
            if (focusedForm != nullptr) {
                Serial.println("Defocused form '" + focusedForm->name + "' on screen '" + this->name + "'");
                focusedForm->defocusForm();
            } else {
                Serial.println("No previously focused form on screen '" + this->name + "'");
            }

            focusedForm = forms[i];
            Serial.println("Setting focusedFormId to " + String(i));

            focusedFormId = i;

            Serial.println("Calling focusForm on form '" + name + "'");
            focusedForm->focusForm();
            Serial.println("Focused form '" + name + "' on screen '" + this->name + "'");
            return;
        }
    }
    Serial.println("Warning: Form '" + name + "' not found on screen '" + this->name + "'");
}

void Screen::defocusCurrentForm() {
    if (focusedForm != nullptr) {
        Serial.println("Defocusing current form '" + focusedForm->name + "' on screen '" + this->name + "'");
        focusedForm->defocusForm();
        focusedForm = nullptr;
        focusedFormId = -1;
        Serial.println("Defocused current form on screen '" + this->name + "'");
    } else {
        Serial.println("No focused form to defocus on screen '" + this->name + "'");
    }
}

//Add elements to screen
void Screen::addElement(Element* element) {
    if (element != nullptr) {
        elements.push_back(element);
        Serial.println("Added element to Screen '" + name + "'. Total elements count: " + String(elements.size()));
    } else {
        Serial.println("Warning: Attempted to add null element to Screen '" + name + "'");
    }
}

// Elements navigation methods

void Screen::focusNextElement(){
    Serial.println("Focusing next element in Screen: " + name + ". Current focusedElementId: " + String(focusedElementId) + ", total elements: " + String(elements.size()));
    if (elements.size() == 0) {
        Serial.println("No elements in Screen: " + name);
        return;
    }
    // Handle initial state or move to next element
    if (focusedElementId == -1 || focusedElementId < (int)(elements.size() - 1)) {
        if (focusedElement != nullptr) {
            focusedElement->defocusElement(); // Defocus current element
        } else {
            Serial.println("No currently focused element in Screen: " + name + ", first element will be focused.");
        }
        focusedElementId++;
        focusedElement = elements[focusedElementId];
        focusedElement->focusElement(); // Focus new element
        Serial.println("Focused element is now: " + String(focusedElement->name));
    } else {
        Serial.println("Already at the last element in Screen: " + name);
    }
}

void Screen::focusPreviousElement() {
    if (elements.size() == 0) {
        Serial.println("No elements in Screen: " + name);
        return;
    }
    if (focusedElementId > 0) {
        focusedElement->defocusElement(); // Defocus current element
        focusedElementId--;
        focusedElement = elements[focusedElementId];
        focusedElement->focusElement(); // Focus new element
    } else {
        Serial.println("Already at the first element in Screen: " + name);
    } 
}