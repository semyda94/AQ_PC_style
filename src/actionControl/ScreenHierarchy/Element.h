#ifndef _AQ_PC_STYLE_ELEMENT_H
#define _AQ_PC_STYLE_ELEMENT_H

#include <Arduino.h>
#include <string>
#include <functional>

#include "../../ui/ui.h"

typedef std::function<void(void*)> ButtonCallback;
typedef std::function<void(void*)> FocusCallback;

class Element {
public:
    String name;
    bool isFocused = false;
    lv_obj_t* focusEventActor;

    //Element focus management
    FocusCallback onFocus;
    FocusCallback onDefocus;
    
    // Element-specific button callbacks
    ButtonCallback onButton1;
    ButtonCallback onButton2;
    ButtonCallback onButton3;
    ButtonCallback onButton4;

    // Constructor
    Element(
        const String& name, 
        bool isFocused = false,
        lv_obj_t* focusEventActor = nullptr,
        ButtonCallback onButton1 = nullptr,
        ButtonCallback onButton2 = nullptr,
        ButtonCallback onButton3 = nullptr,
        ButtonCallback onButton4 = nullptr
    );
    
    // Focus management
    void focusElement();
    void defocusElement();
    
    // Button handling when element is focused
    void handleButton1();
    void handleButton2();
    void handleButton3();
    void handleButton4();

};


#endif