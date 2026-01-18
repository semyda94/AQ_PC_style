#ifndef _AQ_PC_STYLE_FORM_H
#define _AQ_PC_STYLE_FORM_H

#include <Arduino.h>
#include <string>
#include <vector>
#include <functional>

#include "../../ui/ui.h"
#include "Element.h"

// Use std::function for better type safety and flexibility
typedef std::function<void(void*)> ButtonCallback;
typedef std::function<void(void*)> FocusCallback;

class Form {
public:
    String name;
    bool isFocused = false;

    int focusedElementId = -1;
    std::vector<Element*> elements;
    Element* focusedElement = nullptr;

    FocusCallback onFocus;
    FocusCallback onDefocus;
    
    // Button callbacks for when this form is focused
    ButtonCallback onButton1;
    ButtonCallback onButton2;
    ButtonCallback onButton3;
    ButtonCallback onButton4;

    // Constructor
    Form(
        const String& name,
        FocusCallback onFocus = nullptr,
        FocusCallback onDefocus = nullptr,
        ButtonCallback onButton1 = nullptr,
        ButtonCallback onButton2 = nullptr,
        ButtonCallback onButton3 = nullptr,
        ButtonCallback onButton4 = nullptr
    );
    
    // Destructor
    ~Form();

     // Add element to form
    void addElement(Element* element);

    // Element navigation
    void focusNextElement();
    void focusPreviousElement();
    void focusElement(int elementId);
    void defocusCurrentElement();
    
    // Form state management
    void focusForm();
    void defocusForm();
    
    // Button handling when form is active
    void handleButton1();
    void handleButton2(); 
    void handleButton3();
    void handleButton4();
    
};

#endif