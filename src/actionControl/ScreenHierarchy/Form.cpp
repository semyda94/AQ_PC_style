#include "Form.h"

//////////////////// Constructors / Destructors ////////////////////
Form::Form(
        const String& name, //Form name
         FocusCallback onFocus, //Focus callback
         FocusCallback onDefocus, //Defocus callback
         ButtonCallback onButton1, //Button 1 callback
         ButtonCallback onButton2, //Button 2 callback
         ButtonCallback onButton3, //Button 3 callback
         ButtonCallback onButton4  //Button 4 callback
        )
    : name(name),
      onFocus(onFocus),
      onDefocus(onDefocus),
      onButton1(onButton1),
      onButton2(onButton2),
      onButton3(onButton3),
      onButton4(onButton4)
      {
        
      }

////////////////////// FUNCTIONS IMPLEMENTATION ////////////////////

    // Focus methods

    void Form::focusForm() {
        if (onFocus != nullptr) {
            Serial.println("Executing onFocus for form: " + name);
            onFocus(nullptr);
        } else {
            Serial.println("No onFocus function defined for form: " + name);
        }
    }
    
    void Form::defocusForm() {
        if (onDefocus != nullptr) {
            Serial.println("Executing onDefocus for form: " + name);
            onDefocus(nullptr);

            focusedElementId = -1;
            focusedElement = nullptr;
        } else {
            Serial.println("No onDefocus function defined for form: " + name);
        }
    }
    
    
    // Elements management
    void Form::addElement(Element* element) {
        if (element != nullptr) {
            elements.push_back(element);
            Serial.println("Added element to form '" + name + "'. Total elements count: " + String(elements.size()));
        } else {
            Serial.println("Warning: Attempted to add null element to form '" + name + "'");
        }
    }

    // Elements navigation methods
    void Form::focusNextElement(){

        Serial.println("Focusing next element in form: " + name + ". Current focusedElementId: " + String(focusedElementId) + ", total elements: " + String(elements.size()));
        if (elements.size() == 0) {
            Serial.println("No elements in form: " + name);
            return;
        }

        // Handle initial state or move to next element
        if (focusedElementId == -1 || focusedElementId < (int)(elements.size() - 1)) {

            if (focusedElement != nullptr) {
                focusedElement->defocusElement(); // Defocus current element
            } else {
                Serial.println("No currently focused element in form: " + name + ", first element will be focused.");
            }

            focusedElementId++;
            focusedElement = elements[focusedElementId];
            focusedElement->focusElement(); // Focus new element

            Serial.println("Focused element is now: " + String(focusedElement->name));
        } else {
            Serial.println("Already at the last element in form: " + name);
            //focusedElementId = 0; // Wrap around to the first element
        }

    }

    void Form::focusPreviousElement(){
        if (elements.size() == 0) {
            Serial.println("No elements in form: " + name);
            return;
        }

        if (focusedElementId > 0) {

            focusedElement->defocusElement(); // Defocus current element

            focusedElementId--;
            focusedElement = elements[focusedElementId];
            focusedElement->focusElement(); // Focus new element
        } else {
            //focusedElementId = elements.size() - 1; // Wrap around to the last element
        }
        
    }
    
    // Button handlers - each button has a specific purpose
    void Form::handleButton1() {
        if (onButton1 != nullptr) {
            Serial.println("Executing onButton1 for form: " + name);
            onButton1(nullptr);
        } else {
            Serial.println("No action defined for Button 1 on form: " + name);
        }

    } 

    void Form::handleButton2(){
        if (onButton2 != nullptr) {
            Serial.println("Executing onButton2 for form: " + name);
            onButton2(nullptr);
        } else {
            Serial.println("No action defined for Button 2 on form: " + name);
        }
    }

    void Form::handleButton3() {
        if (onButton3 != nullptr) {
            Serial.println("Executing onButton3 for form: " + name);
            onButton3(nullptr);
        } else {
            Serial.println("No action defined for Button 3 on form: " + name);
        }
    }

    void Form::handleButton4() {
        if (onButton4 != nullptr) {
            Serial.println("Executing onButton4 for form: " + name);
            onButton4(nullptr);
        } else {
            Serial.println("No action defined for Button 4 on form: " + name);
        }
    }